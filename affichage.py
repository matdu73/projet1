import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cbook
from matplotlib.colors import LightSource
from matplotlib import cm, animation
import math


fig=plt.figure()

gradient_concentration=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/propre/gradientC.csv', delimiter = ' ', dtype = None)
trace=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/trace.csv', delimiter = ',', dtype = None)
n=int(len(gradient_concentration))
trace1=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/propre/trace1.csv', delimiter = ',', dtype = None)
x1_robot=trace1[::3,0]
y1_robot=trace1[::3,1]

x2_robot=trace1[1::3,0]
y2_robot=trace1[1::3,1]

x3_robot=trace1[2::3,0]
y3_robot=trace1[2::3,1]


print(x1_robot)
x_robot=trace[:,0]
y_robot=trace[:,1]

x=np.linspace(0,n,n)

plt.xlim([0,n])
plt.ylim([0,n])
plt.pcolormesh(x, x, gradient_concentration, shading = 'auto')

bacterie1, = plt.plot([],[], 'ko', ms=3, mfc ='k')
bacterie2, = plt.plot([],[], 'ko', ms=3, mfc ='b')
bacterie3, = plt.plot([],[], 'ko', ms=3, mfc ='g')

def animate(i):
    bacterie1.set_data(x1_robot[i],y1_robot[i])
    bacterie2.set_data(x2_robot[i],y2_robot[i])
    bacterie3.set_data(x3_robot[i],y3_robot[i])
    return bacterie1, bacterie2,bacterie3,


anim = animation.FuncAnimation(fig, animate, frames=len(x1_robot),interval=150, blit=True)

plt.show()






