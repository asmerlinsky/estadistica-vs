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
    sprintf(salida,"FILTRADOS\\corremg%s.%s.dat",perio,entrada);//WINDOWS
    printf("templado es %s \n", filetemplado);
    printf("entrada es %s \n", entrada);    
    //printf("salida es %s\n",salida);

    //CARGA EMG1
    double *emg1;
    Ndatos1=filesize(filetemplado,1);
    emg1=dvector(1,Ndatos1);
    file_to_vector(filetemplado,emg1,1,Ndatos1,1,1);
    printf("perio vale %s \n",perio);
    printf("templado OK\n");
    
    
    //carga SUEÑO
    strcpy(cargar,"FILTRADOS\\"); //WINDOWS
    strcat(cargar, entrada);//WINDOWS
    double *emg2;
    //Ndatos2=filesize(entrada,1); LINUX
    Ndatos2=filesize(cargar,1); //WINDOWS
    int POT2up=nearpow2up(Ndatos2);
    int POT2=nearpow2(Ndatos2);
    

    emg2=dvector(1,Ndatos2);
    //file_to_vector(entrada,emg2,1,Ndatos2,1,1);//LINUX
    file_to_vector(cargar,emg2,1,Ndatos2,1,1);//WINDOWS
    

    printf("sueno OK\n");
    
    printf("Ndatos1: %d Ndatos2: %d\n",Ndatos1,Ndatos2);  
    
    //Hilbert a sueño
    double *hilb2;
    //hilb2=dvector(1,POT2up);
    hilb2=dvector(1,Ndatos2);
    for(i=1;i<=500;i++) hilb2[i]=0.0; //guarda si cambia LFILT

    hilbert(emg2,hilb2,Ndatos2);
    
    //vector_to_file("hilbert.sueno.dat",hilb2,1,Ndatos2);

    printf("hilb ok\n");  
    

   //SUAVIZA ENVOLVENTE CON INTEGRACION
    double v2[1],dt, t;
    double *av_sound2;
    //av_sound2=dvector(1,POT2up);
    av_sound2=dvector(1,POT2);
    
    v2[0]=0.0;
    k=0;
    dt=1/10000.;
    aa.tau=10./1500.;
    //for(i=1;i<=POT2up;i++){
    for(i=1;i<=POT2;i++){
        aa.beta=hilb2[i];
        rk4(takens,v2,1,t+0.0,dt);
        av_sound2[i]=v2[0];
    }  
   
   
    //vector_to_file("int.sueno.dat",av_sound2,1,POT2);
    printf("int ok\n");
    
    //SAVITSKY-GOLAY
    int np,nl,nr,ld,m,index,Nmin,golord;
    float *c2,*data2,*ans2,dum2;
    golord=4;

    c2=vector(1,POT2); data2=vector(1,POT2); ans2=vector(1,2*POT2);    
    
    double *sav2;

    sav2=dvector(1,POT2); 
    

    for(i=1;i<=POT2;i++) data2[i]=(float) av_sound2[i];
    savgol(c2,513,256,256,0,golord);
    

    for(index=1;index<=POT2;index++) data2[index]=fabs(data2[index]);

    convlv(data2,POT2,c2,513,1,ans2);
    
    for(i=1;i<POT2;i++) sav2[i]=(double) ans2[i];
    
    char envname[100];
    //strcpy(envname,ubicacion); LINUX
    //strcat(envname, "/envolvente."); LINUX chequear que funcione en windows
    strcpy(envname,"FILTRADOS\\envolvente."); //WINDOWS
    strcat(envname, entrada);
    strcat(envname, ".dat");
    vector_to_file(envname,sav2,1,POT2); 
    printf("sav ok\n");
    
    
    //calculo de la correlacion entre las señales.
    Nmin=Ndatos1;//longitud del templado
    FILE *ptr;
    ptr=fopen(salida,"w");
    double rmin;
    int cant=0,ultj=0;
    
    if(strcmp(perio, "13")==0){rmin=0.58;} //fijo el umbral de correlación según vi de comparar con cantos diurnos
    else if (strcmp(perio, "16")==0){rmin=0.65;}
    else if (strcmp(perio,"23")==0){rmin=0.62;}
    else if (strcmp(perio,"24")==0){rmin=0.81;}
    else if (strcmp(perio,"26")==0){rmin=0.745;}
    else {rmin=0.8;}
    
    for(j=2;j<POT2-Nmin;j++){ //barro por todos los puntos de la señal que me permita el largo del templado
    
        double x1bar=0.0,sx1=0.0; //Toma el promedio del templado
        for(i=2;i<Nmin;i++){x1bar+=emg1[i];}
        x1bar /= (Nmin-2);

        double x2bar=0.0, sx2=0.0,r=0.0; //Toma el promedio de la señal
        for(i=2;i<Nmin;i++){x2bar+=sav2[i+j];} 
        x2bar /= (Nmin-2); 
        
        for(i = 2; i < Nmin; i++) {sx1 += (emg1[i] - x1bar) * (emg1[i] - x1bar);} //Resta el promedio
        sx1 = sqrt((sx1 / (Nmin-2)));// y toma una especie de norma de la señal con promedio 0            

        
        for(i = 2; i < Nmin; i++) {sx2 += (sav2[i+j] - x2bar) * (sav2[i+j] - x2bar);}//idem
        sx2 = sqrt((sx2 / (Nmin-2)));
    
        for( i = 2; i < Nmin; i++ ) {r += (((emg1[i] - x1bar)/sx1) * ((sav2[i+j] - x2bar)/sx2));}//Hace un producto normalizado(convoluciona)
        r /= (Nmin-2);
                
        fprintf(ptr,"%d\t %g\n",j,r);
        
        if(r>rmin){pFile=fopen("resultados.dat","a");
            if(j-ultj>1000){ cant+=1;}            
            fprintf(pFile,"%d\t %g\t %s\t %s\t %i\n",j,r,entrada,perio,cant);
            fclose(pFile);            
            ultj=j;
            
            }
    }
    
    printf("cantidad de coincidencias=%d \n",cant);
    printf("tauintegracion: %g\n",aa.tau);   
    printf("orden del filtro: %d\n\n\n",golord);
    
    
    free_dvector(av_sound2,1,POT2);
    free_dvector(hilb2,1,Ndatos2);
    free_dvector(emg1,1,Ndatos1);
    free_dvector(sav2,1,POT2);
    free_dvector(emg2,1,Ndatos2);
    
}


