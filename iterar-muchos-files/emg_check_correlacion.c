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
    int i,j,k,Ndatos;
    char perio[5];
    double numerador;
    char ubicacion[100];
    char entrada[200];

    FILE *pFile;

    //sscanf(argv[1],"%[^'/']/%s",ubicacion,entrada);//LINUX tener cuidado si lo corro en windows
    sprintf(entrada,"%s",argv[1]); //WINDOWS
    sprintf(perio,"%s",argv[2]);
  
    //printf("archivo correlacion es %s \n", entrada);
    //printf("salida es %s\n",salida);

    //CARGA CORRELACION
    double **correla;
    sprintf(ubicacion,"FILTRADOS\\%s.",entrada);//WINDOWS
    Ndatos=filesize(ubicacion,1);//WINDOWS
    correla=dmatrix(1,Ndatos,1,2);//WINDOWS
    file_to_matrix(ubicacion, correla, 1, Ndatos, 2);//WINDOWS
    // Ndatos=filesize(argv[1],1);//LINUX
    // correla=dmatrix(1,Ndatos,1,2);//LINUX
    // file_to_matrix(argv[1], correla, 1, Ndatos, 2);//LINUX
    printf("cargo correlacion %sOK\n",entrada);

    printf("elemento 10 1 %g\n",correla[10][1]);
    printf("elemento 10 2 %g\n",correla[10][2]);
    char nombrearchivo[100];
    char tail[10];
    sscanf(entrada,"%*[^'.'].%s",entrada);
    char *dot = strrchr(entrada, '.');
    strcpy(tail, dot);  // Beware buffer overflow
    memcpy(nombrearchivo, entrada, dot - entrada);
    nombrearchivo[dot - entrada] = '\0';
    printf("nombre archivo es %s \n",nombrearchivo);
    //calculo de la correlacion entre las señales.
    
    
    double r,rmin;
    sscanf(argv[3], "%lf", &rmin); 
    int cant=0,ultj=0;  
    for(j=1;j<Ndatos;j++){
        r=correla[j][2];
        //printf("r=%g \n",r);
        //printf("correla=%g \n",correla[j][1]);
        if(r>rmin){pFile=fopen("resultados.dat","a");
            if(j-ultj>1000){ cant+=1;}     
            printf("tengo r>rmin\n");       
            fprintf(pFile,"%g\t %g\t %s\t %s\t %i\n",correla[j][1],r,nombrearchivo,perio,cant);
            fclose(pFile);            
            ultj=j;
            }
    }
    
    printf("cantidad de coincidencias=%d \n",cant);
    
    free_dmatrix(correla, 1,Ndatos,1,2);
    //free_dvector(correla,2,Ndatos);

    
}


