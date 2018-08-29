#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import sys
import os

file_1 = sys.argv[1]

temp = np.loadtxt(file_1)
x = temp[:,0]
y = temp[:,1]
plt.plot(x,y)
plt.show()
