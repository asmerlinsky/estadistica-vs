import numpy as np 
import matplotlib.pyplot as plt
import scipy.stats as stats
import matplotlib.gridspec as gridspec
import glob

files=glob.glob('ZF*')
lugares=np.linspace(1000,125000,80,dtype=int)
relcarchivo=np.zeros(len(files))
m=0
for archivo in files:
    vs=np.loadtxt(archivo)
    envolvente=np.loadtxt('envolvente.'+archivo+'.dat')
    
    print("el archivo es",archivo)
    plt.figure()
    plt.title(archivo)
    relacion=np.zeros(len(lugares))
    j=0
    for i in lugares:
        vsmedia=np.mean(np.abs(vs[i:i+2000]))
        plt.plot(([i,(i+2000)]),([vsmedia,vsmedia]),'r', linewidth=2)
        envmedia=np.mean(envolvente[i:i+2000])
        plt.plot(([i,(i+2000)]),([envmedia,envmedia]),'b',linewidth=2)
        relacion[j]=(envmedia/vsmedia)
        #print("envmedia/vsmedia=",relacion[j])
        j+=1
    
    relcarchivo[m]=np.mean(relacion)
    print("en promedio:",relcarchivo[m])
    m+=1
    plt.plot(vs,'c')
    plt.plot(envolvente) 

print("promediando sobre todos los archivos, la relacion es",np.mean(relcarchivo))

plt.show(block=True)