import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import glob
import matplotlib.gridspec as gridspec

files=glob.glob('ZF*')
vs=[]
lugares=np.linspace(1000,110000,3,dtype=int)
j=0

gs = gridspec.GridSpec(18, 18)
a=[gs[0:8, 0:8]]
a.append(gs[10:12, 0:8])
a.append(gs[12:18, 0:8])
a.append(gs[0:2, 10:18])
a.append(gs[2:8, 10:18])
a.append(gs[10:12, 10:18])
a.append(gs[12:18, 10:18])


for archivo in files:
    n=0
    vs.append(np.loadtxt(archivo))
    
    
    plt.figure()
    ax=plt.subplot(a[n])
    n+=1      
    ax.plot(vs[j])
    
    
    
    for i in lugares:
        ax.axvline(x=i,color='g',linewidth=2)
        ax.axvline(x=i+4000,color='g',linewidth=2)
        
    
    for i in lugares:
        ax=plt.subplot(a[n])
        n+=1      
        ax.plot(vs[j][i:i+4000])
        ax.set_xticks([]) 
        ax.set_yticks([])
        
        ax=plt.subplot(a[n])
        n+=1
        stats.probplot(vs[j][i:i+4000], dist="norm", plot=ax)
        
    print("figura", j+1, "es", archivo)
    j+=1
    
    

plt.show(block=True)
