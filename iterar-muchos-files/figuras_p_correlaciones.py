import matplotlib.pyplot as plt
import numpy as np
import sys
corremg7=np.loadtxt('corremg7.ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound.dat')
vs=np.loadtxt('ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound')
absemg7=np.abs(np.loadtxt('emg7.Sound'))
envemg7=np.loadtxt('envolvente.emg7.Sound.dat')
envvs=np.loadtxt('envolvente.ZF-MCV_2015-12-04_06_51_28_vs_19_band.Sound.dat')

absemg7=absemg7/np.max(absemg7)
envemg7=envemg7/np.max(envemg7)
absvs=np.abs(vs)
envvs=envvs/np.max(envvs)
vs=vs/np.max(vs)
absvs=absvs/np.max(absvs)
tau="{:.5f}".format(float(sys.argv[1])/1500) 
m=sys.argv[2]
#m='4'
#tau='0.006'

#plt.figure()
#plt.title('Tau='+tau+', m='+m)
#plt.plot(absvs,label='señal')
#plt.plot(envvs,'r',label='envolvente',linewidth=2)
#plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absvs,label='señal')
plt.plot(corremg7[:,1],'r',label='correlacion7')
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(absemg7[0:len(envemg7)],label='abs emg7')
plt.plot(envemg7,'r',label='envolvente emg7',linewidth=2)
plt.legend()

plt.figure()
plt.title('Tau='+tau+', m='+m)
plt.plot(envvs,label='envolvente señal')
plt.plot(corremg7[:,1],'r',label='correlacion')
plt.legend()

plt.show(block=True)
