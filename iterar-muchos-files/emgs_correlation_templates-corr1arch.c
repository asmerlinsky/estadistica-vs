//
//apunta a correlaciones
//Procesa los archivos de sueño, los templados ya estan procesados

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "librerias.c"
#include "nrutil.h"
#include "nrutil.c"
#include "ht.c"
#include "rk4.c"
#include <string.h>

#include"convlv.c"
#include"savgol.c"
#include"realft.c"
#include"twofft.c"
#include"four1.c"
#include"lubksb.c"
#include"ludcmp.c"


struct Par {
    double beta; double tau;
} aa;


void takens(int n,double v[],double dv[],double t) {
    double x;    
    x=v[0];     
    dv[0]=-(1/aa.tau)*x+fabs(aa.beta);
    return;
}

int nearpow2(int number){
     int i=0, temp=1;
    while(temp<number) {temp*=2; i++;}
        return(temp/2);
}

int nearpow2up(int number){
     int i=0, temp=1;
    while(temp<number) {temp*=2; i++;}
        return(temp);
}





 /*usa los templados procesados*/
int main(int argc, char *argv[]) {
    long i,j,k,Ndatos1,Ndatos2;
    char perio[20];
    double numerador;
    char filetemplado[100];
    char ubicacion[100];
    char entrada[100];
    char cargar[100];
    char salida[200];
    FILE *pFile;




    //asigno que silaba es
    sscanf(argv[2], "%*[^0123456789]%[^'.']%*s", perio);
    //sscanf(argv[1],"%[^'/']/%s",ubicacion,entrada);//LINUX tener cuidado si lo corro en windows
    sprintf(entrada,"%s",argv[1]); //WINDOWS
    //printf("ubicacion=%s\n",ubicacion);
    
    
    //printf("perio=%s\n",perio);
    sprintf(filetemplado,"%s",argv[2]);
    
    //sprintf(salida,"%s/corremg%s.%s.dat",ubicacion,perio,entrada); LINUX
    
    printf("\ntemplado es %s \n", filetemplado);
    //printf("entrada es %s \n", entrada);    
    //printf("salida es %s\n",salida);
    printf("perio vale %s \n",perio);
    //CARGA EMG1
    double *emg1;
    Ndatos1=filesize(filetemplado,1);
    emg1=dvector(1,Ndatos1);
    file_to_vector(filetemplado,emg1,1,Ndatos1,1,1);
    
    printf("templado OK\n");
    
    
    //carga SUEÑO
    //strcpy(cargar,"FILTRADOS\\"); //WINDOWS
    strcpy(cargar,"FILTRADOS/");//SE SUPONE QUE WINDOWS SE BANCA ESTO
    
    strcat(cargar, entrada);//WINDOWS
    double *emg2;
    //Ndatos2=filesize(entrada,1); LINUX
    printf("cargo %s\n",cargar);//WINDOWS
    Ndatos2=filesize(cargar,1); //WINDOWS
    int POT2up=nearpow2up(Ndatos2);
    int POT2=nearpow2(Ndatos2);
    

    emg2=dvector(1,Ndatos2);
    //file_to_vector(entrada,emg2,1,Ndatos2,1,1);//LINUX
    file_to_vector(cargar,emg2,1,Ndatos2,1,1);//WINDOWS
    

    printf("sueno OK\n");
    
    printf("Ndatos1: %ld Ndatos2: %ld\n",Ndatos1,Ndatos2);  
    

    //FILE *ptr;

    sprintf(salida,"FILTRADOS/corremg%s.%s",perio,entrada);//SE SUONE QUE WINDOWS SE BANCA ESTO


    //ptr=fopen(salida,"w");
    double rmin;
    int cant=0,ultj=0;
    
    
    if(strcmp(perio, "2-1")==0) {rmin=0.7;}
    else if(strcmp(perio, "2-3")==0) {rmin=0.6;}
    else if(strcmp(perio, "2-4")==0) {rmin=0.7;}
    else if(strcmp(perio, "2-45")==0) {rmin=0.75;}
    else if(strcmp(perio, "2-A")==0) {rmin=0.55;}
    else if(strcmp(perio, "2-B")==0) {rmin=0.55;}
    else if(strcmp(perio, "2-B5")==0) {rmin=0.6;}
    else if(strcmp(perio, "2-7")==0) {rmin=0.7;}
    else if(strcmp(perio, "2-67")==0) {rmin=0.55;}
    else if(strcmp(perio, "2-5")==0) {rmin=0.75;}
    else if(strcmp(perio, "2-56")==0) {rmin=0.55;}
    else if(strcmp(perio, "2-6")==0) {rmin=0.7;}
    else {
        fprintf(stderr, "No asignaste umbral a este templado! Exiting...\n");
        exit(-1);
    }
    
    //levanto el umbral de ruido
    char umbfile[100];
    k=0;
    strcpy(umbfile,"FILTRADOS/");
    strcat(umbfile,"umbralruido.dat");
    
    FILE *ptrumbral;
    ptrumbral=fopen(umbfile,"r");
    
    double umbruido;
    char archenfile[50];
    int bien=2;
    while((bien==2) & (k==0)){
       bien=fscanf(ptrumbral,"%s %lf",archenfile,&umbruido);
       if (strcmp(archenfile,entrada)==0){k=1;}
    }
    fclose(ptrumbral);
    
    double *correla,*media;
    correla=dvector(1,Ndatos2);
    correla[1]=0.0;
    media=dvector(1,Ndatos2);
    media[1]=0.0;
    

    
     //capaz me puedo ahorrar mucho si hago las cuentas solo cuando supero el umbral
    for(j=2;j<Ndatos2-Ndatos1;j++){ //barro por todos los puntos de la señal que me permita el largo del templado
    
        double x1bar=0.0,sx1=0.0; //Toma el promedio del templado
        for(i=2;i<Ndatos1;i++){x1bar+=emg1[i];}
        x1bar /= (Ndatos1-2);

        double x2bar=0.0, sx2=0.0, r=0.0; //Toma el promedio de la señal
        for(i=2;i<Ndatos1;i++){x2bar+=emg2[i+j];} 
        x2bar /= (Ndatos1-2);
        
        for(i = 2; i < Ndatos1; i++) {sx1 += (emg1[i] - x1bar) * (emg1[i] - x1bar);} //Resta el promedio
        sx1 = sqrt((sx1 / (Ndatos1-2)));// y toma una especie de norma de la señal con promedio 0            

        
        for(i = 2; i < Ndatos1; i++) {sx2 += (emg2[i+j] - x2bar) * (emg2[i+j] - x2bar);}//idem
        sx2 = sqrt((sx2 / (Ndatos1-2)));
    
        for( i = 2; i < Ndatos1; i++ ) {r += (((emg1[i] - x1bar)/sx1) * ((emg2[i+j] - x2bar)/sx2));}//Hace un producto normalizado(convoluciona)
        r /= (Ndatos1-2);
                
        correla[j]=r;      
        media[j]=x2bar;
            
        if((r>rmin) & (x2bar>umbruido)){pFile=fopen("resultados.dat","a");
            if(j-ultj>Ndatos1/2){ cant+=1;}            
            fprintf(pFile,"%ld\t %g\t %s\t %s\t %d\n",j,r,entrada,perio,cant);
            fclose(pFile);            
            ultj=j;
            
            }
    }
    for(j=Ndatos2-Ndatos1;j<Ndatos2;j++){correla[j]=0.0;}
    
   for(j=Ndatos2-Ndatos1;j<Ndatos2;j++){media[j]=0.0;}
    // guardo correlaciones en un único archivo
    char nomcorr[100],nomcorrtemp[100],nomcorrfilt[100],nomcorrfilttemp[100];
    char buffer[500];
    FILE *ptrcorr;
    FILE *ptrcorrtemp;
    FILE *ptrcorrfilt;
    FILE *ptrcorrfilttemp;
    
    strcpy(nomcorr,"FILTRADOS/corremg.");
    strcat(nomcorr,entrada);
    strcpy(nomcorrtemp,"FILTRADOS/corremgtemp.");
    strcat(nomcorrtemp,entrada);


    printf("salida %s\n",nomcorrtemp);
    ptrcorr = fopen(nomcorr, "r");
    ptrcorrtemp=fopen(nomcorrtemp,"w");

    
    
    
    if (ptrcorr != NULL) { //si existe
        fgets(buffer, 500, ptrcorr);
        buffer[strcspn(buffer, "\n")] = 0;
        fprintf(ptrcorrtemp,"%s\t%s\n",buffer,perio);//guardo el nombre del templado en la primera linea
        
        for(j=2;j<Ndatos2;j++){
            fgets(buffer, 500, ptrcorr);
            buffer[strcspn(buffer, "\n")] = 0;
            fprintf(ptrcorrtemp,"%s\t%g\n",buffer,correla[j]);
        }
        fclose(ptrcorr);
        fclose(ptrcorrtemp);
        remove(nomcorr);
     }
    else {//si no existe genero posicion y primera correlacion
        fprintf(ptrcorrtemp,"%s\t%s\n","pos",perio);//guardo el nombre del templado en la primera linea
        
        for(j=2;j<Ndatos2;j++){
            //printf("%ld\t%g\n",j,correla[j]);
            fprintf(ptrcorrtemp,"%ld\t%g\n",j,correla[j]);
        }
    
        fclose(ptrcorrtemp);
    }

    rename(nomcorrtemp,nomcorr);

    strcpy(nomcorrfilt,"FILTRADOS/corremgfilt.");
    strcat(nomcorrfilt,entrada);
    strcpy(nomcorrfilttemp,"FILTRADOS/corremgfilttemp.");
    strcat(nomcorrfilttemp,entrada);



    ptrcorrfilt=fopen(nomcorrfilt,"r");
    ptrcorrfilttemp=fopen(nomcorrfilttemp,"w");


    if (ptrcorrfilt != NULL) { //si existe
        fgets(buffer, 500, ptrcorrfilt);
        buffer[strcspn(buffer, "\n")] = 0;
        fprintf(ptrcorrfilttemp,"%s\t%s\n",buffer,perio);//guardo el nombre del templado en la primera linea
        
        for(j=2;j<Ndatos2;j++){
            fgets(buffer, 500, ptrcorrfilt);
            buffer[strcspn(buffer, "\n")] = 0;
            if (media[j]>umbruido){fprintf(ptrcorrfilttemp,"%s\t%g\n",buffer,correla[j]);}
            else {fprintf(ptrcorrfilttemp,"%s\t%g\n",buffer,0.0);}
        }        
        fclose(ptrcorrfilt);
        fclose(ptrcorrfilttemp);
        remove(nomcorrfilt);
    }
    else {//si no existe genero posicion y primera correlacion
        fprintf(ptrcorrfilttemp,"%s\t%s\n","pos",perio);//guardo el nombre del templado en la primera linea
        
        for(j=2;j<Ndatos2;j++){
            //printf("%ld\t%g\n",j,correla[j]);
            if (media[j]>umbruido){fprintf(ptrcorrfilttemp,"%ld\t%g\n",j,correla[j]);}
            else {fprintf(ptrcorrfilttemp,"%ld\t%g\n",j,0.0);}
            
            
        }
    
        fclose(ptrcorrfilttemp);
    }


    rename(nomcorrfilttemp,nomcorrfilt);


    printf("cantidad de coincidencias=%d \n\n\n",cant);






    free_dvector(correla, 1, Ndatos2);
    free_dvector(emg2,1,Ndatos2);
    free_dvector(emg1,1,Ndatos1);
}


