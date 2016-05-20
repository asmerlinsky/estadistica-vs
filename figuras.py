import matplotlib.pyplot as plt
import numpy as np


absvs=np.abs(np.loadtxt('ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound'))
emg1=np.loadtxt('emg1.Sound')
emg2=np.loadtxt('emg2.Sound')
envemg1=np.loadtxt('envolvente.emg1.Sound.dat')
envemg2=np.loadtxt('envolvente.emg2.Sound.dat')

envemg1=envemg1/np.max(envemg1)
envemg2=envemg2/np.max(envemg2)
emg1=emg1/np.max(emg1)
emg2=emg2/np.max(emg2)




plt.figure(1)
#plt.xlim(0,len(envolvente))
plt.plot(absvs)

plt.figure(2)
plt.plot(emg1)
plt.plot(envemg1)

plt.figure(3)
#plt.xlim(0,len(envolvente))
plt.plot(emg2)
plt.plot(envemg2)

plt.figure(4)
plt.plot(emg1)
plt.plot(emg2)
plt.show(block=True)
