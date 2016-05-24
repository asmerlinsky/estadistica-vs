import matplotlib.pyplot as plt
import numpy as np

corremg1=np.loadtxt('corremg1.ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound.dat')
vs=np.loadtxt('ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound')
absemg1=np.abs(np.loadtxt('emg1.Sound'))
envemg1=np.loadtxt('envolvente.emg1.Sound.dat')
envvs=np.loadtxt('envolvente.ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound.dat')
absemg1=absemg1/np.max(absemg1)
envemg1=envemg1/np.max(envemg1)

absvs=np.abs(vs)
envvs=envvs/np.max(envvs)
vs=vs/np.max(vs)
absvs=absvs/np.max(absvs)

m='3'
tau='0.0003'

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs[0:(len(vs)-1)/2],label='señal')
plt.plot(envvs,'r',label='envolvente')
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs[0:(len(vs)-1)/2],label='señal')
plt.plot(corremg1[:,0],'r',label='correlacion')
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absemg1[0:(len(absemg1)-1)/2],label='abs emg1')
plt.plot(envemg1,'r',label='envolvente emg1')
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(envvs[0:(len(vs)-1)/2],label='envolvente señal')
plt.plot(corremg1[:,0],'r',label='correlacion')
plt.legend()

plt.show(block=True)
