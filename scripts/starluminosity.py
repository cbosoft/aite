import numpy as np
from matplotlib import pyplot as plt

m = np.exp([-0.5, 0, 0.5, 1.0])
l = np.exp([-2.5, 0, 2.0, 4.0])

plt.plot(m, l)
m, c = np.polyfit(m, l, 1)
fitx = np.linspace(0.1, 10)
fity = np.add(np.multiply(m, fitx), c)
plt.plot(fitx, fity, '--')
print(m , c)
plt.show()
