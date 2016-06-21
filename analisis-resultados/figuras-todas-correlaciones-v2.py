###figuras-todas-correlaciones
##tengo que cargar el archivo .Sound y todos los archivos de correlaciones
##va a andar bien si meto igual cantidad de templados de 2 criterios.
##si tengo otra cantidad de criterios hay que retocar el programa
## puedo cargar tantos archivos como queira que cumplan estas condiciones


import matplotlib.pyplot as plt
import numpy as np
import os
import glob


def consecutivefirst(data, stepsize=1):
    s=np.split(data, np.where(np.diff(data) != stepsize)[0]+1)
    if len(s[0])>0:
        t = tuple(x[0] for x in s)
    else:
        t=[]
        
    return t

files=glob.glob('datos/ZF*.Sound')

resultados=np.genfromtxt('resultados.dat',names=True,dtype=[('f0', '<i4'), ('f1', '<f8'), ('f2', 'S100'),('f3', 'S20'), ('f4', '<i4')])
templados=np.unique(resultados['3'])
poslabel=np.linspace(np.pi/len(templados),2*np.pi-np.pi/len(templados),len(templados))
np.random.shuffle(poslabel)
poslabelx=np.cos(poslabel)
poslabely=np.sin(poslabel)

for archivo in files:
    data=np.loadtxt(archivo)
    tiempo=np.linspace(0,len(data)/44150,len(data))
    plt.figure()
    plt.title(os.path.basename(archivo))
    plt.plot(tiempo,data)
    i=0
    for key in templados: #i in range(0,int(len(silabas)/2)):
        i+=1
        nomfile=bytes('envolvente.'+os.path.basename(archivo)+'.dat',encoding="UTF-8")
        try:
            plt.plot(tiempo[resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==key)]],resultados['1'][np.logical_and(resultados['2']==nomfile,resultados['3']==key)],ms=8,marker='o',label='temp'+key.decode("utf-8"),ls='None')


            lugares=consecutivefirst(resultados['0'][np.logical_and(resultados['2']==nomfile,resultados['3']==key)])
            for lugar in lugares:
                resultado=resultados['1'][np.logical_and(np.logical_and(resultados['2']==nomfile,resultados['3']==key),resultados['0']==lugar)][0]
                plt.annotate('S'+key.decode("utf-8"), xy = (tiempo[lugar], resultado), xytext = (tiempo[lugar]+(5000/44150)*poslabelx[i], resultado+0.15*poslabely[i]),arrowprops=dict(facecolor='black', shrink=0.05,fc='b'))        
                 
        except:
            pass
  

plt.show(block=True)
