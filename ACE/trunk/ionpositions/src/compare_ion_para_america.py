#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data

dim=57


epq_arr=zeros([dim],Float)
epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]

epq_arr_jim=[86.6081,75.025,64.9911,56.2991,48.7696,42.2471,36.5969,31.7024,27.4625,23.7896,20.608,17.8518,16.6152,15.4643,14.3931,13.3961,12.4682,11.6045,10.8007,10.0525,9.35616,8.70806,8.10486,7.54343,7.0209,6.53457,6.08192,5.66063,5.26852,4.90357,4.5639,4.24776,3.95352,3.67966,3.42477,3.18754,2.96674,2.76123,2.56996,2.39194,2.22625,2.07204,1.92851,1.79492,1.67059,1.55487,1.44716,1.34692,1.25362,1.16678,1.08596,1.01073,0.940721,0.875557,0.814908,0.758459,0.705921,0.657022]

f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit3fit.dat")
print "loading ion_para.dat"
s=f.readline()
k=s.split()
numberions=int(k[5])
numberionsstep=numberions
s=f.readline()
xpos=zeros([numberions,dim],Float)
ypos=zeros([numberions,dim],Float)
srimypos=zeros([numberions,dim],Float)
srimxpos=zeros([numberions,dim],Float)
ion_names=""
for j in range(numberionsstep):
    s=f.readline()
    k=s.split()
    ion_names=ion_names+" "+k[0]
ion_name=ion_names.split()        
f.close()    
print ion_name

#f=open("/home/ivar/berger/projects/ionpositions/fmout.dat")
f=open("/home/ivar/berger/projects/ionpositions/ion_para_mu_fitmod2_clean_fast_ges_fit3fit.dat")
for i in range(dim):
    s=f.readline()
    k=s.split()
    numberionsstep=int(k[5])
    s=f.readline()
    for j in range(numberionsstep):
        s=f.readline()
        m=s.split()
        for k in range(numberions):
            if (ion_name[k]==m[0]):
                print i,j,ion_name[k]
                xpos[k][i]=float(m[1])
                ypos[k][i]=float(m[2])
#                xpos[k][i]=float(m[1])*0.5+0.75
#                ypos[k][i]=float(m[2])*0.5+0.75

aorb=2
if (aorb==0):
    f=open("/home/ivar/berger/projects/ionpositions/fmout.dat")
    for i in range(dim):
        s=f.readline()
        k=s.split()
        numberionsstep=int(k[5])
        s=f.readline()
        for j in range(numberionsstep):
            s=f.readline()
            m=s.split()
            for k in range(numberions):
                if (ion_name[k]==m[0]):
                    print i,j,ion_name[k]
                    srimxpos[k][i]=(float(m[1])*0.5)+0.75
                    srimypos[k][i]=(float(m[2])*0.5)+0.75


if (aorb==1):
    f=open("/home/ivar/berger/projects/ionpositions/ion_pos_clean_21.dat")
    for i in range(dim):
        s=f.readline()
        k=s.split()
        numberionsstep=int(k[6])
        s=f.readline()
        for j in range(numberionsstep):
            s=f.readline()
            m=s.split()
            for k in range(numberions):
                if (ion_name[k]==m[0]):
                    print i,j,ion_name[k]
                    srimxpos[k][i]=float(m[3])
                    srimypos[k][i]=float(m[4])
        s=f.readline()

if (aorb==2):
    f=open("/home/ivar/berger/projects/ionpositions/axlv2_pccomp_078_998.dat")
    s=f.readline()
    s=f.readline()
    s=f.readline()
    s=f.readline()
    k=s.split()
    step=int(k[0])
    ions=0
    while (int(k[0])==step):
        ions+=1
        s=f.readline()
        k=s.split()
    f.close()
        
    for ion in range(numberions):
        f=open("/home/ivar/berger/projects/ionpositions/axlv2_pccomp_078_998.dat")
        s=f.readline()
        s=f.readline()
        s=f.readline()
        
        for step in range(dim):
            for i in range(ions):
                s=f.readline()
                k=s.split()
                if (ion_name[ion]==k[2]):
                    if (not(k[3]=="nan")):
                        srimxpos[ion][step]=(float(k[3])*0.5)+0.75
                    if (not(k[5]=="nan")):
                        srimypos[ion][step]=(float(k[5])*0.5)+0.75
            

cfile=open("tmptof.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % epq_arr[i])
    for j in range(numberions):
        cfile.write("%f\t" % srimxpos[j][i])
        cfile.write("%f\t" % xpos[j][i])
    cfile.write("\n")
cfile.close()

cfile=open("tmpech.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % epq_arr[i])
    for j in range(numberions):
        cfile.write("%f\t" % srimypos[j][i])
        cfile.write("%f\t" % ypos[j][i])
    cfile.write("\n")
cfile.close()


cfile=open("tmpratio.dat", "w")
for i in range(dim):
    cfile.write("%f\t" % epq_arr[i])
    for j in range(numberions):
        cfile.write("%f\t" % (srimxpos[j][i]-xpos[j][i]))
    cfile.write("\n")
cfile.close()


plot_ions=[2,3,4,5,7,8,9,10,11]

gp=Gnuplot()
gp("set xrange[0:20]")
gp("set yrange[-3:10]")
gp("set title 'ToF-differences'")
gp("set xlabel 'E/q'")
gp("set ylabel 'Difference america-maxfit'")
gp("plot 'tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]-2],plot_ions[1],ion_name[plot_ions[1]-2],plot_ions[2],ion_name[plot_ions[2]-2],plot_ions[3],ion_name[plot_ions[3]-2],plot_ions[4],ion_name[plot_ions[4]-2],plot_ions[5],ion_name[plot_ions[5]-2],plot_ions[6],ion_name[plot_ions[6]-2],plot_ions[7],ion_name[plot_ions[7]-2],plot_ions[8],ion_name[plot_ions[8]-2]))
#gp("plot 'tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s','tmptof.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]/2-1],plot_ions[1],ion_name[plot_ions[0]/2-1],plot_ions[2],ion_name[plot_ions[2]/2-1],plot_ions[3],ion_name[plot_ions[2]/2-1],plot_ions[4],ion_name[plot_ions[4]/2-1],plot_ions[5],ion_name[plot_ions[4]/2-1],plot_ions[6],ion_name[plot_ions[6]/2-1],plot_ions[7],ion_name[plot_ions[6]/2-1]))
#gp("plot 'tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s','tmpech.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]/2-1],plot_ions[1],ion_name[plot_ions[0]/2-1],plot_ions[2],ion_name[plot_ions[2]/2-1],plot_ions[3],ion_name[plot_ions[2]/2-1],plot_ions[4],ion_name[plot_ions[4]/2-1],plot_ions[5],ion_name[plot_ions[4]/2-1],plot_ions[6],ion_name[plot_ions[6]/2-1],plot_ions[7],ion_name[plot_ions[6]/2-1]))
#gp("plot 'poster_plot_pos.dat' using 1:2 ps 3 pt 2 t 'ToF','poster_plot_pos.dat' using 1:3 pt 3 ps 3 lt 3 t 'Energy'")
#,'tmpenergy.dat' using 1:3")
#gp("plot 'tmpenergy.dat' using 1:6,'tmpenergy.dat' using 1:4")

gp("set term postscript color")
gp("set outp 'tof-differences.ps'")
gp("plot 'tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]-2],plot_ions[1],ion_name[plot_ions[1]-2],plot_ions[2],ion_name[plot_ions[2]-2],plot_ions[3],ion_name[plot_ions[3]-2],plot_ions[4],ion_name[plot_ions[4]-2],plot_ions[5],ion_name[plot_ions[5]-2],plot_ions[6],ion_name[plot_ions[6]-2],plot_ions[7],ion_name[plot_ions[7]-2],plot_ions[8],ion_name[plot_ions[8]-2]))
#gp("plot 'tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s','tmpratio.dat' using 1:%i t '%s'" %(plot_ions[0],ion_name[plot_ions[0]-2],plot_ions[1],ion_name[plot_ions[1]-2],plot_ions[2],ion_name[plot_ions[2]-2],plot_ions[3],ion_name[plot_ions[3]-2],plot_ions[4],ion_name[plot_ions[4]-2],plot_ions[5],ion_name[plot_ions[5]-2],plot_ions[6],ion_name[plot_ions[6]-2],plot_ions[7],ion_name[plot_ions[7]-2],plot_ions[8],ion_name[plot_ions[8]-2]))




