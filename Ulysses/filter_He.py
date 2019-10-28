'''
Script to write a save a subset of PHA words (e.g. for one species)
Code is written for He1+ and He2+ but can be modified to track other species easily
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

    def filter_via_mask(self,esa,tch,ech,species = 'He1+'):
        '''
        Epq and tch are the resp. data of a mask2D that is drawn manually around He+ in the ESA vs Tch matrix
        Pass the arguments e.g. as "esa = d.get_data('maskname','epq')"
        Saving is already included here
        Attention: Be careful that ESA step 0 is included by drawing the mask below 0 or include it manually
        '''
        self.esa_fin = []
        self.tch_fin = []
        self.tch_fin_right = []
        fout = open('data_misc/clicks_epq_ch_%s_mask2D.txt' % species, 'w')
        fout.write('Result of the manual clicking for %s in EpQ vs. Tch'
                   '\nESA Tch_left Tch_right\n' % species)
        for esa_i in unique(esa):
            ind = where(esa == esa_i)[0]
            t1 = min(tch[ind])
            t2 = max(tch[ind])
            fout.write('%i   %i   %i \n'%(esa_i, t1, t2))
            self.esa_fin.append(esa_i)
            self.tch_fin.append(t1)
            self.tch_fin_right.append(t2)
        fout.close()
        # needed to exclude the pile-up+:
        self.tch = []
        self.ech_max = []
        fout2 = open('data_misc/clicks_tch_ech_%s_mask2D.txt' % species, 'w')
        fout2.write('Result of the manual clicking for %s in Ech vs. Tch'
                   '\nTch   ECH_max\n' % species)
        for tch_i in unique(tch):
            ind = where(tch == tch_i)
            ech_max = max(ech[ind])
            fout2.write('%i   %i \n' % (tch_i, ech_max))
            self.tch.append(tch_i)
            self.ech_max.append(ech_max)
        fout2.close()

    def read_clicks(self, species = 'He2+'):
        '''
        Reads in file in which the clicks for He+ Tof and Ech channels per Epq step are stored
        '''
        self.esa_fin = []
        self.tch_fin = []
        self.tch_fin_right = []
        if species == 'He1+':
            fin = open('data_misc/clicks_epq_ch_He1+_mask2D.txt', 'r')
        elif species == 'He2+':
            fin = open('data_misc/clicks_epq_ch_He2+_mask2D.txt', 'r')
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

    def read_ech_clicks(self, species = 'He2+'):
        '''
        Reads in file in which the clicks for He+ Tof and Ech channels per Epq step are stored
        '''
        self.tch = []
        self.ech_max = []
        if species == 'He1+':
            fin = open('data_misc/clicks_tch_ech_He1+_mask2D.txt', 'r')
        elif species == 'He2+':
            fin = open('data_misc/clicks_tch_ech_He2+_mask2D.txt', 'r')
        for i in range(2):
            fin.readline()
        for line in fin:
            l = line.split()
            self.l = l
            self.tch.append(int(l[0]))
            self.ech_max.append(int(l[1]))
        self.tch = array(self.tch)
        self.ech_max = array(self.ech_max)


    def filter_pha(self, year, species = 'He1+'):
        try:
            len(self.tch_fin)
        except:
            self.read_clicks(species = species)
            self.read_ech_clicks(species = species)
        for doy in range(1,366):
            try:
                if species == 'He1+':
                    os.mkdir("%s/%.4i" % ('data_misc/pha_he/' ,year)) # path for writing masked PHAs
                elif species == 'H+':
                    os.mkdir("%s/%.4i" % ('data_misc/pha_h/',  year))
                elif species == 'He2+':
                    os.mkdir("%s/%.4i" % ('data_misc/pha_he2/',year))
            except:
                pass
            if species == 'He1+':
                fout = open("%s/%.4i/%.3i.pha" % ('data_misc/pha_he/', year, doy),'w')
            elif species == 'H+':
                fout = open("%s/%.4i/%.3i.pha" % ('data_misc/pha_h/',year, doy),'w')
            elif species == 'He2+':
                fout = open("%s/%.4i/%.3i.pha" % ('data_misc/pha_he2/',year, doy),'w')
            fname = "%s%.4i/%.3i.pha" % (self.path, year, doy) # path to PHAs
            print fname
            try:
                fin = open(fname, "r")
                headline = fin.readline()
                fout.write(headline)
                for line in fin:
                    l = line.split()
                    epq_step = int(l[1])
                    try:
                        epq_i = argwhere(self.esa_fin == epq_step)[0][0]
                        if self.tch_fin[epq_i] <= int(l[2]) and int(l[2]) <= self.tch_fin_right[epq_i]:
                            t_ind = argwhere(self.tch == int(l[2]))[0][0]
                            if int(l[3]) <= self.ech_max[t_ind]:
                                fout.write(line)
                    except:
                        print(epq_step)
            except:
                print('no file at ', fname)
            fout.close()


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





