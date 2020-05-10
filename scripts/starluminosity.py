import numpy as np
import lmfit
from matplotlib import pyplot as plt

def read_data():
    with open('data/star_luminosity.csv') as f:
        lines = f.readlines()

    lines = [[float(f) for f in line.split(',')] for line in lines if not line.startswith('#')]
    temperature, scale = zip(*lines)
    return np.array(temperature), np.array(scale)

def m(s, p_lo, p_hi, cutoff):
    low = np.power(s, p_lo)
    high = np.add(np.power(cutoff, p_lo), np.power(s, p_hi))
    res = np.where(s > cutoff, high, low)
    return res

def altm(s, c, p, m, a):
    return np.add(np.multiply(np.exp(-np.power(np.divide(c, s), p)), m), a)*np.log(s)

if __name__ == '__main__':
    temperature, scale = read_data()
    TEMPERATURE_SOL = 5000 # K
    LUMINOSITY_SOL = 3.828e26
    SIZE_SOL = 1.3927e9 # m
    size = scale*SIZE_SOL
    luminosity = scale*LUMINOSITY_SOL

    plt.plot(size, temperature)
    #plt.plot(size, m(size, 0.525, 0.37, 5e7))

    c, p, m, a = 1e7, 0.5, 7e2, 1e2
    plt.plot(size, altm(size, c, p, m, a))
    plt.rc('text', usetex=True)
    plt.rc('text.latex', preamble='\\usepackage{sansmath}\\sansmath{}')
    plt.text(0.1, 0.9,
            '$T=\\ln(D)\,\\left[a + m\,e^{-\\left(\\frac{c}{D}\\right)^p}\\right]$',
            transform=plt.gca().transAxes)
    plt.text(0.1, 0.8, f'$c = {c:.0e}$', transform=plt.gca().transAxes)
    plt.text(0.1, 0.7, f'$p = {p}$', transform=plt.gca().transAxes)
    plt.text(0.1, 0.6, f'$m = {m}$', transform=plt.gca().transAxes)
    plt.text(0.1, 0.5, f'$a = {a}$', transform=plt.gca().transAxes)

    plt.title('Mainsequence star luminance, size, and temperature')
    plt.xlabel('Star diameter, $D\\rm/m$')
    plt.ylabel('Surface temperature, $T\\rm/K$')

    plt.xscale('log')
    #plt.yscale('log')
    plt.savefig('star.pdf')
