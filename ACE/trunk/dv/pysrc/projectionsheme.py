from Gnuplot import Gnuplot,Data
from math import cos,acos,tan,atan,pi,sqrt,sin,asin
from scipy import zeros,array

def circle(y,r):
    return sqrt(r**2-y**2)

def getcircle(r):
    tmpcirc=[]
    for y in range(int(-r),int(r)):
        tmpcirc.append([circle(y,r),y])
    ptmpcirc=Data(tmpcirc)
    ptmpcirc.set_option_colonsep("with","l lt -0")
    return ptmpcirc

def getarc(x0,y0,ang0,ang1,r,lt):
    tmparc=[]
    for ang in range(int(min(ang0,ang1)),int(max(ang0,ang1)+1)):
        radang=pi/180.*float(ang)
        tmparc.append([x0+r*cos(radang),y0+r*sin(radang)])
    ptmparc=Data(tmparc)
    ptmparc.set_option_colonsep("with","l ls %i"%(lt))
    radang=pi/180.*(ang0+ang1)/2.
    labelpos=[x0+r*2./3.*cos(radang),y0+r*2./3.*sin(radang)]
    return ptmparc,labelpos

def getvec(x0,y0,r,ang):
    radang=pi/180.*ang
    labelpos=[x0+r/2.*cos(radang)-12.*sin(radang),y0+r/2.*sin(radang)+12.*cos(radang)]
    return [[x0,y0,r*cos(radang),r*sin(radang)]],labelpos

radius=[250,0.]

xrange=[0,400]
yrange=[-275,125]
scan=[]

dv0=130.
dv0=125.

alpha=-15.
beta=-155.
vp,vplabel=getvec(0.,0.,radius[0],alpha)
vd,vdlabel=getvec(vp[0][2],vp[0][3],dv0,beta)
#vd=[[vp[0][2],vp[0][3],va[0][2]-vp[0][2],va[0][3]-vp[0][3]]]
vax=vp[0][2]+vd[0][2]
vay=vp[0][3]+vd[0][3]
var=sqrt(vax**2+vay**2)
radius[1]=var
vaang=asin(vay/var)*180./pi
#va=[[0,0,vd[0][2]+vp[0][2],vd[0][3]+vp[0][3]]]
va,valabel=getvec(0.,0.,var,vaang)
vdsw,vdswlabel=getvec(radius[0],50.,radius[1]-radius[0],0.)
vpsw,vpswlabel=getvec(0.,75.,radius[0],0.)
vasw,vaswlabel=getvec(0.,100.,radius[1],0.)
#vdrec,vdreclabel=getvec(radius[0],25.,radius[0]*cos((180-beta+alpha)*pi/180.)+sqrt(radius[0]**2*cos((180-beta+alpha)*pi/180.)**2+radius[1]**2-radius[0]**2),0.)
vdrec,vdreclabel=getvec(radius[0],25.,dv0,0.)
vdrot,vdrotlabel=getvec(vp[0][2],vp[0][3],dv0,alpha)

pvp=Data(vp)
pvp.set_option_colonsep("with","vectors size 7,25 filled ls 10")
pva=Data(va)
pva.set_option_colonsep("with","vectors size 7,25 filled ls 11")
pvd=Data(vd)
pvd.set_option_colonsep("with","vectors size 7,25 filled ls 12")
pvdsw=Data(vdsw)
pvdsw.set_option_colonsep("with","vectors heads front size 5,90 ls 13")
pvdrec=Data(vdrec)
pvdrec.set_option_colonsep("with","vectors heads front size 5,90ls 12")
pvpsw=Data(vpsw)
pvpsw.set_option_colonsep("with","vectors heads front size 5,90 ls 10")
pvasw=Data(vasw)
pvasw.set_option_colonsep("with","vectors heads front size 5,90 ls 11")
pvdrot=Data(vdrot)
pvdrot.set_option_colonsep("with","vectors size 7,25 filled ls 17")
alphaarc,alphaarclabel=getarc(vp[0][2],vp[0][3],180,180+int(alpha),80.,15)
alphaarc2,alpha2arclabel=getarc(0,0,0,int(alpha),80.,15)
betaarc,betaarclabel=getarc(vp[0][2],vp[0][3],0,int(beta),30.,15)
gammaarc,gammaarclabel=getarc(vp[0][2],vp[0][3],int(beta),-180,50.,15)
vdarc1,b=getarc(vp[0][2],vp[0][3],int(beta),int(alpha),dv0,17)
vdarc2,b=getarc(0.,0.,int(alpha),0,radius[0]+dv0,17)


xaxis=[[xrange[0],0.,xrange[1]-xrange[0],0.]]
pxaxis=Data(xaxis)
pxaxis.set_option_colonsep("with","vectors nohead ls 15")
shxaxis=[[vp[0][2]-100.,vp[0][3],150.,0.]]
pshxaxis=Data(shxaxis)
pshxaxis.set_option_colonsep("with","vectors nohead ls 15")
yaxis=[[0.,yrange[1],0.,-(yrange[1]-yrange[0])]]
pyaxis=Data(yaxis)
pyaxis.set_option_colonsep("with","vectors nohead ls 15")
vline1,a=getvec(radius[0],0.,yrange[1],90.)
pvline1=Data(vline1)
pvline1.set_option_colonsep("with","vectors nohead ls 14")
vline2,a=getvec(radius[1],0.,yrange[1],90.)
pvline2=Data(vline2)
pvline2.set_option_colonsep("with","vectors nohead ls 14")
vline3,a=getvec(radius[0]+dv0,0.,yrange[1],90.)
pvline3=Data(vline3)
pvline3.set_option_colonsep("with","vectors nohead ls 17")
majortics=[]
for i in range(10):
    majortics.append([float(i)*50.,-5.,0.,10.])
pmajortics=Data(majortics)
pmajortics.set_option_colonsep("with","vectors nohead ls 16")
minortics=[]
for i in range(10):
    minortics.append([float(i)*50.+25.,-2.,0.,4.])
pminortics=Data(minortics)
pminortics.set_option_colonsep("with","vectors nohead ls 16")


angarr=[alpha,vaang]
for i in range(len(radius)):
    tmpscan,b=getarc(0.,0.,0.,angarr[i],radius[i],14)
    #scan.append(getarc(0.,0.,-90,90,r,0))
    scan.append(tmpscan)
scan=array(scan)

gp=Gnuplot()
gp("set xlabel 'v_{x} [km^{1}s^{-1}]'")
#gp("set ytics ('-200' '200','' '175' 1,'' '150' 1,'' '125' 1,'-100' '100','' '75' 1,'' '50' 1,'' '25' 1,'0' '0'),'' '-25' 1,'' '-50' 1,'' '-75' 1,'100' '-100','' '-125' 1,'' '-150' 1, '' '-175' 1,'200' '-200')") 
gp("set ytics ('0' '0','' '-25' 1,'50' '-50','' '-75' 1,'100' '-100','' '-125' 1,'150' '-150', '' '-175' 1,'200' '-200', '' '-225' 1,'250' '-250')") 
gp("set xtics ('0' '0','' '25' 1,'50' '50','' '75' 1,'100' '100','' '125' 1,'150' '150', '' '175' 1,'200' '200', '' '225' 1,'250' '250', '' '275' 1,'300' '300', '' '325' 1,'350' '350', '' '375' 1,'400' '400')") 
#gp("set x2tics ('0' '0','' '25' 1,'50' '50','' '75' 1,'100' '100','' '125' 1,'150' '150', '' '175' 1,'200' '200', '' '225' 1,'250' '250', '' '275' 1,'300' '300', '' '325' 1,'350' '350', '' '375' 1,'400' '400')") 
gp("set border lw 2 back")
gp("set style line 10 lt 1 lw 3 linecolor rgb 'red'")
gp("set style line 11 lt 1 lw 3 linecolor rgb 'blue'")
gp("set style line 12 lt 1 lw 3 linecolor rgb 'cyan'")
gp("set style line 13 lt 1 lw 3 linecolor rgb 'magenta'")
gp("set style line 14 lt 2 lw 3 linecolor rgb 'black'")
gp("set style line 15 lt 1 lw 3 linecolor rgb 'black'")
gp("set style line 16 lt 1 lw 4 linecolor rgb 'black'")
gp("set style line 17 lt 2 lw 3 linecolor rgb 'grey'")
#gp("set style arrow 10 size 10,20 nofilled ls 10")

gp("set size square")
gp("set yrange[%i:%i]"%(yrange[0],yrange[1]))
gp("set xrange[%i:%i]"%(xrange[0],xrange[1]))
gp("set label '{/Symbol a}' at %f,%f center" % (alphaarclabel[0],alphaarclabel[1]))
gp("set label '{/Symbol a}' at %f,%f center" % (alpha2arclabel[0],alpha2arclabel[1]))
gp("set label '{/Symbol Q}' at %f,%f center" % (betaarclabel[0],betaarclabel[1]))
#gp("set label '{/HelveticaBold= v}_{{/Symbol a}p,obs}=|{/HelveticaBold= v}_{{/Symbol a}}|-|{/HelveticaBold= v}_{p}|' at %f,%f center" % (vdswlabel[0],vdswlabel[1]))
gp("set label '{/Times-Roman=20 v}_{ip,obs}={/Times-Roman=20 v}_{i}-{/Times-Roman=20 v}_{p}' at %f,%f center" % (vdswlabel[0],vdswlabel[1]))
gp("set label '{/Symbol p}-{/Symbol Q}' at %f,%f center" % (gammaarclabel[0],gammaarclabel[1]))
gp("set label '{/TimesRomanBold=20 v}_{p}' at %f,%f center" % (vplabel[0],vplabel[1]))
#gp("set label '{/HelveticaBold= v}_{{/Symbol a}}' at %f,%f center" % (valabel[0],valabel[1]))
gp("set label '{/Times-RomanBold=20 v}_{i}}' at %f,%f center" % (valabel[0],valabel[1]))
#gp("set label '{/HelveticaBold= v}_{{/Symbol a}p}' at %f,%f center" % (vdlabel[0],vdlabel[1]))
gp("set label '{/Times-RomanBold=20 v}_{ip}' at %f,%f center" % (vdlabel[0],vdlabel[1]))
#gp("set label '|{/HelveticaBold= v}_{{/Symbol a}p}|=|{/HelveticaBold= v}_{p}|cos(180-{/Symbol Q}+{/Symbol a}){/Symbol=\261}(|{/HelveticaBold= v}_{p}|^{2}cos^{2}(180-{/Symbol Q}+{/Symbol a})+|{/HelveticaBold= v}_{{/Symbol a}}|^{2}-|{/HelveticaBold= v}_{p}|^{2})^{1/2}' at %f,%f center" % (200,-250))
gp("set label '|{/Times-RomanBold=20 v}_{ip}|={/Times-Roman=20 v}_{p}cos({/Symbol p}-{/Symbol Q}+{/Symbol a}){/Symbol=\261}({/Times-Roman=20 v}@_{i}^{2}-{/Times-Roman=20 v}@_{p}^{2}sin^{2}({/Symbol p}-{/Symbol Q}+{/Symbol a}))^{1/2}' at %f,%f center" % (200,-250))
gp("set label '{/Times-Roman=20 v}_{p}' at %f,%f center" % (vpswlabel[0],vpswlabel[1]))
#gp("set label '|{/HelveticaBold= v}_{{/Symbol a}}|' at %f,%f center" % (vaswlabel[0],vaswlabel[1]))
gp("set label '{/Times-Roman=20 v}_{i}' at %f,%f center" % (vaswlabel[0],vaswlabel[1]))
#gp("set label '|{/HelveticaBold= v}_{{/Symbol a}p}|' at %f,%f center" % (vdreclabel[0],vdreclabel[1]))
gp("set label '|{/Times-RomanBold=20 v}_{ip}|' at %f,%f center" % (vdreclabel[0],vdreclabel[1]))
#gp("set label 'e_{p}|{/HelveticaBold= v}_{{/Symbol a}}|' at %f,%f center" % (vdrotlabel[0],vdrotlabel[1]))

gp("set label '(v@_{y}^{2}+v@_{z}^{2})^{1/2} [km^{1}s^{-1}]'at screen 0.17, screen .41 center rotate by 90")
gp("set label ''at screen 0.17, screen .84 center rotate by 90")
#gp("set label center'{/HelveticaBold=9  %s}' at screen 0.3, screen 1.02"%(self.title))
gp("set size square")
gp.plot(pvdrot,vdarc2,pmajortics,pminortics,pvline1,pvline2,pvline3,pshxaxis,pvdrec,pvasw,pvpsw,pvdsw,betaarc,alphaarc,gammaarc,alphaarc2,scan[0],scan[1],pxaxis,pvp,pva,pvd)
#gp("set term postscript enhanced color lw 2 eps")
#gp("set output 'projectionscheme.eps'")
#gp("set size ratio 1")
#gp.plot(pvdrot,vdarc2,pmajortics,pminortics,pvline1,pvline2,pvline3,pshxaxis,pvdrec,pvasw,pvpsw,pvdsw,betaarc,alphaarc,gammaarc,alphaarc2,scan[0],scan[1],pxaxis,pvp,pva,pvd)

#gp("set size square")
gp.hardcopy("projectionscheme.eps",terminal="postscript",eps=True,enhanced=True,color=True)
