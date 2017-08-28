import sys
from scipy.io.wavfile import read
import posix_ipc 
import os
from struct import *
import matplotlib.pyplot as plt
import numpy as np

fs, x = read(sys.argv[1])
f = posix_ipc.SharedMemory("shared")
t = []
for i in range(1000):
    t.append(unpack('f', os.read(f.fd, 4))[0])

os.lseek(f.fd, 0, os.SEEK_SET)
print fs, x.ndim, x.size, x.shape, x.dtype
for a in x: 
   for b in a: os.write(f.fd, pack('h',b))
os.close(f.fd)
