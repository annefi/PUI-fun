#import pdb
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def sine(x,phase):
    return np.sin(x+phase)

fig = plt.figure()
ax = fig.gca()

x = np.linspace(0,2*np.pi,100)
data = ax.plot(x, sine(x,0))
#pdb.set_trace()

ax.set_xlabel("x")
ax.set_xlim(0,2*np.pi)
ax.set_ylim(-2,2)


def animate(i):
	print(i)
	phase = i * 0.01 * 2 * np.pi
	yvals = np.cos(x)+sine(x, phase)
	data[0].set_data(x, yvals)
    
ani = FuncAnimation(fig, animate, interval=100, blit=False)
plt.show()
