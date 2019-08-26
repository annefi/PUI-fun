from pylib import dbData
from numpy import *
from ACE.SWICS.tools.tof2mq import tof2mq_new_fulltof
from ACE.SWICS.tools.ancil import getvelocity_allsteps
from ACE.LOADER.ace_ancil import ace_ancil
from ACE.LOADER.ace_sweswi import ace_sweswi
from ACE.LOADER.ace_mag import ace_mag
from pylib.etMisc import loading_bar

class ace_swics_pha(dbData):
    def load_data(self,*args,**kwargs):
        if kwargs.has_key("year"):
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if kwargs.has_key("tf"):
            self.tf = kwargs["tf"]
        if kwargs.has_key("mqrange"):
            self.mqrange = kwargs["mqrange"]
        else:
            self.mqrange = False
        if kwargs.has_key("path"):
            self.path = kwargs["path"]
        else:
            self.path = "/data/etph/ace/swics/lv0/"
        if kwargs.has_key("mag"):
            self.mag = kwargs["mag"]
        else:
            self.mag = True
        if kwargs.has_key("swprops"):
            self.swprops = kwargs["swprops"]
        else:
            self.swprops = True
        if kwargs.has_key("rng"):
            self.rng = kwargs["rng"]
        else:
            self.rng = (0,1,2)
        self.data["year"]=array([])
        self.data["doy"]=array([])
        self.data["epq"]=array([],dtype=int64)
        self.data["tof"]=array([])
        self.data["esd"]=array([])
        self.data["did"]=array([])
        self.data["rng"]=array([])
        self.data["sec"]=array([])
        self.data["twt"]=array([])
        self.data["swt"]=array([])
        self.data["aspphi"]=array([])
        self.data["asptheta"]=array([])
        self.data["aspang"]=array([])
        self.data["vH+"] = array([])
        self.data["vHe2+"] = array([])
        self.data["mq"] = array([])
        if self.swprops:
            self.data["vsw"] = array([])
            self.data["dsw"] = array([])
            self.data["tsw"] = array([])
            self.data["wHe1+"] = array([])
            self.data["wO1+"] = array([])
            self.data["wC1+"] = array([])

        if self.mag:
            self.data["B"] = array([])
            self.data["Bx"] = array([])
            self.data["By"] = array([])
            self.data["Bz"] = array([])
            self.data["Bphi"] = array([])
            self.data["Btheta"] = array([])
            self.data["Balpha"] = array([])


        for year in self.year:
            self.load_year(year)

        self.epq_arr = array([100.,86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611489])
        eff = loadtxt("/data/etph/ace/efficencies/H1+_dcr.eff")
        effdcr = eff[:,1]
        # efficiencies are only for step 1..58 just add two entries for step 0 and 59 (assume equal to 1 and 58, respectively)
        effdcr=append(effdcr[0],effdcr)
        effdcr=append(effdcr,effdcr[-1])
        self.effdcr = effdcr
        weff = 1./effdcr

        self.data["energypq"] = self.epq_arr[self.data["epq"]]
        self.data["weff"] = weff[self.data["epq"]-1]
        self.data["effdcr"] = effdcr[self.data["epq"]-1]
        


    def save_ascii(self):
        fname = str(self.year[0]) + "_" +  str(self.tf[0][0]) + "_" + str(self.tf[-1][1]) + ".dat"
        fout = open("/data/ivar/berger/ace/swics_protons_lario/%s"%(fname), "w")
        fout.write("DoY\t\tE/Q [keV/amu]\tvH+[km/s]\t#Counts\tBrw\tEff\tvsw [km/s]\tdsw [1/cm^3]\ttsw [K]\tB[nT]\n")
        self.reset_mask("Master")
        self.set_mask("Master","epq",1,58,reset = True)
        self.set_mask("Master","mq",0.9,1.2,reset = True)
        times = self.get_data("Master","doy")
        epq = self.get_data("Master","energypq")
        vsw = self.get_data("Master","vsw")
        dsw = self.get_data("Master","dsw")
        tsw = self.get_data("Master","tsw")
        B = self.get_data("Master","B")
        twt = self.get_data("Master","twt")
        vH = self.get_data("Master","vH+")
        vH = unique(vH)
        bintimes = unique(times)
        bintimes = append(bintimes,bintimes[-1]+1./24./5.)
        Hcounts,tbins,ebins = histogram2d(times,epq,bins=(bintimes,self.epq_arr[-2::-1]))
        HBr,tbins,ebins = histogram2d(times,epq,bins=(bintimes,self.epq_arr[-2::-1]),weights = twt)
        HBr = 1.*HBr/Hcounts
        HBr[isnan(HBr)] = 0.
        Hvsw,tbins = histogram(times,bins=(bintimes),weights = vsw)
        NHvsw,tbins = histogram(times,bins=(bintimes))
        Hvsw = 1.*Hvsw/NHvsw
        Hdsw,tbins = histogram(times,bins=(bintimes),weights = dsw)
        NHdsw,tbins = histogram(times,bins=(bintimes))
        Hdsw = 1.*Hdsw/NHdsw
        Htsw,tbins = histogram(times,bins=(bintimes),weights = tsw)
        NHtsw,tbins = histogram(times,bins=(bintimes))
        Htsw = 1.*Htsw/NHtsw
        HB,tbins = histogram(times,bins=(bintimes),weights = B)
        NHB,tbins = histogram(times,bins=(bintimes))
        HB = 1.*HB/NHB
        for t in range(Hcounts.shape[0]):
            for e in range(0,Hcounts.shape[1]):
                fout.write("%.8f\t%.8f\t%.1f\t\t%i\t%.2f\t%.4f\t%.1f\t\t%.3f\t\t%.0f\t%.3f\n"%(tbins[t],ebins[e],vH[e],Hcounts[t,e],HBr[t,e],self.effdcr[e],Hvsw[t],Hdsw[t],Htsw[t],HB[t]))
        fout.close()
        self.reset_mask("Master")
        
    def calc_mq(self):
        self.data["mq"] = tof2mq_new_fulltof(self.data["epq"]-1,self.data["tof"])
        
        
    def load_year(self,year):
        doys = array([])
        epq = array([],dtype=int64)
        tof = array([])
        esd = array([])
        did = array([])
        rng = array([])
        sec = array([])
        twt = array([])
        swt = array([])
        mq = array([])
        print "Loading PHAs",year
        for doy in range(self.tf[0][0],self.tf[-1][1]+1):
            loading_bar(self.tf[-1][1]+1-self.tf[0][0],doy-self.tf[0][0]+1,"#",MSG = "Loading PHAs DoY %i"%(doy))
            for tmprng in self.rng:
                try:
                    dat = loadtxt(self.path+"%.4i/pha/%.3i.ph%.1i"%(year,doy,tmprng),skiprows=2)
                    #dat = loadtxt("/home/ivar/berger/projects/chargestates/rng%i/%.4i/%.3i.pha"%(tmprng,year,doy),skiprows=2)
                    tmpmq = tof2mq_new_fulltof(int64(dat[:,3])-1,dat[:,4])
                    if self.mqrange:
                        mask = (tmpmq > self.mqrange[0]) * (tmpmq < self.mqrange[1])
                    else:
                        mask = ones(dat[:,2].shape,bool)
                    doys = append(doys,dat[:,2][mask])
                    epq = append(epq,int64(dat[:,3])[mask])
                    tof = append(tof,dat[:,4][mask])
                    esd = append(esd,dat[:,5][mask])
                    did = append(did,dat[:,6][mask])
                    rng = append(rng,dat[:,7][mask])
                    sec = append(sec,dat[:,8][mask])
                    twt = append(twt,dat[:,11][mask])
                    swt = append(swt,dat[:,12][mask])
                    mq = append(mq,tmpmq[mask])
                except:
                    print "No rng%i data for doy "%(tmprng),doy,year
        years = ones(doys.shape)*year
        self.data["doy"] = append(self.data["doy"],doys)
        self.data["epq"] = append(self.data["epq"],epq)
        self.data["tof"] = append(self.data["tof"],tof)
        self.data["esd"] = append(self.data["esd"],esd)
        self.data["did"] = append(self.data["did"],did)
        self.data["rng"] = append(self.data["rng"],rng)
        self.data["sec"] = append(self.data["sec"],sec)
        self.data["twt"] = append(self.data["twt"],twt)
        self.data["swt"] = append(self.data["swt"],swt)
        self.data["mq"] = append(self.data["mq"],mq)
        self.data["year"] = append(self.data["year"],years)
        print "PHAs loaded",year
        print "Loading ancillary data",year
        anc_data=ace_ancil()
        anc_data.set_mask("Master","year",year,year)
        anc_doy = anc_data.get_data("Master","doy")
        aphi = anc_data.get_data("Master","aphi")
        atheta = anc_data.get_data("Master","atheta")
        aspang = anc_data.get_data("Master","aspang")
        ind=searchsorted(anc_doy,doys)
        ind[ind==aphi.shape[0]] = ind[ind==aphi.shape[0]] - 1 
        self.data["aspphi"]=append(self.data["aspphi"],aphi[ind])
        self.data["asptheta"]=append(self.data["asptheta"],atheta[ind])
        self.data["aspang"]=append(self.data["aspang"],aspang[ind])
        print "Ancillary data synced",year
        del(anc_data)
        if self.swprops:
            print "Loading SW data",year
            sweswi = ace_sweswi(year=year,fmt = "old", tf = [[int(doys[0]),int(doys[-1])]])
            uT,ind=unique(doys,return_inverse=True)
            sweswi.bin_data(append(uT,uT[-1]+1./24./5.),uT,years[ind],prod1="time",prod2="d00")
            self.data["vsw"] = append(self.data["vsw"],sweswi.data["vsw"][ind])
            self.data["dsw"] = append(self.data["dsw"],sweswi.data["dsw"][ind])
            self.data["tsw"] = append(self.data["tsw"],sweswi.data["tsw"][ind])
            print "SW data synced",year
            self.data["wHe1+"] = append(self.data["wHe1+"],getvelocity_allsteps(4,1,epq)/sweswi.data["vsw"][ind])
            self.data["wO1+"] = append(self.data["wO1+"],getvelocity_allsteps(16,1,epq)/sweswi.data["vsw"][ind])
            self.data["wC1+"] = append(self.data["wC1+"],getvelocity_allsteps(12,1,epq)/sweswi.data["vsw"][ind])
            print "W calculated",year
            del(sweswi)
        self.data["vH+"] = append(self.data["vH+"],getvelocity_allsteps(1,1,epq))
        self.data["vHe2+"] = append(self.data["vHe2+"],getvelocity_allsteps(4,2,epq))
        if self.mag:
            print "Loading MAG data",year
            mag = ace_mag(year = year, tf = [[int(doys[0]),int(doys[-1])]], fmt = "old")
            uT,ind=unique(doys,return_inverse=True)
            mag.transform_data(append(uT,uT[-1]+1./24./5.),prodt="time")
            print "Start syncing MAG data",year
            mag.bin_data(append(uT,uT[-1]+1./24./5.),uT,self.data["year"][ind],prod1="time",prod2="d00")
            self.data["B"] = append(self.data["B"],mag.data["B"][ind])
            self.data["Bx"] = append(self.data["Bx"],mag.data["Bx"][ind])
            self.data["By"] = append(self.data["By"],mag.data["By"][ind])
            self.data["Bz"] = append(self.data["Bz"],mag.data["Bz"][ind])
            self.data["Bphi"] = append(self.data["Bphi"],mag.data["phi"][ind])
            self.data["Btheta"] = append(self.data["Btheta"],mag.data["theta"][ind])
            self.data["Balpha"] = append(self.data["Balpha"],mag.data["alpha"][ind])
            print "MAG data synced",year
            del(mag)
    
