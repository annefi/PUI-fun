#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot 
from os import popen2





dim=57



paps=25.868179
thpos=zeros([dim],Float)
mproton = 1.661e-27
echarge = 1.602e-19
charge=2.
mass=4.

def time2ch(time):
    return -0.000612781*((time-135.509)*(time-135.509))+4.92812*time+14.3373

def hecharge(energypronuc):
    return 0.0141429*energypronuc
#    return 0.00541429*energypronuc**2

def echfit(x,a,b,c):
    return a*x**2+b*x+c

def chargecorr(time,mass):
    simass=mass*1.66053886e-27
    energy=(simass*0.01)/(2.*(time*1e-9)**2)
    energy=energy*6.24150974e15
    tmpenergy=energy/mass
    energy=energy-hecharge(tmpenergy)
    energy=energy/6.24150974e15
    tmptime=sqrt((simass*.01)/(2.*energy))
    tmptime=tmptime*1e9
    return tmptime

epq_arr=zeros([dim],Float)
epq_arr_diff=zeros([dim],Float)
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
#0.611532,0.55]
epq_arr2=zeros([dim],Float)
epq_arr2=[86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

epq_arr_jim=[86.6081,75.025,64.9911,56.2991,48.7696,42.2471,36.5969,31.7024,27.4625,23.7896,20.608,17.8518,16.6152,15.4643,14.3931,13.3961,12.4682,11.6045,10.8007,10.0525,9.35616,8.70806,8.10486,7.54343,7.0209,6.53457,6.08192,5.66063,5.26852,4.90357,4.5639,4.24776,3.95352,3.67966,3.42477,3.18754,2.96674,2.76123,2.56996,2.39194,2.22625,2.07204,1.92851,1.79492,1.67059,1.55487,1.44716,1.34692,1.25362,1.16678,1.08596,1.01073,0.940721,0.875557,0.814908,0.758459,0.705921,0.657022]
for i in range(dim):
    epq_arr_diff[i]=epq_arr[i]-epq_arr_jim[i]

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges.dat")
print "loading ion_para.dat"
s=f.readline()
k=s.split()
numberions=int(k[5])
numberionsstep=numberions
xpos=zeros([numberions,dim],Float)
ypos=zeros([numberions,dim],Float)
srimxpos=zeros([numberions,dim],Float)

ion_names=""
s=f.readline()
for j in range(numberionsstep):
    s=f.readline()
    k=s.split()
    ion_names=ion_names+" "+k[0]
ion_name=ion_names.split()        
f.close()
print ion_name

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges.dat")
for i in range(dim):
    s=f.readline()
    k=s.split()
    numberionsstep=int(k[5])
    s=f.readline()
    for j in range(numberionsstep):
        s=f.readline()
        k=s.split()
        for l in range(numberions):
            if (ion_name[l]==k[0]):
                print i,l,ion_name[l]
                xpos[l][i]=float(k[1])
                ypos[l][i]=float(k[2])
f.close()

f=open("/home/ivar/berger/projects/ionpositions/ion_pos_clean_21.dat")
for j in range(dim):
    s=f.readline()
    k=s.split()
    numberionsstep=int(k[6])
    s=f.readline()
    for i in range(numberionsstep):
        s=f.readline()
        m=s.split()
        for k in range(numberions):
            if (ion_name[k]==m[0]):
                srimxpos[k][j]=float(m[3])
    s=f.readline()

    
#    convert from time to tch
#    srim[i]=1295.61*exp(0.00177262*srim[i])-1286.51
#    -(16./16.)**2

cfile=open("tmpepq.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % float(i))
    cfile.write("%f\t" % epq_arr_diff[i])
    cfile.write("\n")
cfile.close()

cfile=open("tmptof.dat", "w")
for i in range(dim):
#    cfile.write("%f\t" % (float(i)+1.))
    cfile.write("%f\t" % epq_arr2[i])
    for j in range(numberions):
        cfile.write("%f\t" % srimxpos[j][i])
        cfile.write("%f\t" % xpos[j][i])
    cfile.write("\n")
cfile.close()

cfile=open("tmpratio.dat", "w")
for i in range(0,10):
#    cfile.write("%f\t" % (float(i)+1.))
    cfile.write("%f\t" % epq_arr2[i])
    for j in range(numberions):
#        if (j==3):
#            cfile.write("%f\t" % ((srimxpos[j][i]-xpos[j][i])-echo6(epq_arr2[i])))
#        elif (j==1):
#            cfile.write("%f\t" % ((srimxpos[j][i]-xpos[j][i])-echhe2(epq_arr2[i])))
#        else:
        cfile.write("%f\t" % ((srimxpos[j][i]-xpos[j][i])))
    cfile.write("\n")
cfile.close()

cfile=open("tmpc4fit.dat", "w")
for i in range(3,10):
    cfile.write("%f\t" % epq_arr2[i])
    cfile.write("%f\t" % (srimxpos[8][i]-xpos[8][i]))
    cfile.write("\n")
#cfile.write("%f\t" % epq_arr2[11])
#cfile.write("%f\t" % (srimxpos[8][11]-xpos[8][11]))
#cfile.write("%f\t" % epq_arr2[13])
#cfile.write("%f\t" % (srimxpos[8][13]-xpos[8][13]))
#cfile.write("%f\t" % epq_arr2[14])
#cfile.write("%f\t" % (srimxpos[8][14]-xpos[8][14]))
#for i in range(24,dim-5):
#    cfile.write("%f\t" % epq_arr2[i])
#    cfile.write("%f\t" % (srimxpos[8][i]-xpos[8][i]))
#    cfile.write("\n")
cfile.close()

l=3
m=8
n=10
plot_ions=[3,3,3,5,10,10,10,9,10]
#plot_ions=[2,3,4,5,6,7,8,9,10]
#plot_ions=[20,21,16,17,18,19,14,15,20]
#plot_ions=[2,3,7,5,9,11,4,8,10]

gp=Gnuplot()
gp("a=-0.1")
gp("b=0.01")
gp("c=-.1")
gp("d=-.1")
gp("e=0.01")
gp("f=-.1")

gp("f(x)= a*x**2+b*x+c")
gp("i(x)= d*x**2+e*x+f")
gp("fit f(x) 'tmpratio.dat' using 1:3 via a,b,c")
gp("fit i(x) 'tmpc4fit.dat' using 1:2 via d,e,f")
tmpx=gp.eval("a")
print "tmpx=",tmpx

gp("set xrange[20:90]")
#gp("set yrange[-4:4]")

gp("set xlabel 'E/q'")
gp("set ylabel 'Channel'")

gp("plot 'tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s',i(x),f(x)"%(plot_ions[0],ion_name[plot_ions[0]-2],plot_ions[1],ion_name[plot_ions[1]-2],plot_ions[2],ion_name[plot_ions[2]-2],plot_ions[3],ion_name[plot_ions[3]-2],plot_ions[4],ion_name[plot_ions[4]-2],plot_ions[5],ion_name[plot_ions[5]-2],plot_ions[6],ion_name[plot_ions[6]-2],plot_ions[7],ion_name[plot_ions[7]-2],plot_ions[8],ion_name[plot_ions[8]-2]))
#gp("plot 'tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]/2-1],plot_ions[1],ion_name[plot_ions[0]/2-1],plot_ions[2],ion_name[plot_ions[2]/2-1],plot_ions[3],ion_name[plot_ions[2]/2-1],plot_ions[4],ion_name[plot_ions[4]/2-1],plot_ions[5],ion_name[plot_ions[4]/2-1],plot_ions[6],ion_name[plot_ions[6]/2-1],plot_ions[7],ion_name[plot_ions[6]/2-1]))


gp("set term postscript color")
gp("set outp 'tof.ps'")
gp("plot 'tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s',i(x)"%(plot_ions[0],ion_name[plot_ions[0]-2],plot_ions[1],ion_name[plot_ions[1]-2],plot_ions[2],ion_name[plot_ions[2]-2],plot_ions[3],ion_name[plot_ions[3]-2],plot_ions[4],ion_name[plot_ions[4]-2],plot_ions[5],ion_name[plot_ions[5]-2],plot_ions[6],ion_name[plot_ions[6]-2],plot_ions[7],ion_name[plot_ions[7]-2],plot_ions[8],ion_name[plot_ions[8]-2]))




