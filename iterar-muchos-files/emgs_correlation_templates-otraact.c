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


char* sacarespacios(char* input)                                         
{
    int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}


 /*usa los templados procesados*/
int main(int argc, char *argv[]) {
    int i, j, k, Ndatos;
    
    double numerador;
    char entrada[100];
    char cargar[100];
    char nomcorr[100];

    //cargo el nombre del archivo
    sprintf(entrada,"%s",argv[1]); //WINDOWS
    strcpy(nomcorr,"FILTRADOS/corremg");
    strcat(nomcorr,entrada);
        
    //carga la envolvente
    strcpy(cargar,"FILTRADOS/");    
    strcat(cargar, entrada);//WINDOWS
    
    printf("cargo %s\n",cargar);//WINDOWS
    Ndatos=filesize(cargar,1); //WINDOWS
    double *emg;
    emg=dvector(1,Ndatos);
    file_to_vector(cargar,emg,1,Ndatos,1,1);//WINDOWS
    

    printf("sueno OK\n");
    
    printf("Ndatos: %d\n",Ndatos);  
    
    //CARGO CORRELACIONES
    //CUENTO COLUMNAS
    int ncols = 1;
    int nfilas = 0;
    int c;
    FILE *ptrcorr;
    strcpy(nomcorr,"FILTRADOS/corremg.");
    strcat(nomcorr,entrada);
    printf("nomcorr=%s\n",nomcorr);
    ptrcorr = fopen(nomcorr, "r");
    
    if (ptrcorr != NULL) { 
        c = fgetc(ptrcorr);
        while(c!='\n'){
            if (c=='\t'){++ncols;}
            c = fgetc(ptrcorr);
            
        }
    }    
    else {
        printf("Falta archivo %s\n", nomcorr);
        exit(0); 
    }
    //CUENTO FILAS 
    rewind(ptrcorr);
    char buffer[500];
    char bufferperios[500];
    fgets(bufferperios, 500, ptrcorr);
    while(!feof(ptrcorr)){
        fgets(buffer, 500, ptrcorr);
        ++nfilas;
    }
    --nfilas;//esta es la cantidad de filas de la matrix(solo los numeros)
    
    printf("conte %d filas y %d columnas\n",nfilas,ncols);    
    fclose(ptrcorr);
    
    //CARGO LA MATRIZ
    double **correla;
    correla=dmatrix(0,nfilas-1,0,ncols-1);
    //file_to_matrix1(nomcorr, correla, EN QUE FILA EMPIEZA LA MATRIZ, CUANTAS FILAS TIENE, CUANTAS COLUMNAS TIENE)
    file_to_matrix1(nomcorr, correla, 1, nfilas, ncols);
   

    
    
    
    i = 0;
    char *p = strtok (bufferperios, "\t");
    char *labelcorr[ncols];

    while (p != NULL){
        labelcorr[i++] = p;
        p = strtok (NULL, " \r\n\t");
    }
     
    for (i = 0; i < ncols; ++i) {sacarespacios(labelcorr[i]); }    
        
    //LEVANTO EL UMBRAL DE RUIDO
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
    
    //LEVANTO LA LONGITUD DE LOS ARCHIVOS
    char labellong[20][ncols-1];
    int longtemp[ncols-1];
    double umbralcorrelacion[ncols-1];
    char label[20];
    int ltemp;
    double rmin;
    
    FILE *ptrlong;
    ptrlong=fopen("datatemplados.dat","r");
    fgets(buffer, 500, ptrlong);
    for (i=0;i<(ncols-1);i++){
       fscanf(ptrlong,"%s\t%d\t%lf",labellong[i],&longtemp[i],&umbralcorrelacion[i]);

    }
    fclose(ptrlong);  

    
    int ii, cota, m, n, mm;
    FILE *pFile;
    int cant=0;
    int ultj=0;
    double xbar=0.0;
    int step=(correla[1][0]-correla[0][0]);
    int fracstep=(1000/step);

    for (j=0;j<(nfilas-fracstep);j+=10){//recorro las posiciones donde tome correlaciones si cambio i++ por i+=n lo recorro en multiplos de n*step

        for(i=correla[j][0];i<correla[j][0]+1000;i++){xbar+=emg[i];}
        xbar /= 1000;
        k=0;
        if (xbar>3*umbruido){
            m=1;//el 0 es la posicion
            while( (k!=-1) && (m<ncols) ){// mientras no encuentre correlacion en algun templado
                ii=0;
                for (;;){ //mientras no de con el templado a aanlizar comparo.
                    if (strcmp(labelcorr[m],labellong[ii])==0){
                        cota=longtemp[ii];
                        rmin=umbralcorrelacion[ii];
                        break;
                        
                    }
                    ii+=1;
                    if ( (ii>ncols) && ii<ncols+4 ){printf("cague, no enconte igualdad con labelcorr[%d]=%s\n",m,labelcorr[m]);}
                } 
                
                
                n=(j+1000);//empieza a buscar esta cantidad de lugares y va hacia atras (va a ser un poco mas eficiente) 
                
                while( n>=(j-cota) && n>0 ){//mientras no encuentre correlacion que supere el umbral con este templado, sigo buscando
                    
                    if( (correla[n][m]>rmin) ){
                    k=-1;
                    break;
                    }//encontre correlacion con el templado, así que dejo de buscar
                    
                    n-=1;    
                
                }
                
                m+=1;//paso al proximo templado.
                
                
            
            
                
            
            }
            //si recorri todo el loop y k=0, entonces tengo un segmento
            if (k==0){k=1;}
        }
        
        if (k==1){
            if(j-ultj>1500){ cant+=1;}  
            pFile=fopen("resultados.dat","a");
            fprintf(pFile,"%g\t %G\t %s\t %s\t %d\n",correla[j][0],-0.8,entrada,"sincorr",cant);
            fclose(pFile);            
            ultj=j;
                        
        }
    
    }
    printf("encontre %d segmentos de ruido\n",cant);
    free_dmatrix(correla,0,nfilas-1,0,ncols-1);
    free_dvector(emg,1,Ndatos);
    
}


