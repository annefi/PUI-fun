#!/usr/bin/python
from os import system
from scipy.linalg import inv
from scipy import zeros, dot
from numpy import float
from Gnuplot import Gnuplot, GridData
from math import sin,cos,tan,asin,acos,atan,exp,pi
from os import popen2
from sys import stdin
import random
from scipy.integrate import quad
from Gnuplot.func_ext import *

Float=float
matrixmultiply=dot
gp=Gnuplot()
gp2=Gnuplot()

#ions=["C6","O8","C5","O7","O6","C4","Fe15","Fe12","Fe13","Fe14","Si8","Si9","Si10","Si11","He2"]
#ion_label=["C^{6+}","O^{8+}","C^{5+}","O^{7+}","O^{6+}","C^{4+}","Fe^{15+}","Fe^{12+}","Fe^{13+}","Fe^{14+}","Si^{8+}","Si^{9+}","Si^{10+}","Si^{11+}","He^{2+}"]
ions=["C4","C5","C6","N5","N6","N7","O5","O6","O7","O8","Mg8","Mg9","Mg10","Mg11","Ne8","Si8","Si9","Si10","Si11","Si12","He2"]
ion_label=["C^{4+}","C^{5+}","C^{6+}","N^{5+}","N^{6+}","N^{7+}","O^{5+}","O^{6+}","O^{7+}","O^{8+}","Mg^{8+}","Mg^{9+}","Mg^{10+}","Mg^{11+}","Ne^{8+}","Si^{8+}","Si^{9+}","Si^{10+}","Si^{11+}","Si^{12+}","He^{2+}"]

data=zeros([len(ions),58,3],Float)



step=43

for j in range(len(ions)):
    file0=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/003/"+str(ions[j])+"+_eff")
    l=0
    for i in file0:
        x=i.split()
        data[j,l,0]=float(x[0])
        data[j,l,1]=float(x[2])+1
        data[j,l,2]=float(x[1])+1
        l+=1
    file0.close()



gp("unset key")
gp("set pm3d map")
gp("set logscale cb")
gp("set xrange[150:250]")
gp("set yrange[8:60]")
gp("set zrange[10:*]")

#gp("set label '\264' at "+str(he2[step,1])+","+str(he2[step,2])+" center font 'Symbol,24' front")
for i in range(len(ions)):
    gp("set label '\264' at "+str(data[i,step,1])+","+str(data[i,step,2])+" center font 'Symbol,24' front")
    gp("set label '"+ion_label[i]+"' at "+str(data[i,step,1])+","+str(data[i,step,2]+2.2)+" center font '36' front")
#gp("set label '\264' at "+str(data[len(ions)-1,step,1])+","+str(data[len(ions)-1,step,2])+" center font 'Symbol,24' front")
#gp("set label '"+ion_label[len(ions)-1]+"' at "+str(data[len(ions)-1,step,1])+","+str(data[len(ions)-1,step,2]-2)+" center font '36' front")
gp("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp("set format cb '10^{%L}'")
gp("set xlabel 'Flugzeit-Kanal'")
gp("set ylabel 'Energie-Kanal'")
gp("splot '/data/wimmer/mu/jahresdaten/all_data/step_files/all/step_"+str(step)+"_o_cme' u 2:1:3")
#gp("splot '/data/wimmer/mu/jahresdaten/all_data/step_files/all_under_he_speed+2/step_"+str(step)+"_o_cme' u 2:1:3")
#gp("set term postscript enhanced color 18")
#gp("set output 'pictures/step"+str(step)+".eps")
#gp("replot")
#system("ps2eps -l -B -f pictures/step"+str(step)+".eps")