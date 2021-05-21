import matplotlib.pyplot as plt
import matplotlib.mlab as mlab

i=0
f = open("Delay.csv", "r")
HIS_SIZE = f.readline()

i = len(HIS_SIZE)

x=15
mult = 100
SIZE = 0
while x < i :
    print(HIS_SIZE[x])
    if HIS_SIZE[x] == '\n':
        break
    SIZE= SIZE + mult*int(HIS_SIZE[x])
    mult = mult/10
    x += 1
print(SIZE)

print(f.readline())
print(f.readline())
lines = f.readlines()


tableline= []

tablelen= 0
for line in lines:
    tableline.append(line.split('\t',2))
    
tablelen = len(tableline)
print(tableline)

j=0
call=[]
value= []
while j < tablelen:
    call.append(tableline[j][0])
    value.append(tableline[j][1])
    j+= 1
print(call)
print(value)

k=0
while k < tablelen:
    value[k] =value[k].rstrip('\n')
    k+=1
print(value)
print(call)

m=0 
while m < len(call):
    call[m] = int(call[m])
    value[m] = float(value[m])
    m+=1

print(call)
print(value)

num_bins = 100
# the histogram of the data
n, bins, patches = plt.hist(value, num_bins,density=True, facecolor='blue', alpha=0.5)
plt.show()