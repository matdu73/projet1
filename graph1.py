import numpy as np
import matplotlib.pyplot as plt

donnee = np.genfromtxt('lol.csv', delimiter = ',')
donnee=np.reshape(donnee[0,], (-1,6))
print(donnee)
#x = np.arange(0, donnee.shape[1] + 1) * 0.2
#y = 5 - np.arange(0, donnee.shape[0] + 1) * 0.2

#plt.axes().set_aspect('equal')
#plt.title('donnees')
#plt.pcolormesh(x, y, donnee)
#plt.show()
