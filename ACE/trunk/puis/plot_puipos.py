#!/usr/bin/python
import sys
from scipy import zeros, sqrt,mean
from numpy import float
from Gnuplot import Gnuplot, GridData, Data

elemq=1.602176*10**(-19)


def vel(Eq,q,mass):
    amu=1.66053886*10**(-27)
    energy=Esd(Eq,q)
    velocity=sqrt((2*energy)/(mass*amu))
    return velocity

def Tof(Eq,q,mass):    
    velocity=vel(Eq,q,mass)
    time=0.1/velocity
    return time

def Esd(Eq,q):
    Eacc=24.868179
    elemq=1.602176*10**(-19)
    energy=(Eq*q+Eacc*q)*1000.*elemq
    return energy

def Tch(time):
    tch=((time*10**(9)*(1023./200.))/2.)+0.75
    return tch

def Ech(energy):
    elemq=1.602176*10**(-19)
    ech=(((energy/(elemq*1000.))*(255./610.78))/2.)+0.75
    return ech

def Tch2Tof(tch):
    time=(2*((tch)-0.75))*(200./1023.)*10**(-9)
    return time

def Ech2Esd(ech):
    elemq=1.602176*10**(-19)
    esd=(2*((ech)-0.75))*(610.78/255.)*elemq*1000.
    return esd

def dt2Esd(t1,t2,e1,mass):
    dt=Tch2Tof(t1)-Tch2Tof(t2)
    e0=Ech2Esd(e1)
    amu=1.66053886*10**(-27)
    m=mass*amu
    e2=e0/(1.-sqrt((8.*e0*(dt**(2)))/(0.01*m))+((2*e0*(dt**(2)))/(m*0.01)))
    return Ech(e2)


epq_arr = [86.6359,75.0485,65.0109,56.3158,48.7837,42.2589,36.6069,31.7108,27.4695,23.7955,20.6129,17.856,16.619,15.4678,14.3962,13.399,12.4708,11.6069,10.8028,10.0545,9.35797,8.70971,8.10635,7.5448,7.02214,6.5357,6.08294,5.66156,5.26936,4.90433,4.56459,4.24839,3.95409,3.68017,3.42523,3.18796,2.96711,2.76157,2.57027,2.39222,2.2265,2.07226,1.92871,1.7951,1.67075,1.55501,1.44729,1.34703,1.25372,1.16687,1.08603,1.0108,0.940778,0.875607,0.81495,0.758496,0.705952,0.657048]
filter_arr=[300,300,300,300,300,300,300,300,300,300,310,320,320,295,300,305,310,315,320,190,295,300,300,305,310,310,315,320,320,320,300,305,305,305,305,305,305,305,305,305,290,280,260,255,240,240,240,240,240,240,220,220,220,220,220,220,220,220]
dim=58
xdim=512
ydim=128
ion_names=["H1+","He1+","C1+","N1+","O1+","Ne1+","Mg1+","Si1+","S1+","Ca1+","Fe1+"]

printall=0
listeions=[]
gp=Gnuplot()
paraname1="/home/ivar/berger/projects/puis/ion_para.dat"


if (len(sys.argv)>1):
    step = int(sys.argv[1])
else:
    step = 30
    print "default step = 30"

mass=zeros([len(ion_names)],float)
charge=zeros([len(ion_names)],float)
points1=[]
xerrorp=[]
xerrorm=[]
yerrorp=[]
yerrorm=[]

for ion in range(len(ion_names)):
    f=open(paraname1)
    for i in range(step-1):
        s=f.readline()
        k=s.split()
        s=f.readline()
        for k in range(int(k[5])):
            s=f.readline()

    s=f.readline()
    k=s.split()
    s=f.readline()
    numpoints1=int(k[5])
    ionda=0
    for i in range(numpoints1):
        s=f.readline()
        m=s.split()
        if (m[0]==ion_names[ion]):
           ionda=1
           points1.append([float(m[1])+1.,float(m[2])+1.,0.])
           xerrorp.append([float(m[1])+1.,float(m[2])+1.,1.,float(m[3]),0.,0.])
           xerrorm.append([float(m[1])+1.,float(m[2])+1.,1.,-float(m[3]),0.,0.])
           yerrorp.append([float(m[1])+1.,float(m[2])+1.,1.,0.,float(m[5]),0.])
           yerrorm.append([float(m[1])+1.,float(m[2])+1.,1.,0.,-float(m[5]),0.])
           mass[ion]=float(m[8])
           charge[ion]=float(m[9])
    if (not ionda):
           points1.append([0.,0.,0.,0.,0.,0.,0.])
           mass[ion]=0.
           charge[ion]=0.
    f.close()



#data=open("/data/ivar/berger/work/america/runs/2005280-284_speed640/axlv2_sumspeed_0600-0680.dat")
data=open("/data/ivar/berger/binneddata/axlv2_sumwhol_asp_00.0-15.0_bin.dat")
#data=open("/home/ivar/berger/projects/ionpositions/src/axlv2_et_slices_2004_120_16.35.34_2004_120_17.35.34.dat")

et_mat_plot=zeros([xdim,ydim],float)
et_mat=zeros([ydim,xdim],float)
if (0):
    s=data.readline()
    k=s.split()
    while (k[0]!="*****"):
        s=data.readline()
        k=s.split()
    
    for i in range(step-1):
        s=data.readline()
        for k in range(ydim):
            s=data.readline()

    s=data.readline()
    for i in range(ydim):
        s=data.readline()
        line=s.split()
        for k in range(xdim):
            et_mat[i][k]=float(line[k])

    for i in range(xdim):
        for j in range(ydim):
            et_mat_plot[i][j]=et_mat[j][i]
else:
    s=data.readline()
    for i in range(step-1):
        s=data.readline()
        for k in range(xdim):
            s=data.readline()
    s=data.readline()
    for i in range(xdim):
        s=data.readline()
        line=s.split()
        for k in range(ydim):
            et_mat_plot[i][k]=float(line[k])

pointsmat=zeros([len(points1),len(points1)],float)    
xval=zeros([xdim],float)
yval=zeros([ydim],float)
xvalpoints=zeros([len(points1)],float)
yvalpoints=zeros([len(points1)],float)
for i in range(xdim):
    xval[i]=float(i)+1.
for i in range(ydim):
    yval[i]=float(i)+1.
for i in range(len(points1)):
    pointsmat[i][i]=1.
    xvalpoints[i]=points1[i][0]
    yvalpoints[i]=points1[i][1]
gpdata=GridData(et_mat_plot,xval,yval,binary=0)
gpdata.set_option_colonsep("with","lines")
gppoints=GridData(pointsmat,xvalpoints,yvalpoints,binary=0)
#gppoints=Data(points1,binary=0)
gppoints.set_option_colonsep("with", "p pt 2 lt 5 ps 2.5")
#gppoints.set_option_colonsep("at", "bs")
gpxerrorp=Data(xerrorp)
gpxerrorm=Data(xerrorm)
gpyerrorp=Data(yerrorp)
gpyerrorm=Data(yerrorm)
#gpvectors.set_option_colonsep("using", "1:2:3:4")
gpxerrorp.set_option_colonsep("with", "vectors head filled lt 5 lw 2")
gpxerrorm.set_option_colonsep("with", "vectors head filled lt 5 lw 2")
gpyerrorp.set_option_colonsep("with", "vectors head filled lt 5 lw 2")
gpyerrorm.set_option_colonsep("with", "vectors head filled lt 5 lw 2")

#yrange=[6,40]
#xrange=[100,223]
yrange=[2,20]
xrange=[200,512]
#yrange=[0,127]
#xrange=[80,330]
for ion in range(len(ion_names)):
    labelx=((points1[ion][0]-float(xrange[0]))/float(xrange[1]-xrange[0]))-0.025
    labely=(1.-(points1[ion][1]-float(yrange[0]))/(yrange[1]-yrange[0]))-0.04
    print ion_names[ion],labelx,labely
    if (points1[ion][0] > xrange[0] and points1[ion][0] < xrange[1]):
        if (points1[ion][1] > yrange[0] and points1[ion][1] < yrange[1]):
            gp("set label '%s' at graph %f,%f front" % (ion_names[ion],labelx,labely))
#            gp("set arrow from graph %f,%f to graph %f,%f front" % ((xposjim[i]-float(xrange[0]))/(float(xrange[1])-float(xrange[0])),1.-(yposjim[i]-float(yrange[0]))/(float(yrange[1])-float(yrange[0])),(xpos[i]-float(xrange[0]))/(float(xrange[1])-float(xrange[0])),1.-(ypos[i]-float(yrange[0]))/(float(yrange[1])-float(yrange[0]))))

gp("set term postscript enhanced color 18 lw 2 eps")
gp("set output '%i.ps'"%(step))

gp("set multiplot")
gp("set size 1.,1.")
gp("set origin 0.,0.")
gp("set mouse")
#gp("set pm3d at bs map explicit corners2color c1")
#gp("set pm3d")
#gp("set dgrid3d %i,%i,8"%(xrange[1]-xrange[0]+1,yrange[1]-yrange[0]+1))
#gp("set dgrid3d 512,128,8")
gp("unset pm3d")
#gp("set palette rgbformula -32,-5,-7")
gp("set palette model RGB functions gray<0.0000001 ? 1 : gray , gray<0.0000001 ? 1 : 0.5-gray , gray <0.0000001 ? 1 : (1-gray)*0.7")
gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
#gp("set palette rgbformulae 33,13,10")
#gp("set palette rgbformulae 22,13,-31")
#gp("set mapping cartesian")
#gp("set palette model RGB functions gray<0.0001 ? 1 : 0.5-gray , gray<0.0001 ? 1 : gray , gray <0.0001 ? 1 : 1-gray")
gp("set cblabel 'Counts' 0")
gp("unset cblabel")
gp("set log cb")
gp("set xlabel 'Time-of-Flight Channel'")
gp("set ylabel 'Energy Channel'")
#gp("show cblabel")
gp("set xrange[%i:%i]" % (xrange[0],xrange[1]))
gp("set yrange[%i:%i]" % (yrange[0],yrange[1]))
#gp("set log z")
gp("set cbrange[1e0:1e6]")
gp("set format cb '10^%T'")
gp("set contour both")
gp("set cntrparam levels discrete 1e2,3.3e2,6.6e2,1e3,3.3e3,6.6e3,1e4,3.3e4,6.6e4,1e5,3.3e5,6.6e5,1e6")
gp("set pm3d map")
#gp("unset clabel")
gp("unset key")
gp.splot(gpdata)
gp("unset ztics")
gp("unset surface")
#gp("set clabel offset -100,0")
gp("set grid front noxtics noytics")
gp("set isosamples 1000")
gp("set pm3d at b corners2color median")
gp.replot(gpdata)

gp("set surface")
gp("set clabel '%0.0f'")
gp("unset contour")
gp("unset pm3d")
gp("unset log z")
gp("set zrange[0.5:1.5]")
gp.splot(gppoints)
gp.replot(gpxerrorp,gpxerrorm,gpyerrorp,gpyerrorm)
#gp.splot(gppoints)
#gp("unset multiplot")
#gp("set pm3d at b")
#gp.replot(gpdata)
#gp("unset contour")
#gp.replot(gppoints,gpxerrorp,gpxerrorm,gpyerrorp,gpyerrorm)
#gp("set pm3d at b")
#gp("set pm3d at b")
#gp("unset contour")
#gp("set contour")
#gp.replot(gpdata)
#gp("unset contour")
#gp("set pm3d map")
#gp.splot(et_mat_plot)

#set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? sqrt(gray*2) : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0
        
#gp("set title 'step%i'" %(step))
#gp("set title 'Ion-Positions'")
#gp("set term postscript color 18 lw 2 eps")
#if (step>9):
#    gp("set outp 'step%i.ps'"%(step))
#if (step<10):
#    gp("set outp 'step0%i.ps'"%(step))
#gp("set outp 'etslicefastswnew.ps'")
#gp.hardcopy("longtermpos.ps",color=True, fontsize=18)
#gp("splot 'tmpetmat.dat' with pm3d t'', 'tmppointsmat.dat' w p lt 5 pt 2 ps 2.5 t '','tmppointsmat3.dat' w p lt 5 pt 2 ps 2.5 t ''")
#gp("show palette")


