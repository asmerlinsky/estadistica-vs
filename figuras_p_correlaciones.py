import matplotlib.pyplot as plt
import numpy as np
import sys
corremg6=np.loadtxt('corremg6.ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound.dat')
vs=np.loadtxt('ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound')
absemg6=np.abs(np.loadtxt('emg6.Sound'))
envemg6=np.loadtxt('envolvente.emg6.Sound.dat')
envvs=np.loadtxt('envolvente.ZF-MCV_2015-12-03_07_10_22_vs_5_band.Sound.dat')

absemg6=absemg6/np.max(absemg6)
envemg6=envemg6/np.max(envemg6)
absvs=np.abs(vs)
envvs=envvs/np.max(envvs)
vs=vs/np.max(vs)
absvs=absvs/np.max(absvs)
tau="{:.4f}".format(float(sys.argv[1])/1500) 
m=sys.argv[2]
#m='4'
#tau='0.006'

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs,label='señal')
plt.plot(envvs,'r',label='envolvente',linewidth=2)
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs,label='señal')
plt.plot(corremg6[:,1],'r',label='correlacion6')
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absemg6,label='abs emg6')
plt.plot(envemg6,'r',label='envolvente emg6',linewidth=2)
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(envvs,label='envolvente señal')
plt.plot(corremg6[:,1],'r',label='correlacion')
plt.legend()

plt.show(block=True)
