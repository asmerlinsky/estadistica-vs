import matplotlib.pyplot as plt
import numpy as np
import glob

resultados=np.genfromtxt('resultados.dat',names=True,dtype=[('f0', '<i4'), ('f1', '<f8'), ('f2', 'S100'),('f3', '<i4'), ('f4', '<i4')])
#labels = np.genfromtxt('resultados.dat', delimiter='\t', usecols=[2],dtype=None)

#values = np.loadtxt('resultados.dat', delimiter='\t', usecols=[0,1,3,4],dtype=None)
# bincan=np.bincount(resultados['3'])#para esto tengo que numerar las columnas de resultados.dat

# plt.figure()
# plt.title()
# plt.hist(resultados['3'],range=(11,27),bins=(27-11))
listaarchivos=np.unique(resultados['2'])
silabas=np.unique(resultados['3'])
ccporarch1=np.zeros(len(silabas))
ccporarch2=np.zeros(len(silabas))
cctot=np.zeros(len(silabas))#cctot=np.zeros(shape=(len(silabas),2))
masdeunasilabaC1=0
masdeunasilabaC2=0
#Tomo el ultimo elemento que tiene cierto nombre y cierta silaba
for archivo in listaarchivos:#itero por archivos
    for j in range(0,len(silabas)):#itero por silabas
        try: #tomo la cantitad de correlaciones que da el ultimo elemento que tenga el mismo del archivo y la silaba        
            cctot[j]+=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==silabas[j]))][-1]
            
            if j<(len(silabas)+1)/2: #guardo la cantidad por archivo acá para ver en cuales ví más de una sílaba
                ccporarch1[j]=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==silabas[j]))][-1]
            else:
                ccporarch2[j]=resultados['4'][np.logical_and((resultados['2']==archivo),(resultados['3']==silabas[j]))][-1]
              
            
        except:
            ccporarch1[j]=0
            ccporarch2[j]=0
        
    
    cantc1=np.nonzero(ccporarch1)[0].size
    cantc2=np.nonzero(ccporarch2)[0].size
    
    if  ( (cantc1>1) and (cantc2<2) ):
        print('El archivo {} correlaciona con {} silabas C1'.format(archivo,cantc1))
        masdeunasilabaC1+=1
    elif ( (cantc2>1) and (cantc1<2) ):
        print('El archivo {} correlaciona con {} silabas C2'.format(archivo,cantc2))
        masdeunasilabaC2+=1
    elif ( (cantc1>1) and (cantc2>1) ):
        print('El archivo {} correlaciona con {} C1 y {} C2'.format(archivo,cantc1,cantc2))
        masdeunasilabaC1+=1
        masdeunasilabaC2+=1
    
    
print('Tengo {} de {} archivos que correlacionan con mas de una silaba de criterio 1'.format(masdeunasilabaC1,len(listaarchivos)))

print('Tengo {} de {} archivos que correlacionan con mas de una silaba de criterio 2'.format(masdeunasilabaC2,len(listaarchivos)))

plt.figure()
plt.ylabel('cantidad de correlaciones')
plt.xlabel('silabas')
plt.bar(silabas,cctot,align='center')

plt.show(block=True)
