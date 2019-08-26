
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

Float=float
matrixmultiply=dot
gp=Gnuplot()
c=zeros([101],Float)
t_data=zeros([512,3],Float)
e_data=zeros([128,3],Float)
x=zeros([9],Float)
G=zeros([9],Float)
sg=zeros([9],Float)
sk=zeros([9],Float)
sl=zeros([9],Float)
sr=zeros([9],Float)
kappa=zeros([9],Float)
breite=zeros([9],Float)
bg=zeros([9],Float)
tp=zeros([9],Float)
tp_all=zeros([9,58],Float)
cr=zeros([9],Float)

#modus=int(0) # gkbf
modus=int(1) # kkbf

# Faltung Gauss und Dreieck
#gd=ExternalFunction(gp, "gd", ["x1","G1","sg1","bg1","breite1"], conv_gd)

# Faltung Kappa und Dreieck
#kd=ExternalFunction(gp, "kd", ["x1","G1","sk1","kappa1","bg1","breite1"], conv_kd)

# Faltung Kappa und Gauss
#kg=ExternalFunction(gp, "kg", ["x1","G1","sk1","sg1","kappa1","bg1"], conv_kg)

# Faltung Dreieck und Rechteck
#dr=ExternalFunction(gp, "dr", ["x1","G1","l","r","breite1"], conv_dr)

# Faltung (links Gauss, rechts Kappa) und Gauss
#gkg=ExternalFunction(gp, "gkg", ["x1","G1","sg1","sk1","sg2","kappa1","bg1"], conv_gkg)

# Faltung (links Gauss, rechts Kappa) und Dreieck
#gkd=ExternalFunction(gp, "gkd", ["x1","G1","sg1","sk1","kappa1","bg1","breite1"], conv_gkd)

# Faltung (links Kappa1, rechts Kappa2) und Dreieck
#kkd=ExternalFunction(gp, "kkd", ["x1","G1","sk1","sk2","kappa1","kappa2","bg1","breite1"], conv_kkd)

# Faltung (links Gauss, rechts Kappa) und Bodmer Funktion
if (modus == 0):
    gkbf0=ExternalFunction(gp, "gkbf0", ["x0","G0","sg0","sk0","kappa0","bg0","breite0"], conv_gkbf)
    gkbf1=ExternalFunction(gp, "gkbf1", ["x1","G1","sg1","sk1","kappa1","bg1","breite1"], conv_gkbf)
    gkbf2=ExternalFunction(gp, "gkbf2", ["x2","G2","sg2","sk2","kappa2","bg2","breite2"], conv_gkbf)
    gkbf3=ExternalFunction(gp, "gkbf3", ["x3","G3","sg3","sk3","kappa3","bg3","breite3"], conv_gkbf)
    gkbf4=ExternalFunction(gp, "gkbf4", ["x4","G4","sg4","sk4","kappa4","bg4","breite4"], conv_gkbf)
    gkbf5=ExternalFunction(gp, "gkbf5", ["x5","G5","sg5","sk5","kappa5","bg5","breite6"], conv_gkbf)
    gkbf6=ExternalFunction(gp, "gkbf6", ["x6","G6","sg6","sk6","kappa6","bg6","breite6"], conv_gkbf)
    gkbf7=ExternalFunction(gp, "gkbf7", ["x7","G7","sg7","sk7","kappa7","bg7","breite7"], conv_gkbf)
    gkbf8=ExternalFunction(gp, "gkbf8", ["x8","G8","sg8","sk8","kappa8","bg8","breite8"], conv_gkbf)


# Faltung (links Kappa1, rechts Kappa2) und Bodmer Funktion
if (modus == 1):
    kkbfhe=ExternalFunction(gp, "kkbfhe", ["xhe","Ghe","slhe","srhe","klhe","krhe","bghe","breitehe"], conv_kkbf)
    kkbf0=ExternalFunction(gp, "kkbf0", ["x0","G0","sl0","sr0","kl0","kr0","bg0","breite0"], conv_kkbf)
    kkbf1=ExternalFunction(gp, "kkbf1", ["x1","G1","sl1","sr1","kl1","kr1","bg1","breite1"], conv_kkbf)
    kkbf2=ExternalFunction(gp, "kkbf2", ["x2","G2","sl1","sr1","kl1","kr2","bg2","breite2"], conv_kkbf)
    kkbf3=ExternalFunction(gp, "kkbf3", ["x3","G3","sl1","sr1","kl1","kr3","bg3","breite3"], conv_kkbf)
    kkbf4=ExternalFunction(gp, "kkbf4", ["x4","G4","sl1","sr1","kl1","kr4","bg4","breite4"], conv_kkbf)
    kkbf5=ExternalFunction(gp, "kkbf5", ["x5","G5","sl1","sr1","kl1","kr5","bg5","breite5"], conv_kkbf)
    kkbf6=ExternalFunction(gp, "kkbf6", ["x6","G6","sl1","sr1","kl1","kr6","bg6","breite6"], conv_kkbf)
    kkbf7=ExternalFunction(gp, "kkbf7", ["x7","G7","sl1","sr1","kl1","kr7","bg7","breite7"], conv_kkbf)
    kkbf8=ExternalFunction(gp, "kkbf8", ["x8","G8","sl1","sr1","kl1","kr8","bg8","breite8"], conv_kkbf)


# count rates von Lars
#cr[0]=2546.91 # N7
cr[0]=0. # N7
cr[1]=8186. # C12
cr[2]=100. # C13 geschätzt
cr[3]=11054.63 # O7
cr[4]=9591.11 # N6
cr[5]=6940.99 # C5
cr[6]=4254.4 # Ne8
cr[7]=2858.22 # O6
#cr[8]=1029.88 # N5
cr[8]=0. # N5

# Theoretische Positionen aus dem Eff-Modell
ions=["n7","c12","c13","o7","n6","c5","ne8","o6","n5"]
for j in range(len(ions)):
    file0=open("ion_pos/"+ions[j])
    l=0
    for i in file0:
        xx=i.split()
        tp_all[j,l]=float(xx[0])
        l+=1
    file0.close()

# step 47 (48)
step=47
for step in range(45,51):
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
    system("rm sl_sr_variation_"+str(step))
    sl[1]=1.75
    sr[1]=1.89
    for j in range(11):
        for k in range(11):
            for l in range(9):
                gp("sl"+str(l)+"="+str(sl[1]+j*0.03))
                gp("sr"+str(l)+"="+str(sr[1]+k*0.02))

            gp("set xrange[160:170]")
            gp("fit kkbf1(x)'/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via x1,G1")

            x[1]=float(str(gp.eval("x1")))

            for i in range(2,8):
                gp("x"+str(i)+"="+str(tp[i]*x[1]/tp[1]))


            gp("set xrange[190:200]")
            gp("fit kkbf7(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G7")

            gp("set xrange[150:200]")
            gp("fit kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G1,G2,G3,G4,G5,G6,G7")

            gp("plot kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x), '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 with errorbars, kkbf0(x),kkbf1(x),kkbf2(x),kkbf3(x),kkbf4(x),kkbf5(x),kkbf6(x),kkbf7(x),kkbf8(x)" )
            gp("set term postscript color")
            gp("set output 'plots/step"+str(step)+"_sl"+str(sl[1]+j*0.03)+"_sr"+str(sr[1]+k*0.02)+".ps'")
            gp("replot")
            gp("set term X11")
            for i in range(9):
                res_G[j,k,i]=float(str(gp.eval("G"+str(i))))
            file0=open("sl_sr_variation_"+str(step),"a")
            file0.write(str(sl[1]+j*0.03))
            file0.write("   ")
            file0.write(str(sr[1]+k*0.02))
            file0.write("   ")
            for i in range(9):
                file0.write(str(res_G[j,k,i]))
                file0.write("   ")
            file0.write("\n")
        file0.write("\n")
    file0.close()

"""
# Fit nur über die Höhen mit festem Rest
for i in range(9):
    gp("x"+str(i)+"="+str(tp[i]))
    gp("G"+str(i)+"=0.8*"+str(cr[i]))
    gp("bg"+str(i)+"=0.")
    gp("breite"+str(i)+"=2.")
    gp("sl"+str(i)+"=1.9")
    gp("sr"+str(i)+"=2.15")
    gp("kl"+str(i)+"=2.75")
    gp("kr"+str(i)+"=1.56")

gp("set xrange[160:170]")
gp("fit kkbf1(x)'/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via x1,G1")

x[1]=float(str(gp.eval("x1")))

for i in range(2,8):
    gp("x"+str(i)+"="+str(tp[i]*x[1]/tp[1]))


for i in range(9):
    gp("breite"+str(i)+"=breite1")
    gp("sl"+str(i)+"=sl1")
    gp("sr"+str(i)+"=sr1")
    gp("kl"+str(i)+"=kl1")
    gp("kr"+str(i)+"=kr1")

gp("set xrange[190:200]")
gp("fit kkbf7(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G7")

gp("set xrange[150:200]")
gp("fit kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G1,G2,G3,G4,G5,G6,G7")
gp("fit kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via sl1,sr1")
gp("fit kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 via G1,G2,G3,G4,G5,G6,G7")

gp("plot kkbf0(x)+kkbf1(x)+kkbf2(x)+kkbf3(x)+kkbf4(x)+kkbf5(x)+kkbf6(x)+kkbf7(x)+kkbf8(x), '/data/kleopatra/mu/jahresdaten/all_data/step_files/345/e_files/345_step_"+str(step)+"_e_20_25' u 1:2:3 with errorbars, kkbf0(x),kkbf1(x),kkbf2(x),kkbf3(x),kkbf4(x),kkbf5(x),kkbf6(x),kkbf7(x),kkbf8(x)" )
#for i in range(9):
#    x[i]=float(str(gp.eval("x"+str(i))))
#    G[i]=float(str(gp.eval("G"+str(i))))
#    sg[i]=float(str(gp.eval("sg"+str(i))))
#    sk[i]=float(str(gp.eval("sk"+str(i))))
#    kappa[i]=float(str(gp.eval("kappa"+str(i))))
#    bg[i]=float(str(gp.eval("bg"+str(i))))
#    breite[i]=float(str(gp.eval("breite"+str(i))))
"""
###########################################################


"""


# Helium Positionsfit

res=zeros([5,12,7],Float)
gp("x1=165.")
gp("G1=8000.")
gp("bg1=0.")
gp("breite1=2.")
gp("sl1=2.")
gp("sr1=2.")
gp("kl1=3.")
gp("kr1=2.1")
i=0
j=0
for v_int in [345,355,365,375,385]:
    for step in range(30,39):
        gp("set xrange[150:185]")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1,breite1,kl1,kr1,sl1,sr1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1,breite1,kl1,kr1,sl1,sr1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1,breite1,kl1,kr1,sl1,sr1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1")
        gp("fit kkbf1(x) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3 via G1,x1,breite1,kl1,kr1,sl1,sr1")
        gp("plot kkbf1(x), '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/e_files/"+str(v_int)+"_step_"+str(step)+"_e_6_13' u 1:2:3")
        res[i,j,0]=float(str(gp.eval("x1")))
        res[i,j,1]=float(str(gp.eval("G1")))
        res[i,j,2]=float(str(gp.eval("bg1")))
        res[i,j,3]=float(str(gp.eval("breite1")))
        res[i,j,4]=float(str(gp.eval("sl1")))
        res[i,j,5]=float(str(gp.eval("sr1")))
        res[i,j,6]=float(str(gp.eval("kl1")))
        res[i,j,6]=float(str(gp.eval("kr1")))
        j+=1
    i+=1
    j=0

file0=open("he_res_2","w")
file0.write("# v_int    step    pos     Höhe    bg      breite(bf)  sl  sr  kl  kr")
file0.write("\n")
i=0
j=0
for v_int in [345,355,365,375,385]:
    for step in range(30,39):
        file0.write(str(v_int))
        file0.write("   ")
        file0.write(str(step))
        file0.write("   ")
        for k in range(7):
            file0.write(str(res[i,j,k]))
            file0.write("   ")
        file0.write("\n")
        j+=1
    file0.write("\n")
    i+=1
    j=0
file0.close()
"""