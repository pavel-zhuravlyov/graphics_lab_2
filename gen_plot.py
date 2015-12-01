import sys
import numpy as np
import math
from itertools import product
 
def generate_mesh(X, Y, F):
    with open('res/plot.obj', 'w') as f:

        interpolate = lambda array: map(lambda elem: np.interp(elem, (min(array), max(array)), (-1, 1)), array)

        Z = [F(x, y) for x, y in product(X, Y)]
        A, B = zip(*product(X, Y))

        indices = [(y * len(X) + x + 1, y * len(Y) + x + 2) for x, y in product(xrange(len(X) - 1), xrange(len(Y)))] 
        indices += [(y * len(X) + x + 1, (y + 1) * len(Y) + x + 1) for x, y in product(xrange(len(X)), xrange(len(Y) - 1))]

        for x, y, z in zip(interpolate(A), interpolate(B), interpolate(Z)):
            f.write("v %f %f %f\n" % (x, y, z))

        for index in indices:
            f.write("l %d %d\n" % (index[0], index[1]))
    
X = np.arange(0, 10, 1)
Y = np.arange(0, 10, 1)
# F = lambda x, y: math.sqrt(x) + math.sqrt(y)
F = lambda x, y: math.sin(x) + math.cos(y)

generate_mesh(X, Y, F)    