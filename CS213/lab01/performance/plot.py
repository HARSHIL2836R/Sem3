import matplotlib.pyplot as plt
X = [2,2*64,2*64*64,2*64*64*64,2*64*64*64*64]
for i in range(4):
    f = open("ga"+str(i)+".txt","r")
    Y = f.readlines()
    Y = [float(y.strip('\n')) for y in Y]

    plt.plot(X,Y,label = "Compilation level "+str(i))
    print(X)
    print(Y)

plt.legend()
plt.show()