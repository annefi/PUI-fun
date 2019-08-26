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
matrixmultiply=dot
gp=Gnuplot()
start_2001=[]
start_2002=[]
start_2003=[]
start_2004=[]
start_2005=[]
start_2006=[]
start_2007=[]
stop_2001=[]
stop_2002=[]
stop_2003=[]
stop_2004=[]
stop_2005=[]
stop_2006=[]
stop_2007=[]
cme_2001=[]
cme_2002=[]
cme_2003=[]
cme_2004=[]
cme_2005=[]
cme_2006=[]
cme_2007=[]

md_array=[0,31,59,90,120,151,181,212,243,273,304,334]
md_array_sj=[0,31,60,91,121,152,182,213,244,274,305,335]

year=int(2001)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    print x[2], x[4], x[5]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2001+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2001):
                cme_2001+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2001+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2001):
                cme_2001+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))

year=int(2002)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    print x[2], x[4], x[5]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2002+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2002):
                cme_2002+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2002+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2002):
                cme_2002+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))


year=int(2003)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    print x[2], x[4], x[5]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2003+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2003):
                cme_2003+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2003+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2003):
                cme_2003+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))


year=int(2004)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    print x[2], x[4], x[5]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2004+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2004):
                cme_2004+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2004+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2004):
                cme_2004+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))


year=int(2003)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    print x[2], x[4], x[5]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2003+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2003):
                cme_2003+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2003+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2003):
                cme_2003+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))



year=int(2006)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2006+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2006):
                cme_2006+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2006+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2006):
                cme_2006+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))

year=int(2007)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    l+=1
data=zeros([l,4],Float)
file0=open("cme_"+str(year)+".dat")
l=0
for i in file0:
    x=i.split()
    print x[2], x[4], x[5]
    data[l,0]=float(x[2][0]+x[2][1])
    data[l,1]=float(x[2][3]+x[2][4])
    data[l,2]=float(x[4][0]+x[4][1])
    if (len(x[4]) == 5):
        data[l,3]=float(x[4][3]+x[4][4])
    if (len(x[4]) == 4):
        data[l,3]=float(x[4][3])
    if (len(x[4]) == 3):
        data[l,3]=float(x[5])
    l+=1

for i in range(l):
    for j in range(12):
        if (int(data[i,0]) == int(j+1)):
            start_2007+=[md_array[j]+data[i,1]]
            if not (int(md_array[j]+data[i,1]) in cme_2007):
                cme_2007+=[int(md_array[j]+data[i,1])]
    for j in range(12):
        if (int(data[i,2]) == int(j+1)):
            stop_2007+=[md_array[j]+data[i,3]]
            if not (int(md_array[j]+data[i,3]) in cme_2007):
                cme_2007+=range(int(md_array[j]+data[i,1]+1),int(md_array[j]+data[i,3]+1))


# bd = broken days (hier existieren weder res_files noch ein list.in file)
bd_2001=[37,38,205,206,207]
bd_2002=[1,2]
bd_2003=[]
bd_2004=[range(101,120),137,138]
bd_2005=[]
bd_2006=[346]
bd_2007=[]


# bbrd = broken but repairable days (hier stimmen tatsächliche anzahl der res_files nicht mit der in list.in überein)
bbrd_2001=[]
bbrd_2002=[331,332,333,340,341,343,344,353,356,357,358,359,360,361]
bbrd_2003=[18,19,31,169,175,188,228,230,236,281,304,335]
bbrd_2004=[140]
bbrd_2005=[37,38,42,46,52,56,61,62,63,104,123,129,134,192,230,237,249,258,269,271,274,282,286,310]
bbrd_2006=[]
bbrd_2007=[]

# norf = number of res files on the respective  broken but repairable days

norf_2001=[]
norf_2002=[0,2,1,23,0,1,1,9,1,1,1,1,1,1]
norf_2003=[5,4,23,12,4,12,15,12,3,5,25,19]
norf_2004=[16]
norf_2005=[7,0,3,8,12,22,15,12,14,2,19,9,1,18,23,17,0,10,17,18,7,3,1,4]
norf_2006=[]
norf_2007=[]

years=range(2002,2003)



for year_int in years:
    year=str(year_int)
    data2=[]
    names=[]
    data3=zeros([51,60,128,512],Float)
    import cPickle
    data=cPickle.load(open("cPickle_files/res_"+year+".dat", "rb")) 
    system("rm "+year+"_data/cme_days")
    filex=open(year+"_data/cme_days","a")

    system("rm list.in")
    system("rm axlv2_et_slices*.dat")
    counter=int(0.0)
    if (year == "2001"):
        bd=bd_2001
        bbrd=bbrd_2001
        norf=norf_2001
        cme=cme_2001
    if (year == "2002"):
        bd=bd_2002
        bbrd=bbrd_2002
        norf=norf_2002
        cme=cme_2003
    if (year == "2003"):
        bd=bd_2003
        bbrd=bbrd_2003
        norf=norf_2003
        cme=cme_2003
    if (year == "2004"):
        bd=bd_2004
        bbrd=bbrd_2004
        norf=norf_2004
        cme=cme_2004
    if (year == "2005"):
        bd=bd_2005
        bbrd=bbrd_2005
        norf=norf_2005
        cme=cme_2005
    if (year == "2006"):
        bd=bd_2006
        bbrd=bbrd_2006
        norf=norf_2006
        cme=cme_2006
    if (year == "2007"):
        bd=bd_2007
        bbrd=bbrd_2007
        norf=norf_2007
        cme=cme_2007
    if (1 == 1):
        kt=0
        for z in range(365):
            if z+1 in bbrd:
                counter=counter+norf[kt]
                kt+=1
            if not ((z+1 in bd) or (z+1 in bbrd)):
                print "Tag ",z+1
                stop=0
                if (z < 9):
                   day="00"+str(z+1)
                if ((z >= 9) and (z < 99)):
                    day="0"+str(z+1)
                if (z >= 99):
                    day=str(z+1)
                if (z+1 in cme):
                    system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                    #system("(echo axlv2_et_slices_*|wc -w;ls -1 axlv2_et_slices_*) > cme_list.in") # das und 
                #listin=open("list.in") # das und den mv befehl weiter unten einschaten wenn die listinfiles noch nicht existieren
                try:
                    listin=open(year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in") # das einschalten, wenn die listin files existieren
                except IOError:
                    print "listin_file für tag ",z+1," existiert nicht"
                    stop=1
                    anzahl=0
                    continue
                s=0
                names=[]
                if (stop==0):
                    for w in listin:
                        v=w.split()
                        if (s == 0):
                            anzahl=int(v[0])
                        if (s > 0):
                            names+=v
                        s+=1
                print names
                #system("mv list.in "+year+"_data/listin_files_"+year+"/"+str(z+1)+"_list.in")
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if (z+1 in cme):
                        filex.write(day+"  "+str(y)+"\n")
                        if not ((data[y][2][0][0]) == "He2+"):
                            print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                        for va in range(51):
                            if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                                file=open(names[u])
                                i=0
                                l=0
                                for j in file:
                                    x=j.split()
                                    if (i > 5):
                                        if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                            l+=1
                                            i=5
                                        if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                            for k in range(512):
                                                data3[va,l,i-6,k]+=float(x[k])
                                    i+=1
                                file.close()
                        u+=1
                system("rm axlv2_et_slices_*.dat")

        for va in range(51):
            v_int=str(345+va*10)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    filex.close()



"""

for yearfloat in [2007]:
    year=str(yearfloat)
    data2=[]
    names=[]
    data3=zeros([51,60,128,512],Float)
    import cPickle
    data=cPickle.load(open("cPickle_files/res_"+year+".dat", "rb")) 


    system("rm list.in")
    system("rm axlv2_et_slices*.dat")
    counter=int(0.0)
    if (year == "2001"):
        for z in cme_2001:
            if not (((z>=205) and (z<=207)) or (z==37) or (z==38)):#(2001)
                print "Tag ",z
    
                if (z < 10):
                   day="00"+str(z)
                if ((z >= 10) and (z < 100)):
                    day="0"+str(z)
                if (z >= 100):
                    day=str(z)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if not ((data[y][2][0][0]) == "He2+"):
                        print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                    for va in range(51):
                        if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                            file=open(names[u])
                            i=0
                            l=0
                            for j in file:
                                x=j.split()
                                if (i > 5):
                                    if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        l+=1
                                        i=5
                                    if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        for k in range(512):
        #                                    print i,l, float(x[k])
                                            data3[va,l,i-6,k]+=float(x[k])
                                i+=1
                            file.close()
                    u+=1
                system("rm axlv2_et_slices_"+year+"*.dat")

        for va in range(51):
            v_int=str(345+va*10)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2002"):
        for z in cme_2002:
            if (z==332):#(2002) am tag 332 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+2#(2002) anzahl res_files=2, list.in sagt 24
            if (z==333):#(2002) am tag 333 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+1#(2002) anzahl res_files=1, list.in sagt 24
            if (z==340):#(2002) am tag 340 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+23#(2002) anzahl res_files=23, list.in sagt 24

            if not ((z==1) or (z==2) or (z==331) or (z==332) or (z==333) or (z==340) or (z==341) or ((z>=343) and (z<=362))):#(2002)
        #        #die restlichen tage, die ausgelassen wurden, sind nicht vorhanden, enthalten also weder res_files noch list.in_files
                print "Tag ",z
    
                if (z < 10):
                   day="00"+str(z)
                if ((z >= 10) and (z < 100)):
                    day="0"+str(z)
                if (z >= 100):
                    day=str(z)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if not ((data[y][2][0][0]) == "He2+"):
                        print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                    for va in range(51):
                        if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                            file=open(names[u])
                            i=0
                            l=0
                            for j in file:
                                x=j.split()
                                if (i > 5):
                                    if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        l+=1
                                        i=5
                                    if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        for k in range(512):
        #                                    print i,l, float(x[k])
                                            data3[va,l,i-6,k]+=float(x[k])
                                i+=1
                            file.close()
                    u+=1
                system("rm axlv2_et_slices_"+year+"*.dat")

        for va in range(51):
            v_int=str(345+va*10)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2004"):
        for z in cme_2004:
            if (z==140):#(2004) am tag 140 stimmen anzahl der res_files mit der angabe in der list.in nicht überein
                counter=counter+16#(2004)
            if not (((z>=101) and (z<=119)) or (z==137) or (z==138) or (z==140)):#(2004)
                print "Tag ",z
                if (z < 10):
                   day="00"+str(z)
                if ((z >= 10) and (z < 100)):
                    day="0"+str(z)
                if (z >= 100):
                    day=str(z)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if not ((data[y][2][0][0]) == "He2+"):
                        print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                    for va in range(51):
                        if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                            file=open(names[u])
                            i=0
                            l=0
                            for j in file:
                                x=j.split()
                                if (i > 5):
                                    if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        l+=1
                                        i=5
                                    if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        for k in range(512):
        #                                    print i,l, float(x[k])
                                            data3[va,l,i-6,k]+=float(x[k])
                                i+=1
                            file.close()
                    u+=1
                system("rm axlv2_et_slices_"+year+"*.dat")

        for va in range(51):
            v_int=str(345+va*10)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2006"):
        for z in cme_2006:
            if not (((z>=236) and (z<=239)) or (z==346) or (z==347)):#(2006)
                print "Tag ",z
                if (z < 10):
                   day="00"+str(z)
                if ((z >= 10) and (z < 100)):
                    day="0"+str(z)
                if (z >= 100):
                    day=str(z)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if not ((data[y][2][0][0]) == "He2+"):
                        print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                    for va in range(51):
                        if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                            file=open(names[u])
                            i=0
                            l=0
                            for j in file:
                                x=j.split()
                                if (i > 5):
                                    if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        l+=1
                                        i=5
                                    if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        for k in range(512):
                                            data3[va,l,i-6,k]+=float(x[k])
                                i+=1
                            file.close()
                    u+=1
                system("rm axlv2_et_slices_"+year+"*.dat")

        for va in range(51):
            v_int=str(345+va*10)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
    if (year == "2007"):
        for z in cme_2007:
            if (1 == 1):#(2007)
                print "Tag ",z
                if (z < 10):
                   day="00"+str(z)
                if ((z >= 10) and (z < 100)):
                    day="0"+str(z)
                if (z >= 100):
                    day=str(z)

                system("../run-axlv2-many.pl "+year+day+" "+year+day+" --accum=1h --config_file='axlv2.in'")
                names=[]
                listin=open(year+"_data/listin_files_"+year+"/"+str(z)+"_list.in")
                s=0
                for w in listin:
                    v=w.split()
                    if (s == 0):
                        anzahl=int(v[0])
                    if (s > 0):
                        names+=v
                    s+=1
                print names
                u=0
                runner=counter
                for y in range(runner,(runner+anzahl)):
                    counter+=1
                    if not ((data[y][2][0][0]) == "He2+"):
                        print "Ion evtl. nicht an der richtigen Stelle -- Bitte prüfen!!!"
                    for va in range(51):
                        if (((data[y][2][0][1][0]) > (340.+va*10)) and ((data[y][2][0][1][0]) < (340.+(va+1)*10))):
                            file=open(names[u])
                            i=0
                            l=0
                            for j in file:
                                x=j.split()
                                if (i > 5):
                                    if ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        l+=1
                                        i=5
                                    if not ((int(x[0]) == 128) and  (int(x[1]) == 512)):
                                        for k in range(512):
        #                                    print i,l, float(x[k])
                                            data3[va,l,i-6,k]+=float(x[k])
                                i+=1
                            file.close()
                    u+=1
                system("rm axlv2_et_slices_"+year+"*.dat")
        system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data")
        system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files")
        for va in range(51):
            v_int=str(345+va*10)
            system("mkdir /data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he") 
            for i in range(60):
                print "/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i)
                file2=open("/data/wimmer/mu/jahresdaten/"+year+"_data/step_files/"+v_int+"_he/cme_step_"+str(i),"w")
                for j in range(128):
                    for k in range(512):
                        file2.write(str(j+1))
                        file2.write("   ")
                        file2.write(str(k+1))
                        file2.write("   ")
                        file2.write(str(data3[va,i,j,k]))
                        file2.write("\n")
                file2.close()
"""
