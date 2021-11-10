import numpy as np
import matplotlib.pyplot as plt

donnee = np.genfromtxt('matdu72.txt', delimiter = ',')
#donnee=np.reshape(donnee[0,], (-1,6))
#print(donnee)
t = donnee[0::6]
ypop1 = donnee[1::6]
ypop2=donnee[2::6]
ymorap=donnee[3::6]
ymolent=donnee[4::6]
ysubsol=donnee[5::6]
#print(t,ypop1)

#plt.axes().set_aspect('equal')

plt.plot(t, ypop1, ".", label="pop heterotrophe")
plt.plot(t, ypop2, ".", label="pop autotrophe")
plt.plot(t, ymorap, ".", label="mat org rapidement degradée")
plt.plot(t, ymolent, ".", label="mat org lentement degradée")
plt.plot(t, ysubsol, ".", label="substrat soluble")

plt.title("évolution de nos paramètres d'interet en fonction du temps")
plt.xlabel("t")
#plt.legend()
plt.show()

#linearisation

coeffs = np.polyfit(t, ypop1, 12)
#print(coeffs)
polynomial = np.poly1d(coeffs)
plt.plot(t, polynomial(t), label="linearisation de pop heterotrophe")
plt.plot(t, ypop1, ".", label="pop heterotrophe")

plt.title("évolution de nos paramètres d'interet en fonction du temps")
plt.xlabel("t")
plt.legend()
plt.show()
