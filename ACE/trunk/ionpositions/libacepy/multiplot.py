#!/usr/bin/python
from numpy import float
from Gnuplot import Gnuplot,Data,GnuplotOpts
from scipy import zeros
from libacepy.plotdata import plotdata
from libacepy.plotmark import plotmark
from math import log
import os
import sys


GnuplotOpts.prefer_fifo_data=0
GnuplotOpts.prefer_inline_data=0

class multiplot:
    """
    docstring should be added ...
    """

    def __init__(self,panels,setformat=0):
        self.panel=[]
        for i in range(panels):
            self.panel.append(plotdata())
        self.xrange=[0.,100.]
        self.xlabel="DoY"
        self.xaxis_flag=0
	self.title=""
        self.gv=1
        self.format=setformat #0 Querformat, 1 Hochformat
        self.outname="multiplot"
        self.plotmarks=[]

    def addplotmark(self,style,lt=5):
        self.plotmarks.append(plotmark(style,lt))
        
    def addpanel(self,data):
        self.panel.append(plotdata())
        
    def setxrange(self,a,b):
        self.xrange[0]=a
        self.xrange[1]=b
        
    def settitle(self,a):
        self.title=a

    def setgv(self,a):
        self.gv=a
    def setxaxis2(self,a):
    	"""
	This routine plots a seconds xaxis on top of the screen.
	Input must be a list of lists containing the x2label and xposition of that label:
	e.g: [["Jan",30],["Feb",58]...]
	"""
	self.xaxis_flag=1
	try:
		b=a[0][0]
		b=a[0][1]
	except:
		print "Wrong input for SELF.SETXAXIS2()"
		print "Input must be of the form of [['label',xpos],['label',xpos],[],[],...,[]]"
		print "Second x axis is omitted. Hit ENTER to proceed"
		blub=raw_input()
    	self.xaxis2=a
    def setxlabel(self,a):
        self.xlabel=str(a)

    def setname(self,a):
        self.outname=str(a)
    def build_xaxis2(self):
    	"""
 	This routine builds the seconds xaxis from self.xaxis2
	"""
	for label in self.xaxis2:
		if label[1]>self.xrange[0] and label[1]<self.xrange[1]:
			self.gp("set label center'{/Helvetica=5  %s}' at first %f, screen 1.00"%(label[0],label[1]))
	self.xaxis_flag=0
    def plot(self):
        self.gp=Gnuplot()
        self.generatebox()
        for panel in range(len(self.panel)):
		self.plotpanel(panel)
        #self.gp("unset tmargin")
        #self.gp("unset title")
        #self.gp("unset multiplot")
        #self.gp("set size 1,1")
        #self.gp("set xtics")
        self.gp("set autoscale")
        self.gp.sync()
        os.system("ps2eps -f -B -l %s.ps"%(self.outname))
        os.system("rm %s.ps"%(self.outname))
        if (self.gv):
            os.system("okular %s.eps"%(self.outname))
        del self.gp
        
    def generatebox(self):
        self.gp("set term postscript solid enhanced color")
        self.gp("set output '%s.ps'"%(self.outname))
	self.gp("set border front")
        self.gp("unset key")
        self.gp("unset colorbox")
        self.gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
        if (self.format):
            self.gp("set xtics nomirror font 'Helvetica,9'")
        else:
            self.gp("set xtics nomirror")
        self.gp("set multiplot")
        self.gp("set xlabel 0,0.1")
        if (self.format):
            self.gp("set xlabel '%s' font 'Helvetica,9'"%(self.xlabel))
        else:
            self.gp("set xlabel '%s' font 'Helvetica,12'"%(self.xlabel))
        self.gp("set xrange[%e:%e]"%(float(self.xrange[0]),float(self.xrange[1])))
        if (self.format):
            self.gp("set ytics font 'Helvetica,9'")
        else:
            self.gp("set ytics")
        #self.gp("set autoscale")
        self.gp("set key right samplen 0.5")
        self.gp("set key spacing 0.8")
        self.gp("unset xtics")
        self.gp("unset xlabel")
        self.gp("set border front")
	if self.xaxis_flag==1:
		self.build_xaxis2()

    def plotpanel(self,panel):
        self.buildplotmarks(panel)
        first=1
        self.gp("unset key")
	self.gp("set label center'{/Helvetica=9  %s}' at screen 0.3, screen 1.02"%(self.title))
        self.gp("set border front")
        #self.gp("unset label")
        if (self.panel[panel].grid):
            self.gp("set grid xtics front")
        else:
            self.gp("set grid xtics front")
            self.gp("unset grid")
        size=(.86/(float(len(self.panel))))+0.06
        size2=.86
        self.gp("unset xlabel")
        self.gp("set format x ''")
        self.buildytics(panel)
        if (panel==0):
            size=(.86/float((len(self.panel))))+0.1
            self.gp("set xlabel 0,0.2")
            if (self.format):
                self.gp("set xlabel '%s' font 'Helvetica,9'"%(self.xlabel))
            else:
                self.gp("set xlabel '%s' font 'Helvetica,12'"%(self.xlabel))
            self.gp("set format x")
            if (self.format):
                self.gp("set xtics font 'Helvetica,9'")
            else:
                self.gp("set xtics")
            self.gp("set mxtics 10")
        if (self.panel[panel].type=="plot"):
            self.gp("set size 1.,%f"%(size))
            if (self.format):
                self.gp("set size 0.6,%f"%(size))
        elif (self.panel[panel].type=="splot"):
            self.gp("set size 1.2935,%f"%(size*1.65))
        if (panel==0):
            self.gp("set origin 0,%f"%(0.05))
        else:
            if (self.panel[panel].type=="plot"):
                self.gp("set origin 0,%f"%(0.09+float(panel)*(size-0.06)))
            elif (self.panel[panel].type=="splot"):
                self.gp("set origin -.147,%f"%((0.09+float(panel)*(size-0.06))-.1315))

        self.gp("set lmargin 8")
        if (self.format):
            self.gp("set label '%s' at screen 0.05,%f center rotate by 90 font 'Helvetica,9'"%((self.panel[panel].ylabel),(0.09+float(panel)*(size-0.06)+size/2.)))
        else:
            self.gp("set label '%s' at screen 0.03,%f center rotate by 90 font 'Helvetica,12'"%((self.panel[panel].ylabel),(0.09+float(panel)*(size-0.06)+size/2.)))
        self.gp("set yrange[%e:%e]"%(self.panel[panel].yrange[0],self.panel[panel].yrange[1]))
	if self.panel[panel].xrange[0]!="NAN":
        	self.gp("set xrange[%e:%e]"%(self.panel[panel].xrange[0],self.panel[panel].xrange[1]))
        # plot marks
        for mark in self.plotmarks:
            doplotmark=0
            for i in mark.panels:
                if (i==-1 or i==panel and self.panel[panel].type=="plot"):
                    doplotmark=1
            if (doplotmark):
                doplotlabel=0
                if (mark.label!=""):
                    for i in mark.labelpanels:
                        if (i==-1 or i==panel):
                            doplotlabel=1
                if (mark.style=="vline"):
                    head=""
                    if (mark.arrowhead==0):
                        head="nohead"
                    elif (mark.arrowhead==1):
                        head="head filled"
                    mark.plot[panel].set_option_colonsep("with", "vectors %s lt %i lw %i"%(head,mark.linetype,mark.linewidth))
                    #self.gp("plot 'testvector.dat' with vectors")
                    if (doplotlabel):
                        if (self.format):
                            self.gp("set label '%s' at graph %f,%f tc lt %i font 'Helvetica,9' front"%((mark.label,mark.pos[0][0]/(self.xrange[1]-self.xrange[0])+0.01,0.8,mark.linetype)))
                        else:
                            self.gp("set label '%s' at graph %f,%f tc lt %i font 'Helvetica,12' front"%((mark.label,mark.pos[0][0]/(self.xrange[1]-self.xrange[0])+0.01,0.8,mark.linetype)))
                    if (first):
                        self.gp.plot(mark.plot[panel])
                        first=0
                    else:
                        self.gp.replot(mark.plot[panel])
                if (mark.style=="box"):
                    mark.plot[panel].set_option_colonsep("using", "1:2:3")
                    mark.plot[panel].set_option_colonsep("with", "filledcurves lt %i"%(mark.linetype))
                    if (doplotlabel):
                        if (self.format):
                            self.gp("set label '%s' at graph %f,%f tc lt %i font 'Helvetica,9' center front"%(mark.label,(mark.pos[0][0]+(mark.pos[0][2]-mark.pos[0][0])/2.)/(self.xrange[1]-self.xrange[0]),0.8,0))
                        else:
                            self.gp("set label '%s' at graph %f,%f tc lt %i font 'Helvetica,12' center front"%(mark.label,(mark.pos[0][0]+(mark.pos[0][2]-mark.pos[0][0])/2.)/(self.xrange[1]-self.xrange[0]),0.8,0))
                    if (first):
                        self.gp.plot(mark.plot[panel])
                        first=0
                    else:
                        self.gp.replot(mark.plot[panel])
                if (mark.style=="hline"):
                    head=""
                    if (mark.arrowhead==0):
                        head="nohead"
                    elif (mark.arrowhead==1):
                        head="head filled"
                    mark.plot[panel].set_option_colonsep("with", "vectors %s lt %i lw %i"%(head,mark.linetype,mark.linewidth))
                    #self.gp("plot 'testvector.dat' with vectors")
                    if (doplotlabel):
                        if (self.format):
                            self.gp("set label '%s' at graph %f,%f tc lt %i font 'Helvetica,9' front"%((mark.label,mark.pos[0][0]/(self.xrange[1]-self.xrange[0])+0.01,0.8,mark.linetype)))
                        else:
                            self.gp("set label '%s' at graph %f,%f tc lt %i font 'Helvetica,12' front"%((mark.label,mark.pos[0][0]/(self.xrange[1]-self.xrange[0])+0.01,0.8,mark.linetype)))
                    if (first):
                        self.gp.plot(mark.plot[panel])
                        first=0
                    else:
                        self.gp.replot(mark.plot[panel])
                if (mark.style=="function"):
                    if (first):
                        self.gp.plot(mark.plot[panel])
                    else:
                        self.gp.replot(mark.plot[panel])


        if (first and self.panel[panel].type=="plot"):
            if len(self.panel[panel].data)==1:
                self.gp("%s"%(self.panel[panel].key))
            self.gp.plot(self.panel[panel].data[0])
            first=0
        elif (first and self.panel[panel].type=="splot"):
            self.gp("set pm3d map")
            self.gp.splot(self.panel[panel].data[0])
            first=0
        else:
            self.gp.replot(self.panel[panel].data[0])
        for i in range(len(self.panel[panel].data)-1):
            if i==len(self.panel[panel].data)-2:
                self.gp("%s"%(self.panel[panel].key))
            self.gp.replot(self.panel[panel].data[i+1])
        self.gp("unset pm3d")

    def buildplotmarks(self,panel):
        for mark in self.plotmarks:
            tmpmark=[]
            if (mark.style=="vline"):
                tmppos=mark.pos
                tmppos[0][1]=self.panel[panel].yrange[0]*1.01
                tmppos[0][3]=(self.panel[panel].yrange[1]-self.panel[panel].yrange[0])*0.99
                tmpmark=Data(tmppos)
            if (mark.style=="hline"):
                tmppos=mark.pos
                tmppos[0][0]=self.xrange[0]*1.01
                tmppos[0][2]=(self.xrange[1]-self.xrange[0])*0.99
                tmpmark=Data(tmppos)
            if (mark.style=="box"):
                if mark.pos[0][2]==1e-20:
                    ymin=self.panel[panel].yrange[0]
                else:
                    ymin=mark.pos[0][2]
                if mark.pos[0][3]==1e20:
                    ymax=self.panel[panel].yrange[1]
                else:
                    ymax=mark.pos[0][3]
                tmppos=[[mark.pos[0][0],ymin,ymax],[mark.pos[0][1],ymin,ymax]]
                #tmppos=[[mark.pos[0][0],self.panel[panel].yrange[1],self.panel[panel].yrange[0]],[mark.pos[0][2],self.panel[panel].yrange[1],self.panel[panel].yrange[0]]]
                tmpmark=Data(tmppos)
            if (mark.style=="function"):
                tmpmark=mark.function
            if (tmpmark!=[]):
                mark.addplot(tmpmark)

    def buildytics(self,panel):
        # the tics for panel=panel are set. The cases logscale and linear scale are handled. In the first panel (panel==0) all tics are labeled set   
        # in all other panels the first tic is unlabeled to avoid overlapp with the tics from the panel below.
        # logscale tics are set   --->  if yrange is smaller than 7 orders of magnitude the tics are set each order of magnitude and 8 minor tics
        #                               corresponding to 2*,3*,...,9* are set (will fail if yrange is smaller than one order of magnitude
        #                               if yrange is greater than 
        # linearscale tics are set ---> 

        if (self.panel[panel].ytics!=""):
            if (self.format):
                self.gp("set ytics %s font 'Helvetica,9'"%(self.panel[panel].ytics))
            else:
                self.gp("set ytics %s"%(self.panel[panel].ytics))
            if (self.panel[panel].logscale):
                self.gp("set logscale y")
            return
        
        # begin if logscale
        if (self.panel[panel].logscale):
            self.gp("unset ytics")
            self.gp("set logscale y")
            self.gp("set format y '10^{%2T}'")
            adjust=0
            i=1.e0
            while (not adjust):
                i=i*10.
                tmp=self.panel[panel].yrange[0]
                tmp=tmp*i**6
                if (tmp>=self.panel[panel].yrange[1]):
                    adjust=1

            if (self.panel[panel].minor<0):
                if (i<=10.):
                    minor=8
                else:
                    minor=int(log(i,10.)+.01)
                    minor2=2
            if (self.panel[panel].minor==0):
                if (i<=10.):
                    minor=0
                else:
                    minor=int(log(i,10.)+.01)
                    minor2=1
            if (self.panel[panel].minor>0):
                if (i<=10.):
                    minor=self.panel[panel].minor
                else:
                    minor=int(log(i,10.)+.01)
                    minor2=2
            tic=self.panel[panel].yrange[0]
            utic=tic
            if (i<=10.):
                j=-1
                while (utic<=self.panel[panel].yrange[1]):
                    j+=1
                    utic=tic*i**j
                    if (j==0):
                        if (panel==0):
                            if (self.format):
                                self.gp("set ytics (%e) font 'Helvetica,9'"%(utic))
                            else:
                                self.gp("set ytics (%e)"%(utic))
                        else:
                            if (self.format):
                                self.gp("set ytics (' ' %e) font 'Helvetica,9'"%(float(utic)))
                            else:
                                self.gp("set ytics (' ' %e)"%(float(utic)))
                    else:
                        self.gp("set ytics add (%e)"%(utic))
                    for l in range(minor):
                        self.gp("set ytics add ('' %e 1)"%(utic+(utic*9./float(minor+1)*float(l+1))))
            else:
                j=-1
                while (utic<=self.panel[panel].yrange[1]):
                    j+=1
                    utic=tic*i**j
                    if (j==0):
                        if (panel==0):
                            if (self.format):
                                self.gp("set ytics (%e) font 'Helvetica,9'"%(utic))
                            else:
                                self.gp("set ytics (%e)"%(utic))
                        else:
                            if (self.format):
                                self.gp("set ytics (' ' %e) font 'Helvetica,9'"%(float(utic)))
                            else:
                                self.gp("set ytics (' ' %e)"%(float(utic)))
                    else:
                        self.gp("set ytics add (%e)"%(utic))
                    for k in range(minor):
                        for l in range(minor2):
                            if (not (k==minor-1 and l==minor2-1)):
                                if (l==minor2-1):
                                    self.gp("set ytics add ('' %e)"%(float(utic)*float(10**k)*float((l+1)*10./float(minor2))))
                                else:
                                    self.gp("set ytics add ('' %e 1)"%(float(utic)*float(10**k)*float((l+1)*10./float(minor2))))
        # begin if linear scale
        else:
            self.gp("unset ytics")
            self.gp("unset logscale y")
            self.gp("set format y '%6g'")
            i=.1
            while (self.panel[panel].yrange[1]-self.panel[panel].yrange[0]>i):
                i=i*10.
            minor=9
            if (i/4.>=self.panel[panel].yrange[1]-self.panel[panel].yrange[0]):
                i=i/4.
                minor=4
            elif (i/2.>=self.panel[panel].yrange[1]-self.panel[panel].yrange[0]):
                i=i/2.
                minor=9
            if (self.panel[panel].minor==0):
                minor=0
            elif (self.panel[panel].minor>0):
                minor=self.panel[panel].minor

            if (i>10.):
                for j in range(6):
                    if (j==0):
                        if (panel==0):
                            if (self.format):
                                self.gp("set ytics (%i) font 'Helvetica,9'"%(int(self.panel[panel].yrange[0])))
                            else:
                                self.gp("set ytics (%i)"%(int(self.panel[panel].yrange[0])))
                        else:
                            if (self.format):
                                self.gp("set ytics (' ' %i) font 'Helvetica,9'"%(int(self.panel[panel].yrange[0])))
                            else:
                                self.gp("set ytics (' ' %i)"%(int(self.panel[panel].yrange[0])))
                    else:
                        self.gp("set ytics add (%i)"%(int(self.panel[panel].yrange[0]+i/5.*j)))
                    print "minor = ",minor
                    for k in range(minor):
                        if ((minor+1)%5==0 and (k+1)%5==0):
                            self.gp("set ytics add (' ' %i)"%(int(self.panel[panel].yrange[0]+j*i/5.+(i/5./float(minor+1)*float(k+1)))))
                        else:
                            self.gp("set ytics add (' ' %i 1)"%(int(self.panel[panel].yrange[0]+j*i/5.+(i/5./float(minor+1)*float(k+1)))))
            else:
                for j in range(6):
                    if (j==0):
                        if (panel==0):
                            if (self.format):
                                self.gp("set ytics (%f) font 'Helvetica,9'"%(self.panel[panel].yrange[0]))
                            else:
                                self.gp("set ytics (%f)"%(self.panel[panel].yrange[0]))
                        else:
                            if (self.format):
                                self.gp("set ytics (' ' %f) font 'Helvetica,9'"%(self.panel[panel].yrange[0]))
                            else:
                                self.gp("set ytics (' ' %f)"%(self.panel[panel].yrange[0]))
                    else:
                        self.gp("set ytics add (%f)"%(self.panel[panel].yrange[0]+i/5.*j))
                    for k in range(minor):
                        if ((minor+1)%5==0 and (k+1)%5==0):
                            self.gp("set ytics add (' ' %f)"%(self.panel[panel].yrange[0]+j*i/5.+(i/5./float(minor+1)*float(k+1))))
                        else:
                            self.gp("set ytics add (' ' %f 1)"%(self.panel[panel].yrange[0]+j*i/5.+(i/5./float(minor+1)*float(k+1))))
