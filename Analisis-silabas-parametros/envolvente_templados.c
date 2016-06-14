
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


int main(int argc, char *argv[]) {
    int i,j,k,Ndatos,golord;
    char *nomfile;
    char perio[30];
    char entrada[60];
    double numerador;
    FILE *pFile;
    nomfile=argv[1];
    sprintf(entrada,"%s",nomfile);
    sscanf(argv[2], "%lf", &numerador); 
    sscanf(argv[3], "%d", &golord);
    printf("nomfile=%s\n",entrada);
    //golord=4;
    aa.tau=numerador/1500.;

    //CARGA TEMPLATE
    double *temp;
    Ndatos=filesize(entrada,1);
    printf("Ndatos=%d\n",Ndatos);
    int POT2up=nearpow2up(Ndatos);
    //Ndatoss2=Ndatos/2;
    temp=dvector(1,POT2up);
    file_to_vector(entrada,temp,1,Ndatos,1,1);
    printf("templado es %s \n", nomfile);
    for(i=Ndatos;i<=POT2up;i++){temp[i]=temp[Ndatos];}


   //CALCULA ENVOLVENTE CON HILBERT
    double *hilb;
    char hilbtempname[150], integtempname[150];
    hilb=dvector(1,POT2up);
    //hilb=dvector(1,Ndatos); //este gato inicializa mal
   
    for(i=1;i<=500;i++) hilb[i]=0.0; //guarda si cambia LFILT
   
    //hilbert(temp,hilb,Ndatos);
    hilbert(temp,hilb,POT2up);
    strcpy(hilbtempname, "hilbert.");
    strcat(hilbtempname, nomfile);
    strcat(hilbtempname, ".dat");

    printf("hilbert ok \n nombrehilbert %s \n",hilbtempname);
    vector_to_file(hilbtempname,hilb,1,Ndatos);
        

    //SUAVIZA ENVOLVENTE CON INTEGRACION
    double v[1],dt, t;
    double *av_sound;
    //av_sound=dvector(1,Ndatos);
    av_sound=dvector(1,POT2up);
    v[0]=0.0;
    k=0;
    dt=1/10000.;
    
    //aa.tau=.5/1500.;
    //for(i=1;i<=Ndatos;i++){
    for(i=1;i<=POT2up;i++){
        aa.beta=hilb[i];
        rk4(takens,v,1,t+0.0,dt);
        av_sound[i]=v[0];
    }
    
    strcpy(integtempname, "integrado.");
    strcat(integtempname, nomfile);
    strcat(integtempname, ".dat");
    vector_to_file(integtempname,av_sound,1,Ndatos);
    
    
    //SAVITSKY-GOLAY
    int np,nl,nr,ld,m,index,Nmin;
    //int POT=nearpow2(Ndatos);
    char suavtempname[200];
    float *c1,*data1,*ans1,dum1;
   
    //c1=vector(1,POT); data1=vector(1,POT); ans1=vector(1,2*POT);
    c1=vector(1,POT2up); data1=vector(1,POT2up); ans1=vector(1,2*POT2up);

    double *sav;
    //sav=dvector(1,Ndatos);
    sav=dvector(1,POT2up);
    // primera
  
    //for(i=1;i<=POT;i++) data1[i]=(float) av_sound[i];
    for(i=1;i<=POT2up;i++) data1[i]=(float) av_sound[i];
    
    savgol(c1,513,256,256,0,golord);
    
    //for(index=1;index<=POT;index++) data1[index]=fabs(data1[index]);
    for(index=1;index<=POT2up;index++) data1[index]=fabs(data1[index]);
    
    //convlv(data1,POT,c1,513,1,ans1);
    convlv(data1,POT2up,c1,513,1,ans1);

    //for(i=2;i<POT-1;i++) sav[i]=(double) ans1[i];
    for(i=2;i<POT2up-1;i++) sav[i]=(double) ans1[i];
    
    
    strcpy(suavtempname, "envolvente.");
    strcat(suavtempname, nomfile);
    strcat(suavtempname, ".dat");
    //vector_to_file(suavtempname,sav,1,Ndatoss2);
    vector_to_file(suavtempname,sav,1,Ndatos);
            
    printf("tauintegracion: %g\n",aa.tau);
    printf("orden del filtro: %d\n\n\n",golord);
/*
    free_dvector(av_sound,1,Ndatos);
    free_dvector(hilb,1,Ndatos);
    free_dvector(sav,1,Ndatos);
*/
    free_dvector(av_sound,1,POT2up);
    free_dvector(hilb,1,POT2up);
    free_dvector(sav,1,POT2up);

}


