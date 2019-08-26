#!/usr/bin/python

"""
  Revision controlled by SVN:
  $Id: ionerror.py 4783 2007-08-06 15:07:09Z berger $
"""

from numpy import float
from scipy import zeros,sqrt

class ionerror:
    "Class ionerror : contains ..."
    def __init__(self,ionname,step,names,normerg):
        self.filename="/data/wimmer/ace/errors/"+ionname+".err"
        self.name=names
        self.ionname=ionname
        self.ionpos=-1
        self.step=step
        self.frac=[]
        self.error=0.
        self.normerg=normerg
        self.stepintervall=0
        self.steplist=[]
        self.fraclist=[]
        self.erglist=[]
        self.errordat=[]
        self.fracint=[]
        self.stepint=[]
        self.ergint=0

    def getfracint(self):
        for frac in self.frac:
            tmpfrac=0
            for i in range(len(self.fraclist)):
                if (frac<=self.fraclist[i]):
                    tmpfrac=i-1
                    break
                if (i==len(self.fraclist)-1):
                    tmpfrac=i-1
            if (tmpfrac==-1):
                tmpfrac=0
            self.fracint.append(tmpfrac)

    def getstepint(self):
        for ion in self.name:
            if (ion!=self.ionname):
                tmpstep=0
                for i in range(len(self.steplist)):
                    if (self.step<=self.steplist[i]):
                        tmpstep=i-1
                        break
                    if (i==len(self.steplist)-1):
                        tmpstep=i-1
                if (tmpstep==-1):
                    tmpstep=0
                self.stepint.append(tmpstep)

    
    def loaderrorfile(self):
        for ion in range(len(self.name)-1):
            tmparr3=[]
            for step in range(len(self.steplist)):
                tmparr2=[]
                for i in range(len(self.erglist)):
                    tmparr=[]
                    for i in range(len(self.fraclist)):
                        tmparr.append(0.)
                    tmparr2.append(tmparr)
                tmparr3.append(tmparr2)
            self.errordat.append(tmparr3)
        tmpion=-1
        for ion in self.name:
            if (ion!=self.ionname):
                tmpion=tmpion+1
                errin=open(self.filename)
                step=-1
                erg=0
                for line in errin:
                    k=line.split()
                    if (k[0]=="Step"):
                        step=step+1
                    for i in range(len(self.erglist)):
                        if (k[0]==str(self.erglist[i])):
                            erg=i
                    if (k[0]==ion):
#                        print "step = ",step
#                        print "k = ",k
#                        print "erg = ",erg
#                        print "tmpion = ",tmpion
                        for i in range(len(self.fraclist)):
                            self.errordat[tmpion][step][erg][i]=float(k[i+1])
        errin.close()
        
    def getlists(self):
        errfile=open(self.filename)
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



    def getionpos(self):
        for ion in range(len(self.name)):
            if (self.name[ion]==self.ionname):
                self.ionpos=ion

    def getfrac(self):
        for ion in range(len(self.name)):
            if (self.ionpos!=ion):
                if (self.normerg[self.ionpos]!=0.):
                    self.frac.append(self.normerg[ion]/self.normerg[self.ionpos])
                else:
                    self.frac.append(0.)

    def calc(self):
        self.getionpos()
        self.getfrac()
        self.getlists()
        self.loaderrorfile()
        self.getfracint()
        self.getstepint()
        shift=0
        for ion in range(len(self.name)):
            if (ion==self.ionpos):
                shift=1
            else:
                if (self.errordat[ion-shift][self.stepint[ion-shift]][0][self.fracint[ion-shift]]==0.):
                    if (self.stepint[ion-shift]!=len(self.steplist)-2):
                        self.stepint[ion-shift]=self.stepint[ion-shift]+1
                if (self.errordat[ion-shift][self.stepint[ion-shift]+1][0][self.fracint[ion-shift]]==0.):
                    if (self.stepint[ion-shift]!=0):
                        self.stepint[ion-shift]=self.stepint[ion-shift]-1
                fraclinint=[]
                x=self.normerg[self.ionpos]
                erglinint=[]
                for j in range(2):
                    for i in range(2):
                        x1=self.erglist[0]
                        x2=self.erglist[1]
                        y1=self.errordat[ion-shift][self.stepint[ion-shift]+j][0][self.fracint[ion-shift]+i]*self.erglist[0]
                        y2=self.errordat[ion-shift][self.stepint[ion-shift]+j][1][self.fracint[ion-shift]+i]*self.erglist[1]
                        erglinint.append(linint(x1,x2,y1,y2,x))
                x1=self.fraclist[self.fracint[ion-shift]]
                x2=self.fraclist[self.fracint[ion-shift]+1]
                x=self.frac[ion-shift]
                fraclinint.append(linint(x1,x2,erglinint[0],erglinint[1],x))
                fraclinint.append(linint(x1,x2,erglinint[2],erglinint[3],x))
                x1=self.steplist[self.stepint[ion-shift]]
                x2=self.steplist[self.stepint[ion-shift]+1]
#                print self.errordat[ion-shift][self.stepint[ion-shift]][0]
#                print self.errordat[ion-shift][self.stepint[ion-shift]+1][0]
                error=linint(x1,x2,fraclinint[0],fraclinint[1],self.step)
#                print self.name[ion]
#                print "erg = ",self.normerg[ion]
#                print "frac = ",self.frac[ion-shift]
#                print "error = ",error
                #*self.normerg[self.ionpos]
                if (not((self.normerg[self.ionpos]==0.)and(self.normerg[ion-shift]==0.))):
                    self.error=self.error+error*error
                #*self.normerg[sbelf.ionpos]
        self.error=sqrt(self.error)
#        print "step = ",self.step
#        print "ionname = ",self.ionname

def linint(x1,x2,y1,y2,x):
    a=(y2-y1)/(x2-x1)
    b=y1-a*x1
#    print "a = ",a
#    print "b = ",b
    return a*x+b
