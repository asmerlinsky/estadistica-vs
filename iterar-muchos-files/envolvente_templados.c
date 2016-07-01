
/*Realiza envolvente de templados
HAY QUE INTRODUCIRLO POR LINEA DE COMANDO COMO ARGV

*/
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
#include <stdbool.h>



bool match(const char *pattern, const char *candidate, int p, int c) {
  if (pattern[p] == '\0') {
    return candidate[c] == '\0';
  } else if (pattern[p] == '*') {
    for (; candidate[c] != '\0'; c++) {
      if (match(pattern, candidate, p+1, c))
        return true;
    }
    return match(pattern, candidate, p+1, c);
  } else if (pattern[p] != '?' && pattern[p] != candidate[c]) {
    return false;
  }  else {
    return match(pattern, candidate, p+1, c+1);
  }
}


struct Par {
    double beta; double tau;
} aa;


void takens(int n,double v[],double dv[],double t) {
    double x;    
    x=v[0];     
    dv[0]=-(1/aa.tau)*x+fabs(aa.beta);
    return;
}



int nearpow2up(int number){
    int i=0, temp=1;
    while(temp<number) {temp*=2; i++;}
        return(temp);
}


int main(int argc, char *argv[]) {
    int i,k,Ndatos, golord;
    char *nomfile;
    char entrada[100];
    nomfile=argv[1];
    sprintf(entrada,"%s",nomfile);
    //printf("nomfile=%s\n",entrada);
    golord=4;
    
    //CARGA TEMPLATE
    double *temp;
    Ndatos=filesize(entrada,1);

    
    int POT2up=nearpow2up(Ndatos);

    temp=dvector(1,POT2up);
    file_to_vector(entrada,temp,1,Ndatos,1,1);
    printf("templado es %s \n", nomfile);
    printf("Ndatos=%d\n",Ndatos);
    for(i=Ndatos;i<=POT2up;i++){temp[i]=temp[Ndatos];}


   //CALCULA ENVOLVENTE CON HILBERT
    double *hilb;
    hilb=dvector(1,POT2up);
   
    for(i=1;i<=500;i++) hilb[i]=0.0; //guarda si cambia LFILT
   
    hilbert(temp,hilb,POT2up);



    //SUAVIZA ENVOLVENTE CON INTEGRACION
    double v[1],dt, t;
    double *av_sound;


    av_sound=dvector(1,POT2up);
    v[0]=0.0;
    k=0;
    dt=1/10000.;
    
    aa.tau=10/1500.;

    for(i=1;i<=POT2up;i++){
        aa.beta=hilb[i];
        rk4(takens,v,1,t+0.0,dt);
        av_sound[i]=v[0];
    }
    
    
    
    int np,nl,nr,ld,m,index,Nmin;
    char suavtempname[100];
    float *c1,*data1,*ans1,dum1;
   
    c1=vector(1,POT2up); data1=vector(1,POT2up); ans1=vector(1,2*POT2up);

    double *sav;
    sav=dvector(1,POT2up);
  
    for(i=1;i<=POT2up;i++) data1[i]=(float) av_sound[i];
    
    savgol(c1,513,256,256,0,golord);
    
    for(index=1;index<=POT2up;index++) data1[index]=fabs(data1[index]);
    
    convlv(data1,POT2up,c1,513,1,ans1);

    for(i=2;i<POT2up-1;i++) sav[i]=(double) ans1[i];
    
    
    strcpy(suavtempname, "envolvente.");
    strcat(suavtempname, nomfile);
    strcat(suavtempname, ".dat");
    vector_to_file(suavtempname,sav,1,Ndatos);
            
    printf("tauintegracion: %g\t",aa.tau);
    printf("orden del filtro: %d\n\n\n",golord);

    
    
    
    if (match("emg*Sound", nomfile, 0, 0)){
        char perio[20];
        sscanf(nomfile, "%*[^0123456789]%[^'.']%*s", perio);
        double rmin;
        if(strcmp(perio, "2-1")==0) {rmin=0.7;}
        else if(strcmp(perio, "2-3")==0) {rmin=0.6;}
        else if(strcmp(perio, "2-4")==0) {rmin=0.7;}
        else if(strcmp(perio, "2-45")==0) {rmin=0.7;}
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
        
        FILE *pFile;
        pFile=fopen("datatemplados.dat","a");         
        fprintf(pFile,"%s\t%d\t%g\n",perio,Ndatos,rmin);
        fclose(pFile);   
        
    }
    
    free_dvector(av_sound,1,POT2up);
    free_dvector(hilb,1,POT2up);
    free_dvector(sav,1,POT2up);

}


