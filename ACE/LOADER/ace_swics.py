from ace_utils import calc_day00
from pylib import dbData
from numpy import *
import os

class ace_swics(dbData):
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
            self.path="/data/ivar/ace/swics/12mspec/"
        if kwargs.has_key("fmt"):
            self.fmt=kwargs["fmt"]
        else:
            self.fmt="new"
        if self.fmt=="old":
            time=[]
            years=[]
            vel=[]
            cr=[]
            effion=[]
            eff=[]
            for ion in self.ion:
                tmpeff=loadtxt("/data/etph/ace/efficencies/"+ion+".eff")
                tmpeff[:,1][tmpeff[:,1]==0]=1.
                effion.append(list(tmpeff[:,1]))
            for i in range(len(self.ion)):
                vel.append([])
                cr.append([])
                eff.append([])
            for year in self.year:
                dlist=os.listdir(self.path+str(year)+"/")
                for tf in self.timeframe:
                    for doy in arange(tf[0],tf[1]+0.1,1.):
                        print doy
                        tmpname="%.3i"%(doy)
                        for f in dlist:
                            if tmpname in f:
                                flist=os.listdir(self.path+str(year)+ "/" + str(tmpname))
                                flist2=[]
                                for name in flist:
                                    if "flux" in name:
                                        flist2.append(name)
                                flist2.sort()
                                times=[]
                                for name in flist2:
                                    tmptime=float(doy)
                                    if int(name[21:25])!=year and int(name[39:43])!=year:
                                        print "File : " + name + " wrong year!"
                                    elif int(name[26:29])!=doy and int(name[44:47])!=doy:
                                        print "File : " + name + " wrong doy!"
                                    else:
                                        if int(name[26:29])<doy:
                                            tmptime=float(name[26:29])
                                            tmpyear=year
                                        elif int(name[21:25])<year and int(name[26:29])>doy:
                                            tmptime=float(name[26:29])
                                            tmpyear=float(name[21:25])
                                        else:
                                            tmptime=float(doy)
                                            tmpyear=year
                                        tmptime+=float(name[30:32])/24.
                                        tmptime+=float(name[33:35])/(24.*60.)
                                        tmptime+=float(name[36:38])/(24.*60.*60.)
                                        tmpion=[]
                                        for i,ion in enumerate(self.ion):
                                            tmpion.append(ion)
                                        fin=open(self.path+str(year)+ "/" + str(tmpname) + "/" + name, "r")
                                        s="****"
                                        while not(len(tmpion)==0 or len(s)==0):
                                                s=fin.readline()
                                                k=s.split()
                                                s=fin.readline()
                                                s=fin.readline()
                                                s=fin.readline()
                                                if k==[]:
                                                    k=["*"]
                                                if k[0] in tmpion:
                                                    for i,ion in enumerate(self.ion):
                                                        if k[0]==ion:
                                                            for step in range(58):
                                                                s=fin.readline()
                                                                l=s.split()
                                                                vel[i].append(float(l[0]))
                                                                cr[i].append(float(l[1]))
                                                                eff[i].append(effion[i][step])
                                                                if i==0:
                                                                    years.append(tmpyear)
                                                                    time.append(tmptime)
                                                            tmpion.remove(ion)
                                                            break
                                                else:
                                                    for step in range(58):
                                                        s=fin.readline()
            self.data["year"]=array(years)
            self.data["time"]=array(time)
            for i,ion in enumerate(self.ion):
                self.data["v"+ion]=array(vel[i])
                self.data["cr"+ion]=array(cr[i])
                self.data["eff"+ion]=array(eff[i])
            self.data["d00"]=calc_day00(self.data["year"],self.data["time"])
        # Alternative "new" data structure
        elif self.fmt=="new":
            self.data["year"]=[]
            self.data["time"]=[]
            self.data["d00"]=[]
            for ion in self.ion:
                self.data["v"+ion]=[]
                self.data["cr"+ion]=[]
                self.data["eff"+ion]=[]
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
                                    self.data["cr"+ion].append(float(k[3]))
                                    self.data["eff"+ion].append(float(k[4]))
                                fin.close()
            ud00,ud00ind=unique(array(self.data["d00"]),return_inverse=True)
            self.data.add_reduced_data("d00",ud00,"ud00ind",expansion=ud00ind)
            self.data["year"]=array(self.data["year"])                
            self.data["time"]=array(self.data["time"])                
            for ion in self.ion:
                uv=array(self.data["v"+ion][:58])
                ueff=array(self.data["eff"+ion][:58])
                ueff[ueff==0]=1
                ind=array(range(len(uv))*len(ud00))
                self.data.add_reduced_data("v"+ion,uv,"uvind",expansion=ind)
                self.data.add_reduced_data("eff"+ion,ueff,"uvind")
                self.data["cr"+ion]=array(self.data["cr"+ion])
    def calc_moments(self):
        uTi,index=unique(self.data["d00"],return_inverse=True)
        uTi=append(uTi,uTi[-1]+0.00001)
        if not "d00" in self.data.expand.keys():
            self.data.add_reduced_data("d00",uTi[:-1],"ud00ind",expansion=index)
        for ion in self.ion:
            dens=self.data["cr"+ion]/self.data["eff"+ion]/(self.data["v"+ion]*0.03)
            #0th order moment
            nrc=histogram(self.data["d00"],bins=uTi,weights=self.data["cr"+ion])
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

    def save_spec(self,path="/data/ivar/ace/swics/12mspec/"):
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
                            fout.write("doy\t\td00\t\tv\tcr\teff\n")
                for day in range(int(amin(doys)),int(amax(doys))+1):
                    self.set_mask("Master","time",day,day+1,reset=True)
                    for ion in self.ion:
                        tmpname="%s%s/%.3i.%s"%(path,str(year),day,ion)
                        tmpdoy=self.get_data("Master","time")
                        tmpv=self.get_data("Master","v"+ion)
                        tmpcr=self.get_data("Master","cr"+ion)
                        tmpeff=self.get_data("Master","eff"+ion)
                        tmpd00=self.get_data("Master","d00")
                        tmpdat=zeros((tmpdoy.shape[0],5))
                        tmpdat[:,0]=tmpdoy
                        tmpdat[:,1]=tmpd00
                        tmpdat[:,2]=tmpv
                        tmpdat[:,3]=tmpcr
                        tmpdat[:,4]=tmpeff
                        fout=open(tmpname,"a")
                        savetxt(fout,tmpdat,fmt=["%.8f","%.8f","%.2f","%.2f","%.8f"],delimiter="\t")
        self.reset_mask("Master")
