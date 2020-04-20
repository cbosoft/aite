from matplotlib import pyplot as plt
import numpy as np

NAMES_OF_COLOURS = [
    ((   0.0, 1.00, 1.00), 'red'),
    ((   4.0, 0.71, 1.00), 'orange-red'),
    ((  35.0, 0.92, 0.53), 'brown'),
    ((  45.0, 1.00, 1.00), 'orange'),
    ((  60.0, 1.00, 1.00), 'yellow'),
    ((  84.0, 0.82, 1.00), 'yellow-green'),
    (( 120.0, 1.00, 1.00), 'lime-green'),
    (( 136.0, 1.00, 0.76), 'green'),
    (( 180.0, 1.00, 1.00), 'cyan'),
    (( 240.0, 1.00, 1.00), 'blue'),
    (( 275.0, 0.92, 0.68), 'purple'),
    (( 300.0, 1.00, 1.00), 'magenta'),
    (( 300.0, 0.54, 0.99), 'pink'),
    ((np.nan, 0.00, 0.00), 'black'),
    ((np.nan, 0.00, 0.50), 'grey'),
    ((np.nan, 0.00, 1.00), 'white')
]

UNSAT = [
    'dilute',
    'pale',
    'dull'
]

SAT = [
    'lively',
    'spirited',
    'intense',
    'vivid'
]

BRIGHT = [
    'bright',
    'vibrant'
]

DARK = [
    'dark',
    'gloomy'
]



def norm(colour):
    h, s, v = colour
    h = h/150.0
    return h, s, v

def linear(colour):
    h, s, v = colour
    h = 2.0*np.pi*h/360.0
    return s*v*np.cos(h), s*v*np.sin(h), v

def cdist(col1, col2):
    linear1 = linear(col1)
    linear2 = linear(col2)
    dist = np.sum(np.power(np.subtract(linear1, linear2), 2.0))
    return dist

def name_colour(colour):
    h, s, v = colour
    min_dist = 1e9
    name = 'na'
    ignore_hue = colour[1] <= 0.25
    norm_colour = norm(colour)
    if ignore_hue:
        norm_colour = norm_colour[1:]
    for named_colour, colour_name in NAMES_OF_COLOURS:
        norm_named_colour = norm(named_colour)
        if ignore_hue:
            norm_named_colour = norm_named_colour[1:]
        #dist = np.sum(np.power(np.subtract(norm_named_colour, norm_colour), 2.0))
        dist = cdist(named_colour, colour)
        if dist < min_dist:
            min_dist = dist
            name = colour_name

    description = list()
    if s < 0.5:
        description.insert(0, np.random.choice(UNSAT))
    else:
        if s > 0.95:
            description.insert(0, np.random.choice(SAT))
    
        if v < 0.5:
            description.insert(0, np.random.choice(DARK))
        elif v > 0.8:
            description.insert(0, np.random.choice(BRIGHT))

    # if description:
    #     name = ', '.join(description) + ' ' + name
    return name

def hsv2rgb(h, s, v):

    if s > 1.0:
        s = 1.0
    if s < 0.0:
        s = 0.0
    if v > 1.0:
        v = 1.0
    if v < 0.0:
        v = 0.0

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

if __name__ == '__main__':
    colour = (136.0, 1.0, 1.0)
    plt.gca().add_artist(plt.Circle((0.5,0.5), 1.0, color=hsv2rgb(*colour)))
    plt.text(0.5,0.5, name_colour(colour), ha='center', va='center')
    plt.savefig('colour.pdf')
