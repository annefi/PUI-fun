#!/usr/bin/python
from numpy import float
from math import pi
from scipy import zeros
from libacepy.errors import gethistogram
from Gnuplot import Gnuplot,Data,GnuplotOpts

GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

class error:
    "Class error : contains errordata\n\t name = array[steps][ions] ..."
    def __init__(self,filename):
        self.filename=filename
        self.name=[]
        self.ionname=""
        self.step=0
        self.counts=0.
        self.frac=0.
        self.error=0.
        self.fiterg=[]
        self.normerg=[]
        self.histogram=[]
#        self.gp=Gnuplot()

    """
    method : reads in maximum-likelihood-fitresults to generated data. the name of the file is in self.filename
    """
    def readerrordata(self):
        dim=200
        infile=open(self.filename)
        tmpfitergion1=[]
        tmpfitergion2=[]
        tmpnormergion1=[]
        tmpnormergion2=[]
        for step in range(dim):
            s=infile.readline()
            k=s.split()
            numions=int(k[5])
            numions=2
            s=infile.readline()
            for ion in range(numions):
                s=infile.readline()
                k=s.split()
                if (step==0):
                    self.name.append(k[0])
                if (ion==0):
                    tmpfitergion1.append(float(k[10]))
                    tmpnormergion1.append(float(k[11]))
                if (ion==1):
                    tmpfitergion2.append(float(k[10]))
                    tmpnormergion2.append(float(k[11]))
        self.fiterg.append(tmpfitergion1)
        self.fiterg.append(tmpfitergion2)
        self.normerg.append(tmpnormergion1)
        self.normerg.append(tmpnormergion2)
        print "load : ",self.filename
        
    """
    method : calculates error from already loaded maximum-likelihodd-fitresults (via readerrordata)
    gethistogram first makes a histogram out of the m-l-fitresults. afterwards getfitpara determines the parameters for the final fitting to the histogram. in the end the fit to the histogram is performed. 
    """
    def calcerror(self):
        gethistogram(self)
        self.getfitpara()
        self.geterror()
        
    """
    method :
    """
    def geterror(self):
        gp=Gnuplot()
#        gp("set yrange[0:1e20]")
        gp("a=%f" %(self.counts))
        print len(self.histogram[0])
        gp("b=5.")
        gp("c=200.")
        gp("f(x)=c/(sqrt(2.*pi)*b)*exp(-((x-a)**2/(2.*b**2)))")
        self.gphist=Data(self.histogram[0])
        self.gphist.set_option_colonsep("with","boxes")
        if (len(self.histogram[0])>3):
            gp("fit f(x) '"+self.gphist.filename+"' using 1:2 via a,b")
            gp("fit f(x) '"+self.gphist.filename+"' using 1:2 via b")
        else:
            gp("b=0.1")
#        gp.plot(self.gphist,"f(x)")
#        gp("pause 3")
        self.error=gp.eval("b")/self.counts
        print self.error
    
    """
    method :
    """
    def getfitpara(self):
        positions=[]
        for i in range(len(self.filename)):
            if (self.filename[i:i+1]=="_"):
                positions.append(i)
        print positions
        self.ionname=self.filename[positions[2]+1:positions[3]]
        self.step=int(self.filename[positions[3]+5:positions[4]])
        self.counts=float(self.filename[positions[4]+1:positions[5]])
        self.frac=float(self.filename[positions[5]+1:positions[6]])
        print self.ionname
        print self.step
        print self.counts
        print self.frac
        print self.name
