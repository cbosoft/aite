import numpy as np
from matplotlib import pyplot as plt


def fit(x, y):
    m, c = np.polyfit(x, y, 1)
    f = lambda a: np.add(np.multiply(a, m), c)
    return m, c, f


def plot_diagram(points):

    gas_liquid, liquid_solid = points

    glt, glp = zip(*gas_liquid)
    lst, lsp = zip(*liquid_solid)

    P = np.power(10.0, np.linspace(-1, 2))

    m, c, f = fit(glp, glt)
    plt.plot(f(P), P, label=f'gas-liquid $m={m:.1e}$, $c={c:.1e}$')
    m, c, f = fit(lsp, lst)
    plt.plot(f(P), P, label=f'liquid-solid $m={m:.1e}$, $c={c:.1e}$')

def pa2atm(pa):
    return pa / 101325.0

def bar2atm(bar):
    return bar / 1.01325


if __name__ == '__main__':

    # P in atm, T in K
    data = [
        ('H', [
            ((13.8033, pa2atm(7041.0)), (32.938, pa2atm(1285800.0))),
            ((13.8033, pa2atm(7041.0)), (20.0, bar2atm(50.0)))
            ]),
        ('He', [
            ((2.17, 0.08), (4.22, 1.0)),
            ((1.9, 50.0), (3.0, 80.0))
            ]),
    ]

    i = len(data)-1

    for symbol, points in data[i:i+1]:
        plot_diagram(points)
        plt.yscale('log')
        plt.xscale('log')
        plt.title(symbol)
        plt.ylabel('Pressure, $\\ P\\rm\\ [atm]$')
        plt.xlabel('Temperature, $\\ T\\rm\\ [K]$')
    plt.legend()
    plt.savefig('state_diagram.pdf')
