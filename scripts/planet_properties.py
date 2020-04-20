import numpy as np
from matplotlib import pyplot as plt

from csv import read_csv
from colour_names import name_colour

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
    density = np.random.lognormal(mn, std, 10000)
    for i, rhoi in enumerate(density):
        while np.log(rhoi) >= 10.0:
            rhoi = np.random.lognormal(mn, std)
        density[i] = rhoi
    edges, bins = do_hist(np.log(density))
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
    muhigh = 55
    mulow = 0
    dmu = muhigh - mulow
    drho = (high_density - low_density)
    dndrho = dn/drho
    dmudrho = dmu/drho

    def rho2mu(rho):
        rhomc = np.subtract(rho, low_density)
        mu = (rhomc * dmudrho) + mulow
        return mu

    kws = {
        'transform': plt.gca().transAxes,
        'bbox': {'color': 'white', 'alpha':0.8}
    }

    std = 10
    l = 10000
    plt.text(0.2, 0.9,  '$\\xi = $Normal (trunc: 0-117)', **kws)
    plt.text(0.2, 0.8,  '$\\mu = ' + f'\\left({muhigh} - {mulow}\\right)' + ' \\frac{\\ln\\rho - \\ln\\rho_{l}}{\\ln\\rho_h - \\ln\\rho_l} + ' + f'{mulow}' + '$', **kws)
    plt.text(0.2, 0.7, f'$\\sigma = {std}$', **kws)
    plt.text(0.2, 0.6, f'$\\ln\\rho_l = {low_density:.1f}$', **kws)
    plt.text(0.2, 0.5, f'$\\ln\\rho_h = {high_density:.1f}$', **kws)
    # plt.text(0.2, 0.4,  '$n_E = (\\xi < 0) ? \\left|\\xi\\right| + \\mu : \\left[(\\xi > 117) ? 117 - \\xi \\% 117 : \\xi\\right]$', **kws)

    for rho in [low_density, mid_density, high_density]:
        mu = rho2mu(rho)
        dist = np.random.normal(mu, std, l)
        dist = np.where(dist < 0.0, np.add(np.abs(dist), mu), dist)
        dist = np.where(dist > nelem, np.subtract(nelem, np.fmod(dist, nelem)), dist)

        sdist = np.random.normal(mu, 2*(std+mu), l)
        sdist = np.where(sdist < 0.0, np.add(np.abs(sdist), mu), sdist)
        sdist = np.where(sdist > nelem, np.subtract(nelem, np.fmod(sdist, nelem)), sdist)
        dist = np.where(np.random.uniform(0, 1, l) > 0.5, dist, sdist)



        plt.plot(*do_hist(dist))

    plt.ylabel('$P(n_E)$')
    plt.xlabel('Element, $n_E$')
    plt.xticks(ticks=[0, 20, 40, 60, 80, 100, 117], labels=['H', 'Ca', 'Zr', 'Nd', 'Hg', 'Fm', 'Og'])
    #plt.xscale('log')
    plt.yticks([])


def hsv2rgb(h, s, v):

    if s > 1.0:
        s = 1.0
    if s < 0.0:
        s = 0.0
    if v > 1.0:
        v = 1.0
    if v < 0.0:
        v = 0.0
    # https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
    #     if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
    #         out.r = in.v;
    #         out.g = in.v;
    #         out.b = in.v;
    #         return out;
    #     }
    if s == 0.0:
        return (v, v, v)

    hh = np.fmod(h, 360.0)
    hh /= 60.0
    i = int(hh);
    ff = hh - float(i)
    p = v*(1.0 - s)
    q = v*(1.0 - s*ff)
    t = v*(1.0 - (s*(1.0 - ff)))
    if i == 0:
        return v, t, p
    elif i == 1:
        return q, v, p
    elif i == 2:
        return p, v, t
    elif i == 3:
        return p, q, v
    elif i == 4:
        return t, p, v
    else:
        return v, p, q






def choose_palette():
    primary_colour = [
        np.random.uniform(0.0, 360.0), 
        np.subtract(1.0, np.abs(np.subtract(np.random.normal(1.0, 0.3), 1.0))),
        np.subtract(1.0, np.abs(np.subtract(np.random.normal(1.0, 0.3), 1.0)))
    ]

    light_colour = list(primary_colour)
    light_colour[0] *= np.random.normal(1.0, 0.1)
    light_colour[1] *= np.random.normal(1.0, 0.1)
    light_colour[2] *= 1.1
    light_colour[2] = min([light_colour[2], 1.0])

    unsat_colour = list(primary_colour)
    unsat_colour[0] *= np.random.normal(1.0, 0.1)
    unsat_colour[1] -= np.random.uniform(0.2, 0.4)
    unsat_colour[2] *= np.random.normal(1.0, 0.1)

    complementary_colour = [
        primary_colour[0] + np.random.normal(180.0, 10.0), 
        primary_colour[1]*np.random.uniform(0.9, 1.1),
        primary_colour[2]*np.random.uniform(0.9, 1.1)
    ]

    complementary_light = list(complementary_colour)
    complementary_light[0] *= np.random.normal(1.0, 0.1)
    complementary_light[1] *= np.random.normal(1.0, 0.1)
    complementary_light[2] *= 1.1
    complementary_light[2] = min([light_colour[2], 1.0])

    complementary_unsat = list(complementary_colour)
    complementary_unsat[0] *= np.random.normal(1.0, 0.1)
    complementary_unsat[1] -= np.random.uniform(0.2, 0.4)
    complementary_unsat[2] *= np.random.normal(1.0, 0.1)

    colours = [primary_colour, light_colour, unsat_colour,
            complementary_colour, complementary_light, complementary_unsat]
    categories = ['primary', 'light', 'unsaturated', 'complementary', 'compl. light', 'compl. unsat']
    return categories, colours

def plot_colour(colour_ax):
    plt.sca(colour_ax)

    n = 5

    for i in range(n):
        categories, colours = choose_palette()
        for j, colour in enumerate(colours):
            colour_ax.add_artist(plt.Circle([i, j], 0.3, color=hsv2rgb(*colour)))
            plt.text(i,j,name_colour(colour), ha='center', va='center')
    plt.xlim(left=-0.5, right=n-0.5)
    plt.ylim(bottom=-0.5, top=len(colours)-0.5)
    plt.yticks(ticks=list(range(len(categories))), labels=categories)





if __name__ == '__main__':
    planet_data = read_csv('data/planet_data.csv')

    plt.rcParams['figure.subplot.wspace'] = 0.4
    plt.rcParams['figure.subplot.hspace'] = 0.4

    fig, axes = plt.subplots(ncols=3, nrows=2, figsize=(20,10))

    size_ax, density_ax, temp_ax, pressure_ax, element_ax, colour_ax = axes.flatten()

    size_data = planet_data['fpl_smax']
    plot_size_dist(size_data, size_ax)

    density_data = planet_data['fpl_dens']
    plot_density_dist(density_data, density_ax)

    temp_data = planet_data['fpl_eqt']
    plot_temperature_dist(temp_data, temp_ax)

    plot_pressure(pressure_ax)

    #plot_elements(element_ax, density_data)

    plot_colour(colour_ax)

    plt.savefig('plot.pdf', bbox_inches='tight')
