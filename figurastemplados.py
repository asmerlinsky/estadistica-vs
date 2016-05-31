##ingresar por linea de comando cantidad de templados a graficar

import matplotlib.pyplot as plt
import numpy as np
import sys

#cargo la señal, y los archivos correspondientes al primer templado y los normalizo
canttemp=int(sys.argv[1])
vs=np.loadtxt('ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound')
absvs=np.abs(vs)
emg=[np.loadtxt('emg1.Sound')]
envemg=[np.loadtxt('envolvente.emg1.Sound.dat')]
envemg[0]=envemg[0]/np.max(envemg[0])
absemg=[np.abs(emg[0])]
absmax=np.max(absemg[0])
absemg[0]=absemg[0]/absmax
emg[0]=emg[0]/absmax
hilbemg=[np.loadtxt('hilbert.emg1.Sound.dat')]
hilbemg[0]=hilbemg[0]/np.max(hilbemg[0])
intemg=[np.loadtxt('integrado.emg1.Sound.dat')]
intemg[0]=intemg[0]/np.max(intemg[0])



for i in range(1,canttemp): #cargo todos los demas y los normalizo
	emg.append(np.loadtxt('emg'+str(i+1)+'.Sound'))
	envemg.append(np.loadtxt('envolvente.emg'+str(i+1)+'.Sound.dat'))
	hilbemg.append(np.loadtxt('hilbert.emg'+str(i+1)+'.Sound.dat'))
	intemg.append(np.loadtxt('integrado.emg'+str(i+1)+'.Sound.dat'))
	absemg.append(np.abs(emg[i]))
	absmax=np.max(absemg[i])
	absemg[i]=absemg[i]/absmax
	emg[i]=emg[i]/absmax
	envemg[i]=envemg[i]/np.max(envemg[i])
	hilbemg[i]=hilbemg[i]/np.max(hilbemg[i])
	intemg[i]=intemg[i]/np.max(intemg[i])


for i in range(0,len(emg)): #grafico el abs de los templados y su envolvente
	plt.figure()
	plt.title('absemg'+str(i+1))
	plt.plot(absemg[i][0:len(envemg[i])],label='absemg')
	plt.plot(envemg[i],'r',label='envolvente',linewidth=2)
	plt.legend()

fig = plt.figure() #grafico en una sola ventana los hilberts
fig.suptitle("Hilberts", fontsize=16)
for i in range(0,len(emg)): 
	ax = plt.subplot(str(len(emg))+"1"+str(i+1))
	ax.set_title("hilbemg"+str(i+1))
	ax.plot(hilbemg[i])
	
fig = plt.figure() #grafico en una sola ventana los integrados de la señal
fig.suptitle("Integrados", fontsize=16)
for i in range(0,len(emg)):
	ax = plt.subplot(str(len(emg))+"1"+str(i+1))
	ax.set_title("intemg"+str(i+1))
	ax.plot(intemg[i])
	
fig = plt.figure() #grafico en una sola ventana las señales sin procesar
fig.suptitle("señal", fontsize=16)
for i in range(0,len(emg)):
	ax = plt.subplot(str(len(emg))+"1"+str(i+1))
	ax.set_title("emg"+str(i+1))
	ax.plot(emg[i][0:len(envemg[i])])

plt.show(block=True)

