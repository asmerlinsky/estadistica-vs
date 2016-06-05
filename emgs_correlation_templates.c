//
//apunta a correlaciones
//Procesa los archivos de sueño, los templados ya estan procesados
//Los meto sin duplicar, y agrego ceros al vector para llegar a POT2up(primer potencia de 2 mayor a la cantidad de datos)
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
    int i,j,k,Ndatos1,Ndatos2,perio,golord;
    double numerador;
	char filetemplado[100];
	char entrada[100];
    char salida[200];
    FILE *pFile;
    //cargo los paremetros que pase por linea de comando
    sscanf(argv[3], "%lf", &numerador);
	sscanf(argv[4], "%d", &golord);

    
	aa.tau=numerador/1500.;

	//asigno que silaba es
	sscanf(argv[2], "%*[^0123456789]%i%*s", &perio); 
	sprintf(filetemplado,"%s",argv[2]);
	sprintf(entrada,"%s",argv[1]);
    sprintf(salida,"corremg%i.%s.dat",perio,argv[1]);
	printf("templado es %s \n", filetemplado);
	printf("entrada es %s \n", entrada);	


    //CARGA EMG1
    double *emg1;
    Ndatos1=filesize(filetemplado,1);
    emg1=dvector(1,Ndatos1);
    file_to_vector(filetemplado,emg1,1,Ndatos1,1,1);
	printf("perio vale %i \n",perio);
	printf("templado OK\n");
	
	
	//carga SUEÑO
    double *emg2;
    Ndatos2=filesize(entrada,1);
	int POT2up=nearpow2up(Ndatos2);
    
    emg2=dvector(1,POT2up);    
	file_to_vector(entrada,emg2,1,Ndatos2,1,1);
	for(i=Ndatos2;i<=POT2up;i++){emg2[i]=0.0;}
    printf("sueno OK\n");
    
    printf("Ndatos1: %d Ndatos2: %d\n",Ndatos1,Ndatos2);  
	
	//Hilbert a sueño
    double *hilb2;
    hilb2=dvector(1,POT2up);
	for(i=1;i<=500;i++) hilb2[i]=0.0; //guarda si cambia LFILT
	hilbert(emg2,hilb2,POT2up);
    vector_to_file("hilbert.sueno.dat",hilb2,1,Ndatos2);

    printf("hilb ok\n");  
    

   //SUAVIZA ENVOLVENTE CON INTEGRACION
    double v2[1],dt, t;
    double *av_sound2;
	av_sound2=dvector(1,POT2up);
	v2[0]=0.0;
    k=0;
    dt=1/10000.;
    //aa.tau=.5/1500.;
	for(i=1;i<=POT2up;i++){
		aa.beta=hilb2[i];
        rk4(takens,v2,1,t+0.0,dt);
        av_sound2[i]=v2[0];
    }  
   
   
	vector_to_file("int.sueno.dat",av_sound2,1,Ndatos2);
    printf("int ok\n");
    
    //SAVITSKY-GOLAY
    int np,nl,nr,ld,m,index,Nmin;
    float *c2,*data2,*ans2,dum2;
   
    c2=vector(1,POT2up); data2=vector(1,POT2up); ans2=vector(1,2*POT2up);
    double *sav2;
    sav2=dvector(1,POT2up); 
	
	for(i=1;i<=POT2up;i++) data2[i]=(float) av_sound2[i];
    savgol(c2,513,256,256,0,golord);
    for(index=1;index<=POT2up;index++) data2[index]=fabs(data2[index]);
    convlv(data2,POT2up,c2,513,1,ans2);
    for(i=1;i<POT2up;i++) sav2[i]=(double) ans2[i];
    

	char envname[100];
	strcpy(envname, "envolvente.");
    strcat(envname, entrada);
	strcat(envname, ".dat");
    vector_to_file(envname,sav2,1,Ndatos2); 
    printf("sav ok\n");
    
    
    //calculo de la correlacion entre las señales.
    Nmin=Ndatos1;//longitud del templado
    FILE *ptr;
    ptr=fopen(salida,"w");
	
    int cant=0,ultj=0;
    for(j=2;j<Ndatos2-Nmin;j++){ //barro por todos los puntos de la señal que me permita el largo del templado
	
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
		
        if(r>0.8){pFile=fopen("resultados.dat","a");
			if(j-ultj>800){ cant+=1;}			
            fprintf(pFile,"%d\t %g\t %s\t %d,%i\n",j,r,entrada,perio,cant);
			fclose(pFile);			
			ultj=j;
			
			}
    }
    FILE *cantcorr;//guardo cuanto correlaciono cada templado con el archivo (para analizar mas facil los parámetros optimos. Se puede borrar al correrlo con todos los archivos, o usarlo
    cantcorr=fopen("ccs.dat","a");
    //fprintf(cantcorr,"%d\t %d\n",perio,cant);
    fprintf(cantcorr,"%d\t %d\t %g\t %d\n",perio,cant,numerador,golord);
    fclose(cantcorr);
    printf("cantidad de coincidencias=%d \n",cant);
	printf("tauintegracion: %g\n",aa.tau);   
	printf("orden del filtro: %d\n\n\n",golord);
	free_dvector(av_sound2,1,POT2up);
    free_dvector(hilb2,1,POT2up);
    free_dvector(emg1,1,Ndatos1);
    free_dvector(sav2,1,POT2up);
	free_dvector(emg2,1,POT2up);

}


