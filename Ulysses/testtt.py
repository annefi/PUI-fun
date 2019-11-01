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
    phi = D.phi[D.w > 1.8]
    theta = D.theta[D.w > 1.8]
    wR = D.wR[D.w > 1.8]
    wT = D.wT[D.w > 1.8]
    wN = D.wN[D.w > 1.8]
    return phi, theta, wR, wT, wN
