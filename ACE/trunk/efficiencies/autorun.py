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
from libacepy.frange import frange
import random

Float=float

from Gnuplot import GnuplotOpts
GnuplotOpts.gnuplot_command='/usr/local/bin/gnuplot'


gp=Gnuplot()

# In Spalte 1 steht das Stopping in keV/(ug/cm^2)
# Der Faktor 22.661 macht daraus eV/A
# Der Faktor c1=0.085 machst daraus eine Anzahl von Elektronen
gp("f(x)=(1-(1+x)*exp(-x))*(1-pf1**x)")
gp("C1=0.085")
gp("pf1=0.8")
gp("fit f(x) 'fsr_cal_o_He' u ($1*0.085*22.661):2 via pf1")
gp("pf2=pf1")
ion='O'
#ion='Fe'

system("cat runconfig_orig.dat |sed 's/set_fitmode/1/'|sed 's/set_run2/0/'|sed 's/set_run4/0/'|sed 's/set_run6/0/'|sed 's/set_caldatzion/8/'|sed 's/set_ba/0/'|sed 's/set_aspang/5.0/'|sed 's/set_beta/5.0/'|sed 's/set_thang/0/'> runconfig.dat")
#system("cat runconfig_orig.dat |sed 's/set_fitmode/1/'|sed 's/set_run2/0/'|sed 's/set_run4/0/'|sed 's/set_run6/0/'|sed 's/set_caldatzion/26/'|sed 's/set_ba/0/'|sed 's/set_aspang/5.0/'|sed 's/set_beta/5.0/'|sed 's/set_thang/0/' > runconfig.dat")
system("make")
system("make plugin")

gp("Ethr    = 25.33")
gp("FWHM    = 10")
gp("C2      = 0.18")
gp("C3      = 33")
gp("defl    = 0.0349")
gp("thick   = 2.5")
gp("z       = 8")
gp("m       = 16")
gp("auxpar1 = 1")
gp("auxpar2 = 1")
gp("auxpar3 = 1")
gp("ladung  = 1")

# C3 wird hier als aspect angle benutzt

for i in range(3):
    gp("dcr_fsr(e)= 'swxeff_gpt.so', '"+ion+"'")
    gp("probmode= 1")
    gp("fit dcr_fsr(x,z,m,ladung,C1,C2,C3,pf1,pf2,Ethr,FWHM,thick,defl,probmode,auxpar1,auxpar2,auxpar3) './caldat/o2_o_con.txt' u ($13/$1):16:($34) via C2,defl")
    gp("plot dcr_fsr(x,z,m,ladung,C1,C2,C3,pf1,pf2,Ethr,FWHM,thick,defl,probmode,auxpar1,auxpar2,auxpar3), './caldat/o2_o_con.txt' u ($13/$1):16:($34) w e")


    gp("tcr_dcr(e)= 'swxeff_gpt.so', '"+ion+"'")
    gp("probmode= 2")
    gp("fit tcr_dcr(x,z,m,ladung,C1,C2,C3,pf1,pf2,Ethr,FWHM,thick,defl,probmode,auxpar1,auxpar2,auxpar3) './caldat/o2_o_con.txt' u ($13/$1):15:33 via Ethr, FWHM,C3")
    gp("plot tcr_dcr(x,z,m,ladung,C1,C2,C3,pf1,pf2,Ethr,FWHM,thick,defl,probmode,auxpar1,auxpar2,auxpar3), './caldat/o2_o_con.txt' u ($13/$1):15:33 w e")

Ethr=float(str(gp.eval("Ethr")))
FWHM=float(str(gp.eval("FWHM")))
pf1=float(str(gp.eval("pf1")))
pf2=float(str(gp.eval("pf2")))
C1=float(str(gp.eval("C1")))
C2=float(str(gp.eval("C2")))
C3=float(str(gp.eval("C3")))
defl=float(str(gp.eval("defl")))
thick=float(str(gp.eval("thick")))
#memory=mkstemp()[1]
file2=open("./param/parameters", "w")
file2.write("Ethr    "+str(Ethr))
file2.write("\n")
file2.write("FWHM    "+str(FWHM))
file2.write("\n")
file2.write("pf1     "+str(pf1))
file2.write("\n")
file2.write("pf2     "+str(pf2))
file2.write("\n")
file2.write("C1      "+str(C1))
file2.write("\n")
file2.write("C2      "+str(C2))
file2.write("\n")
file2.write("aa      "+str(C3))
file2.write("\n")
file2.write("defl    "+str(defl))
file2.write("\n")
file2.write("thick   "+str(thick))
file2.close()

system("cat runconfig_orig.dat |sed 's/set_fitmode/1/'|sed 's/set_run2/1/'|sed 's/set_run4/0/'|sed 's/set_run6/0/'|sed 's/set_caldatzion/8/'|sed 's/set_ba/0/'|sed 's/set_aspang/5.0/'|sed 's/set_beta/5.0/'|sed 's/set_thang/0/' > runconfig.dat")
system("./test1")

system("cat runconfig_orig.dat |sed 's/set_fitmode/0/'|sed 's/set_run2/0/'|sed 's/set_run4/1/'|sed 's/set_run6/0/'|sed 's/set_caldatzion/8/'|sed 's/set_ba/0/'|sed 's/set_aspang/5.0/'|sed 's/set_beta/5.0/'|sed 's/set_thang/0/' > runconfig.dat")
system("./test1")

system("cat runconfig_orig.dat |sed 's/set_fitmode/0/'|sed 's/set_run2/0/'|sed 's/set_run4/0/'|sed 's/set_run6/1/'|sed 's/set_caldatzion/8/'|sed 's/set_ba/0/'|sed 's/set_aspang/5.0/'|sed 's/set_beta/5.0/'|sed 's/set_thang/0/' > runconfig.dat")
system("./test1")


eff_data=zeros([58,2],Float)
p_data=zeros([101,2],Float)
o_data=zeros([58,3],Float)

listmion=["1H","3He","4He","12C","13C","14N","16O","20Ne","24Mg","28Si","32S","40Ca","56Fe"]
listmionraw=["H","3He","He","C","13C","N","O","Ne","Mg","Si","S","Ca","Fe"]
listchargehigh=["1","2","2","6","6","7","8","8","12","12","12","14","26"]
listchargelow=["1","1","1","3","3","4","4","7","5","5","5","6","5"]

for m in range(len(listmion)):
        for h in range(int(listchargelow[m])-1,int(listchargehigh[m])):
            stop=0
            dateiname1="lars/aspeff/330/"+listmion[m]+str(h+1)+"+.eff"
            print dateiname1
            file1=open(dateiname1)
            l=0
            for i in file1:
                data=i.split()
                if not ((float(data[1])) == 0.):
                    for k in range(2):
                        eff_data[l,k]=float(data[k])
                if ((float(data[1])) == 0.):
                    eff_data[l,0]=float(data[0])
                    for k in range(1,2):
                        eff_data[l,k]=0.0
                    stop=1
                if (data[1] == "NAN"):
                    eff_data[l,0]=float(data[0])
                    for k in range(1,2): # geändert 31.3.2008 vorher range(1,1) -> macht keinen sinn
                        eff_data[l,k]=0.0
                    stop=2
                l=l+1
#            print eff_data

            for j in range(58):
                if not (eff_data[j,1] == 0.0):
                    dateiname2="lars/aspeff/err/"+listmion[m]+str(h+1)+"_step"+str(j+1)
                    print dateiname2
                    file2=open(dateiname2)
                    l=0
                    for i in file2:
                        data=i.split()
                        for k in range(2):
                            p_data[l,k]=float(data[k])
                        l=l+1
#                    print p_data

                    print "FITTEN MIT GNUPLOT"
                    x0=p_data[51,0]
                    sigma=(p_data[51,0])*0.1
                    pi=3.1415927
                    A=sigma*800.
                    gp("pi="+str(pi))
                    gp("x0="+str(x0))
                    gp("A="+str(A))
                    gp("sigma="+str(sigma))
                    if (x0 > 0.01):
                        gp("f(x)=A*(1/(sigma*(2*pi)**0.5))*exp(-((x-x0)**2)/(2*sigma**2))")
                        for tft in range(3):
                            gp("fit f(x) '"+dateiname2+"' via A,x0")
                            gp("fit f(x) '"+dateiname2+"' via A,sigma,x0")
                        o_data[j,0]=float(str(gp.eval("A")))
                        o_data[j,1]=float(str(gp.eval("sigma")))
                        o_data[j,2]=float(str(gp.eval("x0")))
                    else:
                        o_data[j,0]=0.0
                        o_data[j,1]=0.0
                        o_data[j,2]=0.0
#                    gp("plot f(x),'"+dateiname2+"'")
            dateiname3 = "lars/aspeff/eff_we/"+listmionraw[m]+str(h+1)+"+.eff"
            file3= open(dateiname3,"w")
            for j in range(58):
                if (eff_data[j,1] == 0.0):
                    o_data[j,1]=0.0
                file3.write(str(eff_data[j,0]))
                file3.write("   ")
                file3.write(str(eff_data[j,1]))
                file3.write("   ")
                file3.write(str(o_data[j,1]))
                file3.write("\n")
            file3.close()
            if not (stop == 0):
                dateiname4 = "broken"
                file4= open(dateiname4,"a")
                file4.write(listmion[m]+str(h+1))
                file4.write("\n")
                file4.close()

del gp


