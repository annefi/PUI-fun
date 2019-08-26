from ace_utils import calc_day00
from pylib import dbData
from numpy import *
import os

class swics_dcrtcr(dbData):
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
            self.path="/data/ivar/ace/pui/12mspec/"
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
                                                eff[nri].append(effion[nri][step])
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





