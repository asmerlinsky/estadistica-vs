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
    char perio[5];
    double numerador;
    char filetemplado[100];
    char ubicacion[100];
    char entrada[100];
    char cargar[100];
    char salida[200];
    FILE *pFile;


    //asigno que silaba es
    sscanf(argv[2], "%*[^0123456789]%[^'.']", perio); 
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
    strcpy(cargar,"FILTRADOS\\"); //WINDOWS
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
    
    printf("Ndatos1: %d Ndatos2: %d\n",Ndatos1,Ndatos2);  
    

    
    //calculo de la correlacion entre las señales.
    //Nmin=Ndatos1;//longitud del templado
    FILE *ptr;
   
    sprintf(salida,"FILTRADOS\\corremg%s.%s",perio,entrada);//WINDOWS
    //printf("salida %s\n",salida);

    ptr=fopen(salida,"w");
    double rmin;
    int cant=0,ultj=0;
    
    if(strcmp(perio, "13")==0){rmin=0.58;} //fijo el umbral de correlación según vi de comparar con cantos diurnos
    else if (strcmp(perio, "16")==0){rmin=0.65;}
    else if (strcmp(perio,"23")==0){rmin=0.62;}
    else if (strcmp(perio,"24")==0){rmin=0.81;}
    else if (strcmp(perio,"26")==0){rmin=0.745;}
    else {rmin=0.8;}
    
    for(j=2;j<Ndatos2-Ndatos1;j++){ //barro por todos los puntos de la señal que me permita el largo del templado
    
        double x1bar=0.0,sx1=0.0; //Toma el promedio del templado
        for(i=2;i<Ndatos1;i++){x1bar+=emg1[i];}
        x1bar /= (Ndatos1-2);

        double x2bar=0.0, sx2=0.0,r=0.0; //Toma el promedio de la señal
        for(i=2;i<Ndatos1;i++){x2bar+=emg2[i+j];} 
        x2bar /= (Ndatos1-2); 
        
        for(i = 2; i < Ndatos1; i++) {sx1 += (emg1[i] - x1bar) * (emg1[i] - x1bar);} //Resta el promedio
        sx1 = sqrt((sx1 / (Ndatos1-2)));// y toma una especie de norma de la señal con promedio 0            

        
        for(i = 2; i < Ndatos1; i++) {sx2 += (emg2[i+j] - x2bar) * (emg2[i+j] - x2bar);}//idem
        sx2 = sqrt((sx2 / (Ndatos1-2)));
    
        for( i = 2; i < Ndatos1; i++ ) {r += (((emg1[i] - x1bar)/sx1) * ((emg2[i+j] - x2bar)/sx2));}//Hace un producto normalizado(convoluciona)
        r /= (Ndatos1-2);
                
        fprintf(ptr,"%d\t %g\n",j,r);
        
        if(r>rmin){pFile=fopen("resultados.dat","a");
            if(j-ultj>1000){ cant+=1;}            
            fprintf(pFile,"%d\t %g\t %s\t %s\t %i\n",j,r,entrada,perio,cant);
            fclose(pFile);            
            ultj=j;
            
            }
    }
    
    printf("cantidad de coincidencias=%d \n\n\n",cant);
    
    
    free_dvector(emg2,1,Ndatos2);
    
}


