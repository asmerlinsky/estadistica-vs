##ingresar por linea de comando cantidad de templados a graficar

import matplotlib.pyplot as plt
import numpy as np
import sys

#cargo la señal, y los archivos correspondientes al primer templado y los normalizo
criterio=sys.argv[1]
canttemp=int(sys.argv[2])
vs=np.loadtxt('ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound')
absvs=np.abs(vs)
emg=[np.loadtxt('emg'+criterio+'1.Sound')]
envemg=[np.loadtxt('envolvente.emg'+criterio+'1.Sound.dat')]
envemg[0]=envemg[0]/np.max(envemg[0])
absemg=[np.abs(emg[0])]
absmax=np.max(absemg[0])
absemg[0]=absemg[0]/absmax
emg[0]=emg[0]/absmax


for i in range(1,canttemp): #cargo todos los demas y los normalizo
    print('cargo:'+'emg'+criterio+str(i+1)+'.Sound')
    emg.append(np.loadtxt('emg'+criterio+str(i+1)+'.Sound'))
    envemg.append(np.loadtxt('envolvente.emg'+criterio+str(i+1)+'.Sound.dat'))
    absemg.append(np.abs(emg[i]))
    absmax=np.max(absemg[i])
    absemg[i]=absemg[i]/absmax
    emg[i]=emg[i]/absmax
    envemg[i]=envemg[i]/np.max(envemg[i])

print('largo emg=\n',len(emg[0]))
print('largo envolvente=\n',len(envemg[0]))

for i in range(0,len(emg)): #grafico el abs de los templados y su envolvente
    plt.figure()
    plt.title('emg'+criterio+str(i+1))
    plt.plot(emg[i],label='absemg')
    plt.plot(envemg[i],'r',label='envolvente',linewidth=2)
    plt.legend()


plt.show(block=True)

