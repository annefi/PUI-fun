#!/usr/bin/python
from libacepy.lv1data import lv1data
ion_list=["Fe17+"]
paraname="./ion_para.dat"
counts=[10.,100.]
frac=[0.,0.1,1.,10.,100.]
steps=[1,5,10,15,20,25,30,35,40,45,50,55]

for step in steps:
    for ion in ion_list:
        for tmpcounts in counts:
            for tmpfrac in frac:
                testdata=lv1data(paraname)
                testdata.readionpara()
                testdata.writeerrorpara(ion,step-1,200,tmpcounts,tmpfrac)
