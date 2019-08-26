#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data

dim=20



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

#Final set of parameters            Asymptotic Standard Error
#=======================            ==========================
#
#a               = 0.0141429        +/- 0.0005533    (3.912%)
#b               = -0.00142857      +/- 0.01237      (866%)



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
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
#0.611532,0.55]
epq_arr2=zeros([dim],Float)
epq_arr2=[86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048,0.611532,0.55]

epq_arr_jim=[86.6081,75.025,64.9911,56.2991,48.7696,42.2471,36.5969,31.7024,27.4625,23.7896,20.608,17.8518,16.6152,15.4643,14.3931,13.3961,12.4682,11.6045,10.8007,10.0525,9.35616,8.70806,8.10486,7.54343,7.0209,6.53457,6.08192,5.66063,5.26852,4.90357,4.5639,4.24776,3.95352,3.67966,3.42477,3.18754,2.96674,2.76123,2.56996,2.39194,2.22625,2.07204,1.92851,1.79492,1.67059,1.55487,1.44716,1.34692,1.25362,1.16678,1.08596,1.01073,0.940721,0.875557,0.814908,0.758459,0.705921,0.657022]

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_1-20.dat")
print "loading ion_para.dat"
s=f.readline()
k=s.split()
numberions=int(k[5])

xpos=zeros([numberions,dim],Float)
ypos=zeros([numberions,dim],Float)
ion_names=""

plot_data=zeros([2,dim],Float)

for i in range(dim):
    ion_names=""
    s=f.readline()
    for j in range(numberions):
        s=f.readline()
        k=s.split()
        xpos[j][i]=float(k[1])
        ypos[j][i]=float(k[2])
        ion_names=ion_names+" "+k[0]
    s=f.readline()
ion_name=ion_names.split()        
print ion_name
# loading srim-Tof
srimxpos=zeros([numberions,dim],Float)
k=0

f=open("/home/ivar/berger/projects/ionpositions/test_ion_pos.dat")
for j in range(dim):
    s=f.readline()
    s=f.readline()
    for i in range(numberions):
        s=f.readline()
        m=s.split()
        srimxpos[i][j]=float(m[3])
    s=f.readline()
    
#    convert from time to tch
#    srim[i]=1295.61*exp(0.00177262*srim[i])-1286.51
#    -(16./16.)**2

cfile=open("tmptof.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % epq_arr2[i])
    for j in range(numberions):
        cfile.write("%f\t" % srimxpos[j][i])
        cfile.write("%f\t" % xpos[j][i])
    cfile.write("\n")
cfile.close()

cfile=open("tmpratio.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % epq_arr2[i])
    for j in range(numberions):
        cfile.write("%f\t" % (srimxpos[j][i]-xpos[j][i]))
    cfile.write("\n")
cfile.close()

cfile=open("tmpc4fit.dat", "w")
cfile.write("%f\t" % epq_arr2[3])
cfile.write("%f\t" % (xpos[5][3]))
cfile.write("%f\t" % epq_arr2[5])
cfile.write("%f\t" % (xpos[5][5]))
for i in range(11,19):
    cfile.write("%f\t" % epq_arr2[i])
    cfile.write("%f\t" % (xpos[5][i]))
    cfile.write("\n")
cfile.close()



plot_ions=[10,11,2,3,12,13,24,25,38]

gp=Gnuplot()
gp("a=-0.001")
gp("b=10.")
gp("c=100.")
gp("d=-0.001")
gp("e=80.")
gp("f=60.")
#gp("f(x)= b*exp(a*x)+c")
gp("g(x)= e*exp(d*x)+f")
gp("fit g(x) 'tmptof.dat' using 1:11 via e,d,f")
#gp("fit f(x) 'tmpc4fit.dat' using 1:2 via a,b,c")
#gp("set logscale y")
#gp("set term postscript color")
#gp("set outp 'sige.ps'")
#gp("set data style line")
gp("set xrange[0:90]")
#gp("set yrange[0:200]")

gp("set xlabel 'E/q'")
gp("set ylabel 'Channel'")

#gp("set yrange[0:512]")
#gp("plot 'tmptof.dat' using 4:2")
#,'tmptof.dat' using 1:3,'tmptof.dat' using 1:4,'tmptof.dat' using 1:5")
gp("plot 'tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]-2],plot_ions[1],ion_name[plot_ions[1]-2],plot_ions[2],ion_name[plot_ions[2]-2],plot_ions[3],ion_name[plot_ions[3]-2],plot_ions[4],ion_name[plot_ions[4]-2],plot_ions[5],ion_name[plot_ions[5]-2],plot_ions[6],ion_name[plot_ions[6]-2],plot_ions[7],ion_name[plot_ions[7]-2],plot_ions[8],ion_name[plot_ions[8]-2]))
gp("plot 'tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s',g(x)" %(plot_ions[0],ion_name[plot_ions[0]/2-1],plot_ions[1],ion_name[plot_ions[0]/2-1],plot_ions[2],ion_name[plot_ions[2]/2-1],plot_ions[3],ion_name[plot_ions[2]/2-1],plot_ions[4],ion_name[plot_ions[4]/2-1],plot_ions[5],ion_name[plot_ions[4]/2-1],plot_ions[6],ion_name[plot_ions[6]/2-1],plot_ions[7],ion_name[plot_ions[6]/2-1]))
#gp("plot 'poster_plot_pos.dat' using 1:2 ps 3 pt 2 t 'ToF','poster_plot_pos.dat' using 1:3 pt 3 ps 3 lt 3 t 'Energy'")
#,'tmpenergy.dat' using 1:3")
#gp("plot 'tmpenergy.dat' using 1:6,'tmpenergy.dat' using 1:4")

#gp("set term postscript color")
#gp("set outp 'poster_pos.ps'")
#gp("plot 'poster_plot_pos.dat' using 1:2 ps 3 pt 2 t 'ToF','poster_plot_pos.dat' using 1:3 pt 3 ps 3 lt 3 t 'Energy'")

#gp("set term postscript color")
#gp("set outp 'o6energydiff.ps'")
#gp("plot 'tmp5.dat' using 1:5")



