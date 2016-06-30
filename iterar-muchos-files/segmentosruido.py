import numpy as np
import glob
import os
import re
#3912	 0.800252	 envolvente.ZF-MCV-NOCHE_2015-12-01_00.01.33_vs_2101.Sound.dat	 2-1	 1

longruido=1000 #longitud de los segmentos que chequeo
longsueno=123450#longitud de los archivos de sueño
resultados=np.genfromtxt('resultados.dat',names=True,dtype=[('f0', '<i4'), ('f1', '<f8'), ('f2', 'S100'),('f3', 'S20'), ('f4', '<i4')])
umbralesenvolvente=np.genfromtxt('FILTRADOS/umbralruido.dat',names=True,dtype=[('f0', 'S100'), ('f1', '<f8')])

longtemplados = {}
with open("longtemp.dat") as f:
    for line in f:
       (key, val) = line.split()
       longtemplados[bytes( key,encoding="UTF-8")] = int(val)

longtemplados.pop(b'sincorr', None)
lista=glob.glob("FILTRADOS/envolvente*")

lugares=np.arange(0,longsueno-longruido,10,dtype=int)
actsincorr=np.vstack((lugares,np.zeros(len(lugares)))).T

for archivo in lista:
    
    
    nomfile=bytes(os.path.basename(archivo),encoding="UTF-8")
    print("archivo:",nomfile)
    envolvente=np.loadtxt(archivo)
    concorrelacion=resultados['0'][resultados['2']==nomfile] #lugares donde correlaciono algun templado
    umbralarch=umbralesenvolvente['1'][umbralesenvolvente['0']==nomfile]
    templados=np.unique(resultados['3'][resultados['2']==nomfile])#templados que correlacionaron en este archivo
    if b'sincorr' not in templados: ##busco si no lo hice todavia (por si lo quiero volver a correr por algun motivo y que no repita resultados)
        if concorrelacion.size>0:#si algun templado correlaciono en el archivo
            
            concorrelacion=np.unique(concorrelacion)
            i=0
            for puntos in lugares: #recorro lugares en el archivo cada 10
            
                if not np.where(np.logical_and(concorrelacion>=puntos, concorrelacion<=(puntos+1000)))[0].any():#si 1000 puntos hacia adelante no hay una correlacion, sigo
                    k=0
                    for perio in templados:
                        if (k==0):
                            lugcorrperio=resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==perio)]##aca tengo los puntos del archivo que correlacionaron con el templado "perio"
                            if np.where(np.logical_and(lugcorrperio>puntos-longtemplados[perio],lugcorrperio<puntos))[0].any():##esto da true si hay correlacion con el templado "perio" entre donde estoy y Npuntos antes, con Npuntos=longtempl
                                k=1
                    
                    if (k==0) and np.mean(envolvente[puntos:puntos+1000])>umbralarch: #Si hacia atrás no correlacionó, me fijo si el promedio supera mi umbral
                        actsincorr[i,1]=1.
                    else:    
                        actsincorr[i,1]=0.
                else:#si 1000 puntos hacia adelante hay una correlacion, entonces 0
                    actsincorr[i,1]=0.        
                
                i+=1            
                    
        else:#si ningun templado correlaciono en este archivo solo miro que pase el umbral de ruido
            print("no correlacionó ningún templado en",nomfile)
            i=0
            for puntos in lugares:
                if np.mean(envolvente[puntos:puntos+1000])>umbralarch:
                    actsincorr[i,1]=1.
                else:
                    actsincorr[i,1]=0.
                
                
        actconcorr=actsincorr[:,0][actsincorr[:,1]==1.]      
        
        if actconcorr.any():
            cant=1
            with open('resultados.dat', 'a') as f:
                f.write(str(actconcorr[0])+'\t-0.8\t'+os.path.basename(archivo)+'\tsincorr\t'+str(cant)+'\n')   
                for i in range(1,len(actconcorr)): ##guardo estos puntos
                    f.write(str(actconcorr[i])+'\t-0.8\t'+os.path.basename(archivo)+'\tsincorr\t'+str(cant)+'\n')   
                    if (actconcorr[i]-actconcorr[i-1])>1000:
                        cant+=1
                
            
            
            
            
            