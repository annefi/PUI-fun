#!/usr/bin/python

"""
  Revision controlled by SVN:
  $Id: ionerror.py 3838 2007-07-06 10:03:36Z berger $
"""

from numpy import float
from scipy import zeros,sqrt

class fiterrordat:
    "Class ionerror : contains ..."
    def __init__(self,ionname):
        self.name=ionname
        self.steplist=[]
        self.fraclist=[]
        self.erglist=[]
        self.errordat=[]
        self.errexist=1
        try:
            errfile=open("/data/wimmer/ace/errors/"+self.name+".err")
        except:
            self.errexist=0
        if (self.errexist):
            self.getlists()
            self.geterrordat()
            
    """
    function : reads errorfile and sets step- frac- and erglist
    """
    def getlists(self):
        errfile=open("/data/wimmer/ace/errors/"+self.name+".err")
        for line in errfile:
            k=line.split()
            if (k[0]=="Step"):
                self.steplist.append(int(k[2]))
            if (k[0]=="Ion"):
                if (len(self.fraclist)==0):
                    for i in range(len(k)-1):
                        self.fraclist.append(float(k[i+1]))
            iserg=1
            try:
                float(k[0])
            except:
                iserg=0
            if (iserg==1):
                da=0
                for i in range(len(self.erglist)):
                    if (float(k[0])==self.erglist[i]):
                        da=1
                if (da==0):
                    self.erglist.append(float(k[0]))
        errfile.close()
        


    def geterrordat(self):
        errfile=open("/data/wimmer/ace/errors/"+self.name+".err")
        stepint=-1
        ergint=-1
        for step in range(len(self.steplist)):
            self.errordat.append([])
            for erg in range(len(self.erglist)):
                self.errordat[step].append([])
        for line in errfile:
            k=line.split()
            if (k[0]=="Step"):
                stepint=stepint+1
            if (k[0]=="Ion"):
                if (ergint<len(self.erglist)-1):
                    ergint=ergint+1
                else:
                    ergint=0
            if (k[0]!="Step" and k[0]!="Ion"):
                app=0
                try:
                    float(k[0])
                except:
                    app=1
                if (app==1):
                    tmpfrac=[]
                    tmpfrac.append(k[0])
                    for frac in range(len(self.fraclist)):
                        tmpfrac.append(float(k[frac+1]))
                    print "stepint =",stepint
                    print "ergint =",ergint
                    self.errordat[stepint][ergint].append(tmpfrac)
        errfile.close()
