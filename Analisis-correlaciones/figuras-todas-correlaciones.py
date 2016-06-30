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

files=glob.glob('datos/ZF*772.Sound')
for i in range(0,len(files)):
    print("cargo todas las correlaciones con", files[i])

    corrfiles=glob.glob('datos/corremg'+'*'+os.path.basename(files[i])+'.dat')
    #cargo corrfiles
    corrs=[np.loadtxt(corrfiles[0])[:,1]]
    
    [corrs.append(np.loadtxt(corrfiles[j])[:,1]) for j in range(1,len(corrfiles))]

    
    emg=np.loadtxt(files[i])
    emg/=np.max(np.abs(emg))
    plt.figure()
    plt.title(files[i])
    plt.plot(emg)
    for j in range(0,7):
        if (str(j+1)=='3'):
            umbral=0.58
        elif (str(j+1)=='6'):
            umbral=0.65
        else:
            umbral=0.80
        longcorrs=len(corrs[j])
        lin=np.linspace(0,longcorrs-1,longcorrs)
        plt.plot(lin[corrs[j]>umbral],corrs[j][corrs[j]>umbral],ms=8,marker='o',label='temp 1'+str(j+1)+' umbral='+str(umbral),ls='None') #linewidth=)
        lugares=consecutive(lin[corrs[j]>umbral])
        
        if lugares:
            for k in range(len(lugares)):
                x=lugares[k]
                y=corrs[j][x]
                if (k % 2 == 0):
                    plt.annotate('S1'+str(j+1), xy = (x, y), xytext = (x-3000, y+0.1),arrowprops=dict(facecolor='black', shrink=0.05))
                else:
                    plt.annotate('S1'+str(j+1), xy = (x, y), xytext = (x-3000, y-0.1),arrowprops=dict(facecolor='black', shrink=0.05))

    plt.legend()
        
    plt.figure()
    plt.title(files[i])
    plt.plot(emg)

    for j in range(7,len(corrfiles)):
        if str(j-6)=='3':
            umbral=0.62
        elif str(j-6)=='4':
            umbral=0.81
        elif str(j-6)=='6':
            umbral=0.745
        else:
            umbral=0.80
        
        longcorrs=len(corrs[j])
        lin=np.linspace(0,longcorrs-1,longcorrs)
        plt.plot(lin[corrs[j]>umbral],corrs[j][corrs[j]>umbral],ms=8,marker='o',label='temp 2'+str(j-6)+' umbral='+str(umbral),ls='None')
        lugares=consecutive(lin[corrs[j]>umbral])
        
        if lugares:
            for k in range(len(lugares)):
                x=lugares[k]
                y=corrs[j][x]
                if (k % 2 == 0):
                    plt.annotate('S2'+str(j-6), xy = (x, y), xytext = (x-3000, y+0.1),arrowprops=dict(facecolor='black', shrink=0.05))
                else:
                    plt.annotate('S2'+str(j-6), xy = (x, y), xytext = (x-3000, y-0.1),arrowprops=dict(facecolor='black', shrink=0.05))

    
    plt.legend()
    #plt.axhline(y=0.8,color='b',linewidth=2)

plt.show(block=True)