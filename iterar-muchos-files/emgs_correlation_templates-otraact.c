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
    int i,j,k,Ndatos1,Ndatos2;
    
    double numerador;
    char filetemplado[100];
    char ubicacion[100];
    char entrada[100];
    char cargar[100];
    char salida[200];
    char nomcorr[100];
    FILE *pFile;




    //asigno que silaba es
    sprintf(entrada,"%s",argv[1]); //WINDOWS
    
    strcpy(nomcorr,"FILTRADOS/corremg");
    strcat(nomcorr,entrada);
    sprintf(filetemplado,"%s",argv[2]);
    
    //sprintf(salida,"%s/corremg%s.%s.dat",ubicacion,perio,entrada); LINUX
    
    printf("\ntemplado es %s \n", filetemplado);
    //printf("entrada es %s \n", entrada);    
    //printf("salida es %s\n",salida);
    printf("perio vale %s \n",perio);

    
    //carga SUEÑO
    strcpy(cargar,"FILTRADOS/");    
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
    
    printf("Ndatos1: %d\n",Ndatos1);  
    
    //cargo correlaciones
    int ncols = 1;
    char nomcorr[100]
    buffer[500];
    FILE *ptrcorr;
    strcpy(nomcorr,"FILTRADOS/corremg");
    strcat(nomcorr,entrada);
    ptrcorr = fopen(nomcorr, "r");
    fgets(buffer, 500, ptrcorr);
    i=0
    while (letra[i]!='\n'){
        if (letra[i]=='\t'){
            ++ncols;
            i+=1;
        }
    }
    //char perios[20];
    
    printf("conte %d columnas\n",ncols);
    
    
    
    int longcorrela;
    double **correla
    longcorrela=filesize(cargar,);
    correla=dmatrix
    //FILE *ptr;

    sprintf(salida,"FILTRADOS/corremg%s.%s",perio,entrada);//SE SUONE QUE WINDOWS SE BANCA ESTO
    printf("salida %s\n",salida);

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

            
        if((r>rmin) & (x2bar>umbruido)){pFile=fopen("resultados.dat","a");
            if(j-ultj>Ndatos1/2){ cant+=1;}            
            fprintf(pFile,"%d\t %g\t %s\t %s\t %d\n",j,r,entrada,perio,cant);
            fclose(pFile);            
            ultj=j;
            
            }
    }
    for(j=Ndatos2-Ndatos1;j<Ndatos2;j++){correla[j]=0.0;}
    
    // guardo correlaciones en un único archivo
    
    


    

    free_dvector(correla, 1, Ndatos2);
}


