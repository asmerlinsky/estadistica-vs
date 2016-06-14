##ingresar por linea de comando cantidad de templados a graficar

import matplotlib.pyplot as plt
import numpy as np
import sys
import glob

#cargo la señal, y los archivos correspondientes al primer templado y los normalizo
templados=glob.glob('emg*.Sound')
vs=np.loadtxt('ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound')
absvs=np.abs(vs)
emg=[np.loadtxt(templados[0])]
envemg=[np.loadtxt('envolvente.'+templados[0]+'.dat')]
envemg[0]=envemg[0]/np.max(envemg[0])
absemg=[np.abs(emg[0])]
absmax=np.max(absemg[0])
absemg[0]=absemg[0]/absmax
emg[0]=emg[0]/absmax
hilbemg=[np.loadtxt('hilbert.'+templados[0]+'.dat')]
hilbemg[0]=hilbemg[0]/np.max(hilbemg[0])
intemg=[np.loadtxt('integrado.'+templados[0]+'.dat')]
intemg[0]=intemg[0]/np.max(intemg[0])



for i in range(1,len(templados)): #cargo todos los demas y los normalizo
    print('cargo:',templados[i])
    emg.append(np.loadtxt(templados[i]))
    envemg.append(np.loadtxt('envolvente.'+templados[i]+'.dat'))
    hilbemg.append(np.loadtxt('hilbert.'+templados[i]+'.dat'))
    intemg.append(np.loadtxt('integrado.'+templados[i]+'.dat'))
    absemg.append(np.abs(emg[i]))
    absmax=np.max(absemg[i])
    absemg[i]=absemg[i]/absmax
    emg[i]=emg[i]/absmax
    envemg[i]=envemg[i]/np.max(envemg[i])
    hilbemg[i]=hilbemg[i]/np.max(hilbemg[i])
    intemg[i]=intemg[i]/np.max(intemg[i])


print('largo emg=\n',len(emg[0]))
print('largo envolvente=\n',len(envemg[0]))
print('largo hilbert=\n',len(hilbemg[0]))
print('largo integrado=\n',len(intemg[0]))
for i in range(0,len(emg)): #grafico el abs de los templados y su envolvente
    plt.figure()
    plt.title(templados[i])
    plt.plot(emg[i],label='absemg')
    plt.plot(envemg[i],'r',label='envolvente',linewidth=2)
    plt.legend()

# fig = plt.figure() #grafico en una sola ventana los hilberts
# fig.suptitle("Hilberts", fontsize=16)
# for i in range(0,len(emg)): 
    # ax = plt.subplot(str(len(emg))+"1"+str(i+1))
    # ax.set_title("hilbemg"+str(i+1))
    # ax.plot(hilbemg[i])
    
# fig = plt.figure() #grafico en una sola ventana los integrados de la señal
# fig.suptitle("Integrados", fontsize=16)
# for i in range(0,len(emg)):
    # ax = plt.subplot(str(len(emg))+"1"+str(i+1))
    # ax.set_title("intemg"+str(i+1))
    # ax.plot(intemg[i])
    
# fig = plt.figure() #grafico en una sola ventana las señales sin procesar
# fig.suptitle("señal", fontsize=16)
# for i in range(0,len(emg)):
    # ax = plt.subplot(str(len(emg))+"1"+str(i+1))
    # ax.set_title("emg"+str(i+1))
    # ax.plot(emg[i][0:len(envemg[i])])

plt.show(block=True)

