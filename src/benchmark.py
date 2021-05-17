import matplotlib.pyplot as plt

#with open("report/benchmarks","r") as f:
#    data = f.read().strip().split("\n")
#    
#x = []
#y = [] 
#for a,b,time in map(lambda x: x.split(),data):
#    x.append(int(a)+int(b))
#    y.append(float(time))

x = [4000+1000, 5000+1000,  6000+1000,  7000+1000,  8000+1000,  9000+1000,  10000+1000]
y = [1.037,     1.717,      2.545,      3.776,      4.296,      5.621,      6.855]

plt.plot(x,y)
plt.legend(["Solução"])
plt.xlabel("V+E")
plt.ylabel("Tempo (s)")
plt.show()
