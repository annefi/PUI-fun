# Created by fischer at 15/02/22 *** last change:

import datetime
import os
from numpy import column_stack
from ulysses_mag_loader import mag_loader
from Ulysses.Trajectory.ul_coordinates_utils import rtn_to_hg
from Ulysses.Trajectory.SPICE.spice_ulysses import *


path = "/data/projects/Ulysses/VHM_FGM/1min/"
#path = "Ulysses/DataLoader/mag_stuff/"

def calc_datetime():
    datetimes = []
    for i in range(len(mag.data['year'])):
        datetimes.append(datetime.datetime(mag.data['year'][i], 1, 1, int(mag.data['hour'][i]), int(mag.data['min'][i]),
                                           int(mag.data['sec'][i])) + datetime.timedelta(days = mag.data['doy'][i] - 1))
    mag.add_data('datetime', datetimes)

def calc_hg():
    # traj = UlyssesTrajSpice(year = self.year, tf = self.timeframe)
    # sc_vecs = column_stack((traj.data["R"],traj.data["HG_Lat"], traj.data["HG_Long"]))
    B_vecs_RTN = column_stack((mag.data["Br"], mag.data["Bt"], mag.data["Bn"]))
    B_r = []
    B_lat = []
    B_long = []
    for i in range(len(B_vecs_RTN)):
        sc_vec = locateUlysses(mag.data['datetime'][i], HCI)
        B_r_i, B_lat_i, B_long_i = rtn_to_hg(B_vecs_RTN[i], sc_vec)
        B_r.append(B_r_i)
        B_lat.append(B_lat_i)
        B_long.append(B_long_i)
    mag.add_data('B_r', B_r)
    mag.add_data('B_lat', B_lat)
    mag.add_data('B_long', B_long)


for YYYY in range(1992,2010):
    mag = mag_loader(year=YYYY, tf='all')
    calc_datetime()
    calc_hg()
    for doy in range(1, 366):
        fout = open(path + str(YYYY) + "/new/" + f"{doy:03d}" + '.dat', 'w')
        for i in range(len(mag.data['year'])):
            if mag.data['doy'][i] == doy:
                line = (f" {str(YYYY)[-2:]} {doy:03d} {int(mag.data['hour'][i]):02} {int(mag.data['min'][i]):02} "
                        f"{int(mag.data['sec'][i]):02} "
                        f"{mag.data['Br'][i]:7.3f} {mag.data['Bt'][i]:7.3f} {mag.data['Bn'][i]:7.3f} "
                        f"{mag.data['Babs'][i]:7.3f} "
                        f"{mag.data['B_r'][i]:7.3f} {mag.data['B_lat'][i]:8.3f} {mag.data['B_long'][i]:8.3f}"
                        f" \n")
                fout.write(line)
        fout.close()































