import matplotlib.pyplot as plt
file = open("time.txt", "r")
data = file.read().split("\n")
plt.plot([i+1 for i in range(len(data))],data)
plt.show()