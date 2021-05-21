import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

i=0
f = open("sensibilidadea.txt", "r")
f.readline()

lines = f.readlines()
print(lines)

tableline = []
for line in lines:
    tableline.append(line.split(' ',1))
    
tablelen = len(tableline)
print(tableline)

j=0
lambdas=[]
atraso= []
while j < tablelen:
    lambdas.append(tableline[j][0])
    atraso.append(tableline[j][1])
    j+= 1
print(lambdas)
print(atraso)

k=0
while k < tablelen:
    atraso[k] =atraso[k].rstrip('\n')
    k+=1

print(atraso)

m=0 
while m < len(lambdas):
    lambdas[m] = int(lambdas[m])
    atraso[m] = float(atraso[m])
    m+=1

print(lambdas)
print(atraso)


plt.plot( lambdas, atraso, 'r^') # red triangulo
plt.plot( lambdas, atraso, 'k--', color='blue')  # linha tracejada azul

plt.title("Sensibilidade")

plt.grid(True)
plt.xlabel("Valor de lambda")
plt.ylabel("Atraso")
plt.show()