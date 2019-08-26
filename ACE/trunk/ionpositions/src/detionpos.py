#!/usr/bin/python
import sys
from scipy import zeros, Float, matrixmultiply,exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data

from os import popen2

class Gnuplot:
    """Interface to gnuplot."""

    def __init__(self):
        """Create a pipe to gnuplot"""
        self.gpwrite,self.gpout=popen2("gnuplot")

    def __call__(self, s):
        """Send string to gnuplot"""

        self.gpwrite.write(s+"\n")
        self.gpwrite.flush()
        
    def getvar(self,var):
        """Get a gnuplot variable

           In order to avoid locking we have to check
           if the variable is really defined.
           This only works with a recent CVS gnuplot
           (having the defined(var) function;
            this is enabled per default).

           FIXME: no real error checking done so far ....
           FIXME: we could try to convert the returned string
                  to a float or int (depending on
                  an optional parameter passed to getvar)

        """
        self(" set print \"-\"\n")      # print output to stdout
        self(" if (defined(%s)) print %s ; else print \"None\" \n" % (var,var))
        result=self.gpout.readline()
        self(" set print\n")            # print output to default stderr
        if result[0:4]=="None":
            return None
        return(result)


def writeion(file,name,mass,charge,tpos,epos,peakh,velocity):
    file.write("%s\t\t%f\t%f\t%f\t%f\t%f\t%f\n" %(name,mass,charge,tpos,epos,peakh,velocity))

dim=58
xdim=512
ydim=128
ionname=''


#print "argv : ",sys.argv[1]
if (int(sys.argv[1])<0 or int(sys.argv[1])>dim):
    step=30
else:
    step=int(sys.argv[1])

#step=14
print "step :",step

f=open("/home/asterix/berger/projects/ionpositions/test_ion_pos.dat")
print "loading test_ion_pos.dat"

for i in range(step-1):
    s=f.readline()
    k=s.split()
    s=f.readline()
    print i,k[6]
    for k in range(int(k[6])):
        s=f.readline()
    s=f.readline()

s=f.readline()
k=s.split()
s=f.readline()
srimionname=''

srimxpos=zeros([int(k[6])],Float)
srimypos=zeros([int(k[6])],Float)
srimsigxp=zeros([int(k[6])],Float)
srimsigxm=zeros([int(k[6])],Float)
srimsigyp=zeros([int(k[6])],Float)
srimsigym=zeros([int(k[6])],Float)
srimpeakh=zeros([int(k[6])],Float)

points_mat=zeros([xdim,ydim],Float)
fit_mat=zeros([xdim,ydim],Float)
numpoints=int(k[6])


for l in range(numpoints):
    s=f.readline()
    m=s.split()
    srimionname=srimionname+m[0]+'  '
    srimxpos[l]=float(m[3])
    srimypos[l]=float(m[4])


f.close()

fit_mat=zeros([xdim,ydim],Float)
data=open("/home/asterix/berger/projects/ionpositions/axlv2_sumwhol_asp_00.0-15.0_bin.dat")
print "loading axlv2_sumwhol_asp_00.0-15.0_bin.dat"

et_mat=zeros([xdim,ydim],Float)


for i in range(step-1):
    s=data.readline()
    print i
    for k in range(xdim):
        s=data.readline()

s=data.readline()
print s
for i in range(xdim):
    s=data.readline()
    line=s.split()
    for k in range(ydim):
        if (float(line[k]) > -1.):
            et_mat[i][k]=float(line[k])

gp=Gnuplot()
et_mat_gp=GridData(et_mat)
points_mat_gp=GridData(points_mat)
cfile=open("tmpetmat.dat", "w")
for i in range(ydim):
    for j in range(xdim):
        cfile.write("%f\t" % float(et_mat[j][i]))
        cfile.write("\n")
    cfile.write("\n")
cfile.close()

cfile=open("tmppointssrimmat.dat", "w")
for i in range(numpoints):
    cfile.write("%f\t" % srimxpos[i])
    cfile.write("%f\t" % srimypos[i])
    cfile.write("%f\t" % 1.)
    cfile.write("\n")
cfile.close()

xrange=[90,350]
yrange=[1,80]

gp("set mouse")
gp("set pm3d map explicit")
gp("set palette rgbformula -32,-5,-7")
gp("set cblabel 'Counts' -14")
gp("set log cb")
gp("set logscale z")
gp("set xlabel 'Time-of-Flight Channel'")
gp("set ylabel 'Energy Channel' ")
gp("show cblabel")
gp("set xrange[%i:%i]" % (xrange[0],xrange[1]))
gp("set yrange[%i:%i]" % (yrange[0],yrange[1]))

print "ionnames = ",srimionname
labelnames=srimionname.split()
print "numpoints = ",numpoints
for i in range(numpoints):
    labelx=((srimxpos[i]-float(xrange[0]))/float(xrange[1]-xrange[0]))-0.025
    labely=(1.-(srimypos[i]-float(yrange[0]))/(yrange[1]-yrange[0]))-0.05
    print labelnames[i],labelx,labely
    if (srimxpos[i] > xrange[0] and srimxpos[i] < xrange[1]):
        if (srimypos[i] > yrange[0] and srimypos[i] < yrange[1]):
            gp("set label '%s' at graph %f,%f front" % (labelnames[i],labelx,labely))
gp("splot 'tmpetmat.dat' w pm3d t '', 'tmppointssrimmat.dat' w p lt 5 pt 2 ps 3 t ''")
gp("splot 'tmpetmat.dat' t '', 'tmppointssrimmat.dat' w p lt 5 pt 2 ps 3 t ''")
gp("pause mouse 'start' ")

mousexpos=zeros([numpoints],Float)
mouseypos=zeros([numpoints],Float)

print "Get coordinates:"
for i in range(numpoints):
    gp("unset label")
    xrange[0]=max(int(srimxpos[i])-30,0)
    xrange[1]=min(int(srimxpos[i])+30,xdim)
    yrange[1]=max(int(srimypos[i])-30,0)
    yrange[0]=min(int(srimypos[i])+30,ydim)
    for j in range(numpoints):
        labelx=((srimxpos[j]-float(xrange[0]))/float(xrange[1]-xrange[0]))-0.025
        labely=(1.-(srimypos[j]-float(yrange[1]))/(yrange[0]-yrange[1]))-0.05
        print labelnames[j],labelx,labely
        if (srimxpos[j] > xrange[0] and srimxpos[j] < xrange[1]):
            if (srimypos[j] > yrange[1] and srimypos[j] < yrange[0]):
                gp("set label '%s' at graph %f,%f front" % (labelnames[j],labelx,labely))
    cfile=open("tmppointsmat.dat", "w")
    for k in range(numpoints):
        cfile.write("%f\t" % mousexpos[k])
        cfile.write("%f\t" % mouseypos[k])
        if (mousexpos[k]>0. and mouseypos[k]>0.):
            cfile.write("%f\t" % 1.)
        else:
            cfile.write("%f\t" % 0.)
        cfile.write("\n")
    cfile.close()

    
    gp("set xrange[%i:%i]" % (xrange[0],xrange[1]))
    gp("set yrange[%i:%i]" % (yrange[0],yrange[1]))
    gp("set title '%s'" %(labelnames[i]))
    gp("splot 'tmpetmat.dat' w pm3d t '', 'tmppointssrimmat.dat' w p lt 5 pt 2 ps 3 t '', 'tmppointsmat.dat' w p lt 3 pt 1 ps 3 t''")
    gp("pause mouse '%s' "%(labelnames[i]))
    tmpx=float(gp.getvar("MOUSE_X"))
    mousexpos[i]=tmpx
    tmpy=float(gp.getvar("MOUSE_Y"))
    mouseypos[i]=tmpy
    print mousexpos[i],mouseypos[i]
    gp("set terminal x11 close")


f=open("/home/asterix/berger/projects/ionpositions/test_ion_pos.dat")
w=open("/home/asterix/berger/projects/ionpositions/tmp_ion_pos_end.dat","w")
print "loading test_ion_pos.dat"

for i in range(step-1):
    s=f.readline()
    w.write(s)
    k=s.split()
    s=f.readline()
    w.write(s)
    print i,k[6]
    for k in range(int(k[6])):
        s=f.readline()
        w.write(s)
    s=f.readline()
    w.write(s)
s=f.readline()
w.write(s)
k=s.split()
s=f.readline()
w.write(s)

numpoints=int(k[6])

for l in range(numpoints):
    s=f.readline()
    m=s.split()
    writeion(w,m[0],float(m[1]),float(m[2]),mousexpos[l],mouseypos[l],max(0.1,float(et_mat[int(mousexpos[l])][int(mouseypos[l])])),float(m[6]))
s=f.readline()
w.write(s)

for i in range(dim-step):
    s=f.readline()
    w.write(s)
    k=s.split()
    s=f.readline()
    w.write(s)
    print i,k[6]
    for k in range(int(k[6])):
        s=f.readline()
        w.write(s)
    s=f.readline()
    w.write(s)

f.close()
w.close()

f=open("/home/asterix/berger/projects/ionpositions/tmp_ion_pos_end.dat")
w=open("/home/asterix/berger/projects/ionpositions/ion_pos_end.dat","w")
print "loading test_ion_pos.dat"

for i in range(dim):
    s=f.readline()
    w.write(s)
    k=s.split()
    s=f.readline()
    w.write(s)
    print i,k[6]
    for k in range(int(k[6])):
        s=f.readline()
        w.write(s)
    s=f.readline()
    w.write(s)

f.close()
w.close()
