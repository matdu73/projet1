import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cbook
from matplotlib import cm
from matplotlib.animation import FuncAnimation
from matplotlib.colors import LightSource
from matplotlib import animation, rc

concentration=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/gradientC.csv', delimiter = ' ', dtype = None)

x=np.linspace(0, 100,100)


y=np.linspace(0, 100,100)


plt.axes().set_aspect('equal')

plt.pcolormesh(x, y, concentration, shading = 'auto')



fig,ax=plt.subplots()

ax.set_xlim(0,100)
ax.set_ylim(0,100)

line,= ax.plot(0,0)
x_data=[]
y_data=[]

def animation1(i):
    x_data.append(i)
    x_data.append(i)

    line.set_xdata(x_data)
    line.set_ydata(x_data)
    return line,

animation = FuncAnimation(fig, func=animation1, frames=np.arange(0, 100, 0.1), interval=10)


#plt.savefig('concentration.png')

plt.show()

# on peut faire for i in range .... et mettre dzans la boucle for un plt.pause(time)