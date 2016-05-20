import matplotlib.pyplot as plt
import numpy as np

vs=np.loadtxt('ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound')
absvs=np.abs(vs)
emg1=np.loadtxt('emg1.Sound')
#emg2=np.loadtxt('emg2.Sound')
absemg1=np.abs(emg1)
#absemg2=np.abs(emg2)
envemg1=np.loadtxt('envolvente.emg1.Sound.dat')
#envemg2=np.loadtxt('envolvente.emg2.Sound.dat')
hilbemg1=np.loadtxt('hilbert.emg1.Sound.dat')
#hilbemg2=np.loadtxt('hilbert.emg2.Sound.dat')
intemg1=np.loadtxt('integrado.emg1.Sound.dat')
#intemg2=np.loadtxt('integrado.emg2.Sound.dat')

hilbemg1=hilbemg1/np.max(hilbemg1)
#hilbemg2=hilbemg2/np.max(hilbemg2)

intemg1=intemg1/np.max(intemg1)
#intemg2=intemg2/np.max(intemg2)

envemg1=envemg1/np.max(envemg1)
#envemg2=envemg2/np.max(envemg2)

emg1=emg1/np.max(emg1)
#emg2=emg2/np.max(emg2)

absemg1=absemg1/np.max(absemg1)
#absemg2=absemg2/np.max(absemg2)



plt.figure()
plt.title('abs vs')
#plt.xlim(0,len(envolvente))
plt.plot(absvs,label='absvs')
plt.legend()


plt.figure()
plt.title('emg1 todos')
plt.plot(absemg1,label='absemg1')
plt.plot(envemg1,label='envemg1')
plt.plot(hilbemg1,label='hilbemg1')
plt.plot(intemg1,label='intemg1')
plt.legend()

#plt.figure()
#plt.title('emg2 todos')
#plt.plot(absemg2,label='absemg2')
#plt.plot(envemg2,label='envemg2')
#plt.plot(hilbemg2,label='hilbemg2')
#plt.plot(intemg2,label='intemg2')
#plt.legend()

plt.figure()
plt.title('hilb emgs')
plt.plot(hilbemg1,label='hilbemg1')
#plt.plot(hilbemg2,label='hilbemg2')
plt.plot(absemg1,label='absemg1')
#plt.plot(absemg2,label='absemg2')
plt.legend()

plt.figure()
plt.title('int emgs')
plt.plot(intemg1,label='intemg1')
#plt.plot(intemg2,label='intemg2')
plt.plot(absemg1,label='absemg1')
#plt.plot(absemg2,label='absemg2')
plt.legend()

plt.figure()
plt.title('env emgs')
plt.plot(envemg1,label='envemg1')
#plt.plot(envemg2,label='envemg2')
plt.plot(absemg1,label='absemg1')
#plt.plot(absemg2,label='absemg2')
plt.legend()

plt.figure()
plt.title('abs emgs')
plt.plot(absemg1,label='absemg1')
#plt.plot(absemg2,label='absemg2')
plt.legend()

plt.figure()
plt.title('vs')
#plt.xlim(0,len(envolvente))
plt.plot(vs,label='vs')
plt.legend()

plt.figure()
plt.title('emgs')
plt.plot(emg1,label='emg1')
#plt.plot(emg2,label='emg1')
plt.legend()

plt.show(block=True)



