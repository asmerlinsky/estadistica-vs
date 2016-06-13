###figuras-todas-correlaciones
##tengo que cargar el archivo .Sound y todos los archivos de correlaciones
##va a andar bien si meto igual cantidad de templados de 2 criterios.
##si tengo otra cantidad de criterios hay que retocar el programa
## puedo cargar tantos archivos como queira que cumplan estas condiciones


import matplotlib.pyplot as plt
import numpy as np
import os
import glob


def consecutive(data, stepsize=1):
    s=np.split(data, np.where(np.diff(data) != stepsize)[0]+1)
    if len(s[0])>0:
        t = tuple(x[0] for x in s)
    else:
        t=[]
        
    return t

files=glob.glob('datos/ZF*.Sound')

resultados=np.genfromtxt('resultados.dat',names=True,dtype=[('f0', '<i4'), ('f1', '<f8'), ('f2', 'S100'),('f3', '<i4'), ('f4', '<i4')])
silabas=np.unique(resultados['3'])
poslabel=np.linspace(0,3.1415,len(silabas))
np.random.shuffle(poslabel)
poslabelx=np.cos(poslabel)
poslabely=np.sin(poslabel)

for archivo in files:
    data=np.loadtxt(archivo)
    plt.figure()
    plt.title(os.path.basename(archivo))
    plt.plot(data)

    for i in range(0,int(len(silabas)/2)):
        nomfile=bytes('envolvente.'+os.path.basename(archivo)+'.dat',encoding="UTF-8")
        try:
            plt.plot(resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i])],resultados['1'][np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i])],ms=8,marker='o',label='temp 1'+str(i+1),ls='None')


            lugares=consecutive(resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i])])
            for lugar in lugares:
                resultado=resultados['1'][np.logical_and(np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i]),resultados['0']==lugar)][0]
                
                #if (i % 2 == 0):
                plt.annotate('S'+str(silabas[i]), xy = (lugar, resultado), xytext = (lugar+5000*poslabelx[i], resultado+0.15*poslabely[i]),arrowprops=dict(facecolor='black', shrink=0.05,fc='b'))        
                #else:
                #    plt.annotate('S'+str(silabas[i]), xy = (lugar, resultado), xytext = (lugar-3000, resultado-.1),arrowprops=dict(facecolor='black', shrink=0.05))      
        except:
            pass
    
    
    plt.figure()
    plt.title(os.path.basename(archivo))
    plt.plot(data)
    for i in range(int(len(silabas)/2),len(silabas)):
        nomfile=bytes('envolvente.'+os.path.basename(archivo)+'.dat',encoding="UTF-8")
        try:
            plt.plot(resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i])],resultados['1'][np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i])],ms=8,marker='o',label='temp 1'+str(i+1),ls='None')


            lugares=consecutive(resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i])])
            for lugar in lugares:
                resultado=resultados['1'][np.logical_and(np.logical_and(resultados['2']==nomfile,resultados['3']==silabas[i]),resultados['0']==lugar)][0]
                
                #if (i % 2 == 0):
                plt.annotate('S'+str(silabas[i]), xy = (lugar, resultado), xytext = (lugar+5000*poslabelx[i], resultado+0.15*poslabely[i]),arrowprops=dict(facecolor='black', shrink=0.05,fc='b'))        
                #else:
                #    plt.annotate('S'+str(silabas[i]), xy = (lugar, resultado), xytext = (lugar-3000, resultado-.1),arrowprops=dict(facecolor='black', shrink=0.05))      
        except:
            pass

plt.show(block=True)
