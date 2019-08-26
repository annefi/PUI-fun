#!/usr/bin/python
from scipy import zeros, Float, matrixmultiply,exp,sqrt,sin
from Gnuplot import Gnuplot, GridData, Data

# Program to fit ToF position to already fitted positions (from ion_para.dat)

dim=58

f=open("/home/asterix/berger/projects/ionpositions/ion_para_unmod.dat")
print "loading ion_pos.dat"
He2=zeros([6,dim],Float)
tposHe2=zeros([dim],Float)
eposHe2=zeros([dim],Float)
tposO6=zeros([dim],Float)
eposO6=zeros([dim],Float)

expfittpos1=zeros([11],Float)
expfittpos2=zeros([dim],Float)
expfittposO61=zeros([11],Float)
expfittposO62=zeros([dim],Float)

diffpos=zeros([dim],Float)
sinfit=zeros([dim],Float)

for i in range(dim):
    s=f.readline()
    s=f.readline()
    s=f.readline()
    k=s.split()
    print k[3],k[4]
    tposHe2[i]=float(k[1])
    eposHe2[i]=float(k[2])
    s=f.readline()
    k=s.split()
    print k[3],k[4]
    tposO6[i]=float(k[1])
    eposO6[i]=float(k[2])

#Final set of parameters He2tpos 11-60 Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.0506351       +/- 6.602e-06    (0.01304%)
#b               = -76.9247         +/- 0.004603     (0.005984%)
#c               = 172.981          +/- 0.00219      (0.001266%)
#d               = 0.0013484        +/- 0.0005702    (42.29%)
#e               = 0.9512           +/- 0.03065      (3.222%)
#f               = 5.91539          +/- 1.131        (19.13%)

#Final set of parameters He2tpos 11-60 Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.0506339       +/- 0.000701     (1.384%)
#b               = -76.9244         +/- 0.4883       (0.6347%)
#c               = 172.981          +/- 0.2324       (0.1343%)

def exptpos2(step):
    a = -0.0506351
    b = -76.9247
    c = 172.981
    d = 0.356002  
    e = 0.194379    
    f = -5.83995    
    return b*exp(a*step)+c
#+d*sin(e*step+f)

#Final set of parameters He2tpos-10 Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.003538        +/- 0.001274     (36.01%)
#b               = -1283.57         +/- 454.1        (35.38%)
#c               = 1364.98          +/- 454.1        (33.27%)

#Final set of parameters He2tpos-10 Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.00476164      +/- 0.0005294    (11.12%)
#b               = -959.584         +/- 104.2        (10.86%)
#c               = 1040.95          +/- 104.2        (10.01%)
#d               = 0.0165807        +/- 0.0147       (88.64%)
#e               = 4.91172          +/- 0.2761       (5.622%)
#f               = 14.6475          +/- 1.613        (11.01%)

def exptpos1(step):
    a = -0.00476164
    b = -959.584   
    c = 1040.95    
    d = -0.103916  
    e = 0.79389  
    f = -7.35022    
    return b*exp(a*step)+c+d*sin(e*step+f)

#Final set of parameters St0-10 O6+ Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.00322476      +/- 0.004211     (130.6%)
#b               = -1595.03         +/- 2050         (128.5%)
#c               = 1688.83          +/- 2050         (121.4%)

def exptposO61(step):
    a = -0.00322476
    b = -1595.03   
    c = 1688.83    
    d = -0.103916  
    e = 0.79389  
    f = -7.35022    
    return b*exp(a*step)+c
#+d*sin(e*step+f)





#Final set of parameters St11-60 O6+Asymptotic Standard Error
#=======================            ==========================
#
#a               = -0.0536209       +/- 0.001475     (2.751%)
#b               = -89.2896         +/- 1.268        (1.42%)
#c               = 197.392          +/- 0.4966       (0.2516%)

def exptposO62(step):
    a = -0.0536209
    b = -89.2896 
    c = 197.392   
    d = -0.103916  
    e = 0.79389  
    f = -7.35022    
    return b*exp(a*step)+c
#+d*sin(e*step+f)




print "writing tmp.dat"
cfile=open("tmp.dat", "w")
for i in range(11):
    cfile.write("%d\t" % i)
    cfile.write("%f\t" % tposO6[i])
    cfile.write("\n")
cfile.close()

cfile=open("tmp2.dat", "w")
for i in range(11,58):
    cfile.write("%d\t" % i)
    cfile.write("%f\t" % tposO6[i])
    cfile.write("\n")
cfile.close()


for i in range(11):
    expfittpos1[i]=exptpos1(i)

for i in range(dim):
    expfittpos2[i]=exptpos2(i)

for i in range(11):
    expfittposO61[i]=exptposO61(i)

for i in range(dim):
    expfittposO62[i]=exptposO62(i)


for i in range(11):
    diffpos[i]=tposHe2[i]-expfittpos1[i]

for i in range(11,dim):
    diffpos[i]=tposHe2[i]-expfittpos2[i]


cfile=open("tmp3.dat", "w")
for i in range(11,dim):
    cfile.write("%d\t" % i)
    cfile.write("%f\t" % diffpos[i])
    cfile.write("\n")
cfile.close()

cfile=open("tmp4.dat", "w")
for i in range(11):
    cfile.write("%d\t" % i)
    cfile.write("%f\t" % diffpos[i])
    cfile.write("\n")
cfile.close()

#Final set of parameters            Asymptotic Standard Error
#=======================            ==========================
#
#d               = -0.103916        +/- 0.01393      (13.4%)
#e               = 0.79389          +/- 0.03795      (4.78%)
#f               = -7.35022         +/- 0.2348       (3.195%)

def sintpos1(step):
    d = -0.103916  
    e = 0.79389  
    f = -7.35022    
    return d*sin(e*step+f)



#Final set of parameters sin10-60   Asymptotic Standard Error
#=======================            ==========================
#
#d               = 0.356002         +/- 0.02721      (7.644%)
#e               = 0.194379         +/- 0.005731     (2.948%)
#f               = -5.83995         +/- 0.1957       (3.351%)

def sintpos2(step):
    d = 0.356002  
    e = 0.194379    
    f = -5.83995    
    return d*sin(e*step+f)

for i in range(11):
    sinfit[i]=sintpos1(i)

for i in range(11,dim):
    sinfit[i]=sintpos2(i)

gp=Gnuplot()
gp("a=-0.2")
gp("b=-900.")
gp("c=1000.")
gp("d=0.15")
gp("e=0.7")
gp("f=-5.8")
#gp("set outp X11")
#gp("f(x)=a*x+b")
gp("f(x)= b*exp(a*x)+c")
#gp("f(x)= d*sin(e*x+f)")

gp("fit f(x) 'tmp.dat' using 1:2 via a,b,c")

#gp("set logscale y")
#gp("set zrange[1:80]")
#gp("set palette rgbformula -3,-3,-3")
#gp("test palette")
#gp("set xrange[400:800]")
#gp("set yrange[0:50]")

#gp("set pm3d map")
#gp.splot(cmgd,data2grid)
gp("set term postscript color")
gp("set outp 'diffhe.ps'")
gp("set data style line")
gp("set xrange[0:60]")
#gp("set yrange[80:180]")

#gp.plot(tposHe2,eposHe2,expfitem,expfitep,sumHe2,sumHefit)
gp.plot(diffpos,sinfit)

#gp.plot(tposO6,expfittposO61,expfittposO62)
#expfitep,expfitem)
#,linfittm,tposHe2,linfittp) 
