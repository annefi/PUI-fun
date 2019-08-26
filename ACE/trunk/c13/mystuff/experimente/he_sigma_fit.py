 
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
import random


Float=float
matrixmultiply=dot
gp=Gnuplot()


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
epos=zeros([400],Float)
tpos=zeros([400],Float)
epos_sum=zeros([58],Float)
tpos_sum=zeros([58],Float)
epos_counter=zeros([58],Float)
tpos_counter=zeros([58],Float)
epos_ave=zeros([58],Float)
tpos_ave=zeros([58],Float)

def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q

file0=open("steps")
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
v2_int_array=range(340+interval,800,interval*2)
slinks=0.
srechts=0.
ll=0
sum=0.
system("rm hsf3")
for v_int in v2_int_array:
    epq=f(4,v_int,2)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
    file1=open("hsf3","a")
    for step in range(epqstep-4,epqstep+5):
        if(1==1):
            if (1==1):
                # Energie + ToF Gauss - alle gleiches sge und sgt, nämlich sge3 und sgt3, sge(i)=xge(i)*sge3
                #gp("ge3(x)=Ge3*exp(-(x-xge3)**2/(2*(sge3*(xge3-0.682817))**2))") # fit an alle, benutzt bis februar 2009
                gp("ge3(x)=Ge3*exp(-(x-xge3)**2/(2*(sge3*(xge3-0.448))**2))") # neuer fit februar 2009

                # tof kappa funktion mit variablem kappa für jeden energiekanal
                #gp("ktl3(x,y)=(1+((x-xkt3)**2/((max1((ksl1*(y-xge3))+ksl2))*(sktl3*(xkt3-5.80315))**2)))**-(max1((ksl1*(y-xge3))+ksl2))") # fit an alle, benutzt bis februar 2009
                #gp("ktr3(x,y)=(1+((x-xkt3)**2/((max1((ksr1*(y-xge3))+ksr2))*(sktr3*(xkt3-5.80315))**2)))**-(max1((ksr1*(y-xge3))+ksr2))") # fit an alle, benutzt bis februar 2009
                gp("ktl3(x,y)=(1+((x-xkt3)**2/((max1((ksl1*(y-xge3))+ksl2))*(sktl3*(xkt3-6.41))**2)))**-(max1((ksl1*(y-xge3))+ksl2))") # neuer fit, s.o.
                gp("ktr3(x,y)=(1+((x-xkt3)**2/((max1((ksr1*(y-xge3))+ksr2))*(sktr3*(xkt3-6.41))**2)))**-(max1((ksr1*(y-xge3))+ksr2))") # neuer fit, s.o.
                # zusammensetzen der kappa funktion
                gp("kt3(x,y)=x<xkt3? Kt3*ktl3(x,y):Kt3*ktr3(x,y)")

                # zusammensetzen der 3d funktion
                gp("s3(x,y)=ge3(x)*kt3(y,x)")

                # setzen der variablen
                gp("Ge3=500000")
                gp("Gt3=1")
                gp("Kt3=1")
                gp("kappatl3=1000000.")
                gp("ksr1=0.8")
                gp("ksr2=2.8")
                gp("ksl1=0.0")
                gp("ksl2=10000")
                #gp("ksr1=0.527")
                #gp("ksr2=2.023")
                gp("xkt3="+str(tp[step,0]))#*random.gauss(1.,0.001)))
                gp("sktl3="+str(0.018))#*random.gauss(1.,0.05)))
                gp("sktr3="+str(0.01736))#*random.gauss(1.,0.05)))
                gp("sgt3=0.01")
                gp("xge3="+str(tp[step,1]))#*random.gauss(1.,0.005)))
                gp("sge3="+str(0.088))#*random.gauss(1.,0.1)))

            gp("s(x,y)=s3(x,y)")#+s2(x,y)+s3(x,y)+s4(x,y)+s5(x,y)+s6(x,y)+s7(x,y)+s8(x,y)+s9(x,y)+s10(x,y)+s11(x,y)+s12(x,y)+s13(x,y)")
            gp("set xrange[8:13]")
            for i in range(10):
                #gp("set yrange["+str(tp[step,0])+"-3*sktl3*(xkt3-5.80315):"+str(tp[step,0])+"+3*sktl3*(xkt3-5.80315)]")
                #gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_he/step_"+str(step)+"_we' u 1:2:3:4 via Ge3")
                #gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_he/step_"+str(step)+"_we' u 1:2:3:4 via Ge3,xkt3,xge3,sktr3,sktl3,sge3,ksr2,ksr1,ksl2")
                #gp("set yrange["+str(tp[step,0])+"-3*sktl3*(xkt3-5.80315):"+str(tp[step,0])+"+3*sktl3*(xkt3-5.80315)]") # fit an alle, benutzt bis februar 2009
                gp("set yrange["+str(tp[step,0])+"-3*sktl3*(xkt3-6.41):"+str(tp[step,0])+"+3*sktl3*(xkt3-6.41)]") # neuer fit, s.o.
                gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_we' u 1:2:3:4 via Ge3")
                gp("fit s(x,y) '/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_we' u 1:2:3:4 via Ge3,xkt3,xge3,sktr3,sktl3,sge3,ksr2,ksr1")

            gp("set isosamples 50")
            #gp("set yrange[140:200]")
            gp("splot s(x,y), '/data/wimmer/mu/jahresdaten/all_data/step_files/"+str(v_int)+"_"+str(interval)+"_he/step_"+str(step)+"_we' u 1:2:3:4 with errorbars")
            res[0]=float(str(gp.eval("xge3")))
            res[1]=float(str(gp.eval("xkt3")))
            res[2]=float(str(gp.eval("Ge3")))
            res[3]=float(str(gp.eval("sge3")))
            res[4]=float(str(gp.eval("sktl3")))
            res[5]=float(str(gp.eval("sktr3")))
            res[6]=float(str(gp.eval("ksr1")))
            res[7]=float(str(gp.eval("ksr2")))
            res[8]=float(str(gp.eval("ksl1")))
            res[9]=float(str(gp.eval("ksl2")))
            epos[ll]=float(str(gp.eval("xge3")))
            tpos[ll]=float(str(gp.eval("xkt3")))
            sktl3[ll]=res[4]
            sktr3[ll]=res[5]
            sge3[ll]=res[3]
            ksr1[ll]=res[6]
            ksr2[ll]=res[7]
            ksl1[ll]=res[8]
            ksl2[ll]=res[9]
            if ((ksr1[ll] > 0.0) and (ksr1[ll] < 1.0)):
                ksr1_sum[step]+=ksr1[ll]*res[2]
                ksr1_counter[step]+=res[2]
                ksr1_ave[step]=ksr1_sum[step]/ksr1_counter[step]
            if ((ksr2[ll] > 0.0) and (ksr1[ll] < 5.0)):
                ksr2_sum[step]+=ksr2[ll]*res[2]
                ksr2_counter[step]+=res[2]
                ksr2_ave[step]=ksr2_sum[step]/ksr2_counter[step]
            if ((ksl1[ll] > -2.0) and (ksl1[ll] < 1.0)):
                ksl1_sum[step]+=ksl1[ll]*res[2]
                ksl1_counter[step]+=res[2]
                ksl1_ave[step]=ksl1_sum[step]/ksl1_counter[step]
            if ((ksr2[ll] > 0.0) and (ksr1[ll] < 12.0)):
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
                
            ll+=1
            slinks+=res[4]*res[2]
            sum+=res[2]
            srechts+=res[5]*res[2]
            file1.write(str(v_int))
            file1.write("   ")
            file1.write(str(step))
            file1.write("   ")
            for i in range(10):
                file1.write(str(res[i]))
                file1.write("   ")
            file1.write("\n")
    file1.close()

file2=open("hsf4","w")
for i in range(58):
    file2.write(str(i))
    file2.write("   ")
    file2.write(str(epos_ave[i]))
    file2.write("   ")
    file2.write(str(tpos_ave[i]))
    file2.write("   ")
    file2.write(str(sge3_ave[i]))
    file2.write("   ")
    file2.write(str(sktl3_ave[i]))
    file2.write("   ")
    file2.write(str(sktr3_ave[i]))
    file2.write("   ")
    file2.write(str(ksr1_ave[i]))
    file2.write("   ")
    file2.write(str(ksr2_ave[i]))
    file2.write("   ")
    file2.write(str(ksl1_ave[i]))
    file2.write("   ")
    file2.write(str(ksl2_ave[i]))
    file2.write("\n")
    
file2.close()

slinks=slinks/sum
srechts=srechts/sum
sumlinks=0.
sumrechts=0.
for i in range(ll):
    sumlinks=(sktl3[i]-slinks)**2
    sumrechts=(sktr3[i]-srechts)**2
errorlinks=(sumlinks/(ll-1))**0.5
errorrechts=(sumrechts/(ll-1))**0.5
print slinks, errorlinks/slinks
print srechts, errorrechts/srechts
