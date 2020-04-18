import numpy as np
from matplotlib import pyplot as plt


def norm(v):
    return v
    return np.divide(v, np.max(v))


def get_diversity(age, n):
    
    diversity = 0.0
    if n < 1e4:
        diversity = np.exp(np.divide(-1e2, n))
    else:
        diversity = 1.0

    number_generations = age//10.
    generation_bonus = number_generations * 0.023
    return diversity


def get_death_rate(br, res):
    dr = 0.8
    dr = 1.0 - (0.01*1.0/res)
    return dr*br


def get_birth_rate(age, n, div, res):
    br = 1.0
    return br


def get_number(number, birth_rate, death_rate, dt):
    return max([number + (birth_rate - death_rate)*dt*number, 0.0])


def get_pop_xp(number, birth_rate, death_rate, pxp):
    dxp = number*birth_rate*(1.0-death_rate)
    return pxp + dxp


def plot_growth(pop_ax):
    for resilience in [0.8, 1.0, 1.2]:
        init_pop = 100.0
        init_diversity = get_diversity(0, init_pop)
        init_birth = get_birth_rate(0.0, init_pop, init_diversity, resilience)
        init_death = get_death_rate(init_birth, resilience)
        init_xp = 1e-3

        t = 0.0
        number = [init_pop]
        birth_rate = [init_birth]
        death_rate = [init_death]
        diversity = [init_diversity]
        xp =[init_xp]
        colony_age = np.power(10.0, np.linspace(0, 3))
        dt = np.average(np.diff(colony_age))
        for a in colony_age[1:]:
            number.append(get_number(number[-1], birth_rate[-1], death_rate[-1], dt))
            diversity.append(get_diversity(a, number[-1]))
            birth_rate.append(get_birth_rate(a, number[-1], diversity[-1], resilience))
            death_rate.append(get_death_rate(birth_rate[-1], resilience))
            xp.append(get_pop_xp(number[-1], birth_rate[-1], death_rate[-1], xp[-1]))

        plt.sca(pop_ax)
        plt.xscale('log')
        plt.yscale('log')
        plt.plot(colony_age, number, label='population')
        plt.ylabel('Population')
        plt.xlabel('Age, Ind.')







if __name__ == '__main__':

    plt.rcParams['figure.subplot.wspace'] = 0.5
    fig, axes = plt.subplots(nrows=1, ncols=3, figsize=(12,4))

    pop_ax, tech_ax, cult_ax = axes.flatten()

    plot_growth(pop_ax)

    plt.savefig('../levelling.pdf')
