#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt
from Gnuplot import Gnuplot, GridData, Data

# Program to fit energy positions to already fitted positions (from ion_para.dat)

dim=58

f=open("/home/asterix/berger/projects/ionpositions/ion_para.dat")
print "loading ion_pos.dat"
He2=zeros([6,dim],Float)
tposHe2=zeros([dim],Float)
eposHe2=zeros([dim],Float)
expfitepos1=zeros([11],Float)
expfitepos2=zeros([dim],Float)
for i in range(dim):
    s=f.readline()
    s=f.readline()
    s=f.readline()
    k=s.split()
    print k[3],k[4]
    tposHe2[i]=float(k[1])
    eposHe2[i]=float(k[2])
    s=f.readline()

#Final set of parameters He2epos-10 Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.151852        +/- 0.001667     (1.097%)
#b               = 33.2131          +/- 0.1806       (0.544%)
#c               = 7.98771          +/- 0.1982       (2.478%)

def expepos1(step):
    a = -0.151852
    b = 33.2131
    c = 7.98771
    return b*exp(a*step)+c

#Final set of parameters He2epos11-58 Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.0860719       +/- 0.001821     (2.116%)
#b               = 16.1329          +/- 0.3692       (2.288%)
#c               = 7.97259          +/- 0.03317      (0.416%)

def expepos2(step):
    a = -0.0860719
    b = 16.1329
    c = 7.97259
    return b*exp(a*step)+c


print "writing tmp.dat"
cfile=open("tmp.dat", "w")
for i in range(11):
    cfile.write("%d\t" % i)
    cfile.write("%f\t" % eposHe2[i])
    cfile.write("\n")
cfile.close()

cfile=open("tmp2.dat", "w")
for i in range(11,58):
    cfile.write("%d\t" % i)
    cfile.write("%f\t" % eposHe2[i])
    cfile.write("\n")
cfile.close()


for i in range(11):
    expfitepos1[i]=expepos1(i)

for i in range(dim):
    expfitepos2[i]=expepos2(i)


gp=Gnuplot()
gp("a=-0.2")
gp("b=10.")
gp("c=7.")
#gp("set outp X11")
#gp("f(x)=a*x+b")
gp("f(x)= b*exp(a*x)+c")
gp("fit f(x) 'tmp2.dat' using 1:2 via a,b,c")

#gp("set logscale y")
#gp("set zrange[1:80]")
#gp("set palette rgbformula -3,-3,-3")
#gp("test palette")
#gp("set xrange[400:800]")
#gp("set yrange[0:50]")

#gp("set pm3d map")
#gp.splot(cmgd,data2grid)
#gp("set term postscript color")
#gp("set outp 'sigt3.ps'")
gp("set data style line")
gp("set xrange[0:60]")
#gp.plot(tposHe2,eposHe2,expfitem,expfitep,sumHe2,sumHefit)
gp.plot(eposHe2,expfitepos1,expfitepos2)
#expfitep,expfitem)
#,linfittm,tposHe2,linfittp) 
