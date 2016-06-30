import matplotlib.pyplot as plt
import numpy as np
import glob

resultados=np.genfromtxt('resultados.dat',names=True,dtype=[('f0', '<i4'), ('f1', '<f8'), ('f2', 'S100'),('f3', 'S20'), ('f4', '<i4')])
listaarchivos=np.unique(resultados['2'])
templados=np.unique(resultados['3'])
dicttemp=dict.fromkeys(templados.tolist(),0)
dicttemparch=dict.fromkeys(templados.tolist(),0)
dictumbral=dict.fromkeys(templados.tolist(),0)

##MODIFICAR SEGUN CRITERIO
dictumbral[b'2-1']= 0.8
dictumbral[b'2-2']= 0.8
dictumbral[b'2-3']= 0.8
dictumbral[b'2-4']= 0.8
dictumbral[b'2-45']= 0.85
dictumbral[b'2-5']= 0.8
dictumbral[b'2-56']= 0.7
dictumbral[b'2-6']= 0.71
dictumbral[b'2-67']= 0.8
dictumbral[b'2-7']= 0.7
dictumbral[b'2-A']= 0.75
dictumbral[b'2-B']= 0.8
dictumbral[b'2-B5']= 0.7

print("hay {} archivos \n",len(listaarchivos))
print("cargado ok. Paso a buscar resultados\n")

for archivo in listaarchivos:
    for key,values in dicttemp.items():
        try:
            dicttemp[key]+=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==key))][-1]
            dicttemparch[key]=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==key))][-1]
        except:
            dicttemparch[key]=0
            



dicttemp_string = dict([(k.decode("utf-8"), v) for k, v in dicttemp.items()])
valores=[dicttemp_string[key] for key in sorted(dicttemp_string.keys())]

plt.figure()
plt.bar(range(len(dicttemp_string)), valores, align='center')
plt.title('Resultados con umbrales bajos')
plt.xticks(range(len(dicttemp_string)), sorted(dicttemp_string.keys()))

print("primer grafico listo \n")






plt.show(block=True)

          
