import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import glob
import matplotlib.gridspec as gridspec

files=glob.glob('ZF*')
vs=[]
envvs=[]
lugares=np.linspace(8000,120000,3,dtype=int)
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
    envvs.append(np.loadtxt('envolvente.'+archivo+'.dat'))
    envvs[j]/=np.max(envvs[j])
    plt.figure()
    ax=plt.subplot(a[n])
      
    ax.plot(vs[j])
    ax.plot(envvs[j])
            
    
    for i in lugares:
        mediaenv=np.mean(envvs[j][i:i+2000])
        ax.plot(([i,i+2000]),([mediaenv,mediaenv]),label=str(mediaenv))
        ax.axvline(x=i,color='g',linewidth=2)
        ax.axvline(x=i+2000,color='g',linewidth=2)
    
    ax.legend()
    
    for i in lugares:
        n+=1  
        ax=plt.subplot(a[n])
            
        ax.plot(vs[j][i:i+2000])
        ax.set_xticks([]) 
        ax.set_yticks([])
        n+=1
        ax=plt.subplot(a[n])
        
        stats.probplot(vs[j][i:i+2000], dist="norm", plot=ax)
        
    print("figura", j+1, "es", archivo)
    j+=1
    
    

plt.show(block=True)
