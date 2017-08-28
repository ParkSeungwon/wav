from scipy.io.wavfile import write
import matplotlib.pyplot as plt
import numpy as np

A = [0.2,0.2,0.2]
phi = [0, 0, 0]
f = [1,2,3]
t = np.arange(0, np.pi * 2, 0.1)
y = np.zeros(t.size)
for i in range(len(A)): y += A[i] * np.sin(2 * np.pi * f[i] * t + phi[i]) 
plt.plot(t, y)
plt.show()
