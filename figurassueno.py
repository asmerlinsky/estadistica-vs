import matplotlib.pyplot as plt
import numpy as np



vs=np.loadtxt('ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound')
absvs=np.abs(vs)
intvs=np.loadtxt('int.sueno.dat')
envvs=np.loadtxt('envolvente.ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound.dat')
hilbvs=np.loadtxt('hilbert.sueno.dat')
corremg1=np.loadtxt('corremg36.ZF-MCV_2015-12-01_13_13_49_vs_29_band.Sound.dat')

hilbvs=hilbvs/np.max(hilbvs)

intvs=intvs/np.max(intvs)

envvs=envvs/np.max(envvs)

vs=vs/np.max(vs)

absvs=absvs/np.max(absvs)

corremg1=corremg1/np.max(corremg1)


plt.figure()
#plt.xlim(0,len(envolvente))
plt.plot(absvs)
plt.plot(hilbvs)

plt.figure()
plt.plot(absvs)
plt.plot(envvs)

plt.figure()
#plt.xlim(0,len(envolvente))
plt.plot(absvs)
plt.plot(intvs)

plt.figure()
plt.plot(absvs)
plt.plot(envvs)

plt.figure()
plt.plot(absvs)
plt.plot(corremg1)
plt.show(block=True)
