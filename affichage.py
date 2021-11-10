import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cbook
from matplotlib import cm
from matplotlib.animation import FuncAnimation
from matplotlib.colors import LightSource
from matplotlib import animation, rc
import math

concentration=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/gradientC.csv', delimiter = ' ', dtype = None)
trace=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/trace.csv', delimiter = ',', dtype = None)

x_robot=trace[:,0]
y_robot=trace[:,1]

longueur_tableau=int(len(concentration))

x=np.linspace(0,longueur_tableau,longueur_tableau)

plt.axes().set_aspect('equal')

plt.pcolormesh(x, x, concentration, shading = 'auto')






fig,ax=plt.subplots()

ax.set_xlim(0,longueur_tableau)
ax.set_ylim(0,longueur_tableau)

line,= ax.plot(0,0)

for i in range(len(x_robot)):
    plt.scatter(x_robot[i],y_robot[i])
    plt.pause(0.1)


#def animate(i):   
#    line.set_data(x_robot[i], y_robot[i])
#    return line,
 
#ani = animation.FuncAnimation(fig, animate, frames=10, blit=True, interval=200, repeat=False)

plt.show()




