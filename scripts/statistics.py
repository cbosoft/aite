import numpy as np
from matplotlib import pyplot as plt


def plot_astrogation():

    astrogation = np.linspace(0, 100)

    max_gravity = np.add(np.multiply(np.power(astrogation, 0.33), 1.1), 5.0)

    plt.ylabel('Gravity')
    plt.plot(astrogation, max_gravity, 'C0')

    max_temperature = np.add(np.multiply(np.power(astrogation, 0.5), 100.0), 300.0)
    plt.gca().twinx()
    plt.ylabel('Temperature')
    plt.plot(astrogation, max_temperature, 'C1')



if __name__ == '__main__':
    plot_astrogation()

    plt.savefig('stats.pdf')
