import numpy as np
from matplotlib import pylab
from matplotlib.animation import FuncAnimation


def test():
    def sine(x,phase):
        return np.sin(x+phase)

    fig = pylab.figure()
    ax = fig.gca()

    x = np.linspace(0,2*np.pi,100)
    XX, YY = np.meshgrid(x,x)

    Z = sine(XX,0)+np.cos(YY)

    data = ax.pcolormesh(x,x, Z)
    ax.set_xlabel("x")
    ax.set_xlabel("y")
    ax.set_xlim(0,2*np.pi)
    ax.set_ylim(0,2*np.pi)


    def animate2(i):
        print(i)
        phase = i * 0.01 * 2 * np.pi
        B = sine(XX, phase)+np.cos(XX*YY)
        B = B[:-1, :-1]
        data.set_array(B.ravel())

    ani = FuncAnimation(fig, animate2, interval=100, blit=False)