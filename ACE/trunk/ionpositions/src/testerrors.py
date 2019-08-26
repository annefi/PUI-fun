#!/usr/bin/python
from libacepy.lv1data import lv1data

paraname="/home/ivar/berger/projects/ionpositions/ion_para.dat"
testdata=lv1data(paraname)
testdata.readionpara()
testdata.writeerrorpara("O6+",30,1000,500.,0.1)
print testdata.overlapplist
