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

bacteries, = plt.plot([],[], 'ko', ms=3, mfc ='red')
fig,ax=plt.subplots()
#for i in range(len(x_robot)):
#    plt.scatter(x_robot[i],y_robot[i], label='skitscat',color='k',marker='*',s=2)
#    plt.plot([x_robot[i]], [y_robot[i]], linestyle = 'none', marker = '*', c = 'lime',markersize = 3)
#    plt.draw()
    
#    plt.pause(0.1)

def animate(i):
    bacteries.set_data(x_robot[i],y_robot[i])
    return bacteries,


anim = animation.FuncAnimation(fig, animate, frames=100, init_func=None, fargs=None, save_count=None,  cache_frame_data=True)







