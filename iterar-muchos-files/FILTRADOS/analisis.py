import matplotlib.pyplot as plt
import numpy as np
import glob

#resultados=np.genfromtxt('resultados.dat',dtype=None)

try:
    labels = np.genfromtxt('resultados.dat', delimiter='\t', usecols=[2],dtype=None)
    values = np.loadtxt('resultados.dat', delimiter='\t', usecols=[0,1,3,4],dtype=None)

    for i in range(1,3):
        for j in range(1,8):
            if int(str(i)+str(j)) in values[:,2]:
                print("templado "+str(i)+str(j)+" correlacionó alguna vez")
            else:  
                print("templado "+str(i)+str(j)+" no correlacionó")
except:
    pass            

listacorr=glob.glob("corremg26*.dat")
print("la cantidad de corremg26 es",len(listacorr))
    
for i in range(0,len(listacorr)):
    print("nombre archivo", listacorr[i])
    a=np.loadtxt(listacorr[i])[:,1]
    for j in range(0,len(a)):
        if a[j]>0.745:
            print("tengo correlacion")
    #maximos[i]=np.max(a)
    #mediaabs[i]=np.mean(np.abs(a))

#print("máxima correlación con emg 26 es",np.max(maximos))
#print("correlacion media con emg 26 es",np.mean(mediaabs))

