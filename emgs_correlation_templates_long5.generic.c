
//apunta a correlaciones

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



int main(int argc, char *argv[]) {
//    int main() {
   int i,j,k,Ndatos1,Ndatos2,Ndatos1s2,perio;
    
    char *letras;
    char entrada[20];
    char salida[50];
    FILE *pFile;
    
    letras=argv[1];
    perio=5;
    sprintf(entrada,"temp01_%s",letras);
    sprintf(salida,"correlaciones5.%s.dat",letras);
    
 //   printf("OK\n");

    //CARGA EMG1
   
    double *emg1;
    Ndatos1=filesize("newtemplate5.Sound",1);
    Ndatos1s2=Ndatos1/2;
    emg1=dvector(1,Ndatos1);
    file_to_vector("newtemplate5.Sound",emg1,1,Ndatos1,1,1);
    
    double *emg2;
    Ndatos2=filesize(entrada,1);
    emg2=dvector(1,Ndatos2);
    file_to_vector(entrada,emg2,1,Ndatos2,1,1);
  //  printf("\n%lg\n", emg2[1]);


   printf("\tNdatos1sd: %d Ndatos2: %d\n",Ndatos1,Ndatos2);  


   //CALCULA ENVOLVENTE CON HILBERT
   double *hilb1;
   hilb1=dvector(1,Ndatos1);
   hilbert(emg1,hilb1,Ndatos1);
   vector_to_file("hilbert.ch2.dat",hilb1,1,Ndatos1);

   printf("ok\n");  

    double *hilb2;
    hilb2=dvector(1,Ndatos2);
    hilbert(emg2,hilb2,Ndatos2);
    vector_to_file("hilbert.ch3.dat",hilb2,1,Ndatos2);

   printf("ok\n");  
    

   //SUAVIZA ENVOLVENTE CON INTEGRACION
   double v1[1],v2[1],dt, t;
   double *av_sound1,*av_sound2;
   av_sound1=dvector(1,Ndatos1);
   av_sound2=dvector(1,Ndatos2);
   
    k=0;
   dt=1/10000.;
   aa.tau=15./1500.;
   //aa.tau=.5/1500.;
   for(i=1;i<=Ndatos1;i++){
        aa.beta=hilb1[i];
        rk4(takens,v1,1,t+0.0,dt);
       av_sound1[i]=v1[0];
   }
    
    for(i=1;i<=Ndatos2;i++){
        aa.beta=hilb2[i];
        rk4(takens,v2,1,t+0.0,dt);
        av_sound2[i]=v2[0];
    }  
   
   

 
    
   //SAVITSKY-GOLAY
   int np,nl,nr,ld,m,index,Nmin;
   int POT1=nearpow2(Ndatos1);
   int POT2=nearpow2(Ndatos2);
    
   float *c1,*data1,*ans1,dum1;
   float *c2,*data2,*ans2,dum2;
   
   c1=vector(1,POT1); data1=vector(1,POT1); ans1=vector(1,2*POT1);
   c2=vector(1,POT2); data2=vector(1,POT2); ans2=vector(1,2*POT2);

   double *sav1,*sav2;
   sav1=dvector(1,Ndatos1);
   sav2=dvector(1,Ndatos2); 

   // primera
  
   for(i=1;i<=POT1;i++) data1[i]=(float) av_sound1[i];
     savgol(c1,513,256,256,0,4);
   for(index=1;index<=POT1;index++) data1[index]=fabs(data1[index]);
   convlv(data1,POT1,c1,513,1,ans1);

   for(i=2;i<POT1-1;i++) sav1[i]=(double) ans1[i];
   vector_to_file("en.ch2.template5.Sound.dat",sav1,1,Ndatos1s2);
  	 
    // segunda


    for(i=1;i<=POT2;i++) data2[i]=(float) av_sound2[i];
    savgol(c2,513,256,256,0,4);
    for(index=1;index<=POT2;index++) data2[index]=fabs(data2[index]);
    convlv(data2,POT2,c2,513,1,ans2);
    
    for(i=2;i<POT2-1;i++) sav2[i]=(double) ans2[i];
    vector_to_file("en.ch3.Sound.dat",sav2,1,Ndatos2); 
    
    //calculo de la correlacion entre las señales.
    
    Nmin=Ndatos1s2;
    
    FILE *ptr;
    ptr=fopen(salida,"w");
    
    for(j=2;j<Ndatos2-Nmin;j++){
        double x1bar=0.0,sx1=0.0;
        for(i=2;i<Nmin;i++){x1bar+=sav1[i];}
        x1bar /= (Nmin-2);
    double x2bar=0.0, sx2=0.0,r=0.0;
    for(i=2;i<Nmin;i++){x2bar+=sav2[i+j];}
    x2bar /= (Nmin-2);
    for(i = 2; i < Nmin; i++) {sx1 += (sav1[i] - x1bar) * (sav1[i] - x1bar);}
    sx1 = sqrt((sx1 / (Nmin-2)));
    for(i = 2; i < Nmin; i++) {sx2 += (sav2[i+j] - x2bar) * (sav2[i+j] - x2bar);}
    sx2 = sqrt((sx2 / (Nmin-2)));
    
    for( i = 2; i < Nmin; i++ ) {r += (((sav1[i] - x1bar)/sx1) * ((sav2[i+j] - x2bar)/sx2));}
    r /= (Nmin-2);
        
    fprintf(ptr,"%g\t %d\n",r,j);
        if(r>0.8){pFile=fopen("resultados.dat","a");
            fprintf(pFile,"%g\t %d\t %s\t%d\n",r,j,letras,perio);
            fclose(pFile);
                    }
    }
        
    free_dvector(av_sound1,1,Ndatos1);
    free_dvector(av_sound2,1,Ndatos2);
    free_dvector(hilb1,1,Ndatos1);
    free_dvector(hilb2,1,Ndatos2);
    free_dvector(sav1,1,Ndatos1);
    free_dvector(sav2,1,Ndatos2);

}


