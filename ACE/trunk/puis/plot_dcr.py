from libacepy.loaddcr import loaddcr
from libacepy.tof2mq import tof2mq
from libacepy.swicsiondata import loadswicsiondata
from os import system
from numpy import zeros,sum,array,histogram
from Gnuplot import Gnuplot,GridData,Data
import cPickle
from os.path import isfile

gp=Gnuplot()

def plotstep(step,gp=gp):
    cut1=[[210,0.1],[210,1.],[210,1e2],[210,1.e3],[210,1.e4],[210,1.e5],[210,1.e6],[210,1.e7],[210,1.e8]]
    cut2=[[408,0.1],[408,1.],[408,1e2],[408,1.e3],[408,1.e4],[408,1.e5],[408,1.e6],[408,1.e7],[408,1.e8]]

    gp("set style data lines")
    gp("set log y")
    gp("set title '%i'"%(step))
    #gp.plot(Data(tof2mq(step),dcr[step]))
    gp.plot(Data(dcr[step]),Data(cut1,with_="l lt 0"),Data(cut2,with_="l lt 0"))

def plotstepmq(step,gp=gp):
    #cut1=[[210,0.1],[210,1.],[210,1e2],[210,1.e3],[210,1.e4],[210,1.e5],[210,1.e6],[210,1.e7],[210,1.e8]]
    #cut2=[[408,0.1],[408,1.],[408,1e2],[408,1.e3],[408,1.e4],[408,1.e5],[408,1.e6],[408,1.e7],[408,1.e8]]

    gp("set style data lines")
    gp("set log y")
    gp("set title '%i'"%(step))
    gp.plot(Data(tof2mq(step),dcr[step]))
    #gp.plot(Data(dcr[step]),Data(cut1,with_="l lt 0"),Data(cut2,with_="l lt 0"))

start=1
stop=365
timeframe=[[float(start),float(stop)+1.]]
years=[2001,2002,2003,2004,2005,2006,2007,2008,2009,2010]
years=[2001,2006,2007,2008,2009,2010]
path="/data/etph/ace/dcr/12mdata/"
path2="/data/wimmer/ace/"

cpicklename="%iyeardatafast.cpi"%(len(years))
loaddump=0
dcr=zeros([58,512])

# read He1+ para
ionposin=open("../ion_para.dat","r")
he1para=[]
for s in ionposin:
    k=s.split()
    if k[0]=="He1+" and float(k[1])<512:
        he1para.append([float(k[1]),float(k[3]),float(k[7])])
ionposin.close()

he1data=zeros([len(years),365])
he1wlist=[]
wlist=[]
he1wlist2=[]
wlist2=[]
if isfile(cpicklename) and loaddump:
    inf=open(cpicklename,"r")
    dcr=cPickle.load(inf)
    inf.close()
    print cpicklename+" loaded"
else:
    ycount=0
    for year in years:
        for doy in range(start,stop+1):
            # load dcr data
            listin=open(path+str(year)+"/%.3i/"%(doy)+"list.in","r")
            listin.readline()
            print year,doy
            for s in listin:
                k=s.split()
                tmpdcr,vsw=loaddcr(path+str(year)+"/%.3i/"%(doy)+"dcr_"+k[0])
                for step in range(len(tmpdcr)):
                    if vsw>200. and he1para[step][2]/vsw>1.5 and he1para[step][2]/vsw<2.:
                        he1data[ycount][doy-1]+=sum(tmpdcr[step,he1para[step][0]-2*int(he1para[step][1]):he1para[step][0]+2*int(he1para[step][1])])
                        he1wlist.append(sum(tmpdcr[step,he1para[step][0]-2*int(he1para[step][1]):he1para[step][0]+2*int(he1para[step][1])]))
                        wlist.append(he1para[step][2]/vsw)
                if vsw>400. and vsw<500.:
                    dcr+=tmpdcr
        # load tcr data
        tmptcr=loadswicsiondata("He1+",720.,year,timeframe,path2,loadres=0,loadflux=0,loaddump=0)
        t=0
        for val in tmptcr.countspec:
            for val2 in val:
                if tmptcr.vsws[t]>200. and val2[0]/tmptcr.vsws[t]>1.5 and val2[0]/tmptcr.vsws[t]<2. and val2[1]>0.:
                    he1data[ycount][int(tmptcr.time[t])-1]+=val2[1]
                    he1wlist.append(val2[1])
                    wlist.append(val2[0]/tmptcr.vsws[t])
                    he1wlist2.append(val2[1])
                    wlist2.append(val2[0]/tmptcr.vsws[t])
            t+=1
        ycount+=1
    if loaddump:
        dumpfile=open(cpicklename,"w")
        cPickle.dump(dcr,dumpfile)
        dumpfile.close()


he1wlist=array(he1wlist)
wlist=array(wlist)
whist,wbins=histogram(wlist,bins=linspace(1.5,2,6),weights=he1wlist)
wbins=wbins[:-1]+(wbins[1]-wbins[0])/2.

he1wlist2=array(he1wlist2)
wlist2=array(wlist2)
whist2,wbins2=histogram(wlist2,weights=he1wlist2)
wbins2=wbins2[:-1]+(wbins2[1]-wbins2[0])/2.

he1data=array(he1data)
he1sum=zeros([365])
for val in he1data:
    he1sum+=val

ionlist=["H1+","He1+","3He1+","C1+","O1+"]
pionpos=[]
for ion in ionlist:
    tmpion=[]
    ionposin=open("../ion_para.dat","r")
    step=0
    for s in ionposin:
        k=s.split()
        if k[0]==ion and float(k[1])<512:
            tmpion.append([float(step),float(k[1]),0])
            step+=1
    ionposin.close()
    pionpos.append(Data(tmpion,with_="l lt -1"))
    #pionpos.append(Data(tmpion,with_="p lt -1"))


gp3=Gnuplot()
gp3.plot(Data(wbins,whist,with_="histeps"),Data(wbins2,whist2,with_="histeps lt 3"))
gp2=Gnuplot()
gp2("set style data lines")
gp2.plot(he1sum)

gp=Gnuplot()
#gp("set term postscript enhanced color 18 lw 2 eps")
#gp("set output 'fouryears.ps'")
#gp("set multiplot")
#gp.splot(pionpos[0],pionpos[1],pionpos[2],pionpos[3])
gp("set pm3d map at b corners2color c1")
gp("set log cb")
gp("set cbrange[.1:]")
#gp("set cbrange[1e2:]")
#gp("set palette model RGB functions gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 1 , gray<1.e-20 ? 1 : gray<0.5 ? gray*2 : 2-gray*2, gray <1.e-20 ? 1 : gray<0.5 ? 1-sqrt(gray*2) : 0")
gp("set xrange[0:57]")
gp("set yrange[0:500]")
#gp.splot(GridData(dcr),pionpos[0],pionpos[1],pionpos[2],pionpos[3],pionpos[4])
gp.splot(GridData(dcr),*pionpos)
gp.hardcopy("10years.ps",color="True")
#gp("set surface")
#gp("set clabel '%0.0f'")
#gp("unset contour")
#gp("unset pm3d")
#gp("unset log z")
#gp("set zrange[0.5:1.5]")
#gp.splot(pionpos[0],pionpos[1],pionpos[2],pionpos[3])
