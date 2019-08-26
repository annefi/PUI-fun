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
from functions import *
from libacepy.frange import frange


Float=float
matrixmultiply=dot
gp=Gnuplot()

c=zeros([101],Float)
t_data=zeros([512,3],Float)
e_data=zeros([128,3],Float)
ions=["mg12","o8","n7","c12","mg11","c13","o7","n6","mg10","c5","ne8","mg9","o6","n5","c4"]
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
tp_all=zeros([len(ions),58,2],Float)
cr=zeros([len(ions)],Float)
res=zeros([58,6,6,15],Float)



# count rates von Lars

cr[1]=500. # O8 # geschätzt
cr[2]=2546.91 # N7
cr[3]=8186. # C12
cr[4]=0. # Mg11 # geschätzt
cr[5]=100. # C13 geschätzt
cr[6]=11054.63 # O7
cr[7]=9591.11 # N6
cr[8]=500. # Mg10 # geschätzt
cr[9]=6940.99 # C5
cr[10]=4254.4 # Ne8
cr[11]=500. # Mg9
cr[12]=2858.22 # O6
cr[13]=1029.88 # N5
cr[14]=500. # C4 # gesschätzt

gp("max1(x)=x>1? x:1")

# Theoretische Positionen aus dem Eff-Modell
for j in range(len(ions)):
    file0=open("ion_pos/"+ions[j])
    l=0
    for i in file0:
        xx=i.split()
        for k in range(2):
            tp_all[j,l,k]=float(xx[k])
        l+=1
    file0.close()

for step in range(47,48):
    for i in range(len(ions)):
        for j in range(2):
            tp[i,j]=tp_all[i,step,j]
    rr=0
    for sr in [2.98]:
        ll=0
        for sl in [3.05]:
            for i in range(len(ions)):
                # Energie + ToF Gauss - unterschiedliche sge(i)
                #gp("ge"+str(i)+"(x)=Ge"+str(i)+"*exp(-(x-xge"+str(i)+")**2/(2*sge"+str(i)+"**2))")
                #gp("gt"+str(i)+"(x)=Gt"+str(i)+"*exp(-(x-xgt"+str(i)+")**2/(2*sgt"+str(i)+"**2))")
                
                # Energie + ToF Gauss - alle gleiches sge und sgt, nämlich sge3 und sgt3, sge(i)=xge(i)*sge3
                gp("ge"+str(i)+"(x)=Ge"+str(i)+"*exp(-(x-xge"+str(i)+")**2/(2*(sge3*xge"+str(i)+")**2))")
                #gp("gt"+str(i)+"(x)=Gt"+str(i)+"*exp(-(x-xgt"+str(i)+")**2/(2*(sgt3*xgt"+str(i)+")**2))")
                
                # ToF kappa, links kappatl(i) + sktl(i), rechts kapptr(i) + sktr(i)
                #gp("ktl"+str(i)+"(x)=(1+((x-xkt"+str(i)+")**2/(kappatl"+str(i)+"*sktl"+str(i)+"**2)))**-(kappatl"+str(i)+")")
                #gp("ktr"+str(i)+"(x)=(1+((x-xkt"+str(i)+")**2/(kappatr"+str(i)+"*sktr"+str(i)+"**2)))**-(kappatr"+str(i)+")")
                
                # ToF kappa, kappa für alle gleich, sktl(i)=sktl3*xkt(i), d.h. sigma proportional zum tof kanal
                # links kappatl3 + sktl3*xkt(i), rechts kapptr3 + sktr3*xkt(i)
                #gp("ktl"+str(i)+"(x)=(1+((x-xkt"+str(i)+")**2/(kappatl3*(sktl3*xkt"+str(i)+")**2)))**-(kappatl3)")
                #gp("ktr"+str(i)+"(x)=(1+((x-xkt"+str(i)+")**2/(kappatr3*(sktr3*xkt"+str(i)+")**2)))**-(kappatr3)")
                
                # tof kappa funktion mit variablem kappa für jeden energiekanal
                gp("ktl"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/((max1((-0.531*9.163/xge"+str(i)+"*(y-xge"+str(i)+"))+7.02))*sktl"+str(3)+"**2)))**-(max1((-0.531*9.163/xge"+str(i)+"*(y-xge"+str(i)+"))+7.02))")
                gp("ktr"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/((max1((0.621*9.163/xge"+str(i)+"*(y-xge"+str(i)+"))+2.28))*sktr"+str(3)+"**2)))**-(max1((0.621*9.163/xge"+str(i)+"*(y-xge"+str(i)+"))+2.28))")
                
                # zusammensetzen der kappa funktion
                gp("kt"+str(i)+"(x,y)=x<xkt"+str(i)+"? Kt"+str(i)+"*ktl"+str(i)+"(x,y):Kt"+str(i)+"*ktr"+str(i)+"(x,y)")
                
                # zusammensetzen der 3d funktion
                #gp("s"+str(i)+"(x,y)=ge"+str(i)+"(x)*gt"+str(i)+"(y)")
                gp("s"+str(i)+"(x,y)=ge"+str(i)+"(x)*kt"+str(i)+"(y,x)")
                
                # setzen der variablen
                gp("Ge"+str(i)+"="+str(cr[i]))
                gp("Gt"+str(i)+"=1")
                gp("Kt"+str(i)+"=1")
                gp("kappatl"+str(i)+"=6.5")
                gp("kappatr"+str(i)+"=1.63")
                gp("xkt"+str(i)+"="+str(tp[i,0]))
                gp("sktl"+str(i)+"="+str(sl))
                gp("sktr"+str(i)+"="+str(sr))
                #gp("sktl"+str(i)+"=0.0188")
                #gp("sktr"+str(i)+"=0.0177")
                gp("xgt"+str(i)+"="+str(tp[i,0]))
                gp("sgt"+str(i)+"=0.01")
                gp("xge"+str(i)+"="+str(tp[i,1]))
                gp("sge"+str(i)+"=0.09")
                #gp("sge"+str(i)+"=1.0")
            #gp("set isosamples 50")
            #gp("set pm3d map")
            #gp("splot s7(x,y)")

            gp("s(x,y)=s1(x,y)+s2(x,y)+s3(x,y)+s4(x,y)+s5(x,y)+s6(x,y)+s7(x,y)+s8(x,y)+s9(x,y)+s10(x,y)+s11(x,y)+s12(x,y)+s13(x,y)")
            gp("set xrange[20:30]")
            for i in range(5):
                gp("set yrange[160:170]")
                gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via Ge1,Ge2,Ge3")
                gp("set yrange[175:200]")
                gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via Ge6,Ge7,Ge8,Ge9,Ge10,Ge11,Ge12,Ge13")
                gp("set yrange[160:200]")
                gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via Ge1,Ge2,Ge3,Ge5,Ge6, Ge7,Ge8,Ge9,Ge10,Ge11,Ge12,Ge13")


        
            gp("set isosamples 50")
            gp("set yrange[160:200]")
            gp("splot s(x,y), '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 with errorbars")
            res[step,rr,ll,0]=float(str(gp.eval("sktl3")))
            res[step,rr,ll,1]=float(str(gp.eval("sktr3")))
            for tt in range(1,14):
                res[step,rr,ll,tt+1]=float(str(gp.eval("Ge"+str(tt))))
            ll+=1
        rr+=1


#    file2=open("sl_scan_"+str(step),"w")
#    for rr in range(6):
#        for ll in range(6):
#            for i in range(15):
#                file2.write(str(res[step,rr,ll,i]))
#                file2.write("   ")
#            file2.write("\n")
#        file2.write("\n") 
#    file2.close()

"""
# Helium Fit

#gp("ge1(x)=E1*exp(-(x-xge)**2/(2*(sge1)**2))")
#gp("ge2(x)=E2*exp(-(x-xge)**2/(2*(sge2)**2))")
gp("ge1(x)=E1*exp(-(x-xge)**2/(2*(ef1*xge)**2))")
gp("ge2(x)=E2*exp(-(x-xge)**2/(2*(ef2*xge)**2))")
#gp("kt1(x)=(1+((x-xkt)**2/(kappat1*skt1**2)))**-(kappat1)")
#gp("kt2(x)=(1+((x-xkt)**2/(kappat2*skt2**2)))**-(kappat2)")
gp("kt1(x)=(1+((x-xkt)**2/(kappat1*(tf1*xkt)**2)))**-(kappat1)")
gp("kt2(x)=(1+((x-xkt)**2/(kappat2*(tf2*xkt)**2)))**-(kappat2)")
gp("kt(x)=x<xkt? Kt*kt1(x):Kt*kt2(x)")
gp("s(x,y)=ge1(x)*kt(y)")
gp("Kt=1")
gp("E1=800000")
gp("xge=9.35")
gp("sge1=2")
gp("ef1=0.1")
gp("ef2=0.1")
gp("xkt=167.38")
gp("kappat1=6.0")
gp("kappat2=1.95")
gp("skt1=3")
gp("skt2=3")
gp("tf1=0.02")
gp("tf2=0.02")
gp("set xrange[8:13]")
gp("set yrange[159:180]")
step=48
for i in range(5):
    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via E1")
#    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via sge1,skt1,skt2")
    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via ef1,tf1,tf2")
    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via E1,xge,xkt")
#    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via E1,xge,xkt,sge1,skt1,skt2")
    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via E1,xge,xkt,ef1,tf1,tf2")
    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 via E1,xge,xkt,ef1,tf1,tf2,kappat1,kappat2")

gp("set isosamples 50")
gp("splot s(x,y), '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/step_"+str(step)+"_we' u 1:2:3:4 with errorbars")

"""


"""

# step 47 (48)
step=47
for step in range(47,48):
    for i in range(9):
        tp[i]=tp_all[i,step]

    for i in range(9):
        gp("x"+str(i)+"="+str(tp[i]))
        gp("G"+str(i)+"=0.8*"+str(cr[i]))
        gp("bg"+str(i)+"=0.")
        gp("breite"+str(i)+"=2.")
        gp("kl"+str(i)+"=2.75")
        gp("kr"+str(i)+"=1.56")

    res_G=zeros([11,11,9],Float)
    sl[1]=1.75
    sr[1]=1.89
    for j in range(1):
        for k in range(1):
            for l in range(9):
                gp("sl"+str(l)+"="+str(sl[1]+j*0.03))
                gp("sr"+str(l)+"="+str(sr[1]+k*0.02))

            gp("set xrange[160:170]")
            #gp("fit kkbf1(x)'/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via x1,G1")

            x[1]=float(str(gp.eval("x1")))

            for i in range(2,8):
                gp("x"+str(i)+"="+str(tp[i]*x[1]/tp[1]))


            gp("set xrange[190:200]")
            #gp("fit kkbf7(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G7")

            gp("set xrange[150:200]")
            #gp("fit kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G1,G2,G3,G4,G5,G6,G7")

            gp("plot kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x), '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 with errorbars, kkbf0(x),kkbf1(x),kkbf2(x),kkbf3(x),kkbf4(x),kkbf5(x),kkbf6(x),kkbf7(x),kkbf8(x)" )

"""