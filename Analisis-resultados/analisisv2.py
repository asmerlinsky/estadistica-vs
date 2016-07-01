import matplotlib.pyplot as plt
import numpy as np
import glob

resultados=np.genfromtxt('resultados.dat',names=True,dtype=[('f0', '<i4'), ('f1', '<f8'), ('f2', 'S100'),('f3', 'S20'), ('f4', '<i4')])
#labels = np.genfromtxt('resultados.dat', delimiter='\t', usecols=[2],dtype=None)

#values = np.loadtxt('resultados.dat', delimiter='\t', usecols=[0,1,3,4],dtype=None)
# bincan=np.bincount(resultados['3'])#para esto tengo que numerar las columnas de resultados.dat

# plt.figure()
# plt.title()
# plt.hist(resultados['3'],range=(11,27),bins=(27-11))
listaarchivos=np.unique(resultados['2'])
templados=np.unique(resultados['3'])
dicttemp=dict.fromkeys(templados.tolist(),0)
dicttemparch=dict.fromkeys(templados.tolist(),0)


for archivo in listaarchivos:
    for key,values in dicttemp.items():
        try:
            dicttemp[key]+=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==key))][-1]
            dicttemparch[key]=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==key))][-1]
        except:
            dicttemparch[key]=0
            

    cantsil=sum(1 for keys in dicttemparch if dicttemparch[keys]!=0)
        
    print('El archivo {} correlaciona con {} templados '.format(archivo,cantsil))

dicttemp_string = dict([(k.decode("utf-8"), v) for k, v in dicttemp.items()])
valores=[dicttemp_string[key] for key in sorted(dicttemp_string.keys())]

plt.bar(range(len(dicttemp_string)), valores, align='center')
plt.xticks(range(len(dicttemp_string)), sorted(dicttemp_string.keys()))


plt.show(block=True)
