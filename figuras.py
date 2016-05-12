import matplotlib.pyplot as plt
import numpy as np


absvs=np.abs(np.loadtxt('ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound'))
hilbert=np.loadtxt('hilbert.sueno.dat')
envolvente=np.loadtxt('envolvente.ZF-MCV_2015-12-01_13_13_49_vs_29_band.dat')
senalpostrk4=np.loadtxt('rk4.dat')


plt.figure(1)
#plt.xlim(0,len(envolvente))
plt.plot(absvs)
plt.plot(hilbert,'r')

plt.figure(2)
plt.plot(hilbert)


plt.figure(3)
#plt.xlim(0,len(envolvente))
plt.plot(senalpostrk4)

plt.figure(4)
plt.plot(envolvente)
plt.show(block=True)
