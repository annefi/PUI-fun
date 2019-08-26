#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean,median
from Gnuplot import Gnuplot, GridData, Data

dim=58
ydimfit=10

f=open("/home/asterix/berger/projects/ionpositions/ion_para_fexvcvioviii.dat")
print "loading ion_para.dat"
He2=zeros([6,dim],Float)
O6=zeros([6,dim],Float)
O7=zeros([6,dim],Float)
Fe14=zeros([6,dim],Float)
C5=zeros([6,dim],Float)
Fe11=zeros([6,dim],Float)
diff=zeros([dim],Float)
diff2=zeros([dim],Float)
lin=zeros([dim],Float)


def time2ch(time):
    return -0.000612781*((time-135.509)*(time-135.509))+4.92812*time+14.3373

def hecharge(energypronuc):
    return 0.0141429*energypronuc

#Final set of parameters            Asymptotic Standard Error
#=======================            ==========================
#
#a               = 0.0141429        +/- 0.0005533    (3.912%)
#b               = -0.00142857      +/- 0.01237      (866%)



def chargecorr(time,mass):
    mass=4.0026
    simass=mass*1.66053886e-27
    energy=(simass*0.01)/(2.*(time*1e-9)**2)
    energy=energy*6.24150974e15
    energy=energy-hecharge(energy/mass)
    energy=energy/6.24150974e15
    tmptime=sqrt((simass*.01)/(2.*energy))
    tmptime=tmptime*1e9
    return tmptime

print "bla = ",chargecorr(50.,4.0026)

epq_arr=zeros([dim],Float)
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]

for i in range(dim):
    s=f.readline()
    s=f.readline()
    s=f.readline()
    k=s.split()
    for j in range(6):
        He2[j][i]=float(k[j+1])
    s=f.readline()
    k=s.split()
    for j in range(6):
        O6[j][i]=float(k[j+1])
    s=f.readline()
    k=s.split()
    for j in range(6):
        Fe14[j][i]=float(k[j+1])
    s=f.readline()
    k=s.split()
    for j in range(6):
        C5[j][i]=float(k[j+1])
    s=f.readline()
    k=s.split()
    for j in range(6):
        O7[j][i]=float(k[j+1])

for i in range(dim):
    print He2[1][i]

f=open("/home/asterix/berger/projects/ionpositions/ion_para_fexii.dat")
for i in range(dim):
    s=f.readline()
    s=f.readline()
    s=f.readline()
    k=s.split()
    for j in range(6):
        Fe11[j][i]=float(k[j+1])


erge_arr=zeros([ydimfit],Float)
for i in range(ydimfit):
    print erge_arr[i]

for j in range(ydimfit):
    ft=20+j*1
    srimname="/home/asterix/berger/projects/ionpositions/srimfit/srimhe2paps24"+"ft"+str(ft)+".mu"
    
    print "opening "+srimname
    f=open(srimname)
    srim=zeros([dim],Float)

    for k in range(dim):
        s=f.readline()
        l=s.split()
        srim[k]=float(l[1])
        srim[k]=chargecorr(srim[k],4.0026)
        srim[k]=time2ch(srim[k])
#        *(1023./200.)
        srim[k]=0.5*srim[k]+0.75
        #        print "srim["+str(k)+"] = ", srim[k]
        #        print "He2["+str(k)+"] = ",He2[0][k]
        #        print abs(srim[k]-He2[0][k])
    cut = 0
    tmparr=zeros([dim-2*cut],Float)

    if (cut>0):
        for k in range(cut,dim-cut):
            tmparr[k-cut]=abs(srim[k]-He2[0][k])
            print tmparr[k-cut]
            erge_arr[j]=erge_arr[j]+abs(srim[k]-He2[0][k]) 
#        erge_arr[j]=median(tmparr)
        erge_arr[j]=erge_arr[j]/(float(dim)-2.*float(cut))
    else:
        for k in range(dim):
            tmparr[k]=abs(srim[k]-He2[0][k])
            print tmparr[k]
            erge_arr[j]=erge_arr[j]+abs(srim[k]-He2[0][k]) 
#        erge_arr[j]=median(tmparr)
        erge_arr[j]=erge_arr[j]/float(dim)

#    erge_arr[j]=erge_arr[j]/38.
#        erge_arr[i][j]=median(tmparr)

#for k in range(ydimfit):
#    print "erge

cfile=open("tmpplot.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % epq_arr[i])
    cfile.write("%f\t" % srim[i])
    cfile.write("%f\t" % He2[0][i])
    cfile.write("\n")
cfile.close()


cfile=open("erge_mat.dat", "w")
for i in range(ydimfit):
    cfile.write("%f\t" % (2.+float(i)/10.))
    cfile.write("%f\t" % erge_arr[i])
    cfile.write("\n")
cfile.close()

#xrange=[30.,38.]

gp=Gnuplot()
gp("g(x)= e*exp(d*x)+f")
#gp("plot 'tmpplot.dat' using 1:2,'tmpplot.dat' using 1:3")

#gp("fit g(x) 'tmptof.dat' using 3:2 via e,d,f")
#gp("set pm3d map explicit")
#gp("set palette rgbformula -32,-5,-7")
#gp("set log cb 2")
#gp("set logscale z")
#gp("set xrange[3.:3.8]")
#gp("set xrange[%i:%i]" % (xrange[0],xrange[1]))
#gp("set yrange[%i:%i]" % (yrange[0],yrange[1]))

#gp("set zrange[0:1000]")
#gp("set palette rgbformula -32,-5,-7")

gp("plot 'erge_mat.dat' using 1:2")


ft=24
srimname="/home/asterix/berger/projects/ionpositions/srimfit/srimO6paps24"+"ft"+str(ft)+".mu"
    
print "opening "+srimname
f=open(srimname)
srim=zeros([dim],Float)

for k in range(dim):
    s=f.readline()
    l=s.split()
    srim[k]=float(l[1])
    srim[k]=srim[k]*(1023./200.)
    srim[k]=0.5*srim[k]+0.75

cfile=open("srimo6tof.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % srim[i])
    cfile.write("\n")
cfile.close()
