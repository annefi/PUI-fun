# Created by fischer at 09/03/22 ***

import sys
import os
from DataLoader.uswipha import uswipha
import numpy as np

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

d = uswipha(year = yyyy, tf = [[1,2]])
dels = []

for i in range(len(d.data['doy'])):
    if i == len(d.data['doy'])-1:
        dels.append(0)
    else:
        del_t_doy = d.data['doy'][i+1] - d.data['doy'][i]
        del_t_min = del_t_doy*24*60
        dels.append(del_t_min)

d.add_data('del_t_min', np.array(dels))

# todo: array sortieren und unique vor delta-Bildung