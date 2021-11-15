import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cbook
from matplotlib.colors import LightSource
from matplotlib import cm, animation
import math


fig=plt.figure()

gradient_concentration=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/gradientC.csv', delimiter = ' ', dtype = None)
trace=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/trace.csv', delimiter = ',', dtype = None)
n=int(len(gradient_concentration))

x_robot=trace[:,0]
y_robot=trace[:,1]

x=np.linspace(0,n,n)

plt.xlim([0,n])
plt.ylim([0,n])
plt.pcolormesh(x, x, gradient_concentration, shading = 'auto')

bacteries, = plt.plot([],[], 'ko', ms=3, mfc ='k')


def animate(i):
    bacteries.set_data(x_robot[i],y_robot[i])
    return bacteries,


anim = animation.FuncAnimation(fig, animate, frames=104,interval=150, blit=True,repeat=True)

plt.show()





