import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import glob



kwargs = {'color': 'r', 'linewidth': 4}
files=glob.glob('ZF*')
lugares=np.linspace(1000,125000,80,dtype=int)
umbral=0.998
for archivo in files:
    
    vs=np.loadtxt(archivo)
    plt.figure()
    for i in lugares:
        
        stdvs=np.std(vs[i:i+1000])
        plt.plot(([i,(i+1000)]),([stdvs,stdvs]),**kwargs)
    
    plt.plot(vs)
    plt.plot([], [], label='desviación standard vs', **kwargs)
    plt.legend()

    plt.title(archivo)




plt.show(block=True)