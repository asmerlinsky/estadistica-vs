
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



int main(int argc, char *argv[]) {
	int i,j,k,Ndatos,Ndatoss2, perio,golord;
    char *nomfile;
	char entrada[20];
	FILE *pFile;
    nomfile=argv[1];
	sprintf(entrada,"%s",nomfile);
    golord=3;
	aa.tau=0.5/1500.;
	//CARGA TEMPLATE
	double *temp;
    Ndatos=filesize(entrada,1);
	Ndatoss2=Ndatos/2;
    temp=dvector(1,Ndatos);
    file_to_vector(entrada,temp,1,Ndatos,1,1);
	printf("templado es %s \n", nomfile);



   //CALCULA ENVOLVENTE CON HILBERT
	double *hilb;
	char hilbtempname[80], integtempname[80];
	hilb=dvector(1,Ndatos); //este gato inicializa mal
   
	for(i=1;i<=500;i++) hilb[i]=0.0; //guarda si cambia LFILT
   
	hilbert(temp,hilb,Ndatos);
	
	strcpy(hilbtempname, "hilbert.");
	strcat(hilbtempname, nomfile);
	strcat(hilbtempname, ".dat");

	printf("hilbert ok \n nombrehilbert %s \n",hilbtempname);
	vector_to_file(hilbtempname,hilb,1,Ndatos);
	    

	//SUAVIZA ENVOLVENTE CON INTEGRACION
	double v[1],dt, t;
    double *av_sound;
    av_sound=dvector(1,Ndatos);
  
    k=0;
    dt=1/10000.;
    
    //aa.tau=.5/1500.;
	printf("v[0]= %d y v[1]=%d \n",v[0],v[1]);
    for(i=1;i<=Ndatos;i++){
		aa.beta=hilb[i];
        rk4(takens,v,1,t+0.0,dt);
        av_sound[i]=v[0];
    }
    printf("tauintegracion: %g\n",aa.tau);
    
	strcpy(integtempname, "integrado.");
	strcat(integtempname, nomfile);
	strcat(integtempname, ".dat");
	printf("integ ok \n nombreinteg %s \n",integtempname);
	vector_to_file(integtempname,av_sound,1,Ndatos);
    
	
	//SAVITSKY-GOLAY
    int np,nl,nr,ld,m,index,Nmin;
    int POT=nearpow2(Ndatos);
    char suavtempname[80];
    float *c1,*data1,*ans1,dum1;
   
    c1=vector(1,POT); data1=vector(1,POT); ans1=vector(1,2*POT);

    double *sav;
    sav=dvector(1,Ndatos);
	
    // primera
  
	for(i=1;i<=POT;i++) data1[i]=(float) av_sound[i];
	
	savgol(c1,513,256,256,0,golord);
    
	for(index=1;index<=POT;index++) data1[index]=fabs(data1[index]);
	
	convlv(data1,POT,c1,513,1,ans1);

    for(i=2;i<POT-1;i++) sav[i]=(double) ans1[i];
    
	strcpy(suavtempname, "envolvente.");
    strcat(suavtempname, nomfile);
    strcat(suavtempname, ".dat");
    vector_to_file(suavtempname,sav,1,Ndatoss2);
    
	printf("nombreenvolventees: %s\n",suavtempname);         
    printf("tauintegracion: %g\n",aa.tau);
	printf("orden del filtro: %i\n",golord);

	free_dvector(av_sound,1,Ndatos);
    free_dvector(hilb,1,Ndatos);
    free_dvector(sav,1,Ndatos);

}


