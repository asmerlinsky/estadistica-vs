import matplotlib.pyplot as plt
import numpy as np


absvs=np.abs(np.loadtxt('ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound'))
hilbert=np.loadtxt('hilbert.vscomp.dat')
envolvente=np.loadtxt('envolventesenal.dat')
convolucion=np.loadtxt('convolucionemg1.dat')
senalpostrk4=np.loadtxt('senalpostrk4.dat')
hilbert=hilbert/np.max(hilbert)
envolvente=envolvente/np.max(envolvente)
convolucion=convolucion/np.max(convolucion)
senalpostrk4=senalpostrk4/np.max(senalpostrk4)

hilbertemg1=np.loadtxt('hilbert.emg1.dat')
emg1postrk4=np.loadtxt('emg1postrk4.dat')
envolventeemg1=np.loadtxt('envolventeemg1.dat')
convolucion=np.loadtxt('convolucionemg1.dat')
hilbert=hilbert/np.max(hilbert)
envolvente=envolvente/np.max(envolvente)
convolucion=convolucion/np.max(convolucion)
senalpostrk4=senalpostrk4/np.max(senalpostrk4)
plt.figure(1)
#plt.xlim(0,len(envolvente))
plt.plot(absvs)
plt.plot(hilbert,'r')
plt.plot(envolvente,'g')

plt.figure(2)
plt.plot(absvs)
plt.plot(convolucion,'r')
plt.show(block=True)


