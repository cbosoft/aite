import numpy as np
from matplotlib import pyplot as plt

import lmfit

from csv import read_csv

def do_hist(v):
    v = [vi for vi in v if not np.isnan(vi)]
    bins, edges = np.histogram(v, bins='auto', density=True)
    #bins = np.divide(bins, len(v))
    edges = np.average([edges[1:], edges[:-1]], axis=0)
    return edges, bins

def binorm(mn1, std1, mn2, std2, p, l):
    a = np.random.lognormal(mean=mn1, sigma=std1, size=l)
    b = np.random.lognormal(mean=mn2, sigma=std2, size=l)
    P = np.random.uniform(size=l)
    return np.where(P < p, a, b)

def plot_size_dist(size_data, size_ax):
    plt.sca(size_ax)
    log_size_data = np.log(size_data)
    edges, bins = do_hist(log_size_data)
    plt.plot(edges, bins, label='real')
    
    mn1, std1, mn2, std2, p = -2.5, 0.7, 0.5, 0.6, 0.8
    size_fit = binorm(mn1, std1, mn2, std2, p, 10000)
    log_size_fit = np.log(size_fit)
    edges, bins = do_hist(log_size_fit)
    plt.plot(edges, bins, label=f'Bi-LogNormal')
    
    #plt.legend()
    plt.text(0.6, 0.9, 'Bi-LogNormal', transform=plt.gca().transAxes)
    for i, (n, v) in enumerate([('\\mu_1', mn1), ('\\sigma_1', std1), ('\\mu_2', mn2), ('\\sigma_2', std2), ('p_1', p)]):
        plt.text(0.6, 0.8 - (0.1*i), f'${n} = {v}$', transform=plt.gca().transAxes)
    # plt.xscale('log')
    # plt.yscale('log')
    plt.ylabel('Probability $P(\\ln(d))$')
    plt.xlabel('Diameter $\\ln(d)\\rm/AU$')
    plt.yticks([])


def plot_density_dist(density_data, density_ax):
    log_density_data = np.log(density_data)

    plt.sca(density_ax)
    edges, bins = do_hist(log_density_data)
    plt.plot(edges, bins)

    mn = 0.7; std = 1.0
    density = np.random.lognormal(mn, std, 1000)
    for i, rhoi in enumerate(density):
        while rhoi >= 10.0:
            rhoi = np.random.lognormal(mn, std)
        density[i] = rhoi
    edges, bins = do_hist(density)
    plt.plot(edges, bins)

    plt.text(0.6, 0.9, 'LogNormal', transform=plt.gca().transAxes)
    plt.text(0.6, 0.8, f'$\\mu = {mn}$', transform=plt.gca().transAxes)
    plt.text(0.6, 0.7, f'$\\sigma = {std}$', transform=plt.gca().transAxes)
    plt.ylabel('$P(\\ln(\\rho))$')
    plt.xlabel('Density $\\ln(\\rho)\\rm/AU$')
    plt.yticks([])


def plot_temperature_dist(temp_data, temp_ax):
    plt.sca(temp_ax)
    edges, bins = do_hist(temp_data)
    plt.plot(edges, bins)

    mn = 1100; std = 600
    tempfit = np.random.normal(mn, std, 100000)
    for i, ti in enumerate(tempfit):
        while ti <= 0.0:
            ti = np.random.normal(mn, std)
        tempfit[i] = ti

    edges, bins = do_hist(tempfit)
    plt.plot(edges, bins)
        
    plt.text(0.6, 0.9, 'LogNormal', transform=plt.gca().transAxes)
    plt.text(0.6, 0.8, f'$\\mu = {mn}$', transform=plt.gca().transAxes)
    plt.text(0.6, 0.7, f'$\\sigma = {std}$', transform=plt.gca().transAxes)

    plt.yticks([])
    plt.xlabel('Temperature $T\\rm/K$')
    plt.ylabel('$P(T)$')


def plot_pressure(pressure_ax):
    plt.sca(pressure_ax)
    mn = -2; std = 1.0
    pressure = np.random.lognormal(mn, std, 100000)
    edges, bins = do_hist(np.log(pressure))
    plt.plot(edges, bins)

    plt.text(0.7, 0.9, 'Normal', transform=plt.gca().transAxes)
    plt.text(0.7, 0.8, f'$\\mu = {mn}$', transform=plt.gca().transAxes)
    plt.text(0.7, 0.7, f'$\\sigma = {std}$', transform=plt.gca().transAxes)
    plt.ylabel('$P(P)$')
    plt.xlabel('Atmospheric Pressure $\\ln(P)\\rm/atm$')
    plt.yticks([])

def plot_elements(element_ax, density_data):
    plt.sca(element_ax)

    log_density_data = np.log(density_data)

    mn = np.nanmean(log_density_data)
    std = np.nanstd(log_density_data)
    low_density = mn - 3.0*std
    mid_density = mn
    high_density = mn + 3.0*std
    nelem = 118.0
    dn = 0.7*nelem
    dstd = 40
    drho = high_density - low_density
    dndrho = dn/drho
    dstddrho = dstd/drho
    stdmin = 30

    def rho2std(rho):
        rhomc = np.subtract(rho, low_density)
        std = (rhomc * dstddrho) + stdmin
        return std


    std = 30.0

    plt.text(0.35, 0.95,  'Normal (trunc: 0-117)', transform=plt.gca().transAxes)
    plt.text(0.35, 0.85,  '$\\mu = 0$', transform=plt.gca().transAxes)
    plt.text(0.35, 0.75,  '$\\sigma = ' + f'{dstd}' + ' \\frac{\\ln\\rho - \\ln\\rho_{l}}{\\ln\\rho_h - \\ln\\rho_l} + ' + f'{stdmin}' + '$', transform=plt.gca().transAxes)
    plt.text(0.35, 0.65, f'$\\ln\\rho_l = {low_density:.1f}$', transform=plt.gca().transAxes)
    plt.text(0.35, 0.55, f'$\\ln\\rho_h = {high_density:.1f}$', transform=plt.gca().transAxes)

    for rho in [low_density, mid_density, high_density]:
        dist = np.random.normal(0, rho2std(rho), 100000)
        dist = np.abs(dist)
        dist = np.where(dist > nelem, np.subtract(nelem, np.fmod(dist, nelem)), dist)

        plt.plot(*do_hist(dist))

    plt.ylabel('$P(n_E)$')
    plt.xlabel('Element, $n_E$')
    plt.xticks(ticks=[0, 20, 40, 60, 80, 100, 117], labels=['H', 'Ca', 'Zr', 'Nd', 'Hg', 'Fm', 'Og'])
    plt.yticks([])




if __name__ == '__main__':
    planet_data = read_csv('data/planet_data.csv')

    plt.rcParams['figure.subplot.wspace'] = 0.4
    plt.rcParams['figure.subplot.hspace'] = 0.4

    fig, axes = plt.subplots(ncols=3, nrows=2, figsize=(10,10))

    size_ax, density_ax, temp_ax, pressure_ax, element_ax, unkn_ax = axes.flatten()

    size_data = planet_data['fpl_smax']
    plot_size_dist(size_data, size_ax)

    density_data = planet_data['fpl_dens']
    plot_density_dist(density_data, density_ax)

    temp_data = planet_data['fpl_eqt']
    plot_temperature_dist(temp_data, temp_ax)

    plot_pressure(pressure_ax)

    plot_elements(element_ax, density_data)


    plt.savefig('plot.pdf', bbox_inches='tight')
