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

yyyy = 1999
d = uswipha(year = yyyy, tf = [[1,366]], path = datapath + "swics/pha/")
dels = []
dels_sec = []
unique_doy = np.unique(d.data['doy'])
unique_doy.sort()

for i in range(len(unique_doy)):
    if i == len(unique_doy)-1:
        dels.append(0)
    else:
        del_t_doy = unique_doy[i+1] - unique_doy[i]
        del_t_min = del_t_doy*24*60
        #print(del_t_min)
        dels.append(del_t_min)
    if 12.8<del_t_min<13.5:
        dels_sec.append((del_t_min-13)*60.)

bins = np.arange(-.5,45)
h = np.histogram(dels,bins)

# here the plot stuff begins:

fig, ax = plt.subplots()
ax.plot(bins[:-1],h[0],drawstyle = 'steps-post')
ax.set_ylim(-1,max(h[0])*1.2)
ax.plot([13.,13.],[0,0.9*ax.get_ylim()[1]], linewidth = 2)
for i in [0.5,2,3]:
    ax.plot([i*13., i*13.], [0, 0.9*ax.get_ylim()[1]], linewidth=1, linestyle = 'dotted', color = 'orange')

ax.text(13,0.95*ax.get_ylim()[1],'t = 13 min', color='orange', ha = 'center', weight= 'bold')
ax.text(30,0.5*ax.get_ylim()[1],'N_tot = %s'%(h[0].sum()), color='blue', ha = 'center', weight= 'bold')
ax.text(30,0.45*ax.get_ylim()[1],'N/N_tot = %3.2f %%' %( ((h[0][13]+h[0][26]+h[0][39])/h[0].sum())*100 ), color='blue', ha = 'center', weight= 'bold')

ax.set_xlabel('time/min')
ax.set_ylabel('# delta time')
ax.grid(True)



# seconds...

bins1 = np.arange(-10,22)
h1 = np.histogram(dels_sec,bins1)
fig1, ax1 = plt.subplots()
ax1.plot(bins1[:-1],h1[0],drawstyle = 'steps-post')

ax1.set_ylim(-1,max(h1[0])*1.2)

ax1.plot([0.,0.],[0,0.9*ax1.get_ylim()[1]], linewidth = 2)
ax1.text(0.,0.95*ax1.get_ylim()[1],'t = 13 min', color='orange', ha = 'center', weight= 'bold')
ax1.set_xlabel('time/s')
ax1.set_ylabel('# delta time')
ax1.grid(True)

plt.show()