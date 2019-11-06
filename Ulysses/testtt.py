from pylab import *
from math import pi
import numpy as np

# n = 100
# phi = np.linspace(-pi, pi, n * 2)
# theta = np.linspace(-pi / 2, pi / 2, n)
# Phi, Theta = np.meshgrid(phi, theta)
# value = np.sin(2 * Phi)**2 + np.sin(Theta)**2 + Theta / 2
#
# subplot(211, projection="hammer")
# pcolormesh(phi, theta, value)
# title("Hammer")
# grid(True)
#
# subplot(212, projection="lambert")
# pcolormesh(phi, theta, value)
# title("Lambert")
# grid(True)
#
# show()

def fast(D):
    phi = D.wphi[(D.w > 1.9) & (D.w < 2.0)]
    theta = D.wtheta[(D.w > 1.9) & (D.w < 2.0)]
    wR = D.wr[(D.w > 1.9) & (D.w < 2.0)]
    wT = D.wt[(D.w > 1.9) & (D.w < 2.0)]
    wN = D.wn[(D.w > 1.9) & (D.w < 2.0)]
    return phi, theta, wR, wT, wN
