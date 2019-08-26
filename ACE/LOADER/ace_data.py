from ace_swics import ace_swics
from ace_swics_dcrtcr import ace_swics_dcrtcr
from ace_mag import ace_mag
from ace_swepam import ace_swepam
from ace_sweswi import ace_sweswi
from ace_utils import get_mass,calc_day00
from ace_ancil import ace_ancil
from pylib import dbData
from numpy import *
from scipy import constants
import pylab

class ace_data(dbData):
    """
    Keywords
    year -> list of years, default = [2007]
    ion -> list of ions, default = ['He2+']
    tf -> list of periods in DoY (the same for all years), default = [], 'all' -> [[1.,367.]]
    path -> string, default = '/data/etph/ace/', (outdated, since subclasses and defaults within are used)
    """

    def load_data(self,*args,**kwargs):
        if kwargs.has_key("year"):
            if isinstance(kwargs["year"],list):
                self.year=kwargs["year"]
            elif isinstance(kwargs["year"],int) or isinstance(kwargs["year"],float):
                self.year=[kwargs["year"]]
        else:
            self.year=[2007]
        if kwargs.has_key("ion"):
            if isinstance(kwargs["ion"],list):
                self.ion=kwargs["ion"]
            elif isinstance(kwargs["ion"],str):
                self.ion=[kwargs["ion"]]
        else:
            self.ion=["He2+"]
        if kwargs.has_key("tf"):
            if isinstance(kwargs["tf"],list) or isinstance(kwargs["tf"],ndarray):
                self.timeframe=kwargs["tf"]
            elif kwargs["tf"]=="all":
                self.timeframe=[[1.,367]]
            else:
                print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
                self.timeframe==[]
        else:
            print "periods need to be specified via key tf ([[start,stop],...,[start,stop]] or 'all'), no data loaded"
            self.timeframe==[]
        if kwargs.has_key("path"):
            self.path=kwargs["path"]
        else:
            self.path="/data/etph/ace/"
        self.dcrtcr = True
        if kwargs.has_key("dcrtcr"):
            if not kwargs["dcrtcr"]:
                print "dcrtcr_flag :",kwargs["dcrtcr"]
                self.dcrtcr = False
        swi_data=ace_swics(ion=self.ion,year=self.year,tf=self.timeframe,fmt="new")
        mag_data=ace_mag(year=self.year,tf=self.timeframe,fmt="new")
        swe_data=ace_sweswi(year=self.year,tf=self.timeframe,fmt="new")
        if self.dcrtcr:
            swi_dcrtcr_data=ace_swics_dcrtcr(year=self.year,tf=self.timeframe,fmt="new")
        anc_data=ace_ancil()
        anc_data.add_data("d00",calc_day00(anc_data.data["year"],anc_data.data["doy"]))
        uTi,index=unique(swi_data.data["d00"],return_inverse=True)
        uTi=append(uTi,uTi[-1]+1./24./5.)
        ind=searchsorted(anc_data.data["d00"],swi_data.data["d00"])
        self.data["aspphi"]=anc_data.data["aphi"][ind]
        self.data["asptheta"]=anc_data.data["atheta"][ind]
        self.data["aspang"]=anc_data.data["aspang"][ind]
        #index=searchsorted(uTi,swi_data.data["d00"])
        #mag_data.bin_data(uTi,unique(swi_data.data["time"]))
        #swe_data.bin_data(uTi,unique(swi_data.data["time"]))
        swi_data.calc_moments()
        if self.dcrtcr:
            swi_dcrtcr_data.calc_moments()
        for key in swi_data.data.keys():
            if key in swi_data.data.expand.keys():
                self.data.add_reduced_data(key,swi_data.data.__getitem__(key,raw=True),swi_data.data.expand[key],expansion=swi_data.data.expansion[swi_data.data.expand[key]])
            else:
                self.data[key]=swi_data.data[key]
        if self.dcrtcr:
            for key in swi_dcrtcr_data.data.keys():
                if key in swi_dcrtcr_data.data.expand.keys():
                    self.data.add_reduced_data(key,swi_dcrtcr_data.data.__getitem__(key,raw=True),swi_dcrtcr_data.data.expand[key],expansion=swi_dcrtcr_data.data.expansion[swi_dcrtcr_data.data.expand[key]])
                else:
                    self.data[key]=swi_dcrtcr_data.data[key]
        for key in mag_data.data.keys():
            if key!="d00" and key!="time":
                self.data.add_reduced_data(key,mag_data.data[key],self.data.expand["d00"])
        for key in swe_data.data.keys():
            if key!="d00" and key!="time":
                self.data.add_reduced_data(key,swe_data.data[key],self.data.expand["d00"])
        for ion in self.ion:
            self.add_reduced_data("dv"+ion,self.data.__getitem__("vel"+ion,raw=True)-self.data.__getitem__("vsw",raw=True),self.data.expand["d00"])
            if self.dcrtcr:
                self.add_reduced_data("sdv"+ion,self.data.__getitem__("vel"+ion,raw=True)-self.data.__getitem__("velH1+",raw=True),self.data.expand["d00"])
        self.add_reduced_data("valf",21.8*self.data.__getitem__("B",raw=True)/sqrt(self.data.__getitem__("dsw",raw=True)),self.data.expand["d00"])
        self.add_reduced_data("vthsw",sqrt((constants.k*self.data.__getitem__("tsw",raw=True))/constants.atomic_mass)/1000.,self.data.expand["d00"])
        self.add_reduced_data("colage",log(6.4e8*self.data.__getitem__("dsw",raw=True)/(self.data.__getitem__("vsw",raw=True)*self.data.__getitem__("tsw",raw=True)**1.5)),self.data.expand["d00"])
        if self.dcrtcr:
            self.add_reduced_data("scolage",log(6.4e8*self.data.__getitem__("dsw",raw=True)/(self.data.__getitem__("vsw",raw=True)*self.data.__getitem__("tH1+",raw=True)**1.5)),self.data.expand["d00"])
        for ion in self.ion:
            self.add_reduced_data("dvalf"+ion,self.data.__getitem__("dv"+ion,raw=True)/self.data.__getitem__("valf",raw=True),self.data.expand["d00"])
            if self.dcrtcr:
                self.add_reduced_data("sdvalf"+ion,self.data.__getitem__("sdv"+ion,raw=True)/self.data.__getitem__("valf",raw=True),self.data.expand["d00"])
        self.calc_moments_alf()
        self.calc_swtype()
        self.add_reduced_data("pbeta",(self.data.__getitem__("dsw",raw=True)*1.e6*constants.k*self.data.__getitem__("tsw",raw=True))/(((self.data.__getitem__("B",raw=True)*1e-9)**2)/(2.*constants.mu_0)),self.data.expand["d00"])
        if self.dcrtcr:
            self.add_reduced_data("spbeta",(self.data.__getitem__("dsw",raw=True)*1.e6*constants.k*self.data.__getitem__("tH1+",raw=True))/(((self.data.__getitem__("B",raw=True)*1e-9)**2)/(2.*constants.mu_0)),self.data.expand["d00"])
        for ion in self.ion:
            self.add_reduced_data("vth"+ion+"p+",self.data.__getitem__("vth"+ion,raw=True)/self.data.__getitem__("vthsw",raw=True),self.data.expand["d00"])
            self.add_reduced_data("t"+ion+"p+",self.data.__getitem__("vth"+ion+"p+",raw=True)**2*get_mass(ion),self.data.expand["d00"])
            if self.dcrtcr:
                self.add_reduced_data("svth"+ion+"p+",self.data.__getitem__("vth"+ion,raw=True)/self.data.__getitem__("vthH1+",raw=True),self.data.expand["d00"])
                self.add_reduced_data("st"+ion+"p+",self.data.__getitem__("svth"+ion+"p+",raw=True)**2*get_mass(ion),self.data.expand["d00"])
            
    def add_stdmask(self):
        self.add_mask("ejecta")
        self.add_mask("sec_rev")
        self.add_mask("stream_belt")
        self.add_mask("cor_hole")
        self.set_mask("ejecta","ejecta",1.,op="eq",reset=True)
        self.set_mask("sec_rev","sec_rev",1.,op="eq",reset=True)
        self.set_mask("stream_belt","stream_belt",1.,op="eq",reset=True)
        self.set_mask("cor_hole","cor_hole",1.,op="eq",reset=True)

    def calc_rdv(self):
        pol=ones(self.data.__getitem__("d00",raw=True).shape[0])*-1.
        pol[(self.data.__getitem__("phi",raw=True)>-45)*(self.data.__getitem__("phi",raw=True)<=135.)]=1.
        gamma=self.data.__getitem__("alpha",raw=True)*1.
        gamma[pol==1]=180.-gamma[pol==1]
        self.add_reduced_data("pol",pol,self.data.expand["d00"])
        self.add_reduced_data("gamma",gamma,self.data.expand["d00"])
        for ion in self.ion:
            rdv0=self.data.__getitem__("vsw",raw=True)*cos(self.data.__getitem__("gamma",raw=True)/180.*pi)
            rdv1=sqrt(self.data.__getitem__("vel"+ion,raw=True)**2-self.data.__getitem__("vsw",raw=True)**2*sin(self.data.__getitem__("gamma",raw=True)/180.*pi)**2)
            rdvp=rdv0+rdv1
            rdvm=rdv0-rdv1
            rdv=rdv0+rdv1
            rdv[abs(rdvp)>abs(rdvm)]=rdvm[abs(rdvp)>abs(rdvm)]
            self.add_reduced_data("rdv"+ion,rdv,self.data.expand["d00"])
            self.add_reduced_data("rdvp"+ion,rdv,self.data.expand["d00"])
            self.add_reduced_data("rdvm"+ion,rdv,self.data.expand["d00"])
            self.add_reduced_data("rdvalf"+ion,rdv/self.data.__getitem__("valf",raw=True),self.data.expand["d00"])
            rdv0=self.data.__getitem__("velH1+",raw=True)*cos(self.data.__getitem__("gamma",raw=True)/180.*pi)
            rdv1=sqrt(self.data.__getitem__("vel"+ion,raw=True)**2-self.data.__getitem__("velH1+",raw=True)**2*sin(self.data.__getitem__("gamma",raw=True)/180.*pi)**2)
            rdvp=rdv0+rdv1
            rdvm=rdv0-rdv1
            rdv=rdv0+rdv1
            rdv[abs(rdvp)>abs(rdvm)]=rdvm[abs(rdvp)>abs(rdvm)]
            self.add_reduced_data("srdv"+ion,rdv,self.data.expand["d00"])
            self.add_reduced_data("srdvp"+ion,rdv,self.data.expand["d00"])
            self.add_reduced_data("srdvm"+ion,rdv,self.data.expand["d00"])
            self.add_reduced_data("srdvalf"+ion,rdv/self.data.__getitem__("valf",raw=True),self.data.expand["d00"])

    def calc_swtype(self):
        # Q1 >1 critetia for ejecta
        # Q2 >1 criteria for coronal hole plasma
        # Q3 <1 citeria for sector reversal plasma
        tmpt=self.data.__getitem__("tsw",raw=True)/1.16045e4
        Q1 = 0.841 * self.data.__getitem__("B",raw=True) * self.data.__getitem__("dsw",raw=True)**(-0.315) * tmpt**(-0.222) * self.data.__getitem__("vsw",raw=True)**(-0.171) 
        Q2 = 8.77e-11 * tmpt * self.data.__getitem__("B",raw=True)**(1.42) * self.data.__getitem__("vsw",raw=True)**(3.44) * self.data.__getitem__("dsw",raw=True)**(-2.12) 
        Q3 = 0.0561 * tmpt * self.data.__getitem__("B",raw=True)**(0.752) * self.data.__getitem__("vsw",raw=True)**(0.445) * self.data.__getitem__("dsw",raw=True)**(-1.14) 
        ejecta = zeros(self.data.__getitem__("d00",raw=True).shape[0])
        cor_hole = zeros(self.data.__getitem__("d00",raw=True).shape[0])
        sec_rev = zeros(self.data.__getitem__("d00",raw=True).shape[0])
        stream_belt = zeros(self.data.__getitem__("d00",raw=True).shape[0])
        ejecta[where(Q1 > 1)] = 1
        cor_hole[where(Q2 > 1)] = 1
        sec_rev[where(Q3 < 1)] = 1
        stream_belt[where((ejecta+cor_hole+sec_rev)==0)] = 1 
        self.add_reduced_data("ejecta",ejecta,"ud00ind")
        self.add_reduced_data("cor_hole",cor_hole,"ud00ind")
        self.add_reduced_data("sec_rev",sec_rev,"ud00ind")
        self.add_reduced_data("stream_belt",stream_belt,"ud00ind")

    def calc_moments_alf(self):
        uTi,index=unique(self.data["d00"],return_inverse=True)
        uTi=append(uTi,uTi[-1]+0.00001)
        if not "d00" in self.data.expand.keys():
            self.data.add_reduced_data("d00",uTi[:-1],"ud00ind",expansion=index)
        for ion in self.ion:
            dens=self.data["cr"+ion]/self.data["eff"+ion]/(self.data["v"+ion])
            #0th order moment
            nrc=histogram(self.data["d00"],bins=uTi,weights=dens)
            #tmpv=(self.data["v"+ion]-self.data["vel"+ion])/self.data["valf"]
            tmpcr=self.data["cr"+ion]
            tmpcr=tmpcr.reshape(tmpcr.shape[0]/58,58)
            tmpvel=self.data["v"+ion]
            tmpvel=tmpvel.reshape(tmpvel.shape[0]/58,58)
            tmpeff=self.data["eff"+ion]
            tmpeff=tmpeff.reshape(tmpeff.shape[0]/58,58)
            tmpcr=tmpcr/tmpvel/tmpeff
            maxind=argmax(tmpcr,axis=1)
            maxind[maxind==0]=2
            maxind[maxind==57]=55
            maxind[maxind==1]=2
            maxind[maxind==56]=55
            vmax=0.
            crmax=0.
            for st in range(-2,3):
                vmax+=(tmpvel[range(tmpcr.shape[0]),maxind+st]*tmpcr[range(tmpcr.shape[0]),maxind+st])
                crmax+=tmpcr[range(tmpcr.shape[0]),maxind+st]
            vmax/=crmax
            #vmax=(tmpvel[range(tmpcr.shape[0]),maxind]*tmpcr[range(tmpcr.shape[0]),maxind]+tmpvel[range(tmpcr.shape[0]),maxind+1]*tmpcr[range(tmpcr.shape[0]),maxind+1]+tmpvel[range(tmpcr.shape[0]),maxind-1]*tmpcr[range(tmpcr.shape[0]),maxind-1])/(tmpcr[range(tmpcr.shape[0]),maxind-1]+tmpcr[range(tmpcr.shape[0]),maxind]+tmpcr[range(tmpcr.shape[0]),maxind+1])
            tmpv=(self.data["v"+ion]-vmax[index])/self.data["valf"]
            self.add_reduced_data("vmax"+ion,vmax,"ud00ind")
            mask=~isnan(nrc[0][index])*(nrc[0][index]>0.)*~isnan(tmpv)
            #2th order moment
            atc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*tmpv[mask]**2)
            ath=sqrt(atc[0]/nrc[0])
            if "ath"+ion in self.data.keys():
                self.data.add_reduced_data("ath"+ion,ath,"ud00ind")
            else:
                self.add_reduced_data("ath"+ion,ath,"ud00ind")
            #3th order moment
            atc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*tmpv[mask]**3)
            ask=atc[0]/nrc[0]/ath**3
            if "ask"+ion in self.data.keys():
                self.data.add_reduced_data("ask"+ion,ask,"ud00ind")
            else:
                self.add_reduced_data("ask"+ion,ask,"ud00ind")
        
        #swics protons
        if self.dcrtcr:
            dens=self.data["dcrH1+"]/self.data["effdcrH1+"]/(self.data["vH1+"])
            #0th order moment
            nrc=histogram(self.data["d00"],bins=uTi,weights=dens)
            #tmpv=(self.data["v"+ion]-self.data["vel"+ion])/self.data["valf"]
            tmpcr=self.data["dcrH1+"]
            tmpcr=tmpcr.reshape(tmpcr.shape[0]/58,58)
            tmpvel=self.data["vH1+"]
            tmpvel=tmpvel.reshape(tmpvel.shape[0]/58,58)
            tmpeff=self.data["effdcrH1+"]
            tmpeff=tmpeff.reshape(tmpeff.shape[0]/58,58)
            tmpcr=tmpcr/tmpvel/tmpeff
            maxind=argmax(tmpcr,axis=1)
            maxind[maxind==0]=2
            maxind[maxind==57]=55
            maxind[maxind==1]=2
            maxind[maxind==56]=55
            vmax=0.
            crmax=0.
            for st in range(-2,3):
                vmax+=(tmpvel[range(tmpcr.shape[0]),maxind+st]*tmpcr[range(tmpcr.shape[0]),maxind+st])
                crmax+=tmpcr[range(tmpcr.shape[0]),maxind+st]
            vmax/=crmax
            #vmax=(tmpvel[range(tmpcr.shape[0]),maxind]*tmpcr[range(tmpcr.shape[0]),maxind]+tmpvel[range(tmpcr.shape[0]),maxind+1]*tmpcr[range(tmpcr.shape[0]),maxind+1]+tmpvel[range(tmpcr.shape[0]),maxind-1]*tmpcr[range(tmpcr.shape[0]),maxind-1])/(tmpcr[range(tmpcr.shape[0]),maxind-1]+tmpcr[range(tmpcr.shape[0]),maxind]+tmpcr[range(tmpcr.shape[0]),maxind+1])
            tmpv=(self.data["vH1+"]-vmax[index])/self.data["valf"]
            self.add_reduced_data("vmaxH1+",vmax,"ud00ind")
            mask=~isnan(nrc[0][index])*(nrc[0][index]>0.)*~isnan(tmpv)
            #2th order moment
            atc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*tmpv[mask]**2)
            ath=sqrt(atc[0]/nrc[0])
            if "ath"+ion in self.data.keys():
                self.data.add_reduced_data("athH1+",ath,"ud00ind")
            else:
                self.add_reduced_data("athH1+",ath,"ud00ind")
            #3th order moment
            atc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*tmpv[mask]**3)
            ask=atc[0]/nrc[0]/ath**3
            if "askH1+" in self.data.keys():
                self.data.add_reduced_data("askH1+",ask,"ud00ind")
            else:
                self.add_reduced_data("askH1+",ask,"ud00ind")

    def calc_mean(self,ions=["He2+"],prodx="colage",prody="dvalf",binx=arange(-5.,2.,.1),biny=arange(-1.,2.,0.05)):
        self.add_mask("calc_mean")
        for ion in ions:
            py=self.get_data("calc_mean",prody+ion)
            px=self.get_data("calc_mean",prodx)
            mask=~isnan(py)*~isinf(py)*~isnan(px)*~isinf(px)
            py=py[mask]
            px=px[mask]
            h,x,y=histogram2d(px,py,bins=(binx,biny))
            pylab.pcolormesh(x,y,h.T,vmin=amin(h[h>0]),vmax=amax(h[h>0]))
            ny,x=histogram(px,bins=binx)
            y,x=histogram(px,bins=binx,weights=py)
            pylab.plot(x[:-1],y/(1.*ny),"o-",label="Mean: "+ion)

        med=zeros((array(ions).shape[0],binx.shape[0]-1))
        for i,b in enumerate(binx[:-1]):
            self.set_mask("calc_mean",prodx,b,binx[i+1],reset=True)
            for j,ion in enumerate(ions):
                med[j,i]=median(self.get_data("calc_mean",prody+ion))
    
        for j,ion in enumerate(ions):
            pylab.plot(binx[:-1],med[j],"o-",label="Meadian: "+ion)
    
        pylab.legend()
        self.remove_mask("calc_mean")
