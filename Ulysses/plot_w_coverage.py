from DataLoader.uswiutils import getvelocity
import numpy as np
import matplotlib.pyplot as plt
import matplotlib

matplotlib.rcParams.update({'font.size': 14,
                            'xtick.major.size': 8,
                            'xtick.major.width': 1.5,
                            'xtick.minor.size': 5,
                            'xtick.minor.width': 1,
                            'ytick.major.size': 8,
                            'ytick.major.width': 1.5,
                            'ytick.minor.size': 5,
                            'ytick.minor.width': 1,
                            'xtick.direction': 'inout',
                            'ytick.direction': 'inout',
                            'figure.subplot.left':0.12,
                            'figure.subplot.bottom': 0.15,
                            'figure.subplot.right': 0.9,
                            'figure.subplot.top': 0.8,
                            'figure.figsize': (7,4.5)})

v_min = getvelocity(4,1,17)
v_max = getvelocity(4,1,0)

v_sw = np.arange(400.,950.,50.)

fig, ax = plt.subplots(figsize=(8,7))

for v in v_sw:
    ax.plot(np.array([v_min-v,v_max-v])/v, [v,v], marker='o')

ax.set_xlabel("w")
ax.set_ylabel("vsw / km/s")
ax.text(0.5,1.1,r'$v_{min} = 928\,\mathrm{km/s}$ (ESA step 17)',horizontalalignment='center',
        verticalalignment='center', transform=ax.transAxes)
ax.text(0.5,1.05,r'$v_{max} = 1708\,\mathrm{km/s}$ (ESA step 0)',horizontalalignment='center',
        verticalalignment='center', transform=ax.transAxes)
ax.text(0.5,1.2,'Possible w-coverage for He+',horizontalalignment='center',
        verticalalignment='center', transform=ax.transAxes, weight = 'bold')
ax.grid()

plt.show()