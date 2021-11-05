from matplotlib import pyplot as plt

#! /usr/bin/python3

import numpy as np
import matplotlib.pyplot as plt

# Lire le fichier
print('Lecture du fichier')
dhm200 = np.genfromtxt('/Users/mathilde/Downloads/DHM200.xyz', delimiter = ' ', dtype = None)

# Transformer les colonnes (x, y, h) en tableau
print('Transformation')
x = dhm200[:, 0]
print(len(x))
y = dhm200[:, 1]
h = dhm200[:, 2]

xMin = np.min(x)

yMin = np.min(y)
xIndex = (x - xMin) / 200


yIndex = (y - yMin) / 200

xIndexInt = xIndex.astype('int32')
yIndexInt = yIndex.astype('int32')
xCount = xIndexInt.max() + 1

yCount = yIndexInt.max() + 1
xp = xMin + np.arange(0, xCount) * 200
print(len(xp))
yp = yMin + np.arange(0, yCount) * 200
print(len(yp))
altitudes = np.zeros((yCount, xCount))
altitudes[yIndexInt, xIndexInt] = h

# Point le plus haut
maxIndex = np.argmax(altitudes)
maxY, maxX = np.unravel_index(maxIndex, altitudes.shape)
maxValue = altitudes[maxY, maxX]
print(f'Le maximum se trouve à {xp[maxX]:0.0f} {yp[maxY]:0.0f} avec une altitude de {maxValue}.')

# Point le plus haut avec les données originales
maxIndex = np.argmax(h)
print(f'Le maximum se trouve à {x[maxIndex]:0.0f} {y[maxIndex]:0.0f} avec une altitude de {h[maxIndex]}.')

# Toute la suisse

plt.axes().set_aspect('equal')
plt.pcolormesh(x[maxIndex], y[maxIndex], altitudes,cmap="hot", shading = 'auto')
plt.pcolormesh(xp, yp, altitudes,cmap="hot", shading = 'auto')
plt.title('Suisse')
plt.savefig('suisse.png')
plt.colorbar()
plt.show()
