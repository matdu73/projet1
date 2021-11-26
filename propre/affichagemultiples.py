import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cbook
from matplotlib.colors import LightSource
from matplotlib import cm, animation
import math

fig=plt.figure()

gradient_concentration=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/propre/gradientC.csv', delimiter = ' ', dtype = None)


n=int(len(gradient_concentration))
trace1=np.genfromtxt('/Users/mathilde/Desktop/myfiles/Programmation/projet/projet1/propre/trace1.csv', delimiter = ',', dtype = None)

n1=trace1[0][0]
print("aaaaaaaa", n1)

x=np.linspace(0,n,n)

plt.xlim([0,n])
plt.ylim([0,n])
plt.pcolormesh(x, x, gradient_concentration, shading = 'auto')


bacterie=n1*[0]
for j in range(n1):
    bacterie[j], = plt.plot([],[], 'ko', ms=2, mfc ='b')

        
def animate(i):
    for j in range(n1):
        bacterie[j].set_data(trace1[1+j::n1,0][i],trace1[1+j::n1,1][i])

    return bacterie

anim = animation.FuncAnimation(fig, animate, frames=(int(np.floor(len(trace1)/n1)+1)),interval=200, blit=True)

plt.show()







