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
gp2=Gnuplot()
gp3=Gnuplot()
gp4=Gnuplot()

interval=int(20)
v_int_array=range(340+interval,500,interval*2)
pea=[44,42,39,35]
pee=[50,47,44,42]

data=zeros([len(v_int_array),8,1000,5],Float)
c12=zeros([len(v_int_array),8],Float)
c13=zeros([len(v_int_array),8],Float)
c12_all=zeros([len(v_int_array)],Float)
c13_all=zeros([len(v_int_array)],Float)
sum_c12=zeros([len(v_int_array),8],Float)
sum_c13=zeros([len(v_int_array),8],Float)
c12_error=zeros([len(v_int_array),8],Float)
c13_error=zeros([len(v_int_array),8],Float)
c12_all_error=zeros([len(v_int_array)],Float)
c13_all_error=zeros([len(v_int_array)],Float)
ratio=zeros([len(v_int_array)],Float)
epq_array=zeros([58],Float)

eff_c12=zeros([58,3],Float)
eff_c13=zeros([58,3],Float)

c12_step=zeros([58,2],Float)
c13_step=zeros([58,2],Float)

c12_hepsi=0.
c13_hepsi=0.
c12_hepsi_error=0.
c13_hepsi_error=0.


file0=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/ave_eff/C6+.eff")
l=0
for i in file0:
    x=i.split()
    for j in range(3):
        eff_c12[l,j]=float(x[j])
    l+=1
file0.close()

file0=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/ave_eff/13C6+.eff")
l=0
for i in file0:
    x=i.split()
    for j in range(3):
        eff_c13[l,j]=float(x[j])
    l+=1
file0.close()




def f(m,v,q):
    return (0.5*m/(6.0221415*10.**26.)*(v*1000.)**2)*(6.24150974*10.**15.)/q

def f2(m,q,epq):
    return (((epq*q/(6.24150974*10.**15.))*2./(m/(6.0221415*10.**26.)))**0.5)/1000.


file0=open("steps")
for i in file0:
    x=i.split()
    for k in range(58):
        epq_array[k]=float(x[k])
file0.close()




epq=0.
v=0
for v_int in v_int_array:
    k=0
    epq=f(12,v_int,6)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
    for step in range(epqstep-4,epqstep+4):
        file0=open(str(v_int)+"_"+str(step)+"_new_opf")
        l=0
        for i in file0:
            x=i.split()
            for j in range(5):
                data[v,k,l,j]=float(x[j])
            sum_c12[v,k]+=float(x[3])
            sum_c13[v,k]+=float(x[4])
            l+=1
        file0.close()
        k+=1
    v+=1


system("rm c13c12_ratios")
system("rm all_new_res")

epq=0.
v=0
for v_int in v_int_array:
    k=0
    epq=f(12,v_int,6)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
    for step in range(epqstep-4,epqstep+4):
        file0=open(str(v_int)+"_"+str(step)+"_new_opf")
        for i in file0:
            x=i.split()
            c12_error[v,k]+=((sum_c12[v,k]/1000.)-float(x[3]))**2
            c13_error[v,k]+=((sum_c13[v,k]/1000.)-float(x[4]))**2
        file0.close()
        k+=1
    v+=1

epq=0.
v=0
for v_int in v_int_array:
    k=0
    kk=0
    epq=f(12,v_int,6)
    print epq
    nepq=100.
    for i in range(58):
        if (nepq > (abs(epq-epq_array[i]))):
            nepq=abs(epq-epq_array[i])
            #print nepq
            epqstep=i
    print epqstep
    file1=open(str(v_int)+"_new_res","w")
    file2=open("all_new_res","a")
    for step in range(epqstep-4,epqstep+4):
        c12_error[v,k]=(c12_error[v,k]/999.)**0.5
        c13_error[v,k]=(c13_error[v,k]/999.)**0.5
        c12[v,k]=sum_c12[v,k]/1000.
        c13[v,k]=sum_c13[v,k]/1000.
        if (c13[v,k] > 0.):
            c12_all[v]+=c12[v,k]
            c13_all[v]+=c13[v,k]
            c12_all_error[v]+=(c12_error[v,k])**2
            c13_all_error[v]+=(c13_error[v,k])**2
            c12_step[step,0]+=c12[v,k]
            c13_step[step,0]+=c13[v,k]
            c12_step[step,1]+=(c12_error[v,k])**2
            c13_step[step,1]+=(c13_error[v,k])**2
            c12_hepsi+=c12[v,k]
            c13_hepsi+=c13[v,k]
            c12_hepsi_error+=(c12_error[v,k])**2
            c13_hepsi_error+=(c13_error[v,k])**2
        print v_int, step, (sum_c12[v,k]/1000.), (sum_c13[v,k]/1000.), c12_error[v,k], c13_error[v,k]
        file1.write(str(step+2))
        file1.write("   ")
        file1.write(str(c12[v,k]))
        file1.write("   ")
        file1.write(str(c13[v,k]))
        file1.write("   ")
        file1.write(str((((c12_error[v,k]/c12[v,k]+1.)**2.*(eff_c12[step,2]/eff_c12[step,1]+1.)**2.)**0.5-1.)*c12[v,k]))
        file1.write("   ")
        file1.write(str((((c13_error[v,k]/c13[v,k]+1.)**2.*(eff_c13[step,2]/eff_c13[step,1]+1.)**2.)**0.5-1.)*c13[v,k]))
        file1.write("   ")
        file1.write(str(f2(12,6,epq_array[step])))
        file1.write("   ")
        file1.write(str(f2(13,6,epq_array[step])))
        file1.write("\n")
        
        file2.write(str(step+2))
        file2.write("   ")
        file2.write(str(c12[v,k]))
        file2.write("   ")
        file2.write(str(c13[v,k]))
        file2.write("   ")
        file2.write(str(c12_error[v,k]))
        file2.write("   ")
        file2.write(str(c13_error[v,k]))
        file2.write("   ")
        file2.write(str(f2(12,6,epq_array[step])))
        file2.write("   ")
        file2.write(str(f2(13,6,epq_array[step])))
        file2.write("\n")

        k+=1
    file1.close()
    file2.close()
    
    gp("set xrange["+str(pea[v]+2)+"-0.5:"+str(pee[v]+2)+"+0.5]")
    gp("set yrange[1:100000]")
    gp("set logscale y")
    gp("set format y '10^{%L}'")
    gp("plot '"+str(v_int)+"_new_res' u 1:2:4 w e title '^{12}C^{6+}', '"+str(v_int)+"_new_res' u 1:3:5 w e title '^{13}C^{6+}'")
    gp("set term postscript enhanced color 18")
    gp("set output '/home/kleopatra/mu/Desktop/doktorarbeit/pictures/c13c12_"+str(v_int)+".eps")
    gp("set xlabel 'E/q step'")
    gp("set ylabel 'Peak height [arbitrary units]'")
    gp("set xtics 1")
    gp("set mytics 10") 
    gp("replot")
    gp("set term X11")
    """
    gp2("set xrange["+str(pea[v]+2)+"-0.5:"+str(pee[v]+2)+"+0.5]")
    gp2("set yrange[0:0.025]")
    gp2("f(x)=c")
    gp2("c=0.1")
    gp2("fit f(x) '"+str(v_int)+"_new_res' u 1:($3/$2):(((1/$2*$5)**2+($3/$2**2*$4)**2)**0.5) via c")
    ratio[v]=float(str(gp2.eval("c")))
    gp2("plot '"+str(v_int)+"_new_res' u 1:($3/$2):(((1/$2*$5)**2+($3/$2**2*$4)**2)**0.5) w e title '^{13}C^{6+}/^{12}C^{6+}', f(x) title 'Average'")
    gp2("set term postscript enhanced color 18")
    gp2("set output '/home/kleopatra/mu/Desktop/doktorarbeit/pictures/c13c12_"+str(v_int)+"_ratio.eps")
    gp2("set xlabel 'E/q step'")
    gp2("set ylabel 'Isotopic ratio'")
    gp2("set xtics 1")
    gp2("set mytics 5") 
    gp2("replot")
    gp2("set term X11")
    """
    file3=open("c13c12_ratios","a")
    file3.write(str(v_int))
    file3.write("   ")
    file3.write(str(c12_all[v]))
    file3.write("   ")
    file3.write(str(c13_all[v]*1.04*(13./12.)**0.5*1.01))
    file3.write("   ")
    file3.write(str((c12_all_error[v])**0.5))
    file3.write("   ")
    file3.write(str((c13_all_error[v])**0.5))
    file3.write("\n")
    file3.close()
    
    gp3("set xrange[320:520]")
    gp3("set yrange[0:0.02]")
    gp3("set xtics 20")
    gp3("set ytics 0.002")
    gp3("set xlabel 'Solar wind speed [km/s]'")
    gp3("set ylabel 'Isotopic ratio'")

    gp3("plot 'c13c12_ratios'  u 1:($3/$2) with boxes title '^{13}C^{6+}/^{12}C^{6+}'")

    gp3("set term postscript enhanced color 18")
    gp3("set output '/home/kleopatra/mu/Desktop/doktorarbeit/pictures/c13c12_ratios.eps'")
    gp3("replot")
    gp3("set term X11")
    
    
    """
    gp4("fgr(x)=A*(erf((x-v0+v)/(s*2**0.5))-erf((x-v0-v)/(s*2**0.5)))")
    gp4("set autoscale")
    gp4("set xrange[360:440]")
    gp4("v=20")
    gp4("s=20")
    gp4("v0=360")
    gp4("A=10000")
    gp4("fit fgr(x) '400_new_res' u 6:2:4 via A,s,v0")
    gp4("plot fgr(x), '400_new_res' u 6:2:4 w e")
    gp4("fit fgr(x) '400_new_res' u 7:3:5 via A,s")
    gp4("plot fgr(x),'400_new_res' u 7:3:5 w e ")
    """
    v+=1


de=1.448055
dt=7.41082818114

tp_c12=zeros([58,2],Float)
tp_c13=zeros([58,2],Float)

file0=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/004/C6+_eff")
l=0
for i in file0:
    xx=i.split()
    tp_c12[l,0]=float(xx[2])+1
    tp_c12[l,1]=float(xx[1])+1
    l+=1
file0.close()

file0=open("/home/kleopatra/mu/Desktop/swics/efficiencies/lars/aspeff/004/13C6+_eff")
l=0
for i in file0:
    xx=i.split()
    tp_c13[l,0]=float(xx[2])+1
    tp_c13[l,1]=float(xx[1])+1
    l+=1
file0.close()


file4=open("all_asafo_step","w")
for i in range(35,51):
    file4.write(str(i))
    file4.write("   ")
    file4.write(str(c12_step[i,0]))
    file4.write("   ")
    c13_weighted=c13_step[i,0]*((13./12.)**0.5)*(eff_c12[i,1])/(eff_c13[i,1])*(tp_c13[i,0]-dt)/(tp_c12[i,0]-dt)*(tp_c13[i,1]-de)/(tp_c12[i,1]-de)
    file4.write(str(c13_weighted))
    file4.write("   ")
    file4.write(str(c12_step[i,1]**0.5))
    file4.write("   ")
    file4.write(str(c13_step[i,1]**0.5))
    file4.write("   ")
    file4.write(str(((((((((1./c12_step[i,0]*(c13_step[i,1]**0.5))**2.)+((c13_weighted/(c12_step[i,0])**2.*(c12_step[i,1]**0.5))**2.))**0.5)/(c13_weighted/c12_step[i,0]))+1.)**2.*((((eff_c12[i,2]/eff_c12[i,1])-(eff_c13[i,2]/eff_c13[i,1]))**2.)**0.5*eff_c12[i,1]/eff_c13[i,1]+1.)**2.)**0.5-1.)*(c13_weighted/c12_step[i,0])))
    file4.write("\n")
file4.close()

gp4("set autoscale")
gp4("set xrange[35:52]")
#gp4("set xtics 20")
#gp4("set ytics 0.002")
gp4("f(x)=c")
gp4("c=0.01")
gp4("fit f(x) 'all_asafo_step' u 1:($3/$2):6 via c")
gp4("set xlabel 'E/q step'")
gp4("set ylabel 'Isotopic ratio'")
gp4("plot 'all_asafo_step' u ($1+1):($3/$2):6 w e, f(x) lt -1   title '^{13}C^{6+}/^{12}C^{6+}'")
gp4("set term postscript enhanced color 18")
gp4("set output '/home/kleopatra/mu/Desktop/doktorarbeit/pictures/c13c12_ratios2.eps'")
gp4("replot")
gp4("set term X11")
    


sm=0.
for i in range(35,51):
    sm+=1./(((1./c12_step[i,0]*c13_step[i,1])**2.)+(c13_step[i,1]/c12_step[i,0]**2.*c12_step[i,1])**2.)
print 1/sm