import numpy as np
from matplotlib import pyplot as plt


def do_hist(v):
    bins, edges = np.histogram(v, bins='auto')
    edges = np.average([edges[:-1], edges[1:]], axis=0)
    return edges, bins


diameter = np.random.lognormal(1, 0.3, 10000)*0.00262503736291
x, y = do_hist(diameter)
plt.plot(x, y)
plt.show()

