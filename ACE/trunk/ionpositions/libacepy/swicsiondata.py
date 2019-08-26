from libacepy.ancil import int2str
from Gnuplot import Gnuplot,Data
from numpy import *
import sys
from pylib import dbData


def convres(res):
        """
        Converts resolution input in time in s. Valid values are '12m','1h','1d',720,3600,86400 -> output is 720.,3600.,or 86400.
        """
        try:
            if (str(res)=="12m"):
                return 720.
            elif (str(res)=="1h"):
                return 3600.
            elif (str(res)=="1d"):
                return 86400.
            elif (float(res)==720.):
                return 720.
            elif (float(res)==3600.):
                return 3600.
            elif (float(res)==86400.):
                return 86400.
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"

def convresname(res):
        """
        Converts resolution input in time in string. Valid values are '12m','1h','1d',720,3600,86400 -> output is '12m','1h',or '1d'
        """
        try:
            if (str(res)=="12m"):
                return "12m"
            elif (str(res)=="1h"):
                return "1h"
            elif (str(res)=="1d"):
                return "1d"
            elif (float(res)==720.):
                return "12m"
            elif (float(res)==3600.):
                return "1h"
            elif (float(res)==86400.):
                return "1d"
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"


class dbswicsion(dbData):
    def load_data(self,*args,**kwargs):
	if ("load_set" in kwargs.keys()):
	    self.load_set=kwargs["load_set"]
	else:
	    self.load_set=False
        if not(("ion" in kwargs.keys()) and ("res" in kwargs.keys()) and ("year" in kwargs.keys()) and ("tf" in kwargs.keys())):
            print "Need ion,res,year,tf!"
            return
        if not("path" in kwargs.keys()):
            path="/data/etph/ace/"
        else:
            path=kwargs["path"]
        if not("resswepam" in kwargs.keys()):
            self.resswepam=720.
        else:
	    self.resswepam=kwargs["resswepam"]

        self.effpath=path+"efficencies/"
        path=path+convresname(kwargs["res"])+"data/%.4i/"%(kwargs["year"])
        self.path=path
        self.timeframe=kwargs["tf"]
        self.resname=convresname(kwargs["res"])
        self.ress=convres(kwargs["res"])
        self.ion=kwargs["ion"]
        self.year=kwargs["year"]
        self.mass=0.
        self.charge=0.
	if "loadswepam" in kwargs.keys():
            self.loadswepam=kwargs["loadswepam"]
        else:
            self.loadswepam=True
	if "loadmag" in kwargs.keys():
            self.loadmag=kwargs["loadmag"]
        else:
            self.loadmag=True
        if "loadflux" in kwargs.keys():
            self.loadflux=kwargs["loadflux"]
        else:
            self.loadflux=True
        if "loadres" in kwargs.keys():
            self.loadres=kwargs["loadres"]
        else:
            self.loadres=True
        if "loaderg" in kwargs.keys():
            self.loaderg=kwargs["loaderg"]
        else:
            self.loaderg=True

	if self.load_set:
		self.load_data_set()
		return

        #initialise data dictionary
        self.data["time"]=array([])
        if self.loadflux:
            self.data["step"]=array([],int)
            self.data["rtime"]=array([])
            self.data["vion"]=array([])
            self.data["cts"]=array([])
            self.data["ctserr"]=array([])
            self.data["ddens"]=array([])
            self.data["ddenserr"]=array([])
            self.data["dflux"]=array([])
            self.data["dfluxerr"]=array([])
        if self.loaderg:
            self.data["aspang"]=array([])
            self.data["vsw"]=array([])
        if self.loadres:
            self.data["vel"]=array([])
            self.data["velerr"]=array([])
            self.data["dens"]=array([])
            self.data["denserr"]=array([])
            self.data["flux"]=array([])
            self.data["fluxerr"]=array([])
            self.data["temp"]=array([])
            self.data["temperr"]=array([])
          
 
        """
        Loads data from the defined timeframe
        """
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                daytime=array([])
                if self.loadflux:
                    daystep=array([],int)
                    dayrtime=array([])
                    dayvion=array([])
                    daycts=array([])
                    dayctserr=array([])
                    dayddens=array([])
                    dayddenserr=array([])
                    daydflux=array([])
                    daydfluxerr=array([])

                if self.loaderg:
                    dayaspang=array([])
                    dayvsw=array([])

                if self.loadres:
                    dayvel=array([])
                    dayvelerr=array([])
                    daydens=array([])
                    daydenserr=array([])
                    dayflux=array([])
                    dayfluxerr=array([])
                    daytemp=array([])
                    daytemperr=array([])


                ergdaypath=self.path+"%.3i/"%(day)
                # look if data for doy is present!
                lpresent=False
                try:
                    open(ergdaypath+"list.in")
                    lpresent=True
                except:
                    print "doy %.3i no list.in"%(day)
                if lpresent:
		    listin=open(ergdaypath+"list.in")
                    s=listin.readline()
                    for s in listin:
                        k=s.split()
                        time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
                        if (time>=tf[0] and time<=tf[1]):
                            fluxname=ergdaypath+"flux_"+k[0]
                            resname=ergdaypath+"res_"+k[0]
                            ergname=ergdaypath+"erg_"+k[0]
                            fpresent=True
                            if self.loadres:
                                try:
                                    open(resname)
                                except:
                                    print "Could not open : ",resname
                                    fpresent=False
                            if self.loadflux:
                                try:
                                    open(fluxname)
                                except:
                                    print "Could not open : ",fluxname
                                    fpresent=False
                            if self.loaderg:
                                try:
                                    open(ergname)
                                except:
                                    print "Could not open : ",ergname
                                    fpresent=False
                            if (fpresent):
                                # first try to read in data in tmpvariables
                                try:
                                    # get aspect angle and SWS speed (SWICS protons) from erg_* file
                                    if self.loaderg:
                                        ergin=open(ergname)
                                        k=["**"]
                                        while (k[0]!="*****"):
                                            s=ergin.readline()
                                            k=s.split()
                                            if k[0]=="Aspang":
                                                tmpasp=float(k[2])
                                            if k[0]=="SWSpeed":
                                                tmpvsw=float(k[2])
                                        if self.ion=="He1+":
                                            for step in range(16):
                                                while k[0]!="He1+":
                                                    s=ergin.readline()
                                                    k=s.split()
                                                tmpcountspec.append([float(k[7]),float(k[11]),float(k[12])])
                                                k[0]="**"
                                        ergin.close()
                                    # get ion parameters (velocity,density,flux,temperature from res_* file)
                                    if self.loadres:
                                        resin=open(resname)
                                        s=resin.readline()
                                        k=s.split()
                                        while (k[0]!=self.ion):
                                            s=resin.readline()
                                            k=s.split()
                                        tmpvel=float(k[1])
                                        tmpvelerr=float(k[2])
                                        tmpdens=float(k[10])
                                        tmpdenserr=float(k[11])
                                        tmpflux=float(k[7])
                                        tmpfluxerr=float(k[8])
                                        tmptemp=float(k[4])
                                        tmptemperr=float(k[5])
                                        resin.close()

                                    # get ion spectra (counts,density,flux, from flux_* file)
                                    if self.loadflux:
                                        fluxin=open(fluxname)
                                        k=["**********"]
                                        while (k[0]!=self.ion):
                                            s=fluxin.readline()
                                            k=s.split()
                                        s=fluxin.readline()
                                        k=s.split()
                                        if (self.mass==0.):
                                            self.mass=float(k[2])
                                        s=fluxin.readline()
                                        k=s.split()
                                        if (self.charge==0.):
                                            self.charge=float(k[2])
                                        s=fluxin.readline()
                                        tmpstep=array(range(58))
                                        tmptime=(tmpstep+1.)*12./24./60./60.
                                        tmptime+=time
                                        tmpvion=zeros(58)
                                        tmpcts=zeros(58)
                                        tmpctserr=zeros(58)
                                        tmpddens=zeros(58)
                                        tmpddenserr=zeros(58)
                                        tmpdflux=zeros(58)
                                        tmpdfluxerr=zeros(58)
                                        for step in range(58):
                                            s=fluxin.readline()
                                            k=s.split()
                                            tmpvion[step]=float(k[0])
                                            tmpcts[step]=float(k[1])
                                            tmpctserr[step]=float(k[2])
                                            tmpddens[step]=float(k[7])
                                            tmpddenserr[step]=float(k[8])
                                            tmpdflux[step]=float(k[3])
                                            tmpdfluxerr[step]=float(k[4])

                                        fluxin.close()
                                except:
                                    print "Data from ",resname," or ",fluxname," or ",ergname," incomplete or contains bad values"
				if self.loadflux:
					daytime=append(daytime,ones(58)*time)
				else:
					daytime=append(daytime,time)

				if self.loadflux:
					daystep=append(daystep,tmpstep)
					dayrtime=append(dayrtime,tmptime)
					dayvion=append(dayvion,tmpvion)
					daycts=append(daycts,tmpcts)
					dayctserr=append(dayctserr,tmpctserr)
					dayddens=append(dayddens,tmpddens)
					dayddenserr=append(dayddenserr,tmpddenserr)
					daydflux=append(daydflux,tmpdflux)
					daydfluxerr=append(daydfluxerr,tmpdfluxerr)
				if self.loaderg:
					if self.loadflux:
						dayaspang=append(dayaspang,ones(58)*tmpasp)
						dayvsw=append(dayvsw,ones(58)*tmpvsw)
					else:
						dayaspang=append(dayaspang,tmpasp)
						dayvsw=append(dayvsw,tmpvsw)
				if self.loadres:
					if self.loadflux:
						dayvel=append(dayvel,ones(58)*tmpvel)
						dayvelerr=append(dayvelerr,ones(58)*tmpvelerr)
						daydens=append(daydens,ones(58)*tmpdens)
						daydenserr=append(daydenserr,ones(58)*tmpdenserr)
						dayflux=append(dayflux,ones(58)*tmpflux)
						dayfluxerr=append(dayfluxerr,ones(58)*tmpfluxerr)
						daytemp=append(daytemp,ones(58)*tmptemp)
						daytemperr=append(daytemperr,ones(58)*tmptemperr)
					else:
						dayvel=append(dayvel,tmpvel)
						dayvelerr=append(dayvelerr,tmpvelerr)
						daydens=append(daydens,tmpdens)
						daydenserr=append(daydenserr,tmpdenserr)
						dayflux=append(dayflux,tmpflux)
						dayfluxerr=append(dayfluxerr,tmpfluxerr)
						daytemp=append(daytemp,tmptemp)
						daytemperr=append(daytemperr,tmptemperr)


                print day
                self.data["time"]=append(self.data["time"],daytime)
                if self.loaderg:
                    self.data["vsw"]=append(self.data["vsw"],dayvsw)
                    self.data["aspang"] =append(self.data["aspang"],dayaspang)
                if self.loadres:
                    self.data["vel"]=append(self.data["vel"],dayvel)
                    self.data["velerr"]=append(self.data["velerr"],dayvelerr)
                    self.data["dens"]=append(self.data["dens"],daydens)
                    self.data["denserr"]=append(self.data["denserr"],daydenserr)
                    self.data["flux"]=append(self.data["flux"],dayflux)
                    self.data["fluxerr"]=append(self.data["fluxerr"],dayfluxerr)
                    self.data["temp"]=append(self.data["temp"],daytemp)
                    self.data["temperr"]=append(self.data["temperr"],daytemperr)
                if self.loadflux:
                    self.data["step"]=append(self.data["step"],daystep)
                    self.data["rtime"]=append(self.data["rtime"],dayrtime)
                    self.data["vion"]=append(self.data["vion"],dayvion)
                    self.data["cts"]=append(self.data["cts"],daycts)
                    self.data["ctserr"]=append(self.data["ctserr"],dayctserr)
                    self.data["ddens"]=append(self.data["ddens"],dayddens)
                    self.data["ddenserr"]=append(self.data["ddenserr"],dayddenserr)
                    self.data["dflux"]=append(self.data["dflux"],daydflux)
                    self.data["dfluxerr"]=append(self.data["dfluxerr"],daydfluxerr)
        #if self.loadres==1:
        #    self.calc_vth()
        #if self.loadflux==1 and self.loadres==1:
        #    self.calc_higher_moments()
        #    self.calc_crmoments()
        print self.ion+" loaded"
	if self.loadswepam:
		from libacepy.swepamdata import dbswepam
		p=dbswepam(res=self.resswepam,year=self.year,tf=[[self.data["time"][0],self.data["time"][-1]+1./24./5.]])
		if self.resswepam==720.:
			pb=p.bin_swepam(append(unique(self.data["time"])-1./48./5.,self.data["time"][-1]+1./48./5.))	
		else:
			pb=p.bin_swepam(append(unique(self.data["time"]),self.data["time"][-1]+1./24./5.))	
		ind=searchsorted(pb.data["time"],self.data["time"],side="right")-1
		self.data["vsw"]=pb.data["vel"][ind]
		self.data["pdens"]=pb.data["dens"][ind]
		self.data["ptemp"]=pb.data["temp"][ind]
		del(p)
		del(pb)
		self.data["dv"]=self.data["vel"]-self.data["vsw"]
		self.data["colage"]=(6.4e8*self.data["pdens"])/(self.data["vsw"]*(self.data["ptemp"])**1.5)
		print "H+ Swepam loaded"
	if self.loadmag:
		from libacepy.mag import dbmag
		mag=dbmag(year=self.year,tf=[[self.data["time"][0],self.data["time"][-1]+1./24./5.]])
		magb=mag.bin_mag(append(unique(self.data["time"]),self.data["time"][-1]+1./24./5.))
		self.data["B"]=magb.data["B"][ind]
		self.data["phi"]=magb.data["phi"][ind]
		self.data["theta"]=magb.data["theta"][ind]
		self.data["alpha"]=magb.data["alpha"][ind]
		del(mag)
		del(magb)
		print "Mag loaded"

	if self.loadmag and self.loadswepam:
		from scipy import constants
		mu0=constants.mu_0
		kb=constants.Bolzmann
		self.data["beta"]=mu0*kb*1e24*self.data["pdens"]*self.data["ptemp"]/self.data["B"]**2
		self.data["valf"]=21.8*self.data["B"]/sqrt(self.data["pdens"])
		
    def calc_moments(self):
        eff=loadtxt(self.effpath+self.ion+".eff")
        eff=eff[:,1]
        eff=eff[self.data["step"]]
        t=unique(self.data["time"])
        v=unique(self.data["vion"])
        tb=append(t,t[-1]+1)
        vb=append(v,v[-1]+1)
        spec,x,y=histogram2d(self.data["time"],self.data["vion"],bins=(tb,vb),weights=self.data["cts"]/eff)
        spec2,x,y=histogram2d(self.data["time"],self.data["vion"],bins=(tb,vb),weights=self.data["cts"]/eff*self.data["vion"])
        vel=sum(spec2,axis=1)/sum(spec,axis=1)
        ind=searchsorted(tb,self.data["time"],side="right")-1
        self.add_data("velnew",vel[ind])
        vel=vel[ind]
        dvsq=(self.data["vion"]-vel)**2
        spec2,x,y=histogram2d(self.data["time"],self.data["vion"],bins=(tb,vb),weights=self.data["cts"]/eff*dvsq)
        vth=sqrt(sum(spec2,axis=1)/sum(spec,axis=1))
        vth=vth[ind]
        self.add_data("vthnew",vth)
        mask=(self.data["vion"]<vel+3.*vth)*(self.data["vion"]>vel-3.*vth)
        spec,x,y=histogram2d(self.data["time"][mask],self.data["vion"][mask],bins=(tb,vb),weights=self.data["cts"][mask]/eff[mask])
        spec2,x,y=histogram2d(self.data["time"][mask],self.data["vion"][mask],bins=(tb,vb),weights=self.data["cts"][mask]/eff[mask]*self.data["vion"][mask])
        vel=sum(spec2,axis=1)/sum(spec,axis=1)
        ind=searchsorted(tb,self.data["time"],side="right")-1
        self.add_data("velnew2",vel[ind])
        vel=vel[ind]

    def calc_days2000(self):
	    dyears=self.year-2000.
	    daysoff=dyears*365
	    if dyears>0:
		    daysoff+=int((dyears-1)/4)+1
	    self.add_data("days2000",self.data["time"]+daysoff)

    def load_data_set(self):
	    infile=open("/data/ivar/berger/ace/swics/%s_%i.dat"%(self.ion,self.year),"r")
	    keys=infile.readline().split()
	    data=loadtxt(infile)
	    for i,key in enumerate(keys):
		    self.data[key]=data[i,:]

    def save_data(self):
	    outfile=open("/data/ivar/berger/ace/swics/%s_%i.dat"%(self.ion,self.year),"w")
	    header=""
	    keys=self.data.keys()
	    for i,s in enumerate(keys):
		    if i<len(keys)-1:
			    header+=s+" "
		    else:
			    header+=s+"\n"
	    outfile.write(header)
	    data=zeros((len(keys),self.data["time"].shape[0]))
	    for i,s in enumerate(keys):
		    data[i,:]=self.data[s]
	    savetxt(outfile,data,fmt="%.9e")
	    outfile.close()
	    del(data)
class swicsiondata:
    """
    Class for swics iondata. Ionname, timeresolution, year, timeframe, and path of data are needed to initialise class. 
    Data is loaded and some further quantities (e.g. thermal velocities, kortosis ...) are calculated automatically.

    important methods :
    getvals([list of keywords],start,stop) returns specified set of data (s. ?swicsiondata.getvals for further information)
    getspec(keywords,start,stop) returns specified set of data (s. ?swicsiondata.getspec for further information)
    """
    def __init__(self,ionname,res,year,timeframe,path,loaderg=1,loadres=1,loadflux=1): 
        """
        Input :
        ionname -> str (e.g. 'He2+')
        res -> int,float,or str (valid 720,720.,'12m',3600,3600.,'1h',86400,86400.,'1d')
        year -> int (e.g. 2007)
        timeframe -> list,array (e.g. [[1.,5.],[7.2,9.5],[100.6,150.])
        path -> str (e.g. '/data/wimmer/ace/')
        """
        self.name=ionname                            #  str -> name of ion  
        self.res=self.convres(res)                   #  timeresolution of data in s
        self.year=year                               #  year of data
        self.loaderg=loaderg                         #  1(0)= load (not)information from erg files -> aspect angle and proton speed 
        self.loadres=loadres                         #  1(0)= load (not)information from res files -> ion parameters (velocity,density,flux,temperature) 
        self.loadflux=loadflux                       #  1(0)= load (not)information from flux files -> spectra of counts,density,flux
        self.time=[]                                 #  vector [time]
        self.vel=[]                                  #  vector [vel]
        self.velerr=[]                               #  vector [velerr]
        self.flux=[]                                 #  vector [flux,cr-error,eff-error]
        self.dens=[]                                 #  vector [dens,cr-error,eff-error]
        self.temp=[]                                 #  vector [temp,cr-error,eff-error]
        self.vth=[]                                  #  vector [thermalvel]
        self.densspec=[]                             #  vector of [[step][vel,diffdens,cr-error,+eff-error,-eff-error]]
        self.fluxspec=[]                             #  vector of [[step][vel,diffflux,cr-error,+eff-error,-eff-error]]
        self.countspec=[]                            #  vector of [[step][vel,counts,cr-error,+eff-error,-eff-error]]
        self.path=path+self.convresname(res)+"data/"+str(year)+"/" #  str -> path of data repository 
                                                                   # e.g. "/data/wimmer/ace/" resolution and year added from input
        self.mass=0.                                 #  float -> ion mass
        self.charge=0.                               #  float -> ion charge
        self.aspang=[]                               #  vector [aspang]. Aspect angle information
        self.vsws=[]                                 #  vector [vsws]. Proton speed from michigan analysis
        self.timeframe=array(timeframe)              #  vector -> [[start,stop]]
        # cr stands for values calculated from countrate spectra -> s. calc_crmoments. The calculation is automatically done if load() is called. 
        self.crvel=[]                                #  vector [crvel]  
        self.crvth=[]                                #  vector [crvth]  
        self.crtemp=[]                               #  vector [crtemp]  
        self.crdens=[]                               #  vector [crdens]  
        # higher moments -> s. calc_highermoments. The calculation is automatically done if load() is called.
        self.skewness=[]                             #  vector [skewness]
        self.kortosis=[]                             #  vector [kortosis]
        tmpstr=""
        for tf in self.timeframe:
            tmpstr+="_"+str(tf[0])+":"+str(tf[1])
        if loaderg:
            tmpstr+="_erg"
        if loadres:
            tmpstr+="_res"
        if loadflux:
            tmpstr+="_flux"
        self.cpicklename=path+"cpickle/"+self.name+"_"+str(self.res)+"_"+str(self.year)+"_"+tmpstr+".cpic"   # location for cpickle dumps

        
        self.load()
        # if mass and charge are not set (eg. loadflux=0), try to get them from ion name
        if (self.mass==0 or self.charge==0):
            self.getmqfromname()
        self.elemname=self.name.replace("%s+"%(str(self.charge)),"")


    def getmqfromname(self):
        """
        mass and charge information usually comes from flux file.
        If flux file is not loaded or for any other reason mass or charge is zero this routine tries to determine mass and charge from the ions name.
        So far only works for names like 'He2+' not for isotopic nomenclature '3He2+' or '22Ne2+'. But this can easily be changed in elemlist adding e.g. ['3He',3.]
        """
        elemlist=[["He",4.],["C",12.],["N",14.],["O",16.],["Ne",20.],["Mg",24.],["Si",28.],["S",32.],["Ca",40.],["Fe",56.]]
        for val in elemlist:
            if self.name[0:len(val[0])]==val[0]:
                try:
                    self.charge=float(self.name[len(val[0]):-1])
                    self.mass=val[1]
                except:
                    continue

    def bindata(self,fac):
        """
        bins data by a (integer) value fac.
        Attention:
        vel,flux,dens,temp -> mean values of original values, neglecting time where velion=0. Corresponding errors are sqrt(sum(sig**2)/N).
        dens-,flux-,count-spec -> sumspectra. Errors as above (vel=0 times are neglected)
        !!!! This means vel,flux,dens,temp are not recalculated from the sumspectra !!!!
        vsws -> mean values of original values, neglecting time where velion=0.
        aspang -> mean values of original values !!! not neglecting velion=0
        vth -> recalculated from new temp
        all other quantites are recalculated from new sumspectra !!!!!!!
        """
        
        fac=int(fac)
        dim=len(self.time)/int(fac)
        newres=self.res*float(fac)
        newtime=zeros([dim])
        newvel=zeros([dim])
        newvelerr=zeros([dim])
        newflux=zeros([dim,3])
        newdens=zeros([dim,3])
        newtemp=zeros([dim,3])
        newdensspec=zeros([dim,len(self.densspec[0]),len(self.densspec[0][0])])
        newfluxspec=zeros([dim,len(self.fluxspec[0]),len(self.fluxspec[0][0])])
        newcountspec=zeros([dim,len(self.countspec[0]),len(self.countspec[0][0])])
        newdensspec[0:dim,:,0]=self.densspec[0:dim,:,0]
        newfluxspec[0:dim,:,0]=self.fluxspec[0:dim,:,0]
        newcountspec[0:dim,:,0]=self.countspec[0:dim,:,0]
        newaspang=zeros([dim])
        newvsws=zeros([dim])
        # reference array -> masking only results velocity > 0
        refarr=self.vel.clip(0.,1.)
        for i in range(dim):
            newtime[i]=self.time[i*int(fac)]
            if self.loadres==1:
                newvel[i]=mean(self.vel[i*fac:(i+1)*fac][refarr[i*fac:(i+1)*fac]>0.])
                newvelerr[i]=sqrt(mean(self.velerr[i*fac:(i+1)*fac][refarr[i*fac:(i+1)*fac]>0.]**2))
                newdens[i,0]=mean(self.dens[i*fac:(i+1)*fac,0][refarr[i*fac:(i+1)*fac]>0.])
                newdens[i,1:3]=sqrt(mean(self.dens[i*fac:(i+1)*fac,1:3][refarr[i*fac:(i+1)*fac]>0.]**2,0))
                newflux[i,0]=mean(self.flux[i*fac:(i+1)*fac,0][refarr[i*fac:(i+1)*fac]>0.])
                newflux[i,1:3]=sqrt(mean(self.flux[i*fac:(i+1)*fac,1:3][refarr[i*fac:(i+1)*fac]>0.]**2,0))
                newtemp[i,0]=mean(self.temp[i*fac:(i+1)*fac,0][refarr[i*fac:(i+1)*fac]>0.])
                newtemp[i,1:3]=sqrt(mean(self.temp[i*fac:(i+1)*fac,1:3][refarr[i*fac:(i+1)*fac]>0.]**2,0))
                #newvth -> is recalculated further down
            if self.loadflux==1:
                newcountspec[i,:,1]=sum(self.countspec[i*fac:(i+1)*fac,:,1])
                newcountspec[i,:,2]=sqrt(mean(self.countspec[i*fac:(i+1)*fac,:,2][refarr[i*fac:(i+1)*fac]>0.]**2,0))
                newdensspec[i,:,1]=sum(self.densspec[i*fac:(i+1)*fac,:,1])
                newdensspec[i,:,2:5]=sqrt(mean(self.densspec[i*fac:(i+1)*fac,:,2:5][refarr[i*fac:(i+1)*fac]>0.]**2,0))
                newfluxspec[i,:,1]=sum(self.fluxspec[i*fac:(i+1)*fac,:,1])
                newfluxspec[i,:,2:5]=sqrt(mean(self.fluxspec[i*fac:(i+1)*fac,:,2:5][refarr[i*fac:(i+1)*fac]>0.]**2,0))
            if self.loaderg==1:
                newaspang[i]=mean(self.aspang[i*fac:(i+1)*fac])
                newvsws[i]=mean(self.vsws[i*fac:(i+1)*fac][refarr[i*fac:(i+1)*fac]>0.])

            #newskewness -> is recalculated further down
            #newkortosis -> is recalculated further down
        self.res=newres
        self.time=newtime
        self.vel=newvel
        self.velerr=newvelerr
        self.flux=newflux
        self.dens=newdens
        self.temp=newtemp
        self.densspec=newdensspec
        self.fluxspec=newfluxspec
        self.countspec=newcountspec
        self.aspang=newaspang
        self.vsws=newvsws

        if self.loadres==1:
            self.calc_vth()
        if self.loadflux==1 and self.loadres==1:
            self.calc_higher_moments()
            self.calc_crmoments()

    def getvals(self,liste,start=0,stop=-9999):
        """
        Returns array that contains values that are defined in liste
        input :
        liste -> list with keywords e.g. ['time','dens'] ; Attention ! If liste has only 1 entry output is different s. output
        start,stop -> set to full lenght by default; (index corresponds to time self.time[index])
                      optional define start and stop index for returned array e.g. start=10,stop=15 returns from index 10 to index 24

        valid keywords for liste are :
        'time' -> time information [doy] 
        'vel','velerr' -> velocity [km/s] and corresponding error from countrates
        'dens','denscrerr','densefferr' -> total density [1/cm^3] and corresponding errors from countrates 'cr' and efficiencies 'eff'
        'flux','fluxcrerr','fluxefferr' -> total flux [fix] and corresponding errors from countrates 'cr' and efficiencies 'eff'
        'temp','tempcrerr','tempefferr' -> temperature [K] and corresponding errors from countrates 'cr' and efficiencies 'eff'
        'vth' -> thermal velocity [km/s]
        'crvel' -> velocity [km/s] from raw counts
        'crvth' -> thermal velocity [km/s] from raw counts
        'crdens' -> total density [#/cm^3] from raw counts 
        'crtemp' -> temperature [K] from raw counts

        output :
        normal case liste has more than one entry ->
        array -> [stop-start,len(liste)] ; first val from liste is first column, ... last val from liste is last column 
        if liste has only a single entry ->
        array -> [stop-start] ; only vector containing the data is returned 
        """
        if (stop==-9999):
            stop=len(self.time)-start
        if len(liste)>1:
            tmpvals=zeros([stop-start,len(liste)])
            i=0
            for col in liste:
                tmpvals[:,i]=self.getcol(col,start,stop)
                i+=1
            return tmpvals
        else:
            return self.getcol(liste[0],start,stop)

    def getspec(self,type,start=0,stop=-9999):
        """
        Returns array that contains spectra from index start to index start+stop-1 (index corresponds to time self.time[index])
        input :
        type -> keyword e.g. 'densspec'
        valid keywords for type are :
        'densspec' -> density spectrum [[start+stop-1][step][vel,diffdens,cr-error,+eff-error,-eff-error]]
        'fluxspec' -> flux spectrum [[start+stop-1][step][vel,diffflux,cr-error,+eff-error,-eff-error]]
        'countspec' -> count spectrum [[start+stop-1][step][vel,counts,cr-error,+eff-error,-eff-error]]
        
        start,stop -> set to full lenght by default; optional define start and stop index for returned array
                      e.g. start=10,stop=15 returns from index 10 to index 24


        output :
        array -> [stop-start,len(liste)] ; first val from liste is first column, ... last val from liste is last column 
        """
        if (stop==-9999):
            stop=len(self.time)-start
        if (type=="densspec"):
            return self.densspec[start:stop]
        elif (type=="fluxspec"):
            return self.fluxspec[start:stop]
        elif (type=="countspec"):
            return self.countspec[start:stop]
        else:
            raise Exception, "Wrong keyword '%s' ! Valid Keywords are 'densspec','fluxspec',countspec'"%(type) 


    def getcol(self,col,start=0,stop=-9999):
        if (stop==-9999):
            stop=len(self.time)-start
        if (col=="time"):
            return self.time[start:stop]
        elif (col=="dens"):
            return self.dens[start:stop,0]
        elif (col=="denscrerr"):
            return self.dens[start:stop,1]
        elif (col=="densefferr"):
            return self.dens[start:stop,2]
        elif (col=="temp"):
            return self.temp[start:stop,0]
        elif (col=="tempcrerr"):
            return self.temp[start:stop,1]
        elif (col=="tempefferr"):
            return self.temp[start:stop,2]
        elif (col=="flux"):
            return self.flux[start:stop,0]
        elif (col=="fluxcrerr"):
            return self.flux[start:stop,1]
        elif (col=="fluxefferr"):
            return self.flux[start:stop,2]
        elif (col=="vel"):
            return self.vel[start:stop]
        elif (col=="velerr"):
            return self.velerr[start:stop]
        elif (col=="vth"):
            return self.vth[start:stop]
        elif (col=="crvel"):
            return self.crvel[start:stop]
        elif (col=="crvth"):
            return self.crvth[start:stop]
        elif (col=="crtemp"):
            return self.crtemp[start:stop]
        elif (col=="crdens"):
            return self.crdens[start:stop]
        elif (col=="skewness"):
            return self.skewness[start:stop]
        elif (col=="kortosis"):
            return self.kortosis[start:stop]
        else:
            raise Exception, "Wrong keyword '%s' ! Valid Keywords are 'time','vel','velerr','dens','denscrerr','densefferr','flux','fluxcrerr','fluxefferr','temp','tempcrerr','tempefferr','vth','crvel','crvth','crdens','crtemp'. For more details s. ?swicsiondata.getvals!"%(col) 
        

    def load(self):
        """
        Loads data from the defined timeframe
        """
        for tf in self.timeframe:
            for day in range(int(tf[0]),int(tf[1])+1):
                doystr=int2str(day)
                ergdaypath=self.path+doystr+"/"
                # look if data for doy is present!
                lpresent=0
                try:
                    open(ergdaypath+"list.in")
                    lpresent=1
                except:
                    print "doy ",doystr," no list.in"
                if (lpresent==1):
                    listin=open(ergdaypath+"list.in")
                    s=listin.readline()
                    for s in listin:
                        k=s.split()
                        time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
                        if (time>=tf[0] and time<=tf[1]):
                            fluxname=ergdaypath+"flux_"+k[0]
                            resname=ergdaypath+"res_"+k[0]
                            ergname=ergdaypath+"erg_"+k[0]
                            fpresent=1
                            if self.loadres==1:
                                try:
                                    open(resname)
                                except:
                                    print "Could not open : ",resname
                                    fpresent=0
                            if self.loadflux==1:
                                try:
                                    open(fluxname)
                                except:
                                    print "Could not open : ",fluxname
                                    fpresent=0
                            if self.loaderg==1:
                                try:
                                    open(ergname)
                                except:
                                    print "Could not open : ",ergname
                                    fpresent=0
                            if (fpresent):
                                tmptime=-9999.
                                tmpvel=-9999.
                                tmpvelerr=-9999.
                                tmpdens=-9999.
                                tmpflux=-9999.
                                tmptemp=-9999.
                                tmpdensspec=[]
                                tmpfluxspec=[]
                                tmpcountspec=[]
                                tmpasp=-9999.
                                tmpvsws=-9999.
                                # first try to read in data in tmpvariables
                                try:
                                    tmptime=time
                                    # get aspect angle and SWS speed (SWICS protons) from erg_* file
                                    if self.loaderg==1:
                                        ergin=open(ergname)
                                        k=["**"]
                                        while (k[0]!="*****"):
                                            s=ergin.readline()
                                            k=s.split()
                                            if k[0]=="Aspang":
                                                tmpasp=float(k[2])
                                            if k[0]=="SWSpeed":
                                                tmpvsws=float(k[2])
                                        if self.name=="He1+":
                                            for step in range(16):
                                                while k[0]!="He1+":
                                                    s=ergin.readline()
                                                    k=s.split()
                                                tmpcountspec.append([float(k[7]),float(k[11]),float(k[12])])
                                                k[0]="**"
                                        ergin.close()
                                    # get ion parameters (velocity,density,flux,temperature from res_* file)
                                    if self.loadres==1:
                                        resin=open(resname)
                                        s=resin.readline()
                                        k=s.split()
                                        while (k[0]!=self.name):
                                            s=resin.readline()
                                            k=s.split()
                                        tmpvel=float(k[1])
                                        tmpvelerr=float(k[2])
                                        tmpdens=[float(k[10]),float(k[11]),float(k[12])]
                                        tmpflux=[float(k[7]),float(k[8]),float(k[9])]
                                        tmptemp=[float(k[4]),float(k[5]),float(k[6])]
                                        resin.close()
                                    # get ion spectra (counts,density,flux, from flux_* file)
                                    if self.loadflux==1:
                                        fluxin=open(fluxname)
                                        s=["**********"]
                                        tmplen=len(self.name)
                                        while (s[0:tmplen]!=self.name):
                                            s=fluxin.readline()
                                            #k=s.split()
                                        s=fluxin.readline()
                                        k=s.split()
                                        if (self.mass==0.):
                                            self.mass=float(k[2])
                                        s=fluxin.readline()
                                        k=s.split()
                                        if (self.charge==0.):
                                            self.charge=float(k[2])
                                        s=fluxin.readline()
                                        for step in range(58):
                                            s=fluxin.readline()
                                            k=s.split()
                                            tmpdensspec.append([float(k[0]),float(k[7]),float(k[8]),float(k[9]),float(k[10])])                    
                                            tmpfluxspec.append([float(k[0]),float(k[3]),float(k[4]),float(k[5]),float(k[6])])                    
                                            tmpcountspec.append([float(k[0]),float(k[1]),float(k[2])])                    
                                        fluxin.close()
                                    if (tmptime<-999.):
                                        raise Exception
                                    if (self.loadres==1 and (tmpvel<-999. or tmpvelerr<-999. or tmpdens<-999. or tmpflux<-999. or tmptemp<-999.)):
                                        raise Exception
                                    if (self.loadflux==1 and (len(tmpdensspec)<58 or len(tmpfluxspec)<58 or len(tmpcountspec)<58)):
                                        raise Exception
                                    self.time.append(tmptime)
                                    self.vel.append(tmpvel)
                                    self.velerr.append(tmpvelerr)
                                    self.dens.append(tmpdens)
                                    self.flux.append(tmpflux)
                                    self.temp.append(tmptemp)
                                    self.densspec.append(tmpdensspec)
                                    self.fluxspec.append(tmpfluxspec)
                                    self.countspec.append(tmpcountspec)
                                    self.aspang.append(tmpasp)
                                    self.vsws.append(tmpvsws)
                                except:
                                    print "Data from ",resname," or ",fluxname," or ",ergname," incomplete or contains bad values"

        self.time=array(self.time)
        self.vel=array(self.vel)
        self.velerr=array(self.velerr)
        self.dens=array(self.dens)
        self.flux=array(self.flux)
        self.temp=array(self.temp)
        self.densspec=array(self.densspec)
        self.fluxspec=array(self.fluxspec)
        self.countspec=array(self.countspec)
        self.aspang=array(self.aspang)
        self.vsws=array(self.vsws)
        if self.loadres==1:
            self.calc_vth()
        if self.loadflux==1 and self.loadres==1:
            self.calc_higher_moments()
            self.calc_crmoments()
        print self.name+" loaded"

    def calc_vth(self):
        """
        Calculates thermal velocities from ion species and temperature
        """
        kb = 1.38065e-23
        u = 1.660538e-27
        self.vth=sqrt((self.temp[:,0]*kb)/(self.mass*u))/1000.
                
    def calc_suprathermal(self):
        """
        Calculates density in suprathermal tails. OLD ONLY USE WITH CARE!
        """
        self.suprath=[]
        self.suprath2=[]
        for i in range(len(self.dens)):
            spdens=0.
            sperr=0.
            spdens2=0.
            sperr2=0.
            #if (self.vel[i]>0.):
            #    print "low boundary = ",(self.vel[i]+3*self.vth[i])/self.vel[i]
            for step in range(len(self.densspec[i])):
                if (step>0 and step<len(self.densspec[i])-1):
                    lrange=(self.densspec[i][step][0]-self.densspec[i][step+1][0])/2.
                    rrange=(self.densspec[i][step-1][0]-self.densspec[i][step][0])/2.
                elif (step==0):
                    lrange=(self.densspec[i][step][0]-self.densspec[i][step+1][0])/2.
                    rrange=lrange
                elif (step==len(self.densspec[i])-1):
                    lrange=(self.densspec[i][step-1][0]-self.densspec[i][step][0])/2.
                    rrange=lrange
                else:
                    lrange=0.
                    rrange=0.
                if (self.densspec[i][step][0]+rrange>(self.vel[i]+3*self.vth[i]) and self.densspec[i][step][0]-lrange<self.vel[i]*2.3):
                    # right side integration
                    if (self.densspec[i][step][0]+rrange>self.vel[i]*2.3):
                        rv=self.vel[i]*2.3
                    elif (self.densspec[i][step][0]+rrange>(self.vel[i]+3*self.vth[i])):
                        rv=self.densspec[i][step][0]+rrange
                    else:
                        rv=(self.vel[i]+3*self.vth[i])
                    if (self.densspec[i][step][0]-lrange<(self.vel[i]+3*self.vth[i])):
                        lv=(self.vel[i]+3*self.vth[i])
                    elif (self.densspec[i][step][0]-lrange<(self.vel[i]*2.3)):
                        lv=self.densspec[i][step][0]-lrange
                    else:
                        lv=(self.vel[i]*2.3)
                    dv=rv-lv
                    spdens+=dv*1000.*self.densspec[i][step][1]
                    sperr+=(dv*1000.*self.densspec[i][step][2])**2
                #    print "integrating from ",lv/self.vel[i]," to ",rv/self.vel[i]
                if (self.densspec[i][step][0]>=2.3*self.vel[i]):
                    if (step==0):
                        spdens2+=(self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][1]
                        sperr2+=((self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][2])**2
                    elif (step==len(self.densspec[i])-1):
                        spdens2+=(self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][1]
                        sperr2+=((self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][2])**2
                    else:
                        spdens2+=(self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][1]
                        sperr2+=((self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][2])**2
            if (self.dens[i][0]!=0.):
                self.suprath.append([spdens/self.dens[i][0],(1/self.dens[i][0])*sqrt(sperr)+(spdens/self.dens[i][0]**2)*self.dens[i][1]])
                self.suprath2.append([spdens2/self.dens[i][0],(1/self.dens[i][0])*sqrt(sperr2)+(spdens2/self.dens[i][0]**2)*self.dens[i][1]])
            else:
                self.suprath.append([0.,0.])
                self.suprath2.append([0.,0.])

    def calc_densvelocity(self,velocity):
        """
        Calculates density from a given velocity to highest velocities. OLD ONLY USE WITH CARE!
        """
        self.densvelocity=[]
        for i in range(len(self.dens)):
            veldens=0.
            velerr=0.
            for step in range(len(self.densspec[i])):
                if (self.densspec[i][step][0]>=velocity):
                    if (step==0):
                        veldens+=(self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][1]
                        velerr+=((self.densspec[i][step][0]-self.densspec[i][step+1][0])*1000.*self.densspec[i][step][2])**2
                    elif (step==len(self.densspec[i])-1):
                        veldens+=(self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][1]
                        velerr+=((self.densspec[i][step-1][0]-self.densspec[i][step][0])*1000.*self.densspec[i][step][2])**2
                    else:
                        veldens+=(self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][1]
                        velerr+=((self.densspec[i][step-1][0]-self.densspec[i][step+1][0])*500.*self.densspec[i][step][2])**2
            if (self.dens[i][0]!=0.):
                self.densvelocity.append([veldens/self.dens[i][0],(1/self.dens[i][0])*sqrt(velerr)+(veldens/self.dens[i][0]**2)*self.dens[i][1]])
            else:
                self.densvelocity.append([0.,0.])
    

                              
    def calc_crmoments(self):
        """
        Calculates moments based on raw countrates! This is used for comparison with virtual detector.
        """
        self.crvel=[]
        self.crtemp=[]
        self.crvth=[]
        self.crdens=[]
        kb = 1.38065e-23
        u = 1.660538e-27
        for i in range(len(self.time)):
            tmpmoments=getcrmoments(self.countspec[i])
            self.crvel.append(tmpmoments[1])
            self.crtemp.append(tmpmoments[2]*1000.**2*u*self.mass/kb)
            self.crvth.append(sqrt(tmpmoments[2]))
            self.crdens.append(tmpmoments[0])
        self.crvel=array(self.crvel)
        self.crtemp=array(self.crtemp)
        self.crvth=array(self.crvth)
        self.crdens=array(self.crdens)

    def calc_higher_moments(self):
        """
        Higher moments skewness and kurtosis are calculated if possible.
        """
        self.skewness=[]
        self.kortosis=[]
        for i in range(len(self.densspec)):
            skewness=0.
            kortosis=0.
            dens=0.
            if (self.vth[i]>1. and self.vel[i]>100. and self.vel[i]<1500.):
                for j in range(len(self.densspec[i])):
                    deltavel=0.
                    if (j==0):
                        deltavel=(self.densspec[i][j][0]-self.densspec[i][j+1][0])*1000.
                    elif (j==len(self.densspec[i])-1):
                        deltavel=(self.densspec[i][j-1][0]-self.densspec[i][j][0])*1000.
                    else:
                        deltavel=((self.densspec[i][j-1][0]-self.densspec[i][j+1][0])*0.5)*1000.
                    skewness+=self.densspec[i][j][1]*deltavel*(((self.densspec[i][j][0]-self.vel[i]))/self.vth[i])**3
                    kortosis+=self.densspec[i][j][1]*deltavel*(((self.densspec[i][j][0]-self.vel[i]))/self.vth[i])**4
                    dens+=self.densspec[i][j][1]*deltavel
            if (dens>0.):
                skewness=skewness/dens
                kortosis=kortosis/dens
            self.skewness.append(skewness)
            self.kortosis.append(kortosis)
        self.skewness=array(self.skewness)
        self.kortosis=array(self.kortosis)

    def convres(self,res):
        """
        Converts resolution input in time in s. Valid values are '12m','1h','1d',720,3600,86400 -> output is 720.,3600.,or 86400.
        """
        try:
            if (str(res)=="12m"):
                return 720.
            elif (str(res)=="1h"):
                return 3600.
            elif (str(res)=="1d"):
                return 86400.
            elif (float(res)==720.):
                return 720.
            elif (float(res)==3600.):
                return 3600.
            elif (float(res)==86400.):
                return 86400.
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"
            
    def convresname(self,res):
        """
        Converts resolution input in time in string. Valid values are '12m','1h','1d',720,3600,86400 -> output is '12m','1h',or '1d'
        """
        try:
            if (str(res)=="12m"):
                return "12m"
            elif (str(res)=="1h"):
                return "1h"
            elif (str(res)=="1d"):
                return "1d"
            elif (float(res)==720.):
                return "12m"
            elif (float(res)==3600.):
                return "1h"
            elif (float(res)==86400.):
                return "1d"
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"


def loadswicsiondata(ionname,res,year,timeframe,path,loaderg=1,loadres=1,loadflux=1,dump=1,loaddump=1):
    """
    loads swicsiondata, prefers cpickled data
    """
    def convres(res):
        """
        Converts resolution input in time in s. Valid values are '12m','1h','1d',720,3600,86400 -> output is 720.,3600.,or 86400.
        """
        try:
            if (str(res)=="12m"):
                return 720.
            elif (str(res)=="1h"):
                return 3600.
            elif (str(res)=="1d"):
                return 86400.
            elif (float(res)==720.):
                return 720.
            elif (float(res)==3600.):
                return 3600.
            elif (float(res)==86400.):
                return 86400.
            else:
                raise Exception
        except:
            raise Exception, "Wrong resolution! Possible values are '12m','1h','1d',720,3600,86400"

    from os.path import isfile
    from libacepy.swicsiondata import swicsiondata
    import cPickle
    tmpstr=""
    for tf in timeframe:
        tmpstr+="_"+str(tf[0])+":"+str(tf[1])
    if loaderg:
        tmpstr+="_erg"
    if loadres:
        tmpstr+="_res"
    if loadflux:
        tmpstr+="_flux"
        
    cpicklename=path+"cpickle/"+ionname+"_"+str(convres(res))+"_"+str(year)+"_"+tmpstr+".cpic"   # location for cpickle dumps
    #print "load : ",cpicklename
    if isfile(cpicklename) and loaddump:
        inf=open(cpicklename,"r")
        tmp=cPickle.load(inf)
        inf.close()
        print cpicklename+" loaded"
        return tmp
    else:
        iondata=swicsiondata(ionname,res,year,timeframe,path,loaderg,loadres,loadflux)
        if dump:
            dumpswicsiondata(iondata)
        return iondata
    
def dumpswicsiondata(iondata):
    """
    cpickles object of type swicsiondata
    """
    from libacepy.swicsiondata import swicsiondata
    import cPickle
    out=open(iondata.cpicklename,"w")
    cPickle.dump(iondata,out)
    out.close()
    print "Dumped "+iondata.cpicklename



def getcrmoments(data):
    """
    data -> array containing spectrum
    """
    A=0.     #-->  integral
    v0=0.    #-->  center of mass
    sigsq=0. #-->  sigma^2
    A=sum(data[:,1])
    v0=sum(data[:,0]*data[:,1])/A
    sigsq=sum(data[:,1]*(data[:,0]-v0)**2)/A
    return [max(0.,A),max(0.,v0),max(0.,sigsq)]


def ionratio(ion1, ion2):
    erg=[]
    for j in range(len(ion1.dens)):
        if (ion2.dens[j][0]!=0.):
            ratio=ion1.dens[j][0]/ion2.dens[j][0]
            err=(ion1.dens[j][1]/ion2.dens[j][0])**2+(ion1.dens[j][0]*ion2.dens[j][1]/ion2.dens[j][0]**2)**2
            err2=(ion1.dens[j][2]/ion2.dens[j][0])**2+(ion1.dens[j][0]*ion2.dens[j][2]/ion2.dens[j][0]**2)**2
        else:
            ratio=0.
            err=0.
            err2=0.
        erg.append([ratio,sqrt(err),sqrt(err2)])
    return erg
