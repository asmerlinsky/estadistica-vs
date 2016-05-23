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


 /*usa los templados procesados*/
int main(int argc, char *argv[]) {
    int i,j,k,Ndatos1,Ndatos2,Ndatos1s2,perio,Ndatos2s2;
    char string1[20], string2[20];
    char filetemplado[80];
	char entrada[80];
    char salida[80];
    FILE *pFile;
    
	//asigno que silaba es
	sscanf(argv[2], "%*[^0123456789]%i%*s", &perio); 
	printf("perio vale %i \n",perio);
	
	sprintf(filetemplado,"%s",argv[2]);
	sprintf(entrada,"%s",argv[1]);
    sprintf(salida,"corremg%i.%s.dat",perio,argv[1]);
	
	printf("filetemplado es %s \n", filetemplado);
	printf("salida es %s \n", salida);	
	printf("entrada es %s \n", entrada);	
	
    //CARGA EMG1
    double *emg1;
    Ndatos1=filesize(filetemplado,1);
    Ndatos1s2=Ndatos1/2;
    emg1=dvector(1,Ndatos1);
    file_to_vector(filetemplado,emg1,1,Ndatos1,1,1);
	printf("templado OK\n");
	//carga SUEÑO
    double *emg2;
    Ndatos2=filesize(entrada,1);
	Ndatos2s2=Ndatos2/2;
    emg2=dvector(1,Ndatos2);
    file_to_vector(entrada,emg2,1,Ndatos2,1,1);
    printf("sueno OK\n");
    printf("\tNdatos1sd: %d Ndatos2: %d\n",Ndatos1,Ndatos2);  
	
	
	//Hilbert a sueño
    double *hilb2;
    hilb2=dvector(1,Ndatos2);
	for(i=1;i<=500;i++) hilb2[i]=0.0; //guarda si cambia LFILT
	hilbert(emg2,hilb2,Ndatos2);
    vector_to_file("hilbert.sueno.dat",hilb2,1,Ndatos2s2);

    printf("ok\n");  
    

   //SUAVIZA ENVOLVENTE CON INTEGRACION
    double v2[1],dt, t;
    double *av_sound2;
    av_sound2=dvector(1,Ndatos2);
	
    k=0;
    dt=1/10000.;
    aa.tau=5./1500.;
    //aa.tau=.5/1500.;
	printf("v2[0]= %d y v2[1]=%d \n",v2[0],v2[1]);
	for(i=1;i<=Ndatos2;i++){
		aa.beta=hilb2[i];
        rk4(takens,v2,1,t+0.0,dt);
        av_sound2[i]=v2[0];
    }  
   
   
	vector_to_file("int.sueno.dat",av_sound2,1,Ndatos2s2);
 
    
    //SAVITSKY-GOLAY
    int np,nl,nr,ld,m,index,Nmin;
    int POT2=nearpow2(Ndatos2);
    float *c2,*data2,*ans2,dum2;
   
    c2=vector(1,POT2); data2=vector(1,POT2); ans2=vector(1,2*POT2);

    double *sav2;
    sav2=dvector(1,Ndatos2); 
	
	for(i=1;i<=POT2;i++) data2[i]=(float) av_sound2[i];
    savgol(c2,513,256,256,0,3);
    for(index=1;index<=POT2;index++) data2[index]=fabs(data2[index]);
    convlv(data2,POT2,c2,513,1,ans2);
    
    for(i=2;i<POT2-1;i++) sav2[i]=(double) ans2[i];
	char envname[50];
	strcpy(envname, "envolvente.");
    strcat(envname, entrada);
	strcat(envname, ".dat");
    vector_to_file(envname,sav2,1,Ndatos2s2); 
    
    //calculo de la correlacion entre las señales.
    
    Nmin=Ndatos1s2;
    
    FILE *ptr;
    ptr=fopen(salida,"w");
    int cant=0,ultj;
    for(j=2;j<Ndatos2s2-Nmin;j++){ //barro por todos los puntos de la señal que me permita el largo del templado
        
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
        
    	fprintf(ptr,"%g\t %d\n",j,r);
        if(r>0.8){pFile=fopen("resultados.dat","a");
			if(j-ultj>50){ cant+=1;}			
            fprintf(pFile,"%g\t %d\t %s\t %d,%i\n",j,r,entrada,perio,cant);
			fclose(pFile);			
			ultj=j;
			}
    }
    printf("cantidad de coincidencias=%i \n",cant);
    free_dvector(av_sound2,1,Ndatos2);
    free_dvector(hilb2,1,Ndatos2);
    free_dvector(emg1,1,Ndatos1);
    free_dvector(sav2,1,Ndatos2);

}


