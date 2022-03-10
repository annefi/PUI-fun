# Created by fischer at 09/03/22 ***

import sys
import os
from DataLoader.uswipha import uswipha
import numpy as np
import matplotlib.pyplot as plt

if os.path.isdir("/home/af/fusessh/data/projects/Ulysses/") == True:
    ### from Laptop old: ###
    datapath = "/home/af/fusessh/data/projects/Ulysses/"
elif os.path.isdir("/media/storage/data/projects/Ulysses/") == True:
    ### from Laptop new: ###
    datapath = "/media/storage/data/projects/Ulysses/"
elif os.path.isdir("/data/projects/Ulysses/") == True:
    ### from Uni/skeletor: ###
    datapath = "/data/projects/Ulysses/"
else:
    print(
        "Problem finding data path on asterix")
    sys.exit()
####################

# Load unfiltered PHA data (not only He+):

yyyy = 1991
d = uswipha(year = yyyy, tf = [[1,366]], path = datapath + "swics/pha/")
dels = []
unique_doy = np.unique(d.data['doy'])
unique_doy.sort()

for i in range(len(unique_doy)):
    if i == len(unique_doy)-1:
        dels.append(0)
    else:
        del_t_doy = unique_doy[i+1] - unique_doy[i]
        del_t_min = del_t_doy*24*60
        dels.append(del_t_min)

bins = np.arange(-.5,60)
h = np.histogram(dels,bins)

fig, ax = plt.subplots()
ax.plot(bins[:-1],h[0],drawstyle = 'steps-post')

ax.set_ylim(-1,max(h[0])*1.2)
ax.plot([13.,13.],[0,0.9*ax.get_ylim()[1]], linewidth = 2)

for i in [0.5,2,3,4]:
    ax.plot([i*13., i*13.], [0, 0.9*ax.get_ylim()[1]], linewidth=1, linestyle = 'dotted', color = 'orange')

ax.text(13,0.95*ax.get_ylim()[1],'t = 13 min', color='orange', ha = 'center', weight= 'bold')
ax.text(50,0.5*ax.get_ylim()[1],'N = %s'%len(unique_doy), color='orange', ha = 'center', weight= 'bold')

ax.set_xlabel('time/min')
ax.set_ylabel('# delta time')
ax.grid(True)

fig1, ax1 = plt.subplots()

plt.show()