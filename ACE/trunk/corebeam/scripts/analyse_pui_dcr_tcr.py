from libacepy.loaddcr import loaddcr
from libacepy.loadtcr import loadtcr
from libacepy.tof2mq import tof2mq
from libacepy.swicsiondata import loadswicsiondata
from os import system
from numpy import zeros,sum,array,histogram
from Gnuplot import Gnuplot,GridData,Data
import cPickle
from os.path import isfile


year=2010
start=1
stop=366
pathdcr="/data/etph/ace/dcr/12mdata/"
pathtcr="/data/etph/ace/12mdata/"
pathpui="/data/etph/ace/pui/12mdata/"
ion="H1+"

# read He1+ para
ionposin=open("../ion_para.dat","r")
ionpara=[]
for s in ionposin:
    k=s.split()
    if k[0]==ion and float(k[1])<512:
        ionpara.append([float(k[1]),float(k[3]),float(k[7])])
ionposin.close()

def write_puidata(filename,data,aspang,cycles,vsw,year,time):
    outf=open(filename,"w")
    outf.write("Cycles  : %i\n"%(cycles))
    outf.write("Aspang  : %.2f\n"%(aspang))
    outf.write("SWSpeed : %.2f\n"%(vsw))
    outf.write("Year    : %.4i\n"%(year))
    outf.write("DoY     : %f\n"%(time))
    outf.write("*****\n")
    outf.write("vel\tw\tdcr\ttcr\n")
    for val in data:
        outf.write("%.2f\t%.2f\t%.1f\t%.1f\n"%(val[0],val[1],val[2],val[3]))
    outf.close()
    
system("mkdir %s%.4i/"%(pathpui,year))
for doy in range(start,stop+1):
    # load dcr+tcr data and fill he1data
    system("rm "+pathpui+str(year)+"/%.3i/"%(doy)+"list.in")
    listin=open(pathdcr+str(year)+"/%.3i/"%(doy)+"list.in","r")
    listin.readline()
    system("mkdir %s%.4i/%.3i"%(pathpui,year,doy))
    print year,doy
    for s in listin:
        #print s
        he1data=zeros([58,4])
        k=s.split()
        time=(float(k[0][21:24])+float(k[0][25:27])/24.+float(k[0][28:30])/(24.*60.)+float(k[0][31:33])/(24.*60.*60.))
        tmpdcr,vsw,aspang,cycles=loaddcr(pathdcr+str(year)+"/%.3i/"%(doy)+"dcr_"+k[0])
        tmptcr,vsw2=loadtcr(pathtcr+"%.4i/%.3i/"%(year,doy)+"erg_"+k[0],ion)
        #print vsw,vsw2
        if vsw==vsw2:
            for step in range(len(tmpdcr)):
                w=ionpara[step][2]/vsw
                he1data[step][0]=ionpara[step][2]
                he1data[step][1]=w
                he1data[step][2]=sum(tmpdcr[step,ionpara[step][0]-3*int(ionpara[step][1]):ionpara[step][0]+3*int(ionpara[step][1])])
                he1data[step][3]=tmptcr[step]
            listout=open(pathpui+str(year)+"/%.3i/"%(doy)+"list.in","a")
            listout.write(k[0]+"\n")
            listout.close()
            write_puidata(pathpui+"%.4i/%.3i/%s_%s"%(year,doy,ion,k[0]),he1data,aspang,cycles,vsw,year,time)



