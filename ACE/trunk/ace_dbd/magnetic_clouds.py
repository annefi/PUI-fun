from numpy import *
from ace_utils import calc_day00
fin=open("2012-09-03-ACE_MC_listII.dat","r")
fin.readline()

dpm=array([31.,28.,31.,30.,31.,30.,31.,31.,30.,31.,30.,31.])
dpml=array([31.,29.,31.,30.,31.,30.,31.,31.,30.,31.,30.,31.])

d00list=[]
doylist=[]
yearlist=[]
for s in fin:
    k=s.split()
    startyear,startmonth,startday=k[0].split("-")
    starthour=k[1]
    stopyear,stopmonth,stopday=k[2].split("-")
    stophour=k[3]
    stadoy=0.
    stodoy=0.
    for i in range(int(startmonth)-1):
        if int(startyear)%4:
            stadoy+=dpm[i]
        else:
            stadoy+=dpml[i]
    stadoy+=float(startday)
    stadoy+=float(starthour[:2])/24.
    for i in range(int(stopmonth)-1):
        if int(stopyear)%4:
            stodoy+=dpm[i]
        else:
            stodoy+=dpml[i]
    stodoy+=float(stopday)
    stodoy+=float(stophour[:2])/24.
    stad00=calc_day00(array([[int(startyear)]]),array([[stadoy]]))
    stod00=calc_day00(array([[int(stopyear)]]),array([[stodoy]]))
    d00list.append([stad00[0],stod00[0]])
    doylist.append([stadoy,stodoy])
    yearlist.append([float(startyear),float(stopyear)])
    print k
    print startyear,stadoy,stodoy,stad00[0],stod00[0]
