from libacepy.swicsdcrtcr import swicsdcrtcr
from libacepy.swicsiondata import loadswicsiondata
from libacepy.swepamdata import swepamdata
from libacepy.mag import magdata
from pylib.etTools import fftPlot
from numpy import cos,arccos,pi,amax,arange,array,sqrt,mean,sum,histogram,linspace,isnan,isinf,zeros
from Gnuplot import Gnuplot,Data

year=2001
timeframe=[[325.,327.]]
timeframe=[[146.62775,146.62775+1./120.]]
timeframe=[[167.,168.]]
timeframe=[[222,223.]]
timeframe=[[39.,40.]]
timeframe=[[4.,5.]]
timeframe=[[153.,155.]]
timeframe=[[32.,34.]]
#year=2008
#timeframe=[[20.,22.]]

hdata=swicsdcrtcr("H1+",year,timeframe,"/data/etph/ace/pui/12mdata/")
hedata=loadswicsiondata("He2+",720.,year,timeframe,"/data/etph/ace/")
odata=loadswicsiondata("O6+",720.,year,timeframe,"/data/etph/ace/")
fedata=loadswicsiondata("Fe9+",720.,year,timeframe,"/data/etph/ace/")
sidata=loadswicsiondata("C6+",720.,year,timeframe,"/data/etph/ace/")
cdata=loadswicsiondata("Fe8+",720.,year,timeframe,"/data/etph/ace/")
swdata=swepamdata(64.,year,timeframe,"/data/etph/ace/swepam/")
magdat=magdata(1.,year,timeframe,"/data/etph/ace/mag/")
#magdat.sync_mag(hedata)

#gp=Gnuplot()
def get_tseries(iond):
    from numpy import where,mean
    timestep=12./86400.    # time of single esa-step
    d3iondata=[]
    d3ionv=[]
    for i in range(len(iond.time)):
        ionmax=amax(iond.countspec[i,:,1])
        vtime=0.
        for j in range(58):
            #d3iondata.append([iond.time[i]-(58-j)*timestep,iond.countspec[i,j,0],iond.countspec[i,j,1]/ionmax])
            if iond.countspec[i,j,1]>=1.:
                #d3iondata.append([iond.time[i]-(58-j)*timestep,iond.countspec[i,j,0],iond.countspec[i,j,1]/ionmax])
                d3iondata.append([iond.time[i]+(j+1)*timestep,iond.countspec[i,j,0],iond.countspec[i,j,1]/ionmax])
            else:
                d3iondata.append([iond.time[i]+(j+1)*timestep,iond.countspec[i,j,0],0.])
                #d3iondata.append([iond.time[i]-(58-j)*timestep,iond.countspec[i,j,0],0.])
            if d3iondata[-1][2]==1.:
                vtime=d3iondata[-1][0]
        mask=iond.countspec[i,:,1]>0.1*ionmax
        tmpcspec=iond.countspec[i]
        vion=mean(tmpcspec[mask][:,0]*tmpcspec[mask][:,1])/mean(tmpcspec[mask][:,1])
        vion=iond.vel[i]
        #vion=mean(iond.countspec[mask][i,:,0]*iond.countspec[mask][i,:,1])/mean(iond.countspec[mask][i,:,1])
        if vtime>0.:
            d3ionv.append([vtime,vion,1.])
    d3iondata=array(d3iondata)
    d3ionv=array(d3ionv)
    return d3iondata[~isnan(d3iondata[:,2])],d3ionv[~isnan(d3ionv[:,1])]


def get_tseriestcrdcr(iond):
    from numpy import where,mean
    timestep=12./86400.    # time of single esa-step
    d3iondata=[]
    d3ionv=[]
    d3ionv2=[]
    for i in range(len(iond.time)):
        ionmax=amax(iond.dcrspec[i]+iond.tcrspec[i])
        vtime=0.
        for j in range(58):
            #d3iondata.append([iond.time[i]-(58-j)*timestep,iond.velspec[j],(iond.dcrspec[i,j]+iond.tcrspec[i,j])/ionmax])
            d3iondata.append([iond.time[i]+(j+1)*timestep,iond.velspec[j],(iond.dcrspec[i,j]+iond.tcrspec[i,j])/ionmax])
            if d3iondata[-1][2]==1.:
                vtime=d3iondata[-1][0]
                vion2=iond.velspec[j]
        mask=(iond.dcrspec[i]+iond.tcrspec[i])>0.1*ionmax
        tmpcspec=iond.dcrspec[i]+iond.tcrspec[i]
        vion=mean(iond.velspec[mask]*tmpcspec[mask])/mean(tmpcspec[mask])
        #vion=mean(iond.countspec[mask][i,:,0]*iond.countspec[mask][i,:,1])/mean(iond.countspec[mask][i,:,1])
        if vtime>0.:
            d3ionv.append([vtime,vion,1.])
            d3ionv2.append([vtime,vion2,1.])
    d3iondata=array(d3iondata)
    d3ionv=array(d3ionv)
    d3ionv2=array(d3ionv2)
    return d3iondata[~isnan(d3iondata[:,1])],d3ionv[~isnan(d3ionv[:,1])],d3ionv2[~isnan(d3ionv2[:,1])]


theta=arccos(cos(magdat.phi)*cos(magdat.theta))
timestep=12./86400.

d3swdata=[]
d3swdens=[]
valf=[]
vswvalf=[]
tsts=len(swdata.time)
for i in range(0,tsts):
    d3swdata.append([swdata.time[i],swdata.vel[i],1.])
    d3swdens.append([swdata.time[i],swdata.dens[i],1.])
    valf.append([swdata.time[i],21.8/sqrt(swdata.dens[i])*mean(magdat.magb[(magdat.time>swdata.time[i])*(magdat.time<swdata.time[i]+64./86400.)])])
    vswvalf.append([swdata.time[i],21.8/sqrt(swdata.dens[i])*mean(magdat.magb[(magdat.time>swdata.time[i])*(magdat.time<swdata.time[i]+64./86400.)])*cos(mean(theta[(magdat.time>swdata.time[i])*(magdat.time<swdata.time[i]+64./86400.)]))+swdata.vel[i]])

valf=array(valf)
valf[isinf(valf)]=0.
#3dhdata=zeros([58*tsts,3])
#d3hdata,d3hv=get_tseries(hdata)

d3hdata=[]

tsts=len(hdata.time)
for i in range(0,tsts):
    for j in range(58):
        d3hdata.append([hdata.time[i]+(j+1.)*timestep,hdata.velspec[j],hdata.dcrspec[i,j]/amax(hdata.dcrspec[i])])

d3hdata,d3hv,d3hv2=get_tseriestcrdcr(hdata)
d3hedata,d3hev=get_tseries(hedata)
d3odata,d3ov=get_tseries(odata)
d3fedata,d3fev=get_tseries(fedata)
d3sidata,d3siv=get_tseries(sidata)
d3cdata,d3cv=get_tseries(cdata)


"""
dvxy1=[]
dvxy2=[]
dvcts=[]
for i in range(len(hedata.time)):
#for i in range(len(hdata.time)):
    maxc=amax(hedata.countspec[i,:,1])
    tmpc=hedata.countspec[i,0,1]
    #maxc=amax(hdata.dcrspec[i])
    #tmpc=hdata.dcrspec[i,0]
    step=0
    while tmpc<0.1*maxc:
        step+=1
        tmpc=hedata.countspec[i,step,1]
        #tmpc=hdata.dcrspec[i,step]
    if step>0:
        tmptime=hedata.time[i]+(12./86440.)*float(step)
        #tmptime=hdata.time[i]+(12./86440.)*float(step)
        magx=mean(magdat.magbx[(magdat.time>tmptime)*(magdat.time<tmptime+64./86400.)])
        magy=mean(magdat.magby[(magdat.time>tmptime)*(magdat.time<tmptime+64./86400.)])
        magz=mean(magdat.magbz[(magdat.time>tmptime)*(magdat.time<tmptime+64./86400.)])
        #print magx,magy,magz
        magnorm=sqrt(magx**2+magy**2+magz**2)
        magx/=magnorm
        magy/=magnorm
        magz/=magnorm
        tmpvalf=valf[(valf[:,0]>tmptime)*(valf[:,0]<tmptime+64./86400.)][:,1]
        vswx=swdata.velx[(swdata.time>tmptime)*(swdata.time<tmptime+64./86400.)]
        vswy=swdata.vely[(swdata.time>tmptime)*(swdata.time<tmptime+64./86400.)]
        vswz=swdata.velz[(swdata.time>tmptime)*(swdata.time<tmptime+64./86400.)]
        #print vswx,vswy,vswz
        if len(vswy)>0 and len(vswz)>0 and len(tmpvalf)>0:
            magx*=.55*tmpvalf[0]
            magy*=.55*tmpvalf[0]
            magz*=.55*tmpvalf[0]
            vswy=vswy[0]
            vswz=vswz[0]
            #print vswy,vswz,magy,magz
            if vswy!=0. and vswz!=0.:
                dvcts.append(sum(hedata.countspec[i,:,1]))
                #dvcts.append(sum(hdata.dcrspec[i,:]))
                dvxy1.append(sqrt((vswy+magy)**2+(vswz+magz)**2))
                dvxy2.append(sqrt((vswy-magy)**2+(vswz-magz)**2))
                #dvxy1.append(sqrt((vswy)**2+(vswz)**2))
                #dvxy2.append(sqrt((vswy)**2+(vswz)**2))
        
dvxy1=array(dvxy1)
dvxy2=array(dvxy2)
dvcts=array(dvcts)


dvxy1h,dvxybins=histogram(dvxy1,linspace(0.,100.,21.),weights=dvcts)
dvxy2h,dvxybins=histogram(dvxy2,linspace(0.,100.,21.),weights=dvcts)
dvxy1hn,dvxybins=histogram(dvxy1,linspace(0.,100.,21.))
dvxy2hn,dvxybins=histogram(dvxy2,linspace(0.,100.,21.))
dvxy1h/=dvxy1hn
dvxy2h/=dvxy2hn
dvxy1h[isnan(dvxy1h)]=0.
dvxy2h[isnan(dvxy2h)]=0.
gp5=Gnuplot()
gp5.plot(Data(dvxybins[:-1],dvxy1h,with_="steps lt 1"),Data(dvxybins[:-1],dvxy2h,with_="steps lt 3"))
#raw_input()
"""

swevecs=[]
magvecs=[]
vecstime=[]
points1=[]
points2=[]
points3=[]
for i in range(len(swdata.time)):
    vecstime.append(swdata.time[i])
    swevecs.append([0.,0.,0.,swdata.velx[i],swdata.vely[i]+0.,swdata.velz[i]])
    magx=mean(magdat.magbx[(magdat.time>swdata.time[i]-0./86400.)*(magdat.time<swdata.time[i]+64./86400.)])
    magy=mean(magdat.magby[(magdat.time>swdata.time[i]-0./86400.)*(magdat.time<swdata.time[i]+64./86400.)])
    magz=mean(magdat.magbz[(magdat.time>swdata.time[i]-0./86400.)*(magdat.time<swdata.time[i]+64./86400.)])
    magnorm=sqrt(magx**2+magy**2+magz**2)
    magx/=magnorm
    magy/=magnorm
    magz/=magnorm
    magx*=.55*valf[i][1]
    magy*=.55*valf[i][1]
    magz*=.55*valf[i][1]
    #magx*=20.
    #magy*=20.
    #magz*=20.
    magvecs.append([swdata.velx[i],swdata.vely[i]+0.,swdata.velz[i],magx,magy,magz])
    points1.append([swdata.velx[i]+magx,swdata.vely[i]+magy,swdata.velz[i]+magz])
    points2.append([swdata.velx[i]+magx,swdata.vely[i]-magy,swdata.velz[i]-magz])
    points3.append([swdata.velx[i],swdata.vely[i],swdata.velz[i]])




swevecs=array(swevecs)
magvecs=array(magvecs)
vecstime=array(vecstime)
points1=array(points1)
points2=array(points2)
points3=array(points3)


d3hdata=array(d3hdata)
d3hedata=array(d3hedata)
d3odata=array(d3odata)
d3fedata=array(d3fedata)
d3sidata=array(d3sidata)
d3cdata=array(d3cdata)
d3swdata=array(d3swdata)
d3swdens=array(d3swdens)
valf=array(valf)
vswvalf=array(vswvalf)
gp=Gnuplot()
gp2=Gnuplot()
#gp("set zrange[0.1:1]")
gp("set yrange[300:900]")
gp("set xlabel 'T'")
gp("set ylabel 'V'")
#gp("set zlabel 'NCts'")
gp("set style data lines")
gp("set y2tics")
gp2("set yrange[0:pi]")
gp2("set xlabel 'T'")
gp2("set ylabel 'Theta'")
gp2("set style data lines")
gp2("set y2tics")
gp3=Gnuplot()
gp3("set xrange[300:700]")
gp3("set ylabel 'vy'")
gp3("set zlabel 'vz'")
gpfft=Gnuplot()
gpfft("set log xy")
gpfft("set style data lines")
gpvdf=Gnuplot()
gpvdf("set xlabel 'v [km/s]'")
gpvdf("set ylabel 'Counts/Max(Counts)'")
gpvdf("set mxtics 5")
gpvdf("set mytics 10")
def plot_vdf(t1,t2):
    meanvalf=mean(valf[(valf[:,0]>t1)*(valf[:,0]<t2)*(valf[:,1]>0.)][:,1])
    meanvsw=mean(swdata.vel[(swdata.time>t1)*(swdata.time<t2)*(swdata.vel>0.)])
    gpvdf.plot(Data(d3hdata[(d3hdata[:,0]>t1)*(d3hdata[:,0]<t2)][:,1],d3hdata[(d3hdata[:,0]>t1)*(d3hdata[:,0]<t2)][:,2],with_="l lt 1 lw 3",title="H^{1+}"),Data(d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)][:,1],d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)][:,2],with_="l lt 3 lw 3",title="He^{2+}"),Data(d3odata[(d3odata[:,0]>t1)*(d3odata[:,0]<t2)][:,1],d3odata[(d3odata[:,0]>t1)*(d3odata[:,0]<t2)][:,2],with_="l lt 4 lw 3",title="O^{6+}"),Data([[meanvsw,0.],[meanvsw,1.]],with_="l lt -1 lw 2"),Data([[meanvsw+meanvalf,0.],[meanvsw+meanvalf,1.]],with_="l lt 0 lw 2"),Data([[meanvsw+2.*meanvalf,0.],[meanvsw+2.*meanvalf,1.]],with_="l lt 0 lw 2"),Data([[meanvsw-meanvalf,0.],[meanvsw-meanvalf,1.]],with_="l lt 0 lw 2"),Data([[meanvsw-2.*meanvalf,0.],[meanvsw-2.*meanvalf,1.]],with_="l lt 0 lw 2"))

def plot_period(t1,t2,off=1,power=5./3.):
    gp("set xrange[%f:%f]"%(t1,t2))
    gp2("set xrange[%f:%f]"%(t1,t2))
    #gp.splot(d3hdata[(d3hdata[:,0]>t1)*(d3hdata[:,0]<t2)],d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)],d3odata[(d3odata[:,0]>t1)*(d3odata[:,0]<t2)],d3fedata[(d3fedata[:,0]>t1)*(d3fedata[:,0]<t2)],d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)*(d3hedata[:,2]==1.)],d3odata[(d3odata[:,0]>t1)*(d3odata[:,0]<t2)*(d3odata[:,2]==1.)],d3fedata[(d3fedata[:,0]>t1)*(d3fedata[:,0]<t2)*(d3fedata[:,2]==1.)],d3hdata[(d3hdata[:,0]>t1)*(d3hdata[:,0]<t2)*(d3hdata[:,2]==1.)],d3swdata[d3swdata[:,1]>0.])
    #gp.splot(d3hdata[(d3hdata[:,0]>t1)*(d3hdata[:,0]<t2)],d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)],d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)],d3hev)    #gp.splot(d3hev,d3ov,d3fev,d3swdata[d3swdata[:,1]>0.])
    #gp.plot(Data(d3hv[:,0],d3hv[:,1],with_="lp lt -1"),Data(d3hv2[:,0],d3hv2[:,1],with_="lp lt 0"),Data(d3hev[:,0],d3hev[:,1],with_="lp lt 1"),Data(d3ov[:,0],d3ov[:,1],with_="lp lt 3"),Data(d3fev[:,0],d3fev[:,1],with_="lp lt 4"),Data(d3swdata[d3swdata[:,1]>0.][:,0],d3swdata[d3swdata[:,1]>0.][:,1],with_="lp lt 5"))#,Data(d3swdens[d3swdens[:,1]>0.][:,0],d3swdens[d3swdens[:,1]>0.][:,1],with_="lp lt 6",axes="x1y2"))
    #gp2.plot(Data(magdat.time,theta,with_="l lt 1"),"pi/2. w l lt -1",Data(d3swdata[:,0],((d3swdata[:,1]-550.)/20.)-1.),Data(vswvalf[:,0],vswvalf[:,1],with_="l lt 4",axes="x1y2"),Data(d3swdata[:,0],d3swdata[:,1],with_="l lt 5",axes="x1y2"))
    gp2.plot(Data(magdat.time,theta,with_="l lt 1"),"pi/2. w l lt -1",Data(valf[:,0],valf[:,1],with_="l lt 3",axes="x1y2"))
    #gp2.hardcopy("magdata.eps",eps=True,color=True)
    gpfft("f(x)=%f*x**-(%f)"%(off,power))
    psdy=fftPlot(magdat.magby[(magdat.time>t1)*(magdat.time<t2)])
    psdz=fftPlot(magdat.magbz[(magdat.time>t1)*(magdat.time<t2)])
    psdx=fftPlot(magdat.magbx[(magdat.time>t1)*(magdat.time<t2)])
    meanvalf=mean(valf[(valf[:,0]>t1)*(valf[:,0]<t2)*(valf[:,1]>0.)][:,1])
    meanvsw=mean(swdata.vel[(swdata.time>t1)*(swdata.time<t2)*(swdata.vel>0.)])
    gp.splot(d3hdata[(d3hdata[:,0]>t1)*(d3hdata[:,0]<t2)],d3hedata[(d3hedata[:,0]>t1)*(d3hedata[:,0]<t2)],d3odata[(d3odata[:,0]>t1)*(d3odata[:,0]<t2)],d3fedata[(d3fedata[:,0]>t1)*(d3fedata[:,0]<t2)],d3sidata[(d3sidata[:,0]>t1)*(d3sidata[:,0]<t2)],d3cdata[(d3cdata[:,0]>t1)*(d3cdata[:,0]<t2)],d3hv,d3hev,d3ov,d3fev,d3swdata[d3swdata[:,1]>0.],Data([[(t1+t2)/2.,meanvsw,0.],[(t1+t2)/2.,meanvsw,1.]],with_="l lt -1"),Data([[(t1+t2)/2.,meanvsw+meanvalf,0.],[(t1+t2)/2.,meanvsw+meanvalf,1.]],with_="l lt 0"),Data([[(t1+t2)/2.,meanvsw+2*meanvalf,0.],[(t1+t2)/2.,meanvsw+2*meanvalf,1.]],with_="l lt 0"),Data([[(t1+t2)/2.,meanvsw-1*meanvalf,0.],[(t1+t2)/2.,meanvsw-1*meanvalf,1.]],with_="l lt 0"),Data([[(t1+t2)/2.,meanvsw-2*meanvalf,0.],[(t1+t2)/2.,meanvsw-2*meanvalf,1.]],with_="l lt 0"))
    #gp.hardcopy("tsspecs.eps",eps=True,color=True)
    gfe=mean(magdat.magb[(magdat.time>t1)*(magdat.time<t2)])*28.*(1+meanvsw/meanvalf)
    gfp=mean(magdat.magb[(magdat.time>t1)*(magdat.time<t2)])*0.01525*abs(1-meanvsw/meanvalf)
    gfhe=gfp*0.5
    gfo=gfp*6./16.
    gfhep=gfhe/0.5
    gfhem=gfhe/1.5
    gfop=gfo/0.5
    gfom=gfo/1.5
    gffe=gfp*12./56.
    gfsi=gfp*9./28.
    gfpu=gfp*0.25
    #gfp=0.5-(gfp-0.5)
    #print "wp =",gfp,"whe =",gfhe,"wo =",gfo,"wsi =",gfsi,"wfe =",gffe,"wpu =",gfpu
    print "whe =",gfhe,"whe =",gfhem,"whep =",gfhep
    print "vsw =",meanvsw,"valf =",meanvalf
    psdy=array(psdy)
    #psdy[:,1]=(psdy[:,1]/(off*psdy[:,0]**-power))
    psdz=array(psdz)
    psdx=array(psdx)
    #psdz[:,0]/=abs(1-meanvsw/meanvalf)
    #psdy[:,0]/=abs(1-meanvsw/meanvalf)
    #psdx[:,0]/=abs(1-meanvsw/meanvalf)
    fmax=meanvalf/2/meanvsw
    print "fmax = ",fmax
    #psdz[:,1]=(psdz[:,1]/(off*psdz[:,0]**-power))
    bw=5
    psdyb=zeros([len(psdy)/bw,2])
    for i in range(len(psdy)/bw):
        psdyb[i,0]=mean(psdy[i*bw:i*bw+bw,0])
        psdyb[i,1]=mean(psdy[i*bw:i*bw+bw,1])
    psdzb=zeros([len(psdz)/bw,2])
    for i in range(len(psdz)/bw):
        psdzb[i,0]=mean(psdz[i*bw:i*bw+bw,0])
        psdzb[i,1]=mean(psdz[i*bw:i*bw+bw,1])
    psdxb=zeros([len(psdx)/bw,2])
    for i in range(len(psdx)/bw):
        psdxb[i,0]=mean(psdx[i*bw:i*bw+bw,0])
        psdxb[i,1]=mean(psdx[i*bw:i*bw+bw,1])
    #gpfft.plot(Data(psdxb,with_="l lt 5",title="'Bx'"),Data(psdyb,with_="l lt 1",title="'By'"),Data(psdzb,with_="l lt 3",title="'Bz'"),"f(x) with l lt 4 title 'x^-(5/3)'",Data([[gfp,1.],[gfp,1e4]],with_="l lt -1",title="'gfp'"),Data([[gfhe,1.],[gfhe,1e4]],with_="l lt 0",title="'gfhe'"),Data([[gfo,1.],[gfo,1e4]],with_="l lt 1",title="'gfo'"),Data([[gffe,1.],[gffe,1e4]],with_="l lt 3",title="'gffe'"))#,Data([[gfe,1.],[gfe,1e4]],with_="l lt 6",title="'gfe'"))
    gpfft.plot(Data(psdxb,with_="l lt 5",title="'Bx'"),Data(psdyb,with_="l lt 1",title="'By'"),Data(psdzb,with_="l lt 3",title="'Bz'"),"f(x) with l lt 4 title 'x^-(5/3)'",Data([[gfhe,1.],[gfhe,1e4]],with_="l lt -1",title="'gfhe'"),Data([[gfhem,1.],[gfhem,1e4]],with_="l lt 0",title="'gfhem'"),Data([[gfhep,1.],[gfhep,1e4]],with_="l lt 0",title="'gfhep'"),Data([[gfop,1.],[gfop,1e4]],with_="l lt 3",title="'gfop'"),Data([[gfom,1.],[gfom,1e4]],with_="l lt 3",title="'gfom'"),Data([[gfo,1.],[gfo,1e4]],with_="l lt 1",title="'gfo'"),Data([[gfp,1.],[gfp,1e4]],with_="l lt 4",title="'gfp'"))
    #gpfft.hardcopy("wavepowerspec.eps",eps=True,color=True)

def plot_vecs(t1,t2):
    gp3.splot(Data(magvecs[(vecstime>t1)*(vecstime<t1+64./86400.)],with_="vectors lt 3"))
    te=t1+64./86400.
    while te<t2:
        print te
        gp3.splot(Data(magvecs[(vecstime>t1)*(vecstime<te)],with_="vectors lt 3"))
        print sqrt((magvecs[(vecstime>te-64./86440)*(vecstime<te)][:,0]+magvecs[(vecstime>te-64./86440)*(vecstime<te)][:,3])**2+(magvecs[(vecstime>te-64./86440)*(vecstime<te)][:,1]+magvecs[(vecstime>te-64./86440)*(vecstime<te)][:,4])**2+(magvecs[(vecstime>te-64./86440)*(vecstime<te)][:,2]+magvecs[(vecstime>te-64./86440)*(vecstime<te)][:,5])**2),hedata.vel[(hedata.time>te-64./86440.)*(hedata.time<te+656./86400.)],sqrt(swdata.velx[(swdata.time>te-64./86440.)*(swdata.time<te)]**2+(swdata.vely[(swdata.time>te-64./86440.)*(swdata.time<te)]+30.)**2+swdata.velz[(swdata.time>te-64./86440.)*(swdata.time<te)]**2)
        te+=64./86400.
        raw_input()
#gp3.splot(Data(swevecs[(vecstime>t1)*(vecstime<t2)],with_="vectors lt 1"),Data(magvecs[(vecstime>t1)*(vecstime<t2)],with_="vectors lt 3"))

#gp3=Gnuplot()
#gp3.splot(Data(swevecs,with_="vectors lt 1"),Data(magvecs,with_="vectors lt 3"))

#gp4=Gnuplot()
#def plot_points(t1,t2):
#    gp4.splot(Data(points3[(vecstime>t1)*(vecstime<t2)],with_="p lt 1"),Data(points2[(vecstime>t1)*(vecstime<t2)],with_="p lt 3"))
