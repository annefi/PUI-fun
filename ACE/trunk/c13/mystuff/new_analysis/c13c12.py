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

c12=zeros([len(v_int_array),58,1000],Float)
c13=zeros([len(v_int_array),58,1000],Float)
sum_c12=zeros([len(v_int_array),58],Float)
sum_c13=zeros([len(v_int_array),58],Float)
ave_c12=zeros([len(v_int_array),58],Float)
ave_c13=zeros([len(v_int_array),58],Float)
sqa_c12=zeros([len(v_int_array),58],Float)
sqa_c13=zeros([len(v_int_array),58],Float)
sigma_c12=zeros([len(v_int_array),58],Float)
sigma_c13=zeros([len(v_int_array),58],Float)
ave_c12_eff=zeros([len(v_int_array),58],Float)
ave_c13_eff=zeros([len(v_int_array),58],Float)
sigma_c12_eff=zeros([len(v_int_array),58],Float)
sigma_c13_eff=zeros([len(v_int_array),58],Float)

#arrays für die step- bzw. geschwindigkeitsintervallweise zusammenfassung
c12_step=zeros([58],Float)
c13_step=zeros([58],Float)
sqa_c12_step=zeros([58],Float)
sqa_c13_step=zeros([58],Float)
sigma_c12_step=zeros([58],Float)
sigma_c13_step=zeros([58],Float)
c12_v_int=zeros([len(v_int_array)],Float)
c13_v_int=zeros([len(v_int_array)],Float)
sqa_c12_v_int=zeros([len(v_int_array)],Float)
sqa_c13_v_int=zeros([len(v_int_array)],Float)
sigma_c12_v_int=zeros([len(v_int_array)],Float)
sigma_c13_v_int=zeros([len(v_int_array)],Float)

# der zusatz "_eff" bedeutet, dass die effizienzen mitberücksichtigt wurden. 
c12_step_eff=zeros([58],Float)
c13_step_eff=zeros([58],Float)
sqa_c12_step_eff=zeros([58],Float)
sqa_c13_step_eff=zeros([58],Float)
sigma_c12_step_eff=zeros([58],Float)
sigma_c13_step_eff=zeros([58],Float)
c12_v_int_eff=zeros([len(v_int_array)],Float)
c13_v_int_eff=zeros([len(v_int_array)],Float)
sqa_c12_v_int_eff=zeros([len(v_int_array)],Float)
sqa_c13_v_int_eff=zeros([len(v_int_array)],Float)
sigma_c12_v_int_eff=zeros([len(v_int_array)],Float)
sigma_c13_v_int_eff=zeros([len(v_int_array)],Float)

epq_array=zeros([58],Float)

eff_c12=zeros([58,3],Float)
eff_c13=zeros([58,3],Float)
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

#v=geschw.intervall (0=360+-20; 1=400+-20 usw.)
#s=step
#r= nummer des durchlaufs (insgesamt 1000 mal)
#sum_c12= summe der 1000 durchläufe
#sum_c13= analog sum_c12
#ave_c12= mittelwert der 1000 durchläufe
#ave_c13= analog ave_c12
#sqa_c12= summe der quadratischen abweichungen
#sqa_c13= analog sqa_c12
#sigma_c12= wurzel aus sqa_c12
#sigma_c13= analog sigma_c12
#ave_c12_eff= mittelwert der 1000 durchläufe mal effizienz
#ave_c13_eff= analog ave_c12_eff
#sigma_c12_eff= sigma_c12 mit berücksichtigung der effizienzenfehler
#sigma_c13_eff= analog sigma_c12_eff

v=0
for v_int in [360,400,440,480]:
    file0=open("results_final/"+str(v_int)+"_error")
    r=int(0)
    for i in file0:
        x=i.split()
        s=int(x[0])
        c12[v,s,r]=float(x[2])
        c13[v,s,r]=float(x[3])
        r+=1
        if (r==1000):
            r=int(0)
        sum_c12[v,s]+=float(x[2])
        sum_c13[v,s]+=float(x[3])
        ave_c12[v,s]=sum_c12[v,s]/1000.
        ave_c13[v,s]=sum_c13[v,s]/1000.
    v+=1
    file0.close()

v=0
for v_int in [360,400,440,480]:
    file0=open("results_final/"+str(v_int)+"_error")
    for i in file0:
        x=i.split()
        s=int(x[0])
        sqa_c12[v,s]=(ave_c12[v,s]-float(x[2]))**2
        sqa_c13[v,s]=(ave_c13[v,s]-float(x[3]))**2
        sigma_c12[v,s]=(sqa_c12[v,s])**0.5
        sigma_c13[v,s]=(sqa_c13[v,s])**0.5
    
    file0.close()
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


v=0
for v_int in [360,400,440,480]:
    for s in range(58):
        if (ave_c13[v,s]>10.):
            # alle geschwindigkeitsintervalle stepweise summiert
            c12_step[s]+=ave_c12[v,s]
            c13_step[s]+=ave_c13[v,s]
            sqa_c12_step[s]+=sqa_c12[v,s]
            sqa_c13_step[s]+=sqa_c13[v,s]
            sigma_c12_step[s]=(sqa_c12_step[s])**0.5
            sigma_c13_step[s]=(sqa_c13_step[s])**0.5
            # das gleiche mit berücksichtigung der effizienzen und der stärkeren gewichtung des c13 peaks, weil
            # 1. in jedem step das geschwindigkeitsfenster für c13 "sqrt(13/12)" kleiner ist
            # 2. die effizienzen anders sind
            # 3. es geht die annahme rein, dass das sigma der peaks proportional ist zur position in der matrix
            # daher muss der c13 peak mit dem faktor (tp_c13[i,0]-dt)/(tp_c12[i,0]-dt)*(tp_c13[i,1]-de)/(tp_c12[i,1]-de) [i=1,..,58]
            # gewichtet werden. dt und de sind dabei die offset werte bei der bestimmung der positionen in der et-matrix.
            c12_step_eff[s]+=ave_c12[v,s]*eff_c12[s,1]
            c13_step_eff[s]+=ave_c13[v,s]*eff_c13[s,1]*(13./12.)**0.5*(tp_c13[s,0]-dt)/(tp_c12[s,0]-dt)*(tp_c13[s,1]-de)/(tp_c12[s,1]-de)
            sigma_c12_step_eff[s]=((c12_step[s]*eff_c12[s,2])**2+(sigma_c12_step[s]*eff_c12[s,1])**2)**0.5
            sigma_c13_step_eff[s]=((c13_step[s]*eff_c13[s,2])**2+(sigma_c13_step[s]*eff_c13[s,1])**2)**0.5
            # alle steps geschwindigkeitsintervallweise summiert
            c12_v_int[v]+=ave_c12[v,s]
            c13_v_int[v]+=ave_c13[v,s]
            sqa_c12_v_int[v]+=sqa_c12[v,s]
            sqa_c13_v_int[v]+=sqa_c13[v,s]
            sigma_c12_v_int[v]=(sqa_c12_v_int[v])**0.5
            sigma_c13_v_int[v]=(sqa_c13_v_int[v])**0.5
            # das gleiche mit berücksichtigung der effizienzen und der stärkeren gewichtung des c13 peaks, weil
            # 1. in jedem step das geschwindigkeitsfenster für c13 "sqrt(13/12)" kleiner ist
            # 2. die effizienzen anders sind
            # 3. es geht die annahme rein, dass das sigma der peaks proportional ist zur position in der matrix
            # daher muss der c13 peak mit dem faktor (tp_c13[i,0]-dt)/(tp_c12[i,0]-dt)*(tp_c13[i,1]-de)/(tp_c12[i,1]-de) [i=1,..,58]
            # gewichtet werden. dt und de sind dabei die offset werte bei der bestimmung der positionen in der et-matrix.
            c12_v_int_eff[v]+=ave_c12[v,s]*eff_c12[s,1]
            c13_v_int_eff[v]+=ave_c13[v,s]*eff_c13[s,1]*(13./12.)**0.5*(tp_c13[s,0]-dt)/(tp_c12[s,0]-dt)*(tp_c13[s,1]-de)/(tp_c12[s,1]-de)
            sqa_c12_v_int_eff[v]+=((sqa_c12[v,s])**0.5*eff_c12[s,1])**2+(ave_c12[v,s]*eff_c12[s,2])**2
            sqa_c13_v_int_eff[v]+=((sqa_c13[v,s])**0.5*eff_c13[s,1])**2+(ave_c13[v,s]*eff_c13[s,2])**2
            sigma_c12_v_int_eff[v]=(sqa_c12_v_int_eff[v])**0.5
            sigma_c13_v_int_eff[v]=(sqa_c13_v_int_eff[v])**0.5
    v+=1


v=0
for v_int in [360,400,440,480]:
    file0=open("results_final/"+str(v_int)+"_we", "w")
    for s in range(58):
        file0.write(str(s+2))
        file0.write("   ")
        file0.write(str(ave_c12[v,s]))
        file0.write("   ")
        file0.write(str(ave_c13[v,s]))
        file0.write("   ")
        file0.write(str(sigma_c12[v,s]))
        file0.write("   ")
        file0.write(str(sigma_c13[v,s]))
        file0.write("\n")
    file0.close()
    v+=1
    
v=0
for v_int in [360,400,440,480]:
    file0=open("results_final/"+str(v_int)+"_weff_we", "w")
    for s in range(58):
        file0.write(str(s+2))
        file0.write("   ")
        file0.write(str(ave_c12[v,s]*eff_c12[s,1]))
        ave_c12_eff[v,s]=ave_c12[v,s]*eff_c12[s,1]
        file0.write("   ")
        file0.write(str(ave_c13[v,s]*eff_c13[s,1]))
        ave_c13_eff[v,s]=ave_c13[v,s]*eff_c13[s,1]
        file0.write("   ")
        file0.write(str((((sigma_c12[v,s]*eff_c12[s,1])**2)+((ave_c12[v,s]*eff_c12[s,2])**2))**0.5))
        sigma_c12_eff[v,s]=((((sigma_c12[v,s]*eff_c12[s,1])**2)+((ave_c12[v,s]*eff_c12[s,2])**2))**0.5)
        file0.write("   ")
        file0.write(str((((sigma_c13[v,s]*eff_c13[s,1])**2)+((ave_c13[v,s]*eff_c13[s,2])**2))**0.5))
        sigma_c13_eff[v,s]=((((sigma_c13[v,s]*eff_c13[s,1])**2)+((ave_c13[v,s]*eff_c13[s,2])**2))**0.5)
        file0.write("\n")
    file0.close()
    v+=1

file0=open("results_final/all_asafo_v","w")
v=0
for v_int in [360,400,440,480]:
    file0.write(str(v_int))
    file0.write("   ")
    file0.write(str(c12_v_int[v]))
    file0.write("   ")
    file0.write(str(c13_v_int[v]))
    file0.write("   ")
    file0.write(str(sigma_c12_v_int[v]))
    file0.write("   ")
    file0.write(str(sigma_c13_v_int[v]))
    file0.write("   ")
    file0.write(str(c12_v_int_eff[v]))
    file0.write("   ")
    file0.write(str(c13_v_int_eff[v]))
    file0.write("   ")
    file0.write(str(sigma_c12_v_int_eff[v]))
    file0.write("   ")
    file0.write(str(sigma_c13_v_int_eff[v]))
    file0.write("\n")
    v+=1
file0.close()

file0=open("results_final/all_asafo_step","w")
for s in range(58):
    file0.write(str(s+2))
    file0.write("   ")
    file0.write(str(c12_step[s]))
    file0.write("   ")
    file0.write(str(c13_step[s]))
    file0.write("   ")
    file0.write(str(sigma_c12_step[s]))
    file0.write("   ")
    file0.write(str(sigma_c13_step[s]))
    file0.write("   ")
    file0.write(str(c12_step_eff[s]))
    file0.write("   ")
    file0.write(str(c13_step_eff[s]))
    file0.write("   ")
    file0.write(str(sigma_c12_step_eff[s]))
    file0.write("   ")
    file0.write(str(sigma_c13_step_eff[s]))
    file0.write("\n")
file0.close()

file0=open("results_final/ratios_asafo_v","w")
v=0
for v_int in [360,400,440,480]:
    file0.write(str(v_int))
    file0.write("   ")
    file0.write(str(c13_v_int_eff[v]/c12_v_int_eff[v]))
    file0.write("   ")
    file0.write(str((((sigma_c13_v_int_eff[v]/c12_v_int_eff[v])**2)+(((c13_v_int_eff[v]/c12_v_int_eff[v]**2)*sigma_c12_v_int_eff[v])**2))**0.5))
    file0.write("\n")
    v+=1
file0.close()

file0=open("results_final/ratios_asafo_step","w")
for s in range(58):
    file0.write(str(s+2))
    file0.write("   ")
    file0.write(str(c13_step_eff[s]/c12_step_eff[s]))
    file0.write("   ")
    file0.write(str((((sigma_c13_step_eff[s]/c12_step_eff[s])**2)+(((c13_step_eff[s]/c12_step_eff[s]**2)*sigma_c12_step_eff[s])**2))**0.5))
    file0.write("\n")
file0.close()

"""
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
    file4.write("   ")
    file4.write(str(c13_weighted/c12_step[i,0]))
    file4.write("\n")
file4.close()

dummy=0.
for i in range(35,51):
    #sm+=1./(((1./c12_step[i,0]*c13_step[i,1])**2.)+(c13_step[i,1]/c12_step[i,0]**2.*c12_step[i,1])**2.)
    dummy+=1./(((((((((1./c12_step[i,0]*(c13_step[i,1]**0.5))**2.)+((c13_weighted/(c12_step[i,0])**2.*(c12_step[i,1]**0.5))**2.))**0.5)/(c13_weighted/c12_step[i,0]))+1.)**2.*((((eff_c12[i,2]/eff_c12[i,1])-(eff_c13[i,2]/eff_c13[i,1]))**2.)**0.5*eff_c12[i,1]/eff_c13[i,1]+1.)**2.)**0.5-1.)*(c13_weighted/c12_step[i,0]))
    sm=4./dummy # siehe http://de.wikipedia.org/wiki/Arithmetisches_Mittel#Gewichtetes_arithmetisches_Mittel. die 4 ist wurzel aus 16= anzahl der datenpunkte, der rest steht bei wikipedia
print sm

gp4("set autoscale")
gp4("set xrange[36:53]")
gp4("f(x)=c")
gp4("c=0.01")
gp4("sm="+str(sm))
gp4("fit f(x) 'all_asafo_step' u 1:($3/$2):6 via c")
gp4("set xlabel 'E/q step'")
gp4("set ylabel 'Isotopic ratio'")
gp4("plot 'all_asafo_step' u ($1+2):($3/$2):6 w e title '^{13}C^{6+}/^{12}C^{6+}(step)', f(x) lt -1   title 'm', c+sm lt 3 title 'm {/Symbol \261} {/Symbol s}_m  ', c-sm lt 3 notitle")
gp4("set term postscript enhanced color 18")
gp4("set output '/home/kleopatra/mu/Desktop/doktorarbeit/pictures/c13c12_ratios2.eps'")
gp4("replot")
gp4("set term X11")
"""

