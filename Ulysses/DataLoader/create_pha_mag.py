from pylib import dbData
from numpy import *
from uswipha import uswipha
import os, sys


path = '/home/asterix/fischer/PUI/Ulysses/data_misc/PHA_mag/'

header = 'doy\t\tepqst\ttch\tech\tsect\tdet\trange\tbrw\tBphi\t\tBtheta\n'

for y in [1993,1994, 1995, 1996, 1997, 1998, 1999, 2000]:
    if os.path.exists('%s%s/' % (path, str(y))) == False:
        os.mkdir('%s%s/' % (path, str(y)))
    for doy in arange(1,366):
        d = uswipha(year=y, tf=[[doy, doy+1]], path='/home/asterix/fischer/PUI/Ulysses/data_misc/pha_he/')
        d.sync_swoops()
        d.sync_traj()
        d.sync_mag()

        fname = "%s%.4i/%.3i.pha" % (path, y, doy)
        out = open(fname, 'w')

        out.write(header)
        for i in arange(len(d.data['year'])):
            do = d.data['doy'][i]
            epq = str(d.data['epq'][i])
            tch = str(d.data['tch'][i])
            ech = str(d.data['ech'][i])
            sec = str(d.data['sec'][i])
            det = str(d.data['det'][i])
            range = str(d.data['rng'][i])
            brw = str(d.data['brw'][i])
            bp = d.data['Bphi'][i]
            bt = d.data['Btheta'][i]
            line = "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%8.5f\t%8.5f\n" %(do,epq,tch,ech,sec,det,range,brw,bp,bt)
            out.write(line)
        out.close()