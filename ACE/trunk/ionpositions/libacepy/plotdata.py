#!/usr/bin/python
from numpy import float

class plotdata:
    #def __init__(self,data):
    #   self.data=data
    #    self.yrange=[0.,100.]
    #    self.ylabel=""
    #    self.title=""
    #    self.logscale=0
    #    self.grid=0
    #    self.minor=-1
        
    def __init__(self):
        self.data=[]
        self.yrange=[0.,100.]
	self.xrange=["NAN","NAN"]
        self.ylabel=""
        self.title=""
        self.outname=""
        self.logscale=0
        self.grid=0
        self.minor=-1
        self.type="plot"
        self.key="unset key"
        self.ytics=""

    def settype(self,type):
        """
        type -> string
        suported types are "plot" and "splot"
        """
        if (type=="plot" or type=="splot"):
            self.type=type
        else:
            print "wrong type -> suported types are 'plot' and 'splot'"
        
    def setytics(self,ytics):
        self.ytics=ytics
        
    def adddata(self,data):
        """
        data -> Gnuplot Data or GridData object\n
        if GridData is added user has set type to 'splot' before(!) and has to take care of all input no options will be set automatically! Do not change tpye after data has been added!
        """
        self.data.append(data)
        i = len(self.data)-1
        options=""
        if (i==0 and self.type=="plot"):
	    try:
                s=self.data[i].get_option("with")
                k=s.split()
                da=0
                for j in range(len(k)):
                    if (k[j]=="lt"):
                        da=1
                if (da):
                    option=s
                else:
                    option=s+" lt %i"%(i+1) 
                self.data[i].set_option_colonsep("with",option)
            except:
		self.data[i].set_option_colonsep("with","l lt %i"%(i+1))
        if (i!=0 and self.type=="plot"):
            try:
                s=self.data[i].get_option("with")
                k=s.split()
                da=0
                for j in range(len(k)):
                    if (k[j]=="lt"):
                        da=1
		if (da):
                    option=s
                else:
                    option=s+" lt %i"%(i+2) 
                self.data[i].set_option_colonsep("with",option)
            except:
		self.data[i].set_option_colonsep("with","l lt %i"%(i+2))
    def setxrange(self,a,b):
    	"""
	Routine that sets xrange for every panel on it's own.
	Thus it is possible to create multipanel plots with different xranges.
	If xrange for panel isn't set, then xrange of multiplot object is used instead 
	"""
	try:
		self.xrange[0]=float(a)
		self.xrange[1]=float(b)
	except:
            print "wrong format setyrange : try setxrange(float,float)"
    def setyrange(self,a,b):
        try:
            self.yrange[0]=float(a)
            self.yrange[1]=float(b)
        except:
            print "wrong format setyrange : try setyrange(float,float)"

    def setminor(self,a):
        try:
            self.minor=int(a)
        except:
            print "wrong format setminor : try setminor(int), -1 (or any negative integer) = auto tics, positive integer = number of minor tics"
            print "note that user has to check if setting make any sense at all. For example if yrange is >=10 in linear mode a lot of setting will be ignored since only integer values are valid. (if yrange is 25 there are only 4 tics possible between 20 and 25 and so on ...)" 
    def settitle(self,a):
        self.title=str(a)

    def setylabel(self,a):
        self.ylabel=str(a)

    def setlogscale(self,a):
        """
        a=bool, default value is 0
        """
        self.logscale=a
        if (self.logscale and self.yrange[0]==0.):
            self.yrange[0]=1e-1
        
    def setgrid(self,a):
        """
        a:bool, default value is 0
        """
        self.grid=a
