from Gnuplot import Gnuplot,Data,GridData
from numpy import *

def extractdcr(etname):
    datain=open(etname,"r")
    outname="dcr_"+etname
    dataout=open(outname,"w")

    #copyheader
    k=["dummy"]
    while k[0]!="*****":
        s=datain.readline()
        dataout.write(s)
        k=s.split()

    dcr=zeros([58,512])
    for step in range(58):
        s=datain.readline()
        s=datain.readline()
        k=s.split()
        for i,val in enumerate(k):
            dcr[step,i]=float(val)
        for i in range(127):
            s=datain.readline()


    step,tof=nonzero(dcr)
    dcrcounts=dcr[step,tof]
    save=zeros([3,len(step)])
    save[0]=step
    save[1]=tof
    save[2]=dcrcounts
    savetxt(dataout,save,fmt='%.1f')
    """
    for i in range(len):
        for val in dcr[step]:
            dataout.write("%f "%(val))
        dataout.write("\n")
    """
    dataout.close()
    datain.close()
    return dcr

"""
dcr=extractdcr("axlv2_et_slices_2003_018_23.52.56_2003_019_00.04.56.dat")
gp=Gnuplot()
gp("set pm3d map corners2color c1")
gp("set cbrange[0.1:%f]"%(amax(dcr)))
gp("set log cb")
gp.splot(GridData(dcr))
"""
