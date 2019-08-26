from decoded import *
from bittools import *
from expand import expand
#from Scientific.IO import NetCDF
from scipy.io.netcdf import netcdf_file as NetCDFFile
import time
import calendar
from numpy import save
import os

class extrswx(object):
    """
    Class for data extraction from lv0 netcdf (binary raw SC data) files. In the current version only ACE/SWICS data is extracted, but the SC files also contain data from SWIMS (the extraction is already implemented but not written)
    rpath -> path to the netcdf files 
    wpath -> path where to put the extracted data 
    year,doy -> obviously year and day of year of the data 
    prange -> list that specifies which priority ranges (SWICS/PHA) should be extracted
              0 = H He (TCR)
              1 = All other ions (TCR)
              2 = DCR
              3 = Error range
    """
    def __init__(self,rpath="/data/missions/ace/swics/lv1",wpath="/data/etph/ace/lv0",year=2007,doy=1,prange = (0,1,2,3),verbose=0):
        self.rpath = rpath
        self.wpath = wpath
        self.year = year
        self.doy = doy
        self.verbose = verbose  # verbosity level not used yet
        self.prange = prange    # used to specifiy the PHA priority ranges that are taken into account (only for PHA data, bra files always have the information for all 4 ranges)
        self.load_data()
        
    def load_data(self):
        """
        Die Daten eines Tages verteilen sich auf bis zu drei NetCDF files. Der letzte cycle eines Tages (Wenn als Cycletime die startzeit des Cycles genommen wird!) ist haeufig im File des naechsten Tages.
        Ausserdem findet sich normalerweise, wenn keine Datenluecken auftreten die daten des letzten E/Q schrittes (step 60) im ersten Datensatz des Folgetages.
        Immer sind alle PHA Daten (und Raten?) um einen E/Q Schritt gegenueber der Zeit verschoben! Dass ist an entsprechender Stelle zu beruecksichtigen!
        D.h. der erste cycle des Folgetages (falls vorhanden) enthaelt stets die Daten von E/Q step 60 des letzten Cycles des Tages.
        """
        # Als erstes wird eine Liste aller fuer den Tag vorhanden Cycles erstellt
        isleap = not(self.year %4)
        # Vorherigen Tag
        try:
            if (self.doy == 1):
                if isleap:
                    prfilein = self._load_netcdf(self.year-1,366)
                else:
                    prfilein = self._load_netcdf(self.year-1,365)
            else:
                prfilein = self._load_netcdf(self.year,self.doy-1)
        except:
            prfilein = False
        # Aktueller Tag
        try:
            actfilein = self._load_netcdf(self.year,self.doy)
        except:
            actfilein = False
        # Nachfolgender Tag
        try:
            if (not(isleap) and self.doy == 365) or (isleap and self.doy == 366):
                nxtfilein = self._load_netcdf(self.year+1,1)
            else:
                nxtfilein = self._load_netcdf(self.year,self.doy+1)
        except:
            nxtfilein = False
        # Finde die Cycles die Daten des zu entpackenden Tages enthalten

        # t0,t1 Start- und Endzeit des Tages in sec since 1 jan 1970 
        t0 = time.strptime("%.3i %.4i"%(self.doy,self.year),"%j %Y")
        if (not(isleap) and self.doy == 365) or (isleap and self.doy == 366):
            t1 = time.strptime("%.3i %.4i"%(1,self.year+1),"%j %Y")
        else:
            t1 = time.strptime("%.3i %.4i"%(self.doy+1,self.year),"%j %Y")
        #print t0,t1
        self.t0 = calendar.timegm(t0)
        self.t1 = calendar.timegm(t1)
        # Startzeiten aller Cycle aus den netCDF files
        if prfilein:
            prtime = prfilein.variables["time"][:]
            prepoch = prfilein.variables["epoch"][:]
        if actfilein:
            acttime = actfilein.variables["time"][:]
            actepoch = actfilein.variables["epoch"][:]
        if nxtfilein:
            nxttime = nxtfilein.variables["time"][:]
            nxtepoch = nxtfilein.variables["epoch"][:]
        
        # container for data products
        self.CYC = zeros((0,60,2436),uint8)
        self.QAC = zeros((0,60),uint8)
        self.TIME = zeros((0,60),uint8)
        self.EPOCH = zeros((0,60),uint8)

        # maskiere alle Cycles; t1+720 da der erste cycle des neuen tages normalerweise den letzten E/Q-step des vorherigen cycles enthaelt
        if prfilein:
            prmask = (prtime[:,0] >= self.t0) * (prtime[:,0] < self.t1+720) 
            prcyc = prfilein.variables["cyc"][:]
            prcyc = prcyc.view(uint8)
            prQAC = prfilein.variables["QAC"][:]
            self.CYC = append(self.CYC,prcyc[prmask],axis=0)
            self.QAC = append(self.QAC,prQAC[prmask],axis=0)
            self.TIME = append(self.TIME,prtime[prmask],axis=0)
            self.EPOCH = append(self.EPOCH,prepoch[prmask],axis=0)
            prfilein.close()
        if actfilein:
            actmask = (acttime[:,0] >= self.t0) * (acttime[:,0] < self.t1+720) 
            actcyc = actfilein.variables["cyc"][:]
            actcyc = actcyc.view(uint8)
            actQAC = actfilein.variables["QAC"][:]
            self.CYC = append(self.CYC,actcyc[actmask],axis=0)
            self.QAC = append(self.QAC,actQAC[actmask],axis=0)
            self.TIME = append(self.TIME,acttime[actmask],axis=0)
            self.EPOCH = append(self.EPOCH,actepoch[actmask],axis=0)
            actfilein.close()
        if nxtfilein:
            nxtmask = (nxttime[:,0] >= self.t0) * (nxttime[:,0] < self.t1+720) 
            nxtcyc = nxtfilein.variables["cyc"][:]
            nxtcyc = nxtcyc.view(uint8)
            nxtQAC = nxtfilein.variables["QAC"][:]
            self.CYC = append(self.CYC,nxtcyc[nxtmask],axis=0)
            self.QAC = append(self.QAC,nxtQAC[nxtmask],axis=0)
            self.TIME = append(self.TIME,nxttime[nxtmask],axis=0)
            self.EPOCH = append(self.EPOCH,nxtepoch[nxtmask],axis=0)
            nxtfilein.close()
        print "TIME.shape = ",self.TIME.shape
        print "CYC.shape = ",self.CYC.shape
        

    def _load_netcdf(self,year,day):
        print "loading %s/%.4i/%.4i%.3i.nc"%(self.rpath,year,year,day)
        filein=NetCDFFile(self.rpath+"/%.4i/%.4i%.3i.nc"%(year,year,day),"r",mmap = False)
        return filein
        
    def save_bin(self,pha=True,bra=True,tra=True,mra=True):
        if pha:
            self.phal = []
        if bra:
            self.bral = []
        if tra:
            self.tral = []
        if mra:
            self.mral =[]
        nxtcycexp = False
        for cyc in range(self.TIME.shape[0]):
            if (self.TIME[cyc][0] > self.t0) * (self.TIME[cyc][0] < self.t1):
                if not nxtcycexp:
                    expcyc=SBCYC()
                    expand(self.CYC[cyc],self.TIME[cyc],self.QAC[cyc],expcyc)
                cyctime = self.TIME[cyc][0] # All PHAs of one cycle get the starting time of the cycle as time
                cycdoy = time.gmtime(cyctime)
                cycdoy = cycdoy.tm_yday+cycdoy.tm_hour/24.+cycdoy.tm_min/(24.*60.)+cycdoy.tm_sec/(24.*60.*60.)
                if pha:
                    self.extr_pha(expcyc,cyctime,cycdoy,laststep = False)
                if bra:
                    self.extr_bra(expcyc,cyctime,cycdoy,laststep = False)
                if tra:
                    self.extr_tra(expcyc,cyctime,cycdoy,laststep = False)
                if mra:
                    self.extr_mra(expcyc,cyctime,cycdoy,laststep = False)
            if (cyc+1 < self.TIME.shape[0]):
                if ((self.TIME[cyc+1][0] - self.TIME[cyc][0])>717) * ((self.TIME[cyc+1][0] - self.TIME[cyc][0])<723) : 
                    expcyc=SBCYC()
                    expand(self.CYC[cyc+1],self.TIME[cyc+1],self.QAC[cyc+1],expcyc)
                    nxtcycexp = True
                    if pha:
                        self.extr_pha(expcyc,cyctime,cycdoy,laststep = True)
                    if bra:
                        self.extr_bra(expcyc,cyctime,cycdoy,laststep = True)
                    if tra:
                        self.extr_tra(expcyc,cyctime,cycdoy,laststep = True)
                    if mra:
                        self.extr_mra(expcyc,cyctime,cycdoy,laststep = True)
                else:
                    nxtcycexp = False
        if pha:
            self.phal = array(self.phal)
            phaout = open(self.wpath+"/%.4i/%.3i.pha.npz"%(self.year,self.doy),"w")
            save(phaout,self.phal)
            phaout.close()
        if bra:
            self.bral = array(self.bral)
            braout = open(self.wpath+"/%.4i/%.3i.bra.npy"%(self.year,self.doy),"w")
            save(braout,self.bral)
            braout.close()
        if tra:
            self.tral = array(self.tral)
            traout = open(self.wpath+"/%.4i/%.3i.tra.npy"%(self.year,self.doy),"w")
            save(traout,self.tral)
            traout.close()
        if mra:
            self.mral = array(self.mral)
            mraout = open(self.wpath+"/%.4i/%.3i.mra.npy"%(self.year,self.doy),"w")
            save(mraout,self.mral)
            mraout.close()

    def _mkdir(self,dirname):
        """
        Create directory specified by dirname
        """
        try:
            os.mkdir(dirname)
            print "Created directory : ",dirname
        except:
            print "Unable to create directory : ",dirname
            return False
        return True

    def _isdir(self,dirname):
        """
        Check if directory dirname exists
        """
        if not os.path.isdir(dirname):
            print "Directory does not exist : ",dirname
            return False
        return True

    def _checkdir(self,dirname,make=False):
        """
        Checks if directory dirname exists, if not and make is True try to make directory dirname.
        """
        if self._isdir(dirname):
            return True
        if make:
            return self._mkdir(dirname)

    def checkdir_structure(self,pha=False,bra=False,tra=False,mra=False,hk=False,cmd=False):
        """
        Checks if needed directories are present, and tries to create them if not.
        """

        # Check if directory specified by wpath is present and stop if not
        if not self._checkdir(self.wpath):
            return False
        # Check if directory for given year is present and try to create if not
        if not self._checkdir(self.wpath+"/%.4i"%(self.year),make=True):
            return False
        # Check if directories for specified data products are present and try to create if not
        if pha and (not self._checkdir(self.wpath+"/%.4i/pha"%(self.year),make=True)):
                return False
        if bra and (not self._checkdir(self.wpath+"/%.4i/bra"%(self.year),make=True)):
                return False
        if tra and (not self._checkdir(self.wpath+"/%.4i/tra"%(self.year),make=True)):
                return False
        if mra and (not self._checkdir(self.wpath+"/%.4i/mra"%(self.year),make=True)):
                return False
        if hk and (not self._checkdir(self.wpath+"/%.4i/hk"%(self.year),make=True)):
                return False
        if cmd and (not self._checkdir(self.wpath+"/%.4i/cmd"%(self.year),make=True)):
                return False
        return True
    
    def save_ascii(self,pha=True,bra=True,tra=True,mra=True,hk=True,cmd=True):
        """
        Extract data and save to ascii files
        The data products are set to True -> write or False -> do not write 
        pha -> PHA data. Extensions ph0,ph1,ph2,ph3 are use for the 4 priority ranges
        bra -> Base rate files. All sectors for all 4 PHA priorities.
        tra -> Trigger rates. Start (fsr) and ssd trigger rates. Coincidences: double (dcr), and triple (tcr). Proton and Helium rates from auxiliary channel. (One rate for each sector and epq)
        mra -> Several matrix rates, which have been filled by onboard classification of PHA data into M/MpQ Boxes (NOTE: No idea how good any of theses boxes work!!!)
        hk  -> Housekeeping data. 25 entries per epq step. Not all of these entries are identified?
        cmd -> A set of 11 commandable values (per 12 minute cycle). Almost constant. Up to now the only relevant quantity is the PAPS level, which changed in 2000. Which means that individual calibrations are needed for the time before and after the switch.
        """
        if not self.checkdir_structure(pha=pha,bra=bra,tra=tra,mra=mra,hk=hk,cmd=cmd):
            return False
        if pha:
            phaout = []
            for rng in range(4):
                if rng in self.prange:
                    phaout.append(open(self.wpath+"/%.4i/pha/%.3i.ph%.1i"%(self.year,self.doy,rng),"w"))
                    phaout[-1].write("year\ttime\t\tdoy\t\teoq\ttof\tesd\tdid\t\trng\t\tsec\t\tmas\tmoq\ttwgt\t\tswgt\n")
                    phaout[-1].write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[CH]\t[CH]\t[detector]\t[priority]\t[sector]\t[CH]\t[CH]\t[totalweight]\t[sectorweight]\n")
                else:
                    phaout.append(False)
        if bra:
            braout = open(self.wpath+"/%.4i/bra/%.3i.bra"%(self.year,self.doy),"w")
            braout.write("year\ttime\t\tdoy\t\teoq\trng\tbr0\tbr1\tbr2\tbr3\tbr4\tbr5\tbr6\tsbr7\tbrall\n")
            braout.write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[range]\t[sec0]\t[sec1]\t[sec2]\t[sec3]\t[sec4]\t[sec5]\t[sec6]\t[sec7]\t[allsecs]\n")
        if tra:
            traout = open(self.wpath+"/%.4i/tra/%.3i.tra"%(self.year,self.doy),"w")
            traout.write("year\ttime\t\tdoy\t\teoq\tsec\tHeaux\tHaux\tssd\ttcr\tdcr\tfsr\tepq\tepq_aux\n")
            traout.write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[sect]\t[/1.5s]\t[/1.5s]\t[/1.5s]\t[/1.5s]\t[/1.5s]\t[/1.5s]\t[keV/e]\t[keV/e]\n")
        if mra:
            mraout = open(self.wpath+"/%.4i/mra/%.3i.mra"%(self.year,self.doy),"w")
            mraout.write("year\ttime\t\tdoy\t\teoq\tsec\tmr0\tmr1\tmr2\tmr3\tmr4\tmr5\tmr6\tmr7\n")
            mraout.write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[sect]\t[H+]\t[He2+]\t[He+]\t[O7+]\t[O6+]\t[Fe]\t[Si]\t[Err]\t'Sector 8 means sum of all sectors'\n")
        if hk:
            hkout = open(self.wpath+"/%.4i/hk/%.3i.hk"%(self.year,self.doy),"w")
            hkout.write("year\ttime\t\tdoy\t\teoq\tGV28\tGV20\tGV10\tGV5P\tGV5M\tSPR1\tGTE1\tGTE2\tGPI1\tGPI2\tGI5P\tGI20\tGPAV\tSPR2\tGEPQ\tSPR3\tPAC7\tPTE1\tPTE2\tPV5P\tPI5P\tPV5M\tPI5M\tPMCP\tPGAI\n")
            hkout.write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[degC]\t[degC]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[kV]\t[Byte]\t[V]\t[Byte]\t[Byte]\t[degC]\t[degC]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[kV]\t[Byte]\tAll units are just guessed!!!\n")
        if cmd:
            cmdout = open(self.wpath+"/%.4i/cmd/%.3i.cmd"%(self.year,self.doy),"w")
            cmdout.write("year\ttime\t\tdoy\t\tTrigger_mode\tMCP_level\tT_Cal\tE_Cal\tE_Cal\tTAC_slope\tSSD_enables\tDPPS_Level\tPAPS_Level\tHV_enables\n")
            cmdout.write("[year]\t[secs1970]\t[DayOfYear]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\t[Byte]\n")

        nxtcycexp = False
        for cyc in range(self.TIME.shape[0]):
            if (self.TIME[cyc][0] > self.t0) * (self.TIME[cyc][0] < self.t1):
                if not nxtcycexp:
                    expcyc=SBCYC()
                    expand(self.CYC[cyc],self.TIME[cyc],self.QAC[cyc],expcyc)
                cyctime = self.TIME[cyc][0] # All PHAs of one cycle get the starting time of the cycle as time
                cycdoy = time.gmtime(cyctime)
                cycdoy = cycdoy.tm_yday+cycdoy.tm_hour/24.+cycdoy.tm_min/(24.*60.)+cycdoy.tm_sec/(24.*60.*60.)
                if pha:
                    self.write_pha(expcyc,cyctime,cycdoy,phaout,laststep = False)
                if bra:
                    self.write_bra(expcyc,cyctime,cycdoy,braout,laststep = False)
                if tra:
                    self.write_tra(expcyc,cyctime,cycdoy,traout,laststep = False)
                if mra:
                    self.write_mra(expcyc,cyctime,cycdoy,mraout,laststep = False)
                if hk:
                    self.write_hk(expcyc,cyctime,cycdoy,hkout,laststep = False)
                if cmd:
                    self.write_cmd(expcyc,cyctime,cycdoy,cmdout)
            if (cyc+1 < self.TIME.shape[0]):
                if ((self.TIME[cyc+1][0] - self.TIME[cyc][0])>717) * ((self.TIME[cyc+1][0] - self.TIME[cyc][0])<723) : 
                    expcyc=SBCYC()
                    expand(self.CYC[cyc+1],self.TIME[cyc+1],self.QAC[cyc+1],expcyc)
                    nxtcycexp = True
                    if pha:
                        self.write_pha(expcyc,cyctime,cycdoy,phaout,laststep = True)
                    if bra:
                        self.write_bra(expcyc,cyctime,cycdoy,braout,laststep = True)
                    if tra:
                        self.write_tra(expcyc,cyctime,cycdoy,traout,laststep = True)
                    if mra:
                        self.write_mra(expcyc,cyctime,cycdoy,mraout,laststep = True)
                    if hk:
                        self.write_hk(expcyc,cyctime,cycdoy,hkout,laststep = True)
                else:
                    nxtcycexp = False
        if pha:
            for f in phaout:
                if f:
                    f.close()
        if bra:
            braout.close()
        if tra:
            traout.close()
        if mra:
            mraout.close()
        if hk:
            hkout.close()
        if cmd:
            cmdout.close()

    def extr_pha(self,expcyc,cyctime,cycdoy,laststep = False):
        if not laststep:
            for step in range(1,60):
                for nrpha in range(expcyc.asxNof[step]):
                    if expcyc.abxrng[step,nrpha] in self.prange:
                        self.phal.append([self.year,cyctime,cycdoy,step-1,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]])
        else:
            for step in range(1):
                for nrpha in range(expcyc.asxNof[step]):
                    if expcyc.abxrng[step,nrpha] in self.prange:
                        self.phal.append([self.year,cyctime,cycdoy,59,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]])

    def extr_bra(self,expcyc,cyctime,cycdoy,laststep = False):
        if not laststep:
            for step in range(1,60):
                for rng in range(4):
                    self.bral.append([self.year,cyctime,cycdoy,step-1,rng,expcyc.alxbr[step,rng,0],expcyc.alxbr[step,rng,1],expcyc.alxbr[step,rng,2],expcyc.alxbr[step,rng,3],expcyc.alxbr[step,rng,4],expcyc.alxbr[step,rng,5],expcyc.alxbr[step,rng,6],expcyc.alxbr[step,rng,7],expcyc.alxbr[step,rng,8]])
        else:
            for step in range(1):
                for rng in range(4):
                    self.bral.append([self.year,cyctime,cycdoy,59,rng,expcyc.alxbr[step,rng,0],expcyc.alxbr[step,rng,1],expcyc.alxbr[step,rng,2],expcyc.alxbr[step,rng,3],expcyc.alxbr[step,rng,4],expcyc.alxbr[step,rng,5],expcyc.alxbr[step,rng,6],expcyc.alxbr[step,rng,7],expcyc.alxbr[step,rng,8]])

    def extr_tra(self,expcyc,cyctime,cycdoy,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(8):
                    self.tral.append([self.year,cyctime,cycdoy,step-1,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec]])
        else:
            for step in range(1):
                for sec in range(8):
                    self.tral.append([self.year,cyctime,cycdoy,59,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec]])

    def extr_mra(self,expcyc,cyctime,cycdoy,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(9):
                    self.mral.append([self.year,cyctime,cycdoy,step-1,sec,expcyc.alxmr[step,0,sec],expcyc.alxmr[step,1,sec],expcyc.alxmr[step,2,sec],expcyc.alxmr[step,3,sec],expcyc.alxmr[step,4,sec],expcyc.alxmr[step,5,sec],expcyc.alxmr[step,6,sec],expcyc.alxmr[step,7,sec]])
        else:
            for step in range(1):
                for sec in range(9):
                    self.mral.append([self.year,cyctime,cycdoy,59,sec,expcyc.alxmr[step,0,sec],expcyc.alxmr[step,1,sec],expcyc.alxmr[step,2,sec],expcyc.alxmr[step,3,sec],expcyc.alxmr[step,4,sec],expcyc.alxmr[step,5,sec],expcyc.alxmr[step,6,sec],expcyc.alxmr[step,7,sec]])
                    
    def write_pha(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for nrpha in range(expcyc.asxNof[step]):
                    if expcyc.abxrng[step,nrpha] in self.prange:
                        fout[expcyc.abxrng[step,nrpha]].write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t\t%i\t\t%i\t\t%i\t%i\t%f\t%f\n"%(self.year,cyctime,cycdoy,step-1,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]))
        else:
            for step in range(1):
                for nrpha in range(expcyc.asxNof[step]):
                    if expcyc.abxrng[step,nrpha] in self.prange:
                        fout[expcyc.abxrng[step,nrpha]].write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t\t%i\t\t%i\t\t%i\t%i\t%f\t%f\n"%(self.year,cyctime,cycdoy,59,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]))

    def write_bra(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for rng in range(4):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,step-1,rng,expcyc.alxbr[step,rng,0],expcyc.alxbr[step,rng,1],expcyc.alxbr[step,rng,2],expcyc.alxbr[step,rng,3],expcyc.alxbr[step,rng,4],expcyc.alxbr[step,rng,5],expcyc.alxbr[step,rng,6],expcyc.alxbr[step,rng,7],expcyc.alxbr[step,rng,8]))
        else:
            for step in range(1):
                for rng in range(4):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,59,rng,expcyc.alxbr[step,rng,0],expcyc.alxbr[step,rng,1],expcyc.alxbr[step,rng,2],expcyc.alxbr[step,rng,3],expcyc.alxbr[step,rng,4],expcyc.alxbr[step,rng,5],expcyc.alxbr[step,rng,6],expcyc.alxbr[step,rng,7],expcyc.alxbr[step,rng,8]))

    def write_tra(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(8):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%.3f\t%.3f\n"%(self.year,cyctime,cycdoy,step-1,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec],expcyc.afxeoqdpu[step-1],expcyc.afxeoqaux[step-1]))
        else:
            for step in range(1):
                for sec in range(8):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%.3f\t%.3f\n"%(self.year,cyctime,cycdoy,59,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec],expcyc.afxeoqdpu[59],expcyc.afxeoqaux[59]))

    def write_mra(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(9):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,step-1,sec,expcyc.alxmr[step,0,sec],expcyc.alxmr[step,1,sec],expcyc.alxmr[step,2,sec],expcyc.alxmr[step,3,sec],expcyc.alxmr[step,4,sec],expcyc.alxmr[step,5,sec],expcyc.alxmr[step,6,sec],expcyc.alxmr[step,7,sec]))
        else:
            for step in range(1):
                for sec in range(9):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,59,sec,expcyc.alxmr[step,0,sec],expcyc.alxmr[step,1,sec],expcyc.alxmr[step,2,sec],expcyc.alxmr[step,3,sec],expcyc.alxmr[step,4,sec],expcyc.alxmr[step,5,sec],expcyc.alxmr[step,6,sec],expcyc.alxmr[step,7,sec]))
    def write_hk(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%.1f\t%.1f\t%i\t%i\t%i\t%i\t%.1f\t%i\t%.1f\t%i\t%i\t%.1f\t%.1f\t%i\t%i\t%i\t%i\t%.3f\t%i\n"%(self.year,cyctime,cycdoy,step-1,expcyc.afxhk[step,0],expcyc.afxhk[step,1],expcyc.afxhk[step,2],expcyc.afxhk[step,3],expcyc.afxhk[step,4],expcyc.afxhk[step,5],expcyc.afxhk[step,6],expcyc.afxhk[step,7],expcyc.afxhk[step,8],expcyc.afxhk[step,9],expcyc.afxhk[step,10],expcyc.afxhk[step,11],expcyc.afxhk[step,12],expcyc.afxhk[step,13],expcyc.afxhk[step,14],expcyc.afxhk[step,15],expcyc.afxhk[step,16],expcyc.afxhk[step,17],expcyc.afxhk[step,18],expcyc.afxhk[step,19],expcyc.afxhk[step,20],expcyc.afxhk[step,21],expcyc.afxhk[step,22],expcyc.afxhk[step,23],expcyc.afxhk[step,24]))
        else:
            for step in range(1):
                fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%.1f\t%.1f\t%i\t%i\t%i\t%i\t%.1f\t%i\t%.1f\t%i\t%i\t%.1f\t%.1f\t%i\t%i\t%i\t%i\t%.3f\t%i\n"%(self.year,cyctime,cycdoy,59,expcyc.afxhk[step,0],expcyc.afxhk[step,1],expcyc.afxhk[step,2],expcyc.afxhk[step,3],expcyc.afxhk[step,4],expcyc.afxhk[step,5],expcyc.afxhk[step,6],expcyc.afxhk[step,7],expcyc.afxhk[step,8],expcyc.afxhk[step,9],expcyc.afxhk[step,10],expcyc.afxhk[step,11],expcyc.afxhk[step,12],expcyc.afxhk[step,13],expcyc.afxhk[step,14],expcyc.afxhk[step,15],expcyc.afxhk[step,16],expcyc.afxhk[step,17],expcyc.afxhk[step,18],expcyc.afxhk[step,19],expcyc.afxhk[step,20],expcyc.afxhk[step,21],expcyc.afxhk[step,22],expcyc.afxhk[step,23],expcyc.afxhk[step,24]))
        return True
    def write_cmd(self,expcyc,cyctime,cycdoy,fout):
        fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,expcyc.abxcmd[0],expcyc.abxcmd[1],expcyc.abxcmd[2],expcyc.abxcmd[3],expcyc.abxcmd[4],expcyc.abxcmd[5],expcyc.abxcmd[6],expcyc.abxcmd[7],expcyc.abxcmd[8],expcyc.abxcmd[9]))
        return True

if __name__ == '__main__':
    years = [1998,1999]
    days = range(1,367)
    for year in years:
        print year
        for day in days:
            try:
                print "day : ",day
                d = extrswx(year=year,doy=day,wpath="/data/ivar/ace/swics/lv0",prange=(0,1,2,3))
                d.save_ascii()
                del(d)
            except:
                print "Problems extracting DoY ",day

