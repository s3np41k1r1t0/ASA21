import matplotlib.pyplot as plt

# with open("times.benchmark","r") as f:
#     data = f.read().split("\n")
    
# x = []
# y = [] 
# for size, time in map(lambda x: x.split(),data):
#     x.append(float(size))
#     y.append(float(time))

# too lazy lol
x = [2,1000+349560,2000+1398226,3000+3149015,4000+5597757,5000+8748142,6000+12596349,7000+17147865,8000+22398701,9000+28344022,10000+34995343]
y = [0.001,0.05,0.183,0.407,0.726,1.135,1.650,2.263,2.952,3.765,4.665]

plt.plot(x,y)
plt.legend(["Solução"])
plt.xlabel("V+E")
plt.ylabel("Tempo (s)")
plt.show()