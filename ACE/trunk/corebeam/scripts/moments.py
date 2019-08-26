from numpy import loadtxt,histogram,linspace,zeros,where,sqrt,array,isnan,amax,exp,mean,cross,ones,amin,arange,isinf
from Gnuplot import Data,Gnuplot
from pylib.etTools import fftPlot
from pylib.etData import etData
from libacepy.swicsiondata import loadswicsiondata
from libacepy.swicsdcrtcr import swicsdcrtcr
from libacepy.mag import magdata
import copy


        
class moments(etData):
    def __init__(self,allign="para"):
        etData.__init__(self)
        self.name="moments%scoreff2.dat"%(allign)
        self.load()
        self.gphist=Gnuplot()
        self.gphist("set title '%s'"%(allign))

    def load(self):
        infile=open(self.name,"r")
        keys=(infile.readline()).split()
        dat=loadtxt(infile)
        for i,key in enumerate(keys):
            self.data[key]=copy.deepcopy(dat[:,i])

    def plot_hist(self,arg,xvals,xlabel=None,ylabel=None,save=False,title=None,reset=False):
        print self.get_hist(arg,xvals)[0],self.get_hist(arg,xvals)[1]
        if reset:
            self.gphist.reset()
        if ylabel:
            self.gphist("set ylabel '%s'"%(ylabel))
        if xlabel:
            self.gphist("set xlabel '%s'"%(xlabel))
        if not title:
            title=arg
        self.gphist.replot(Data(self.get_hist(arg,xvals)[0],self.get_hist(arg,xvals)[1],with_="histeps lw 3",title=title))
        if ylabel or xlabel:
            self.gphist("unset xlabel")


if __name__=="__main__":
    

    test=moments(allign="para")
    test.show_mask()
    test.apply_mask()
    #test.add_data("dvhe",(test.data["maxvhe"]-test.data["vsw"])/test.data["valf"])
    #test.set_mask("dvhe",[[">=",-0.1],"*",["<=",0.1]])
    #test.apply_mask()
    #test.plot_hist("skewhe",linspace(-3.,3,61))
    #test.set_mask("dvhe",(0.4,0.6))
    #test.apply_mask()
    #test.plot_hist("skewhe",linspace(-3.,3,61))
    #test.set_mask("dvhe",(0.9,1.1))
    #test.apply_mask()
    #test.plot_hist("skewhe",linspace(-3.,3,61))
    test.reset_mask()
    test.set_mask("valf",[[">=",30.],"*",[isnan]])
    test.set_mask("dsw",[[">=",0.1],"*",["<=",8.]])
    test.apply_mask()
    #test.gphist("set title 'para'")
    #test.plot_hist("stdh",linspace(0.,2.,41),xlabel="Std",ylabel="# Occurences")
    #test.plot_hist("stdhe",linspace(0.,2.,41))
    #test.plot_hist("stdo",linspace(0.,2.,41))
    #test.set_mask("all",[["isinf",1]])
    #test.show_info()
    #test.show_mask()
