import matplotlib.pyplot as plt
import numpy as np

corremg3=np.loadtxt('corremg3.ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound.dat')
vs=np.loadtxt('ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound')
absemg3=np.abs(np.loadtxt('emg3.Sound'))
envemg3=np.loadtxt('envolvente.emg3.Sound.dat')
envvs=np.loadtxt('envolvente.ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound.dat')

absemg3=absemg3/np.max(absemg3)
envemg3=envemg3/np.max(envemg3)
absvs=np.abs(vs)
envvs=envvs/np.max(envvs)
vs=vs/np.max(vs)
absvs=absvs/np.max(absvs)

m='4'
tau='0.006'

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs,label='señal')
plt.plot(envvs,'r',label='envolvente',linewidth=2)
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs,label='señal')
plt.plot(corremg3[:,1],'r',label='correlacion3')
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absemg3,label='abs emg3')
plt.plot(envemg3,'r',label='envolvente emg3',linewidth=2)
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(envvs,label='envolvente señal')
plt.plot(corremg3[:,1],'r',label='correlacion')
plt.legend()

plt.show(block=True)
