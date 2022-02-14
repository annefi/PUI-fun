# Created by fischer at 10/02/22 *** last change:

import os
import numpy as np

#path = "/data/projects/Ulysses/VHM_FGM/1min/"
path = "/media/storage/data/projects/Ulysses/VHM_FGM/1min/"
years = range(2000,2010)


for year in years:
    filearray = []
    files = os.listdir(path + str(year))
    for file in files:
        fin = open(path + str(year) + "/" + file, 'r')
        filearray.extend(fin.readlines())
        fin.close()
    for doy in range(1,366):
        print(year, f"{doy:03d}")
        doylist = []
        for line in filearray:
            if len(line.split()) > 0:
                if line.split()[1] == f"{doy:03d}":
                    doylist.append(line)
        if np.shape(doylist) != (0,):
            fout = open(path + str(year) + "/" + f"{doy:03d}" + '.dat', 'w')
            for l in doylist:
                fout.write(l)
            fout.close()


