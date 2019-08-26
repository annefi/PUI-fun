from ace_utils import calc_day00,get_mass
from ace_swics import ace_swics
from pylib import dbData
from numpy import *
from scipy import constants
import os

class ace_swics_dcrtcr(dbData):
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
            self.ion=["H1+"]
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
            self.path="/data/ivar/ace/swicsdcrtcr/12mspec/"
        if kwargs.has_key("fmt"):
            self.fmt=kwargs["fmt"]
        else:
            self.fmt="new"
        if self.fmt=="old":
            time=[]
            years=[]
            vel=[]
            dcr=[]
            tcr=[]
            effiontcr=[]
            efftcr=[]
            effiondcr=[]
            effdcr=[]
            for ion in self.ion:
                tmpefftcr=loadtxt("/data/etph/ace/efficencies/"+ion+".eff")
                tmpefftcr[:,1][tmpefftcr[:,1]==0]=1.
                effiontcr.append(list(tmpefftcr[:,1]))
                tmpeffdcr=loadtxt("/data/etph/ace/efficencies/"+ion+"_dcr.eff")
                tmpeffdcr[:,1][tmpeffdcr[:,1]==0]=1.
                effiondcr.append(list(tmpeffdcr[:,1]))
            for i in range(len(self.ion)):
                vel.append([])
                dcr.append([])
                tcr.append([])
                efftcr.append([])
                effdcr.append([])
            for year in self.year:
                dlist=os.listdir(self.path+str(year)+"/")
                for tf in self.timeframe:
                    for doy in arange(tf[0],tf[1]+0.1,1.):
                        print doy
                        tmpname="%.3i"%(doy)
                        for f in dlist:
                            if tmpname in f:
                                for nri,ion in enumerate(self.ion):
                                    flist=os.listdir(self.path+str(year)+ "/" + str(tmpname))
                                    flist2=[]
                                    for name in flist:
                                        if ion in name:
                                            flist2.append(name)
                                    flist2.sort()
                                    times=[]
                                    for name in flist2:
                                        tmptime=float(doy)
                                        ofs=len(ion)
                                        if int(name[17+ofs:21+ofs])!=year and int(name[35+ofs:39+ofs])!=year:
                                            print "File : " + name + " wrong year!"
                                        elif int(name[22+ofs:25+ofs])!=doy and int(name[40+ofs:43+ofs])!=doy:
                                            print "File : " + name + " wrong doy!"
                                        else:
                                            if int(name[22+ofs:25+ofs])<doy:
                                                tmptime=float(name[22+ofs:25+ofs])
                                                tmpyear=year
                                            elif int(name[17+ofs:21+ofs])<year and int(name[22+ofs:25+ofs])>doy:
                                                tmptime=float(name[22+ofs:25+ofs])
                                                tmpyear=float(name[17+ofs:21+ofs])
                                            else:
                                                tmptime=float(doy)
                                                tmpyear=year
                                            tmptime+=float(name[26+ofs:28+ofs])/24.
                                            tmptime+=float(name[29+ofs:31+ofs])/(24.*60.)
                                            tmptime+=float(name[32+ofs:34+ofs])/(24.*60.*60.)
                                            fin=open(self.path+str(year)+ "/" + str(tmpname) + "/" + name, "r")
                                            for i in range(7):
                                                fin.readline()
                                            for step in range(58):
                                                s=fin.readline()
                                                l=s.split()
                                                vel[nri].append(float(l[0]))
                                                dcr[nri].append(float(l[2]))
                                                tcr[nri].append(float(l[3]))
                                                effdcr[nri].append(effiondcr[nri][step])
                                                efftcr[nri].append(effiontcr[nri][step])
                                                if nri==0:
                                                    years.append(tmpyear)
                                                    time.append(tmptime)
            self.data["year"]=array(years)
            self.data["time"]=array(time)
            for i,ion in enumerate(self.ion):
                self.data["v"+ion]=array(vel[i])
                self.data["dcr"+ion]=array(dcr[i])
                self.data["tcr"+ion]=array(tcr[i])
                self.data["efftcr"+ion]=array(efftcr[i])
                self.data["effdcr"+ion]=array(effdcr[i])
            self.data["d00"]=calc_day00(self.data["year"],self.data["time"])
        # Alternative "new" data structure
        elif self.fmt=="new":
            self.data["year"]=[]
            self.data["time"]=[]
            self.data["d00"]=[]
            for ion in self.ion:
                self.data["v"+ion]=[]
                self.data["dcr"+ion]=[]
                self.data["tcr"+ion]=[]
                self.data["effdcr"+ion]=[]
                self.data["efftcr"+ion]=[]
            for year in self.year:
                dlist=os.listdir(self.path+str(year)+"/")
                for tf in self.timeframe:
                    for doy in arange(tf[0],tf[1]+0.1,1.):
                        print doy
                        tmpname="%.3i."%(doy)
                        load_day=True
                        for ion in self.ion:
                            if not (tmpname+ion) in dlist:
                                load_day=False
                        if not load_day:
                            print "load_data: doy ",str(doy)," of year ",str(year), "not all ions found! Skipping day!"
                        else:
                            for i,ion in enumerate(self.ion):
                                fin=open(self.path+str(year)+"/"+tmpname+ion,"r")
                                fin.readline()
                                for s in fin:
                                    k=s.split()
                                    if i==0:
                                        self.data["year"].append(year)
                                        self.data["time"].append(float(k[0]))
                                        self.data["d00"].append(float(k[1]))
                                    self.data["v"+ion].append(float(k[2]))
                                    self.data["dcr"+ion].append(float(k[3]))
                                    self.data["tcr"+ion].append(float(k[4]))
                                    self.data["effdcr"+ion].append(float(k[5]))
                                    self.data["efftcr"+ion].append(float(k[6]))
                                fin.close()
            ud00,ud00ind=unique(array(self.data["d00"]),return_inverse=True)
            self.data.add_reduced_data("d00",ud00,"ud00ind",expansion=ud00ind)
            self.data["year"]=array(self.data["year"])                
            self.data["time"]=array(self.data["time"])                
            for ion in self.ion:
                uv=array(self.data["v"+ion][:58])
                ueffdcr=array(self.data["effdcr"+ion][:58])
                ueffdcr[ueffdcr==0]=1
                uefftcr=array(self.data["efftcr"+ion][:58])
                uefftcr[uefftcr==0]=1
                ind=array(range(len(uv))*len(ud00))
                self.data.add_reduced_data("v"+ion,uv,"uvind",expansion=ind)
                self.data.add_reduced_data("effdcr"+ion,ueffdcr,"uvind")
                self.data.add_reduced_data("efftcr"+ion,uefftcr,"uvind")
                self.data["dcr"+ion]=array(self.data["dcr"+ion])
                self.data["tcr"+ion]=array(self.data["tcr"+ion])

    def calc_moments(self):
        uTi,index=unique(self.data["d00"],return_inverse=True)
        uTi=append(uTi,uTi[-1]+0.00001)
        if not "d00" in self.data.expand.keys():
            self.data.add_reduced_data("d00",uTi[:-1],"ud00ind",expansion=index)
        for ion in self.ion:
            dens=self.data["dcr"+ion]/self.data["effdcr"+ion]/(self.data["v"+ion]*0.03)+self.data["tcr"+ion]/self.data["efftcr"+ion]/(self.data["v"+ion]*0.03)
            #0th order moment
            nrc=histogram(self.data["d00"],bins=uTi,weights=self.data["dcr"+ion]+self.data["tcr"+ion])
            if "cts"+ion in self.data.keys():
                self.data.add_reduced_data("cts"+ion,nrc[0],"ud00ind")
            else:
                self.add_reduced_data("cts"+ion,nrc[0],"ud00ind")
            nrc=histogram(self.data["d00"],bins=uTi,weights=dens)
            if "d"+ion in self.data.keys():
                self.data.add_reduced_data("d"+ion,nrc[0],"ud00ind")
            else:
                self.add_reduced_data("d"+ion,nrc[0],"ud00ind")
            mask=~isnan(nrc[0][index])*nrc[0][index]>0.
            #1th order moment
            vtc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*self.data["v"+ion][mask])
            vel=vtc[0]/nrc[0]
            if "vel"+ion in self.data.keys():
                self.data.add_reduced_data("vel"+ion,vel,"ud00ind")
            else:
                self.add_reduced_data("vel"+ion,vel,"ud00ind")
            #2th order moment
            vtc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*(self.data["v"+ion][mask]-vel[index][mask])**2)
            vth=sqrt(vtc[0]/nrc[0])
            if "vth"+ion in self.data.keys():
                self.data.add_reduced_data("vth"+ion,vth,"ud00ind")
            else:
                self.add_reduced_data("vth"+ion,vth,"ud00ind")
            #3th order moment
            vtc=histogram(self.data["d00"][mask],bins=uTi,weights=dens[mask]*(self.data["v"+ion][mask]-vel[index][mask])**3)
            vsk=vtc[0]/nrc[0]/vth**3
            if "vsk"+ion in self.data.keys():
                self.data.add_reduced_data("vsk"+ion,vsk,"ud00ind")
            else:
                self.add_reduced_data("vsk"+ion,vsk,"ud00ind")
            self.add_reduced_data("t"+ion,1.e6*self.data.__getitem__("vth"+ion,raw=True)**2*get_mass(ion)*constants.atomic_mass/2./constants.k,"ud00ind")

    def bin_data(self,t1,t2,prod1="d00",prod2="time"):
        """
        binning is performed on prod1! default is day since 1.1.2000 (d00). Other prods like doy might not work properly if more than one year is present
        """
        self.reset_mask("Master")
        tmpprod=self[prod1]
        tmpdata={}
        keys=["d00","time","year"]
        for ion in self.ion:
            keys.append("v"+ion)
            keys.append("effdcr"+ion)
            keys.append("efftcr"+ion)
            keys.append("dcr"+ion)
            keys.append("tcr"+ion)
        for key in keys:
            tmpdata[key]=[]
        v={}
        effdcr={}
        efftcr={}
        for ion in self.ion:
            v[ion]=self["v"+ion][0:58]
            effdcr[ion]=self["effdcr"+ion][0:58]
            efftcr[ion]=self["efftcr"+ion][0:58]
        for ti,t in enumerate(t1):
            dt=tmpprod-t
            tmpt=tmpprod[(dt>-1./24./60.)*(dt<1./24./60.)]
            if tmpt.shape[0]==0:
                for i in range(58):
                    tmpdata["d00"].append(t)
                    tmpdata["time"].append(t2[ti])
                    tmpdata["year"].append(self.year[0])
                    for ion in self.ion:
                        tmpdata["v"+ion].append(v[ion][i])
                        tmpdata["effdcr"+ion].append(effdcr[ion][i])
                        tmpdata["efftcr"+ion].append(efftcr[ion][i])
                        tmpdata["dcr"+ion].append(0.)
                        tmpdata["tcr"+ion].append(0.)
            else:
                if tmpt.shape[0]!=58:
                    print "bin_data: tmpt.shape = ",tmpt.shape
                self.set_mask("Master",prod1,tmpt[0],op="eq",reset=True)
                for key in keys:
                    tmpdat=self.get_data("Master",key)
                    for i in range(58):
                        if key=="d00":
                            tmpdata["d00"].append(t)
                        elif key=="time":
                            tmpdata["time"].append(t2[ti])
                        else:
                            tmpdata[key].append(tmpdat[i])
        for key in keys:
            self.data[key]=array(tmpdata[key])
        self.reset_mask("all")
        #self.calc_moments()

    def save_spec(self,path="/data/ivar/ace/swicsdcrtcr/12mspec/"):
        for year in self.year:
            self.reset_mask("Master")
            self.set_mask("Master","year",year,op="eq",reset=True)
            doys=self.get_data("Master","time")
            if doys.shape[0]>0:
                for day in range(int(amin(doys)),int(amax(doys))+1):
                    for ion in self.ion:
                        tmpname="%s%s/%.3i.%s"%(path,str(year),day,ion)
                        if not os.path.isfile(tmpname):
                            fout=open(tmpname,"w")
                            fout.write("doy\t\td00\t\tv\tdcr\ttcr\teffdcr\t\tefftcr\n")
                for day in range(int(amin(doys)),int(amax(doys))+1):
                    self.set_mask("Master","time",day,day+0.9999999,reset=True)
                    if self.get_data("Master","time").shape[0]>0:
                        for ion in self.ion:
                            tmpname="%s%s/%.3i.%s"%(path,str(year),day,ion)
                            tmpdoy=self.get_data("Master","time")
                            tmpv=self.get_data("Master","v"+ion)
                            tmpdcr=self.get_data("Master","dcr"+ion)
                            tmptcr=self.get_data("Master","tcr"+ion)
                            tmpeffdcr=self.get_data("Master","effdcr"+ion)
                            tmpefftcr=self.get_data("Master","effdcr"+ion)
                            tmpd00=self.get_data("Master","d00")
                            tmpdat=zeros((tmpdoy.shape[0],7))
                            tmpdat[:,0]=tmpdoy
                            tmpdat[:,1]=tmpd00
                            tmpdat[:,2]=tmpv
                            tmpdat[:,3]=tmpdcr
                            tmpdat[:,4]=tmptcr
                            tmpdat[:,5]=tmpeffdcr
                            tmpdat[:,6]=tmpefftcr
                            fout=open(tmpname,"a")
                            savetxt(fout,tmpdat,fmt=["%.8f","%.8f","%.2f","%.2f","%.2f","%.8f","%.8f"],delimiter="\t")
        self.reset_mask("Master")

