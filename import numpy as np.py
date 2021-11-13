import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cbook
from matplotlib import cm
from matplotlib.animation import FuncAnimation
from matplotlib.colors import LightSource
from matplotlib import animation, rc
import math

fig, ax = plt.subplots()
for k in range(steps):
    pos = computeNewPos(pos, vel, force)
    ax.clear()        

    ax.scatter(pos[0, 0], pos[0, 1], label = '1', color = 'r')
    ax.scatter(pos[1, 0], pos[1, 1], label = '2', color = 'b')

    ax.xlabel('X')
    ax.ylabel('Y')

    plt.pause(0.05)

plt.show()