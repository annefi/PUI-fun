import matplotlib.pyplot as plt
import pylab
from numpy import array, arange, around
from DataLoader.uswipha import uswipha
from pylib import dbData
import os


class Filter_He(uswipha):
    def set_masks(self):
        self.set_mask('Master', 'ech', 14, 250)
        self.set_mask('Master', 'rng', 0, 0)

    def click_through(self):
        self.ch_ech = []
        self.ch_tch = []
        def mouseclick(event):
            ch_t, ch_e = event.xdata, event.ydata
            print(ch_t,ch_e)
            self.ch_ech.append(ch_e)
            self.ch_tch.append(ch_t)
            if len(self.ch_ech) == 64:
                fig.canvas.mpl.disconnect(cid)

        fig = self.animate2d('tch', 'ech', prodz='epq', binx=arange(100, 500), biny=arange(0, 64),binz=arange(
                                           0, 64), speed=100, norm='ymax', cb=False, weights=False, smask=False,
                                       ncols=False, Master=True, xlabel=False,
                                       ylabel=False, zlabel=False, shade=False, rot_xticks=True, save='', fps=5,
                                       avg=False)
        cid = fig.canvas.mpl_connect('button_press_event', mouseclick)

    def save_clicks(self):
        fout = open('data_misc/clicks_ch_he.txt', 'w')
        for i in range(len(self.ch_ech)):
            fout.write('%5.2f   %5.2f\n'%(self.ch_tch[i],self.ch_ech[i],))
        fout.close()

    def read_clicks(self):
        self.ch_ech = []
        self.ch_tch = []
        fin = open('data_misc/clicks_ch_he.txt', 'r')
        for line in fin:
            l = line.split()
            self.ch_ech.append(float(l[1]))
            self.ch_tch.append(float(l[0]))
        self.ech_fin = array(self.ch_ech).astype(int)
        self.tch_fin = array(self.ch_tch).astype(int)

    def filter_pha(self, year):
        try:
            self.tch_fin.shape()
        except:
            self.read_clicks()
        for tf in self.timeframe:
            for doy in range(int(tf[0]), int(tf[1])):
                try:
                    os.mkdir("%s%.4i" % ('data_misc/pha_he/', year)) # path for writing masked PHAs
                except:
                    pass # dir already exists (or any other fail)
                fout = open("%s%.4i/%.3i.pha" % ('data_misc/pha_he/', year, doy),'a')
                fname = "%s%.4i/%.3i.pha" % (self.path, year, doy) # path to PHAs
                print fname
                fin = open(fname, "r")
                fin.readline()
                for line in fin:
                    l = line.split()
                    epq_step = int(l[1])
                    self.e = epq_step
                    # check if PHA's tch is in the interval for He+
                    if int(l[2]) in range(self.tch_fin[epq_step]-5,self.tch_fin[epq_step]+5):
                        fout.write(line)
                fout.close







