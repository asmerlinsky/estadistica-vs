import matplotlib.pyplot as plt
import numpy as np
import glob

files=glob.glob('ZF*.Sound')
for i in range(0,len(files)):
    print("cargo todo lo relacionado con", files[i])

    corrfiles=glob.glob('corremg'+'*'+files[i]+'.dat')
    #cargo corrfiles
    corrs=[np.loadtxt(corrfiles[0])[:,1]]

    for j in range(1,len(corrfiles)):
        corrs.append(np.loadtxt(corrfiles[j])[:,1])
        
    emg=np.loadtxt(files[i])
    emg/=np.max(np.abs(emg))
    plt.figure()
    plt.title(files[i])
    plt.plot(emg)
    for j in range(0,7):
        if (str(j+1)=='3'):
            umbral='0.58'
        elif (str(j+1)=='6'):
            umbral='0.65'
        else:
            umbral='0.80'
            
        plt.plot(corrs[j],linewidth=2,label='temp 1'+str(j+1)+' umbral='+umbral)

    plt.legend()
        
    plt.figure()
    plt.title(files[i])
    plt.plot(emg)

    for j in range(7,len(corrfiles)):
        if str(j-6)=='3':
            umbral='0.62'
        elif str(j-6)=='4':
            umbral='0.81'
        elif str(j-6)=='6':
            umbral='0.745'
        else:
            umbral='0.80'
        plt.plot(corrs[j],linewidth=2,label='temp 2'+str(j-6)+' umbral='+umbral)
        plt.legend()
    

plt.show(block=True)