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
#from functions import *
from libacepy.frange import frange
import random


Float=float
matrixmultiply=dot
gp=Gnuplot()

c=zeros([101],Float)
t_data=zeros([512,3],Float)
e_data=zeros([128,3],Float)
ions=["He2","O8","N7","C6","13C6","O7","N6","C5","Mg10","Ne8","O6","N5","Si12","Si9","Si10","Si11","C4","O5"]
ions1=["He2","O8","N7","C6","13C6","O7","N6","C5","Mg10","Ne8","O6","N5"]
ions2=["He2","O8","N7","C6","13C6","O7","N6","C5","Mg10","Ne8","O6","N5","Si12","Si9","Si10","Si11","C4","O5"]
#ions1=["He2","O8","N7","C6","13C6","O7","N6","Mg10","C5","Ne8","O6","N5","Si12"]
#ions2=["He2","O8","N7","C6","13C6","O7","N6","Mg10","C5","Ne8","O6","N5","Si12"]
x=zeros([len(ions)],Float)
G=zeros([len(ions)],Float)
sg=zeros([len(ions)],Float)
sk=zeros([len(ions)],Float)
sl=zeros([len(ions)],Float)
sr=zeros([len(ions)],Float)
kappa=zeros([len(ions)],Float)
breite=zeros([len(ions)],Float)
bg=zeros([len(ions)],Float)
tp=zeros([len(ions),2],Float)
tp_all1=zeros([len(ions),58,2],Float)
tp_all2=zeros([len(ions),58,2],Float)
cr=zeros([len(ions)],Float)
res=zeros([30,6],Float)
epq_array=zeros([58],Float)
he_data=zeros([900,58,12],Float)
he_data_2=zeros([58,10],Float)

#de=0.682817 # bis februar 091
#dt=5.80315 # bis februar 09
#de=0.448 # neuer fit, februar 09
#dt=6.41 # neuer fit, februar 09
de=1.448055 # wie vorher nur genauer
dt=7.41082818114 # wie vorher nur genauer
#de=1.451238 # paps=23.8, thick=2.3
#dt=7.48819922535 # paps=23.8, thick=2.3

def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q

def steptov(step,m,q):
    eq=epq_array[int(step)]
    return (((eq*q/(6.24150974*10.**15.)*2.)/(m/(6.0221415*10.**26.)))**0.5)/1000.

file0=open("../experiments/steps")
for i in file0:
    x=i.split()
    for k in range(58):
        epq_array[k]=float(x[k])
file0.close()

file0=open("hsf_results/linear/v_int_40/hsf_all")
for i in file0:
    x=i.split()
    for j in range(12):
        he_data[int(x[0]),int(x[1]),j]=float(x[j])
file0.close()

file0=open("hsf_results/linear/all/hsf_all_ave")
#file0=open("hsf_results/linear/v_int_40/hsf_all_ave")

l=0
for i in file0:
    x=i.split()
    for j in range(10):
        he_data_2[l,j]=float(x[j])
    l+=1
file0.close()
#print he_data_2

# count rates von Lars

cr[0]=100000.
cr[1]=500. # O8 # geschaetzt
cr[2]=2546.91 # N7
cr[3]=18186. # C12
cr[4]=0. # Mg11 # geschaetzt
cr[5]=1000. # C13 geschaetzt
cr[6]=11054.63 # O7
cr[7]=9591.11 # N6
cr[8]=500. # Mg10 # geschaetzt
cr[9]=6940.99 # C5
cr[10]=4254.4 # Ne8
cr[11]=500. # Mg9
#cr[12]=2858.22 # O6
#cr[13]=1029.88 # N5
#cr[14]=500. # C4 # gesschaetzt

v_int=445

gp("max1(x)=x>0.5? x:0.5")

# Theoretische Positionen aus dem Eff-Modell
for j in range(len(ions)):
    file0=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/003/"+ions[j]+"+_eff")
    #file0=open("/data/wimmer/mu/appendix/000/"+ions[j]+"+.et")
    l=0
    for i in file0:
        xx=i.split()
        tp_all1[j,l,0]=float(xx[2])+1
        tp_all1[j,l,1]=float(xx[1])+1
        l+=1
    file0.close()


v_int_array=range(345,350,10)
interval=int(20)
v2_int_array=range(460+interval,500,interval*2)
c12=zeros(len(v2_int_array),Float)
c13=zeros(len(v2_int_array),Float)
c13c12=zeros(len(v2_int_array),Float)
c12_step=zeros(58,Float)
c13_step=zeros(58,Float)
dummy1=zeros([40,1000,len(v2_int_array)],Float)
dummy2=zeros([40,1000,len(v2_int_array)],Float)
epq=0.
ll=0
for v_int in v2_int_array:
#if (1):
    epq=f(12,v_int,6)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
    kk=0
    for step in range(epqstep-4,epqstep+4):
        if (step >= epqstep-3):
            ions=ions1
        else:
            ions=ions1
        for i in range(len(ions)):
            for j in range(2):
                tp[i,j]=tp_all1[i,step,j]
        filex=open("/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_o_cme")
        #filex=open("/data/wimmer/mu/jahresdaten/all_data/step_files/all/step_"+str(step)+"_o_cme")
        for i in filex:
            et_data=i.split()
            if (len(et_data) > 0):
                for j in range(len(ions)):
                    if ((int(et_data[0]) == int(tp[j,1])) and (int(et_data[1]) == int(tp[j,0]))):
                        cr[j] = float(et_data[2])
        pp=0
        for rn in range(1000):
            if(1 == 1): 
                for i in range(len(ions)):
                    gp("ge"+str(i)+"(x)=((x-(xge"+str(i)+"))**2)**0.5<3*(sge*((ev+xge"+str(i)+")-"+str(de)+"))? Ge"+str(i)+"*exp(-(x-(ev+xge"+str(i)+"))**2/(2*(sge*((ev+xge"+str(i)+")-"+str(de)+"))**2)):0.")
                    gp("ktl"+str(i)+"(x,y)=((x-(xkt"+str(i)+"))**2)**0.5<3*(sktl*((tv+xkt"+str(i)+")-"+str(dt)+"))? (1+((x-(tv+xkt"+str(i)+"))**2/((kappatl)*(sktl*((tv+xkt"+str(i)+")-"+str(dt)+"))**2)))**-(kappatl):0.")
                    gp("ktr"+str(i)+"(x,y)=((x-(xkt"+str(i)+"))**2)**0.5<3*(sktr*((tv+xkt"+str(i)+")-"+str(dt)+"))? (1+((x-(tv+xkt"+str(i)+"))**2/(((max1((ksr1*("+str(he_data_2[step,1])+"-"+str(de)+")/((ev+xge"+str(i)+")-"+str(de)+")*(y-(ev+xge"+str(i)+")))+ksr2))*ksr_error)*(sktr*((tv+xkt"+str(i)+")-"+str(dt)+"))**2)))**-((max1((ksr1*("+str(he_data_2[step,1])+"-"+str(de)+")/((ev+xge"+str(i)+")-"+str(de)+")*(y-(ev+xge"+str(i)+")))+ksr2))*ksr_error):0.")
                    #gp("ktr"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/(((max1((ksr1*("+str(he_data[int(v_int),step,2])+"-"+str(de)+")/(xge"+str(i)+"-"+str(de)+")*(y-xge"+str(i)+"))+ksr2))*ksr_error)*(sktr*(xkt"+str(i)+"-"+str(dt)+"))**2)))**-((max1((ksr1*("+str(he_data[int(v_int),step,2])+"-"+str(de)+")/(xge"+str(i)+"-"+str(de)+")*(y-xge"+str(i)+"))+ksr2))*ksr_error)")

                    # Energie + ToF Gauss - alle gleiches sge und sgt, naemlich sge3 und sgt3, sge(i)=xge(i)*sge3
                    #gp("ge"+str(i)+"(x)=Ge"+str(i)+"*exp(-(x-xge"+str(i)+")**2/(2*(sge*(xge"+str(i)+"-"+str(de)+"))**2))")
                    #gp("ktl"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/((kappatl)*(sktl*(xkt"+str(i)+"-"+str(dt)+"))**2)))**-(kappatl)")
                    #gp("ktr"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/((exp(ksr1*(y-xge"+str(i)+"))+ksr2)*(sktr*(xkt"+str(i)+"-"+str(dt)+"))**2)))**-(exp(ksr1*(y-xge"+str(i)+")+ksr2))")

                    # zusammensetzen der kappa funktion
                    gp("kt"+str(i)+"(x,y)=x<xkt"+str(i)+"? Kt"+str(i)+"*ktl"+str(i)+"(x,y):Kt"+str(i)+"*ktr"+str(i)+"(x,y)")

                    # zusammensetzen der 3d funktion
                    gp("s"+str(i)+"(x,y)=ge"+str(i)+"(x)*kt"+str(i)+"(y,x)")
                    teststep=step
                    # setzen der variablen
                    gp("Ge"+str(i)+"="+str(cr[i]))
                    gp("Kt"+str(i)+"=1")
                    gp("xkt"+str(i)+"="+str(tp[i,0]))#+random.gauss(0.,0.26)))
                    gp("xge"+str(i)+"="+str(tp[i,1]))#+random.gauss(0.,0.39)))
                    #gp("ksr_error="+str(1.))#*random.gauss(1.,0.03)))
                    gp("ksr_error="+str(1.*random.gauss(1.,0.03)))
                    #gp("kappatl="+str(he_data_2[teststep,7]))
                    gp("kappatl="+str(he_data_2[teststep,7]*random.gauss(1.,0.05)))
                    #gp("kappatl="+str(he_data[int(v_int),step,9]))#*random.gauss(1.,0.05)))
                    gp("ksr1="+str(he_data_2[teststep,8]))
                    #gp("ksr1="+str(he_data[int(v_int),step,10]))
                    gp("ksr2="+str(he_data_2[teststep,9]))
                    #gp("ksr2="+str(he_data[int(v_int),step,11]))
                    #gp("sktl="+str(he_data_2[teststep,4]))#*random.gauss(1.,0.01)))
                    gp("sktl="+str(he_data_2[teststep,4]*random.gauss(1.,0.01)))
                    #gp("sktl="+str(he_data[int(v_int),step,6]))#*random.gauss(1.,0.01)))
                    #gp("sktr="+str(he_data_2[teststep,5]))#*random.gauss(1.,0.01)))
                    gp("sktr="+str(he_data_2[teststep,5]*random.gauss(1.,0.01)))
                    #gp("sktr="+str(he_data[int(v_int),step,7]))#*random.gauss(1.,0.01)))
                    #gp("sge="+str(he_data_2[teststep,3]))#*random.gauss(1.,0.1)))
                    gp("sge="+str(he_data_2[teststep,3]*random.gauss(1.,0.1)))
                    #gp("sge="+str(he_data[int(v_int),step,5]))#*random.gauss(1.,0.01)))
                    #gp("sge=0.101537731920431")
                    gp("sge=0.1")
                    gp("ev=0.")
                    gp("tv=0.")

                # einige besonderheiten beim helium peak
                gp("ge0(x)=Ge0*exp(-(x-xge0)**2/(2*(sge0*(xge0-"+str(de)+"))**2))")
                gp("xkt0="+str(he_data[int(v_int),step,3]))#+random.gauss(0.,0.26)))
                gp("xge0="+str(he_data[int(v_int),step,2]))#+random.gauss(0.,0.39)))
                gp("sge0="+str(he_data[int(v_int),step,5]))#*random.gauss(1.,0.05)))
                gp("Ge0="+str(he_data[int(v_int),step,4]))

                ss=""
                fp=""
                for ii in range(1,len(ions)-1):
                    ss+="s"+str(ii)+"(x,y)+"
                    fp+="Ge"+str(ii)+","
                ss+="s"+str(len(ions)-1)+"(x,y)"
                gp("s(x,y)="+ss)
                fp+="Ge"+str(len(ions)-1)
                gp("ev=0.01")
                gp("tv=-0.01")
                for i in range(3):
                    gp("set zrange[5:*]")
                    gp("set xrange["+str(tp[3,1]-5)+":"+str(tp[3,1]+15)+"]")
                    gp("set yrange["+str(int(tp[3,0]-8))+":"+str(int(tp[3,0]+4))+"]")
                    gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_o_cme' u 1:2:3:4 via Ge1,Ge2,Ge3,sge")
                    #gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/all_data/step_files/all/step_"+str(step)+"_o_cme' u 1:2:3:4 via Ge1,Ge2,Ge3,sge")
                    gp("set yrange["+str(int(tp[3,0]-8))+":"+str(tp[3,0]+60)+"]")
                    gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_o_cme' u 1:2:3:4 via "+fp)
                    #gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/all_data/step_files/all/step_"+str(step)+"_o_cme' u 1:2:3:4 via "+fp)

                gp("set isosamples 50")
                gp("splot s(x,y), '/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_o_cme' u 1:2:3:4 with errorbars")
                #gp("splot s(x,y), '/data/wimmer/mu/jahresdaten/all_data/step_files/all/step_"+str(step)+"_o_cme' u 1:2:3:4 with errorbars")
                for i in range(len(ions)):
                    res[i,0]=float(str(gp.eval("xge"+str(i))))
                    res[i,1]=float(str(gp.eval("xkt"+str(i))))
                    res[i,2]=float(str(gp.eval("Ge"+str(i))))
                    res[i,3]=float(str(gp.eval("sge")))
                    res[i,4]=float(str(gp.eval("sktl")))
                    res[i,5]=float(str(gp.eval("sktr")))

                if (res[3,2] > 0):
                    c12[ll]+=res[3,2]
                    c12_step[step]+=res[3,2]
                dummy1[kk,pp,ll]=res[3,2]
                if (res[4,2] > 0):
                    c13[ll]+=res[4,2]
                    c13_step[step]+=res[4,2]
                dummy2[kk,pp,ll]=res[4,2]
                
                file0=open("results_final/"+str(v_int)+"_error","a")
                #file0=open("results/"+str(v_int)+"_c_vdf","a")
                file0.write(str(step))
                file0.write("   ")
                file0.write(str(rn+1))
                file0.write("   ")
                file0.write(str(res[3,2]))
                file0.write("   ")
                file0.write(str(res[4,2]))
                file0.write("   ")
                file0.write(str(steptov(step,12.,6.)))
                file0.write("   ")
                file0.write(str(steptov(step,13.,6.)))
                file0.write("\n")
                file0.close()
                pp+=1
                
        kk+=1
    ll+=1

