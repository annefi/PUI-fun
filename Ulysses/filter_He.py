'''
Mask a recognizable species by clicking a) into the center of the peak in an animation of the ET matrix over
different EpQ steps or b) the two outermost left and right outermost channels for every EpQ-steps in a Epq vs. Tch
histogram.
Code is written for H+ and He1+ but can be modified to track other species easily
I recommend to use a) for H+ and b) for He1+
'''

import matplotlib.pyplot as plt
import pylab
from numpy import array, arange, around, argwhere, exp, where, unique
from DataLoader.uswipha import uswipha
from pylib import dbData
import os
import sys

class Filter_He(uswipha):
    def set_masks(self):
        self.set_mask('Master', 'ech', 14, 250)
        self.set_mask('Master', 'rng', 0, 0)

    def click_through_essd(self):
        '''
        call this function if you want to repeat clicking through the Ech and Tof positions.
        Be sure to set the masks before and to start with the first EpQ step:
        EpQ step 1, EpQ step 2, ecc...
        Call function save_clicks() if you're done or call function again if you want to repeat
        the clicking.
        '''
        self.ech_clicks = []
        self.tch_clicks = []
        def mouseclick(event):
            ch_t, ch_e = event.xdata, event.ydata
            print(ch_t,ch_e)
            self.ech_clicks.append(ch_e)
            self.tch_clicks.append(ch_t)
            if len(self.ech_clicks) == 64:
                fig.canvas.mpl.disconnect(cid)
        fig = self.animate2d('tch', 'ech', prodz='epq', binx=arange(100, 500), biny=arange(0, 64),binz=arange(
                                           0, 64), speed=100, norm='ymax', cb=False, weights=False, smask=False,
                                       ncols=False, Master=True, xlabel=False,
                                       ylabel=False, zlabel=False, shade=False, rot_xticks=True, save='', fps=5,
                                       avg=False)
        cid = fig.canvas.mpl_connect('button_press_event', mouseclick)

    def click_through_epq(self):
        '''
        Call this function if you want to repeat clicking through the ESA and Tof positions.
        Be sure to set the masks before. The lists don't have to cover every EpQ step and you don't have to start
        with the first one. But you need to click into the bottom half of a bin!
        Change the hist2d bins according to the species you want to track.
        Call function save_clicks() if you're done or call function again if you want to repeat
        the clicking.
        '''
        self.esa_clicks = []
        self.tch_clicks = []
        def mouseclick(event):
            ch_t, ch_e = event.xdata, event.ydata
            print(ch_t,ch_e)
            self.esa_clicks.append(ch_e)
            self.tch_clicks.append(ch_t)
            if len(self.esa_clicks) == 64:
                fig.canvas.mpl.disconnect(cid)

        #pmod = self.hist2d('tch', 'epq', binx=arange(265, 355), biny=arange(21, 55), norm='ymax', weights='brw') #He2+
        #pmod = self.hist2d('tch', 'epq', binx=arange(120,220), biny=arange(0, 22), norm='ymax', weights = 'brw') #H+
        pmod = self.hist2d('tch', 'epq', binx=arange(340, 500), biny = arange(8, 38), norm = 'ymax') # He1+
        fig = pmod.fig
        cid = fig.canvas.mpl_connect('button_press_event', mouseclick)


    def filter_via_mask(self,esa,tch):
        '''
        Epq and tch are the resp. data of a mask2D that is drawn manually around He+ in the ESA vs Tch matrix
        Pass the arguments e.g. as "esa = d.get_data('maskname','epq')"
        Saving is already included here
        Attention: Be careful that ESA step 0 is included by drawing the mask below 0 or include it manually
        '''
        self.esa_fin = []
        self.tch_fin = []
        self.tch_fin_right = []
        fout = open('data_misc/clicks_epq_ch_he2+test_mask2Ds.txt', 'w')
        fout.write('Result of the manual clicking for He+ in EpQ vs. Tch'
                   '\nESA Tch_left Tch_right\n')
        for esa_i in unique(esa):
            ind = where(esa == esa_i)[0]
            t1 = min(tch[ind])
            t2 = max(tch[ind])
            fout.write('%i   %i   %i \n'%(esa_i, t1, t2))
            self.esa_fin.append(esa_i)
            self.tch_fin.append(t1)
            self.tch_fin_right.append(t2)
        fout.close()





    def save_clicks(self, data_type = 'epq', species = 'He1+'):
        '''
        Saves the list with He+ click positions
        '''
        if data_type == 'epq':
            if species == 'He1+':
                fout = open('data_misc/clicks_epq_ch_he.txt', 'w')
                fout.write('Result of the manual clicking for He+ in EpQ vs. Tch'
                           '\nESA Tch_left Tch_right\n')
            elif species == 'H+':
                fout = open('data_misc/clicks_epq_ch_h.txt', 'w')
                fout.write('Result of the manual clicking for H+ in EpQ vs. Tch'
                           '\nESA Tch_left Tch_right\n')
            elif species == 'He2+':
                fout = open('data_misc/clicks_epq_ch_he2.txt', 'w')
                fout.write('Result of the manual clicking for He2+ in EpQ vs. Tch'
                           '\nESA Tch_left Tch_right\n')
            esa_clicks = []
            tch_clicks_left = []
            tch_clicks_right = []
            for i in range(0,len(self.esa_clicks),2):
                esa_clicks.append(round(self.esa_clicks[i]))
                tch_clicks_left.append(round(self.tch_clicks[i]))
                if round(self.esa_clicks[i+1]) == round(self.esa_clicks[i]):
                    tch_clicks_right.append(round(self.tch_clicks[i+1]))
                else:
                    raise TypeError('EpQ values don\'t match!')
                    sys.exit()
            for c in range(len(esa_clicks)):
                fout.write('%i     %i     %i\n' % (esa_clicks[c], tch_clicks_left[c], tch_clicks_right[c]))
            fout.close()

        elif data_type == "essd":
            if species == 'He1+':
                fout = open('data_misc/clicks_essd_ch_he.txt', 'w')
                fout.write('Result of the manual clicking for He+ in EpQ vs. Tch'
                           '\nTch   Ech\n')
            if species == 'H+':
                fout = open('data_misc/clicks_essd_ch_h.txt', 'w')
                fout.write('Result of the manual clicking for H+ in EpQ vs. Tch'
                           '\nTch   Ech\n')
            for i in range(len(self.ech_clicks)):
                fout.write('%5.2f   %5.2f\n' % (self.tch_clicks[i], self.ech_clicks[i],))
            fout.close()


    def read_clicks(self, data_type = 'epq', species = 'He2+'):
        '''
        Reads in file in which the clicks for He+ Tof and Ech channels per Epq step are stored
        '''
        if data_type == 'epq':
            self.esa_fin = []
            self.tch_fin = []
            self.tch_fin_right = []
            if species == 'He1+':
                fin = open('data_misc/clicks_epq_ch_he_mask2D.txt', 'r')
            elif species == 'H+':
                fin = open('data_misc/clicks_epq_ch_h.txt', 'r')
            elif species == 'He2+':
                fin = open('data_misc/clicks_epq_ch_he2+test_mask2Ds.txt', 'r')
            for i in range(2):
                fin.readline()
            for line in fin:
                l = line.split()
                self.l = l
                self.esa_fin.append(int(l[0]))
                self.tch_fin.append(int(l[1]))
                self.tch_fin_right.append(int(l[2]))
            self.esa_fin = array(self.esa_fin)
            self.tch_fin = array(self.tch_fin)
            self.tch_fin_right = array(self.tch_fin_right)
        elif data_type == 'essd':
            self.ech_clicks = []
            self.tch_clicks = []
            if species == 'He1+':
                fin = open('data_misc/clicks_essd_ch_he.txt', 'r')
            elif species == 'H+':
                fin = open('data_misc/clicks_essd_ch_h.txt', 'r')
            for i in range(2):
                fin.readline()
            for line in fin:
                l = line.split()
                self.ech_clicks.append(float(l[1]))
                self.tch_clicks.append(float(l[0]))
            self.ech_fin = array(self.ech_clicks).astype(int)
            self.tch_fin = array(self.tch_clicks).astype(int)

    def filter_pha(self, year, dt = 'epq', species = 'He2+'):
        try:
            len(self.tch_fin)
        except:
            self.read_clicks(data_type = dt, species = species)
        for doy in range(1,366):
            try:
                if species == 'He1+':
                    os.mkdir("%s%s/%.4i" % ('data_misc/pha_he/', dt ,year)) # path for writing masked PHAs
                elif species == 'H+':
                    os.mkdir("%s%s/%.4i" % ('data_misc/pha_h/', dt, year))
                elif species == 'He2+':
                    os.mkdir("%s%s/%.4i" % ('data_misc/pha_he2_new/', dt, year))
            except:
                pass
            if species == 'He1+':
                fout = open("%s%s/%.4i/%.3i.pha" % ('data_misc/pha_he/', dt, year, doy),'w')
            elif species == 'H+':
                fout = open("%s%s/%.4i/%.3i.pha" % ('data_misc/pha_h/', dt, year, doy),'w')
            elif species == 'He2+':
                fout = open("%s%s/%.4i/%.3i.pha" % ('data_misc/pha_he2_new/', dt, year, doy),'w')
            fname = "%s%.4i/%.3i.pha" % (self.path, year, doy) # path to PHAs
            print fname
            try:
                fin = open(fname, "r")
                headline = fin.readline()
                fout.write(headline)
                if dt == 'epq':
                    for line in fin:
                        l = line.split()
                        epq_step = int(l[1])
                        try:
                            epq_i = argwhere(self.esa_fin == epq_step)[0][0]
                            if self.tch_fin[epq_i] <= int(l[2]) and int(l[2]) <= self.tch_fin_right[epq_i]:
                                fout.write(line)
                        except:
                            pass
                elif dt == 'essd':
                    for line in fin:
                        l = line.split()
                        epq_step = int(l[1]) - 1
                        # check if PHA's tch is in the interval for He+
                        try:
                            if int(l[2]) in range(self.tch_fin[epq_step]-12,self.tch_fin[epq_step]+12):
                                if int(l[3]) in range(self.ech_fin[epq_step] - 6, self.ech_fin[epq_step] + 6):
                                    fout.write(line)
                        except:
                            pass # epq step not tracked#
            except:
                pass
            fout.close


    def test_years(self):
        '''
        test function to check if there is a click difference between years
        '''
        fid = open('data_misc/clicks_epq_ch_he_mask2D.txt', 'r')
        for i in range(2):

            fid.readline()
        esa = []
        tch_1 = []
        tch_2 = []

        # tch_1_95 = []
        # tch_2_95 = []
        # tch_1_96 = []
        # tch_2_96 = []
        # tch_1_97_99 = []
        # tch_2_97_99 = []
        # for line in fid95:
        #     l = line.split()
        #     esa.append(float(l[0]))
        #     tch_1_95.append(float(l[1]))
        #     tch_2_95.append(float(l[2]))
        # # for line in fid96:
        # #     l = line.split()
        # #     tch_1_96.append(float(l[1]))
        # #     tch_2_96.append(float(l[2]))
        # for line in fid97_99:
        #     l = line.split()
        #     esa.append(float(l[0]))
        #     tch_1_97_99.append(float(l[1]))
        #     tch_2_97_99.append(float(l[2]))
        for line in fid:
            l = line.split()
            esa.append(float(l[0]))
            tch_1.append(float(l[1]))
            tch_2.append(float(l[2]))
        self.eesa = esa
        self.tch_1 = tch_1

        fig, ax = plt.subplots()

        ax.plot(tch_1, esa, 'o', label="")
        ax.plot(tch_2, esa, 'o', label="")

        #plt.yticks(arange(200,400,50))
        ax.legend()
        plt.show()





