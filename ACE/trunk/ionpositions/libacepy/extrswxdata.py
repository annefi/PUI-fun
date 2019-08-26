from decoded import *
from bittools import *
from expand import expand
#from Scientific.IO import NetCDF
from scipy.io.netcdf import netcdf_file as NetCDFFile
import time
import calendar
from numpy import save

"""
phas=[]
for doy in range(365,366):
    filein=NetCDFFile("/data/ivar/berger/acedata/2007/2006%.3i.nc"%(doy),"r")
    cyc=filein.variables['cyc'][:]
    #cyc=vectorize(uint8)(cyc)
    cyc2=cyc.view(uint8)
    QAC=filein.variables["QAC"][:]
    time=filein.variables["time"][:]
    #expcyc=SBCYC()
    #expand(cyc2[0],time[0],QAC[0],expcyc)

    for i in range(120,121):
        try :
            expcyc=SBCYC()
            expand(cyc2[i],time[i],QAC[i],expcyc)
            print "Doy,EDB : "+str(doy)+","+str(i)
            for step in range(60):
                for nrpha in range(expcyc.asxNof[step]):
                    phas.append([step,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]])
        except :
            print "Doy,EDB : "+str(doy)+","+str(i), "NO DATA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
            
step = 0
tof = 1
esd = 2
did = 3
rng = 4
sec = 5
mas = 6
moq = 7
twgt = 8
swgt = 9
phas=array(phas)
"""

class extrswx(object):
    def __init__(self,rpath="/data/missions/ace/swics/lv1/",wpath="/data/etph/ace/lv0/",year=2007,doy=1,prange = range(4)):
        self.rpath = rpath
        self.wpath = wpath
        self.year = year
        self.doy = doy
        self.nxtcyctimes = []
        self.cyctimes = []
        self.prange = prange
        
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
        if (self.doy == 1):
            if isleap:
                prfilein = self.load_netcdf(self.year-1,366)
            else:
                prfilein = self.load_netcdf(self.year-1,365)
        else:
            prfilein = self.load_netcdf(self.year,self.doy-1)
        # Aktueller Tag
        actfilein = self.load_netcdf(self.year,self.doy)
        # Nachfolgender Tag
        if (not(isleap) and self.doy == 365) or (isleap and self.doy == 366):
            nxtfilein = self.load_netcdf(self.year+1,1)
        else:
            nxtfilein = self.load_netcdf(self.year,self.doy+1)
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
        prtime = prfilein.variables["time"][:]
        acttime = actfilein.variables["time"][:]
        nxttime = nxtfilein.variables["time"][:]
        prepoch = prfilein.variables["epoch"][:]
        actepoch = actfilein.variables["epoch"][:]
        nxtepoch = nxtfilein.variables["epoch"][:]
        #print "prtime :" ,prtime.shape,prepoch-prtime
        print "acttime =" ,acttime
        #print "nxttime :" ,nxttime.shape,nxtepoch-nxttime
        
        # maskiere alle Cycles; t1+720 da der erste cycle des neuen tages normalerweise den letzten E/Q-step des vorherigen cycles enthaelt
        prmask = (prtime[:,0] >= self.t0) * (prtime[:,0] < self.t1+720) 
        actmask = (acttime[:,0] >= self.t0) * (acttime[:,0] < self.t1+720) 
        nxtmask = (nxttime[:,0] >= self.t0) * (nxttime[:,0] < self.t1+720) 
        print sum(prmask),sum(actmask),sum(nxtmask)
        prcyc = prfilein.variables["cyc"][:]
        prcyc = prcyc.view(uint8)
        prQAC = prfilein.variables["QAC"][:]
        actcyc = actfilein.variables["cyc"][:]
        actcyc = actcyc.view(uint8)
        print "actcyc.shape = ",actcyc.shape
        actQAC = actfilein.variables["QAC"][:]
        nxtcyc = nxtfilein.variables["cyc"][:]
        nxtcyc = nxtcyc.view(uint8)
        nxtQAC = nxtfilein.variables["QAC"][:]
        self.CYC = zeros((0,60,2436),uint8)
        self.QAC = zeros((0,60),uint8)
        self.TIME = zeros((0,60),uint8)
        self.EPOCH = zeros((0,60),uint8)
        self.CYC = append(self.CYC,prcyc[prmask],axis=0)
        self.QAC = append(self.QAC,prQAC[prmask],axis=0)
        self.TIME = append(self.TIME,prtime[prmask],axis=0)
        print "TIME.shape = ",self.TIME.shape
        self.EPOCH = append(self.EPOCH,prepoch[prmask],axis=0)
        self.CYC = append(self.CYC,actcyc[actmask],axis=0)
        self.QAC = append(self.QAC,actQAC[actmask],axis=0)
        self.TIME = append(self.TIME,acttime[actmask],axis=0)
        print "TIME.shape = ",self.TIME.shape
        self.EPOCH = append(self.EPOCH,actepoch[actmask],axis=0)
        self.CYC = append(self.CYC,nxtcyc[nxtmask],axis=0)
        self.QAC = append(self.QAC,nxtQAC[nxtmask],axis=0)
        self.TIME = append(self.TIME,nxttime[nxtmask],axis=0)
        print "TIME.shape = ",self.TIME.shape
        self.EPOCH = append(self.EPOCH,nxtepoch[nxtmask],axis=0)
        print "TIME.shape = ",self.TIME.shape
        print "CYC.shape = ",self.CYC.shape
        

        prfilein.close()
        nxtfilein.close()
        actfilein.close()
        """
        nxtfilein=NetCDFFile(self.rpath+"%.4i/%.4i%.3i.nc"%(self.nxtyear,self.nxtyear,self.nxtdoy),"r")
        self.nxtcyc=nxtfilein.variables['cyc'][:]
        self.nxtcyc2=self.nxtcyc.view(uint8)
        self.nxtQAC=nxtfilein.variables["QAC"][:]
        self.nxttime=nxtfilein.variables["time"][:]
        print "loading %s%.4i/%.4i%.3i.nc"%(self.rpath,self.year,self.year,self.doy)
        filein=NetCDFFile(self.rpath+"%.4i/%.4i%.3i.nc"%(self.year,self.year,self.doy),"r")
        self.cyc=filein.variables['cyc'][:]
        self.cyc2=self.cyc.view(uint8)
        self.QAC=filein.variables["QAC"][:]
        self.time=filein.variables["time"][:]
        self.get_cycletimes()
        """

    def load_netcdf(self,year,day):
        print "loading %s%.4i/%.4i%.3i.nc"%(self.rpath,year,year,day)
        filein=NetCDFFile(self.rpath+"%.4i/%.4i%.3i.nc"%(year,year,day),"r",mmap = False)
        return filein
        
    def get_cycletimes(self,times):
        cyctimes = []
        for t in times:
            tmpt = time.gmtime(t[0])
            cyctimes.append(tmpt.tm_yday+tmpt.tm_hour/24.+tmpt.tm_min/(24.*60.)+tmpt.tm_sec/(24.*60.*60.))
        return cyctimes

    def save_bin(self,pha=True,bra=True,sra=True,mra=True):
        if pha:
            self.phal = []
        if bra:
            self.bral = []
        if sra:
            self.sral = []
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
                if sra:
                    self.extr_sra(expcyc,cyctime,cycdoy,laststep = False)
                if mra:
                    self.extr_mra(expcyc,cyctime,cycdoy,laststep = False)
            if (cyc+1 < self.TIME.shape[0]):
                if ((self.TIME[cyc+1][0] - self.TIME[cyc][0])>717) * ((self.TIME[cyc+1][0] - self.TIME[cyc][0])<723) : 
                    expcyc=SBCYC()
                    expand(self.CYC[cyc],self.TIME[cyc],self.QAC[cyc],expcyc)
                    nxtcycexp = True
                    if pha:
                        self.extr_pha(expcyc,cyctime,cycdoy,laststep = True)
                    if bra:
                        self.extr_bra(expcyc,cyctime,cycdoy,laststep = True)
                    if sra:
                        self.extr_sra(expcyc,cyctime,cycdoy,laststep = True)
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
        if sra:
            self.sral = array(self.sral)
            sraout = open(self.wpath+"/%.4i/%.3i.sra.npy"%(self.year,self.doy),"w")
            save(sraout,self.sral)
            sraout.close()
        if mra:
            self.mral = array(self.mral)
            mraout = open(self.wpath+"/%.4i/%.3i.mra.npy"%(self.year,self.doy),"w")
            save(mraout,self.mral)
            mraout.close()

        

        
    def save_ascii(self,pha=True,bra=True,sra=True,mra=True):
        if pha:
            phaout = open(self.wpath+"/%.4i/%.3i.pha"%(self.year,self.doy),"w")
            phaout.write("year\ttime\t\tdoy\t\teoq\ttof\tesd\tdid\t\trng\t\tsec\t\tmas\tmoq\ttwgt\t\tswgt\n")
            phaout.write("[year]\t[secs1970]\t[DayOfYear]\t[#step]\t[CH]\t[CH]\t[#Detector]\t[#Priority]\t[#Spin]\t\t[CH]\t[CH]\t[totalweight]\t[sectorweight]\n")
        if bra:
            braout = open(self.wpath+"/%.4i/%.3i.bra"%(self.year,self.doy),"w")
            braout.write("year\ttime\t\tdoy\t\teoq\trng\tbr0\tbr1\tbr2\tbr3\tbr4\tbr5\tbr6\tsbr7\tbrall\n")
            braout.write("[year]\t[secs1970]\t[DayOfYear]\t[#step]\t[range]\t[sec0]\t[sec1]\t[sec2]\t[sec3]\t[sec4]\t[sec5]\t[sec6]\t[sec7]\t[allsecs]\n")
        if sra:
            sraout = open(self.wpath+"/%.4i/%.3i.sra"%(self.year,self.doy),"w")
            sraout.write("year\ttime\t\tdoy\t\teoq\tsec\tHeaux\tHaux\tssd\ttcr\tdcr\tfsr\n")
            sraout.write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[sect]\t[/1.5s]\t[/1.5s]\t[/1.5s]\t[/1.5s]\t[/1.5]\t[/1.5]\t 'Sector8=allsecs [/12s]\n")
        if mra:
            mraout = open(self.wpath+"/%.4i/%.3i.mra"%(self.year,self.doy),"w")
            mraout.write("year\ttime\t\tdoy\t\teoq\tsec\tmr0\tmr1\tmr2\tmr3\tmr4\tmr5\tmr6\tmr7\n")
            mraout.write("[year]\t[secs1970]\t[DayOfYear]\t[step]\t[sect]\t[H+]\t[He2+]\t[He+]\t[O7+]\t[O6+]\t[Fe]\t[Si]\t[Err]\t'Sector 8 means sum of all sectors'\n")

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
                if sra:
                    self.write_sra(expcyc,cyctime,cycdoy,sraout,laststep = False)
                if mra:
                    self.write_mra(expcyc,cyctime,cycdoy,mraout,laststep = False)
            if (cyc+1 < self.TIME.shape[0]):
                if ((self.TIME[cyc+1][0] - self.TIME[cyc][0])>717) * ((self.TIME[cyc+1][0] - self.TIME[cyc][0])<723) : 
                    expcyc=SBCYC()
                    expand(self.CYC[cyc],self.TIME[cyc],self.QAC[cyc],expcyc)
                    nxtcycexp = True
                    if pha:
                        self.write_pha(expcyc,cyctime,cycdoy,phaout,laststep = True)
                    if bra:
                        self.write_bra(expcyc,cyctime,cycdoy,braout,laststep = True)
                    if sra:
                        self.write_sra(expcyc,cyctime,cycdoy,sraout,laststep = True)
                    if mra:
                        self.write_mra(expcyc,cyctime,cycdoy,mraout,laststep = True)
                else:
                    nxtcycexp = False
        if pha:
            phaout.close()
        if bra:
            braout.close()
        if sra:
            sraout.close()
        if mra:
            mraout.close()

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

    def extr_sra(self,expcyc,cyctime,cycdoy,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(8):
                    self.sral.append([self.year,cyctime,cycdoy,step-1,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec]])
        else:
            for step in range(1):
                for sec in range(8):
                    self.sral.append([self.year,cyctime,cycdoy,59,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec]])

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
                        fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t\t%i\t\t%i\t\t%i\t%i\t%f\t%f\n"%(self.year,cyctime,cycdoy,step-1,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]))
        else:
            for step in range(1):
                for nrpha in range(expcyc.asxNof[step]):
                    if expcyc.abxrng[step,nrpha] in self.prange:
                        fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t\t%i\t\t%i\t\t%i\t%i\t%f\t%f\n"%(self.year,cyctime,cycdoy,59,expcyc.asxtof[step,nrpha],expcyc.abxesd[step,nrpha],expcyc.abxdid[step,nrpha],expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha],expcyc.afxmas[step,nrpha],expcyc.afxmoq[step,nrpha],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],8],expcyc.afxwgt[step,expcyc.abxrng[step,nrpha],expcyc.abxsec[step,nrpha]]))

    def write_bra(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for rng in range(4):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,step-1,rng,expcyc.alxbr[step,rng,0],expcyc.alxbr[step,rng,1],expcyc.alxbr[step,rng,2],expcyc.alxbr[step,rng,3],expcyc.alxbr[step,rng,4],expcyc.alxbr[step,rng,5],expcyc.alxbr[step,rng,6],expcyc.alxbr[step,rng,7],expcyc.alxbr[step,rng,8]))
        else:
            for step in range(1):
                for rng in range(4):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,59,rng,expcyc.alxbr[step,rng,0],expcyc.alxbr[step,rng,1],expcyc.alxbr[step,rng,2],expcyc.alxbr[step,rng,3],expcyc.alxbr[step,rng,4],expcyc.alxbr[step,rng,5],expcyc.alxbr[step,rng,6],expcyc.alxbr[step,rng,7],expcyc.alxbr[step,rng,8]))

    def write_sra(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(8):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,step-1,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec]))
        else:
            for step in range(1):
                for sec in range(8):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,59,sec,expcyc.alxsr[step,0,sec],expcyc.alxsr[step,1,sec],expcyc.alxsr[step,2,sec],expcyc.alxsr[step,3,sec],expcyc.alxsr[step,4,sec],expcyc.alxsr[step,5,sec]))

    def write_mra(self,expcyc,cyctime,cycdoy,fout,laststep = False):
        if not laststep:
            for step in range(1,60):
                for sec in range(9):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,step-1,sec,expcyc.alxmr[step,0,sec],expcyc.alxmr[step,1,sec],expcyc.alxmr[step,2,sec],expcyc.alxmr[step,3,sec],expcyc.alxmr[step,4,sec],expcyc.alxmr[step,5,sec],expcyc.alxmr[step,6,sec],expcyc.alxmr[step,7,sec]))
        else:
            for step in range(1):
                for sec in range(9):
                    fout.write("%i\t%i\t%f\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n"%(self.year,cyctime,cycdoy,59,sec,expcyc.alxmr[step,0,sec],expcyc.alxmr[step,1,sec],expcyc.alxmr[step,2,sec],expcyc.alxmr[step,3,sec],expcyc.alxmr[step,4,sec],expcyc.alxmr[step,5,sec],expcyc.alxmr[step,6,sec],expcyc.alxmr[step,7,sec]))
                            
for day in range(264,265):
    #try:
        print "day : ",day
        d = extrswx(year=2006,doy=day,prange=[2],wpath="/home/ivar/berger/projects/chargestates/rng2")
        d.load_data()
        d.save_ascii()
        del(d)
    #except:
    #    print "Problems extracting DoY ",day
        #print str(day)+" : "+str(d.nxtcyctimes[0])+" , "+str(d.nxtcyctimes[-1])+" , "+str(d.cyctimes[0])+" , "+str(d.cyctimes[-1])

