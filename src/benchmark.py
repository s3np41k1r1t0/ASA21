import matplotlib.pyplot as plt

with open("report/benchmarks","r") as f:
    data = f.read().strip().split("\n")
    
x = []
y = [] 
for a,b,time in map(lambda x: x.split(),data):
    x.append(int(a)+int(b))
    y.append(float(time))

plt.plot(x,y)
plt.legend(["Solução"])
plt.xlabel("V+E")
plt.ylabel("Tempo (s)")
plt.show()
