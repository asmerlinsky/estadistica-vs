import matplotlib.pyplot as plt
import numpy as np
import glob

#resultados=np.genfromtxt('resultados.dat',dtype=None)


labels = np.genfromtxt('resultados.dat', delimiter='\t', usecols=[2],dtype=None)
values = np.loadtxt('resultados.dat', delimiter='\t', usecols=[0,1,3,4])

for i in range(1,3):
    for j in range(1,8):
       if int(str(i)+str(j)) in values[:,2]:
           print("templado "+str(i)+str(j)+" correlacionó alguna vez")
       else:  
           print("templado "+str(i)+str(j)+" no correlacionó")
            

#listacorr=glob.glob("corremg26*.Sound.dat")
#print("la cantidad de corremg26 es",len(listacorr))
#maximos=np.zeros(len(listacorr))
#mediaabs=np.zeros(len(listacorr))
#for i in range(0,len(listacorr)):
#    a=np.loadtxt(listacorr[i])[:,1]
#    maximos[i]=np.max(a)
#    mediaabs[i]=np.mean(np.abs(a))
#
#print("máxima correlación con emg 26 es",np.max(maximos))
#print("correlacion media con emg 26 es",np.mean(mediaabs))

j=0
a=np.unique(labels
for i in range(0,len(labels)):
    
