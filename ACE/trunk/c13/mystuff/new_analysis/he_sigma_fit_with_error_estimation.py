 
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

#de=0.682817 # bis februar 09
#dt=5.80315 # bis februar 09
de=0.448 # neuer fit, februar 09
dt=6.41 # neuer fit, februar 09
de=0.448055 # wie vorher nur genauer
dt=6.41082818114 # wie vorher nur genauer
#de=0.451238 # paps=23.8, thick=2.3
#dt=6.48819922535 # paps=23.8, thick=2.3
de=1.448055 # wie vorher nur genauer
dt=7.41082818114 # wie vorher nur genauer
#de=1.451238 # paps=23.8, thick=2.3
#dt=7.48819922535 # paps=23.8, thick=2.3
ions=["he2"]

tp=zeros([58,2],Float)
he_pos=zeros([58,2],Float)
res=zeros([10],Float)
ksr1=zeros([400],Float)
ksr2=zeros([400],Float)
ksr1_sum=zeros([58],Float)
ksr2_sum=zeros([58],Float)
ksr1_counter=zeros([58],Float)
ksr2_counter=zeros([58],Float)
ksr1_ave=zeros([58],Float)
ksr2_ave=zeros([58],Float)
ksl1=zeros([400],Float)
ksl2=zeros([400],Float)
ksl1_sum=zeros([58],Float)
ksl2_sum=zeros([58],Float)
ksl1_counter=zeros([58],Float)
ksl2_counter=zeros([58],Float)
ksl1_ave=zeros([58],Float)
ksl2_ave=zeros([58],Float)
sktl3=zeros([400],Float)
sktr3=zeros([400],Float)
sktl3_sum=zeros([58],Float)
sktr3_sum=zeros([58],Float)
sktl3_counter=zeros([58],Float)
sktr3_counter=zeros([58],Float)
sktl3_ave=zeros([58],Float)
sktr3_ave=zeros([58],Float)
sge3=zeros([400],Float)
sge3_sum=zeros([58],Float)
sge3_counter=zeros([58],Float)
sge3_ave=zeros([58],Float)
epq_array=zeros([58],Float)
epos=zeros([1000],Float)
tpos=zeros([1000],Float)
epos_sum=zeros([58],Float)
tpos_sum=zeros([58],Float)
epos_counter=zeros([58],Float)
tpos_counter=zeros([58],Float)
epos_ave=zeros([58],Float)
tpos_ave=zeros([58],Float)
data=zeros([128,512,2],Float)

def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q

file0=open("../experiments/steps")
for i in file0:
    x=i.split()
    for k in range(58):
        epq_array[k]=float(x[k])
file0.close()

gp("max1(x)=x>0.5? x:0.5")

# Theoretische Positionen aus dem Eff-Modell
l=0
filex=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/002/He2+_eff")
for i in filex:
    xx=i.split()
    for j in range(1,3):
        he_pos[l,j-1]=float(xx[j])+1
    l+=1
filex.close()
for i in range(l):
    tp[i,0]=he_pos[i,1]
    tp[i,1]=he_pos[i,0]

v_int_array=range(345,850,10)
interval=int(20)
v2_int_array=range(340+interval,850,interval*2)
sum=0.
years=["2001","2002","2003","2004","2005","2006","2007"]

for year in years:
    system("rm hsf_results/linear/all_"+year+"/hsf")

for year in years:
    file0=open("hsf_results/linear/all_"+year+"/hsf","a")
    ll=0
    for step in range(58):
        if(1==1):
            if (1==1):
                # Energie + ToF Gauss - alle gleiches sge und sgt, nämlich sge3 und sgt3, sge(i)=xge(i)*sge3
                gp("ge3(x)=Ge3*exp(-(x-xge3)**2/(2*(sge3*(xge3-"+str(de)+"))**2))")
                gp("ktl3(x,y)=(1+((x-xkt3)**2/((max1((ksl1*(y-xge3))+ksl2))*(sktl3*(xkt3-"+str(dt)+"))**2)))**-(max1((ksl1*(y-xge3))+ksl2))")
                gp("ktr3(x,y)=(1+((x-xkt3)**2/((max1((ksr1*(y-xge3))+ksr2))*(sktr3*(xkt3-"+str(dt)+"))**2)))**-(max1((ksr1*(y-xge3))+ksr2))")

                # zusammensetzen der kappa funktion
                gp("kt3(x,y)=x<xkt3? Kt3*ktl3(x,y):Kt3*ktr3(x,y)")

                # zusammensetzen der 3d funktion
                gp("s3(x,y)=ge3(x)*kt3(y,x)")

                # setzen der variablen
                gp("Ge3=500000")
                gp("Gt3=1")
                gp("Kt3=1")
                gp("kappatl3=1000000.")
                gp("ksr1=1.0")
                gp("ksr2=2.8")
                gp("ksl1=0.0")
                gp("ksl2=10")
                gp("xkt3="+str(tp[step,0]))#*random.gauss(1.,0.001)))
                gp("sktl3="+str(0.018))#*random.gauss(1.,0.05)))
                gp("sktr3="+str(0.01736))#*random.gauss(1.,0.05)))
                gp("sgt3=0.01")
                gp("xge3="+str(tp[step,1]))#*random.gauss(1.,0.005)))
                gp("sge3="+str(0.088))#*random.gauss(1.,0.1)))

            gp("s(x,y)=s3(x,y)")
            gp("set zrange[10:*]")
            for i in range(10):
                gp("set xrange[8:xge3+4]")
                gp("set yrange[xkt3-3*sktl3*(xkt3-"+str(dt)+"):xkt3+3*sktr3*(xkt3-"+str(dt)+")]") # neuer fit, s.o.
                gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/all/step_"+str(step)+"_o_cme' u 1:2:3:4 via Ge3")
                gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/all/step_"+str(step)+"_o_cme' u 1:2:3:4 via Ge3,xkt3,xge3,sktr3,sktl3,sge3,ksr1,ksr2,ksl2")
            file3=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/all/step_"+str(step)+"_o_cme")
            l=0
            k=0
            for i in file3:
                x=i.split()
                if (len(x) > 0):
                    data[k,l,0]=float(x[2])
                    data[k,l,1]=float(x[3])
                    l+=1
                if (l == 512):
                    l=0
                    k+=1
            file3.close()
            gp("tl=xkt3-3*sktl3*(xkt3-"+str(dt)+")")
            gp("th=xkt3+3*sktr3*(xkt3-"+str(dt)+")")
            gp("el=8")
            gp("eh=xge3+4")
            tl=float(str(gp.eval("tl")))
            th=float(str(gp.eval("th")))
            el=float(str(gp.eval("el")))
            eh=float(str(gp.eval("eh")))
            xs=0.
            for i in range(1,129):
                for j in range(1,513):
                    if (data[i-1,j-1,0] >= 10.):
                        if ((float(i)>=el) and (float(i)<=eh)):
                            if ((float(j)>=tl) and (float(j)<=th)):
                                gp("ss=s("+str(float(i))+","+str(float(j))+")")
                                ss=float(str(gp.eval("ss")))
                                xs+=((ss-data[i-1,j-1,0])/data[i-1,j-1,1])**2.
                                #print i,j,ss,data[i-1,j-1,0],data[i-1,j-1,1]
            print xs
            gp("set isosamples 50")
            #gp("set yrange[140:200]")
            gp("splot s(x,y), '/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/all/step_"+str(step)+"_o_cme' u 1:2:3:4 with errorbars")

            res[0]=float(str(gp.eval("xge3")))
            res[1]=float(str(gp.eval("xkt3")))
            res[2]=float(str(gp.eval("Ge3")))
            res[3]=float(str(gp.eval("sge3")))
            res[4]=float(str(gp.eval("sktl3")))
            res[5]=float(str(gp.eval("sktr3")))
            res[6]=float(str(gp.eval("ksl1")))
            res[7]=float(str(gp.eval("ksl2")))
            res[8]=float(str(gp.eval("ksr1")))
            res[9]=float(str(gp.eval("ksr2")))
            epos[ll]=float(str(gp.eval("xge3")))
            tpos[ll]=float(str(gp.eval("xkt3")))
            sktl3[ll]=res[4]
            sktr3[ll]=res[5]
            sge3[ll]=res[3]
            ksl1[ll]=res[6]
            ksl2[ll]=res[7]
            ksr1[ll]=res[8]
            ksr2[ll]=res[9]
            if ((ksr1[ll] > 0.0) and (ksr1[ll] < 10.0)):
                ksr1_sum[step]+=ksr1[ll]*res[2]
                ksr1_counter[step]+=res[2]
                ksr1_ave[step]=ksr1_sum[step]/ksr1_counter[step]
            if ((ksr2[ll] > 0.0) and (ksr1[ll] < 10.0)):
                ksr2_sum[step]+=ksr2[ll]*res[2]
                ksr2_counter[step]+=res[2]
                ksr2_ave[step]=ksr2_sum[step]/ksr2_counter[step]
            if ((ksl1[ll] > -2.0) and (ksl1[ll] < 10.0)):
                ksl1_sum[step]+=ksl1[ll]*res[2]
                ksl1_counter[step]+=res[2]
                ksl1_ave[step]=ksl1_sum[step]/ksl1_counter[step]
            if ((ksl2[ll] > 0.0) and (ksl1[ll] < 12.0)):
                ksl2_sum[step]+=ksl2[ll]*res[2]
                ksl2_counter[step]+=res[2]
                ksl2_ave[step]=ksl2_sum[step]/ksl2_counter[step]
            if ((sktl3[ll] > 0.01) and (sktl3[ll] < 0.05)):
                sktl3_sum[step]+=sktl3[ll]*res[2]
                sktl3_counter[step]+=res[2]
                sktl3_ave[step]=sktl3_sum[step]/sktl3_counter[step]
            if ((sktr3[ll] > 0.01) and (sktr3[ll] < 0.05)):
                sktr3_sum[step]+=sktr3[ll]*res[2]
                sktr3_counter[step]+=res[2]
                sktr3_ave[step]=sktr3_sum[step]/sktr3_counter[step]
            if ((sge3[ll] > 0.05) and (sge3[ll] < 0.5)):
                sge3_sum[step]+=sge3[ll]*res[2]
                sge3_counter[step]+=res[2]
                sge3_ave[step]=sge3_sum[step]/sge3_counter[step]
            if ((epos[ll] > tp[step,1]-2) and (epos[ll] < tp[step,1]+2)):
                epos_sum[step]+=epos[ll]*res[2]
                epos_counter[step]+=res[2]
                epos_ave[step]=epos_sum[step]/epos_counter[step]
            if ((tpos[ll] > tp[step,0]-4) and (tpos[ll] < tp[step,0]+4)):
                tpos_sum[step]+=tpos[ll]*res[2]
                tpos_counter[step]+=res[2]
                tpos_ave[step]=tpos_sum[step]/tpos_counter[step]
            #file0.write("#step   T-Pos   E-Pos   sge    sktl    sktr     ksl1    ksl2    ksr1   ksr2")
            file0.write("\n")
            file0.write(str(step))
            file0.write("   ")
            file0.write(str(epos[ll]))
            file0.write("   ")
            file0.write(str(tpos[ll]))
            file0.write("   ")
            file0.write(str(sge3[ll]))
            file0.write("   ")
            file0.write(str(sktl3[ll]))
            file0.write("   ")
            file0.write(str(sktr3[ll]))
            file0.write("   ")
            file0.write(str(ksl1[ll]))
            file0.write("   ")
            file0.write(str(ksl2[ll]))
            file0.write("   ")
            file0.write(str(ksr1[ll]))
            file0.write("   ")
            file0.write(str(ksr2[ll]))
            file0.write("\n")
            ll+=1
    file0.close()


