import numpy as np

#from mpl_toolkits.mplot3d import Axes3D
from matplotlib import pyplot as plt



def get_abundance(rho):

    l = 118
    elements = list(range(1,1+l))
    abundance = [0.0 for __ in elements]

    # normalise rho 0-1:
    nrho = (np.log(rho)+3)/9
    high_abundant_range_start = int((nrho*118.0*0.067/0.33) + np.random.uniform(0, np.log(rho)) ) 
    high_abundant_range_end = int(np.random.uniform(5,np.log(rho))) + int((nrho/0.33)*13.0) + high_abundant_range_start

    siderophiles = [44, 45, 46, 52, 75, 76, 77, 78, 79]

    for n in elements:

        a = l/n
        if n % 6 == 0:
            a *= 4.0 # every 6th element is extra probable
        elif n % 2 == 0:
            a *= 2.0 # even elements are also more likeley

        m = 1.0
        if n < high_abundant_range_start:
            m = 1e-1
        # elements heavier than americium are (~)impossible
        elif n > 95:
            m = 1e-5*rho
        # elements heavier than iron are unlikely
        elif n > high_abundant_range_end:
            m = 1e-2

        if n in siderophiles:
            a *= 1e-2

        a = a*m

        if n < 3:
            a /= rho*100

        abundance[n-1] = a*np.random.uniform(0.1,10.0)

    total = np.sum(abundance)
    abundance = np.divide(abundance, total)
    # abundance = [np.nan if a <= 0.0 else a for a in abundance]

    label = f'{nrho}: {high_abundant_range_start} - {high_abundant_range_end}'
    return elements, abundance, label









if __name__ == '__main__':

    densities = [np.exp(-3), np.exp(0), np.exp(3), np.exp(6)]
    #densities = [1.0]


    for density in densities:
        element_number, abundance, label = get_abundance(density)
        plt.plot(element_number, abundance, 'o--', label=label)
    plt.xticks(ticks=[0, 20, 40, 60, 80, 100, 117], labels=['H', 'Ca', 'Zr', 'Nd', 'Hg', 'Fm', 'Og'])

    plt.axvline(26, color='0.5', alpha=0.5)
    plt.axvline(95, color='0.5', alpha=0.5)
    plt.yscale('log')
    plt.legend()
    plt.savefig('abundance.pdf')
