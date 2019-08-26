 
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

c=zeros([101],Float)
t_data=zeros([512,3],Float)
e_data=zeros([128,3],Float)
ions=["he2","o8","n7","c12","mg11","c13","o7","n6","mg10","c5","ne8","mg9","o6","n5","c4"]
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
res=zeros([14,6],Float)
epq_array=zeros([58],Float)
he_data=zeros([800,58,12],Float)
he_data_2=zeros([58,10],Float)


def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q


file0=open("steps")
for i in file0:
    x=i.split()
    for k in range(58):
        epq_array[k]=float(x[k])
file0.close()

file0=open("res_he")
for i in file0:
    x=i.split()
    for j in range(12):
        he_data[int(x[0]),int(x[1]),j]=float(x[j])

file0=open("res_he_2")
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
cr[1]=500. # O8 # geschätzt
cr[2]=2546.91 # N7
cr[3]=8186. # C12
cr[4]=0. # Mg11 # geschätzt
cr[5]=211. # C13 geschätzt
cr[6]=11054.63 # O7
cr[7]=9591.11 # N6
cr[8]=500. # Mg10 # geschätzt
cr[9]=6940.99 # C5
cr[10]=4254.4 # Ne8
cr[11]=500. # Mg9
cr[12]=2858.22 # O6
cr[13]=1029.88 # N5
cr[14]=500. # C4 # gesschätzt

v_int=445

gp("max1(x)=x>0.5? x:0.5")

# Theoretische Positionen aus dem Eff-Modell
for j in range(len(ions)):
    file0=open("ion_pos/"+ions[j])
    l=0
    for i in file0:
        xx=i.split()
        for k in range(2):
            tp_all1[j,l,k]=float(xx[k])
        l+=1
    file0.close()


system("rm res_11")
v_int_array=range(345,650,10)
c12=zeros(len(v_int_array),Float)
c13=zeros(len(v_int_array),Float)
c13c12=zeros(len(v_int_array),Float)
dummy1=zeros([10,len(v_int_array)],Float)
dummy2=zeros([10,len(v_int_array)],Float)
epq=0.
ll=0
samples=100
c12_r=zeros([samples,len(v_int_array)],Float)
c13_r=zeros([samples,len(v_int_array)],Float)
c13c12_r=zeros([samples,len(v_int_array)],Float)
dummy1_r=zeros([samples,10,len(v_int_array)],Float)
dummy2_r=zeros([samples,10,len(v_int_array)],Float)
for v_int in v_int_array:
    epq=f(4,v_int,2)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
    kk=0
    for step in range(epqstep-3,epqstep+4):
        for i in range(len(ions)):
            for j in range(2):
                tp[i,j]=tp_all1[i,step,j]

        for rn in range(samples):
            if(1 == 1): 
                for i in range(len(ions)):
                    gp("ge"+str(i)+"(x)=Ge"+str(i)+"*exp(-(x-xge"+str(i)+")**2/(2*(sge*(xge"+str(i)+"-0.682817))**2))")
                    gp("ktl"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/((kappatl)*(sktl*(xkt"+str(i)+"-5.80315))**2)))**-(kappatl)")
                    #gp("ktr"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/(((max1((ksr1*("+str(he_data_2[step,1])+"-0.682817)/(xge"+str(i)+"-0.682817)*(y-xge"+str(i)+"))+ksr2))+ksr_error)*(sktr*(xkt"+str(i)+"-5.80315))**2)))**-((max1((ksr1*("+str(he_data_2[step,1])+"-0.682817)/(xge"+str(i)+"-0.682817)*(y-xge"+str(i)+"))+ksr2))+ksr_error)")
                    gp("ktr"+str(i)+"(x,y)=(1+((x-xkt"+str(i)+")**2/(((max1((ksr1*("+str(he_data[int(v_int),step,2])+"-0.682817)/(xge"+str(i)+"-0.682817)*(y-xge"+str(i)+"))+ksr2))+ksr_error)*(sktr*(xkt"+str(i)+"-5.80315))**2)))**-((max1((ksr1*("+str(he_data[int(v_int),step,2])+"-0.682817)/(xge"+str(i)+"-0.682817)*(y-xge"+str(i)+"))+ksr2))+ksr_error)")

                    # zusammensetzen der kappa funktion
                    gp("kt"+str(i)+"(x,y)=x<xkt"+str(i)+"? Kt"+str(i)+"*ktl"+str(i)+"(x,y):Kt"+str(i)+"*ktr"+str(i)+"(x,y)")

                    # zusammensetzen der 3d funktion
                    gp("s"+str(i)+"(x,y)=ge"+str(i)+"(x)*kt"+str(i)+"(y,x)")

                    # setzen der variablen
                    gp("Ge"+str(i)+"="+str(cr[i]))
                    gp("Kt"+str(i)+"=1")
                    #gp("kappatl="+str(he_data_2[step,9]))
                    gp("kappatl="+str(he_data[int(v_int),step,11]))
                    #gp("ksr1="+str(he_data_2[step,6]))
                    gp("ksr1="+str(he_data[int(v_int),step,8]))
                    #gp("ksr2="+str(he_data_2[step,7]))
                    gp("ksr2="+str(he_data[int(v_int),step,9]))
                    gp("ksr_error="+str(random.gauss(0.,0.05)))
                    gp("xkt"+str(i)+"="+str(tp[i,0]+random.gauss(0.,0.25)))
                    #gp("sktl="+str(he_data_2[step,4]))#*random.gauss(1.,0.01)))
                    gp("sktl="+str(he_data[int(v_int),step,6]*random.gauss(1.,0.02)))
                    #gp("sktr="+str(he_data_2[step,5]))#*random.gauss(1.,0.01)))
                    gp("sktr="+str(he_data[int(v_int),step,7]*random.gauss(1.,0.02)))
                    gp("xge"+str(i)+"="+str(tp[i,1]+random.gauss(0.,0.38)))
                    #gp("sge="+str(0.11))#*random.gauss(1.,0.1)))
                    gp("sge="+str(he_data[int(v_int),step,5]*random.gauss(1.,0.01)))

                # einige besonderheiten beim helium peak
                gp("ge0(x)=Ge0*exp(-(x-xge0)**2/(2*(sge0*(xge0-0.682817))**2))")
                gp("xkt0="+str(he_data[int(v_int),step,3]))#+random.gauss(0.,0.25)))
                gp("xge0="+str(he_data[int(v_int),step,2]))#+random.gauss(0.,0.38)))
                gp("sge0="+str(he_data[int(v_int),step,5]))#*random.gauss(1.,0.1)))
                gp("Ge0="+str(he_data[int(v_int),step,4]))
                #gp("xkt5="+str((tp[3,0]+tp[7,0])/2.))#+random.gauss(0.,0.25)))
                #gp("xge5="+str((tp[3,1]+tp[7,1])/2.))#+random.gauss(0.,0.38)))
                gp("s(x,y)=s0(x,y)+s1(x,y)+s2(x,y)+s3(x,y)+s4(x,y)+s5(x,y)+s6(x,y)+s7(x,y)+s8(x,y)+s9(x,y)+s10(x,y)+s11(x,y)+s12(x,y)+s13(x,y)")
                for i in range(3):
                    gp("set xrange[8:32]")
                    gp("set yrange["+str(int(tp[3,0]-10))+":"+str(int(tp[3,0]+2))+"]")
                    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/step_"+str(step)+"_we' u 1:2:3:4 via Ge1,Ge2,Ge3")
                    gp("set yrange["+str(int(tp[5,0])+2)+":200]")
                    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/step_"+str(step)+"_we' u 1:2:3:4 via Ge6,Ge7,Ge8,Ge9,Ge10,Ge11,Ge12,Ge13")
                    gp("set yrange[150:200]")
                    gp("fit s(x,y) '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/step_"+str(step)+"_we' u 1:2:3:4 via Ge1,Ge2,Ge3,Ge5,Ge6,Ge7,Ge8,Ge9,Ge10,Ge11,Ge12,Ge13")

                gp("set isosamples 50")
                gp("set xrange[20:32]")
                gp("set yrange[150:200]")
                
                gp("splot s(x,y), '/data/kleopatra/mu/jahresdaten/all_data/step_files/"+str(v_int)+"/step_"+str(step)+"_we' u 1:2:3:4 with errorbars")
                for i in range(14):
                    res[i,0]=float(str(gp.eval("xge"+str(i))))
                    res[i,1]=float(str(gp.eval("xkt"+str(i))))
                    res[i,2]=float(str(gp.eval("Ge"+str(i))))
                    res[i,3]=float(str(gp.eval("sge")))
                    res[i,4]=float(str(gp.eval("sktl")))
                    res[i,5]=float(str(gp.eval("sktr")))

                if (res[3,2] > 0):
                    c12[ll]+=res[3,2]
                    c12_r[rn,ll]+=res[3,2]
                    dummy1[kk,ll]+=res[3,2]
                    dummy1_r[rn,kk,ll]=res[3,2]
                if (res[5,2] > 0):
                    c13[ll]+=res[5,2]
                    c13_r[rn,ll]+=res[5,2]
                    dummy2[kk,ll]+=res[5,2]
                    dummy2_r[rn,kk,ll]=res[5,2]
        kk+=1
    c13c12[ll]=c13[ll]/c12[ll]
    file1=open("res_11","a")
    file1.write(str(v_int_array[ll]))
    file1.write("   ")
    file1.write(str(c12[ll]))
    file1.write("   ")
    file1.write(str(c13[ll]))
    file1.write("   ")
    file1.write(str(c13c12[ll]))
    file1.write("   ")
    for i in range(kk):
        file1.write(str(dummy1[i,ll]))
        file1.write("   ")
        file1.write(str(dummy2[i,ll]))
        file1.write("   ")
    file1.write("\n")
    for rn in range(samples):
        file1.write(str(v_int_array[ll]))
        file1.write("   ")
        file1.write(str(c12_r[rn,ll]))
        file1.write("   ")
        file1.write(str(c13_r[rn,ll]))
        file1.write("   ")
        file1.write(str(c13_r[rn,ll]/c12_r[rn,ll]))
        file1.write("   ")
        for i in range(kk):
            file1.write(str(dummy1_r[rn,i,ll]))
            file1.write("   ")
            file1.write(str(dummy2_r[rn,i,ll]))
            file1.write("   ")
        file1.write("\n")
    file1.close()
    ll+=1
