#!/usr/bin/python
from scipy import sqrt,zeros
from numpy import float
from libacepy.lv2data import lv2data
from sys import argv

liste=open("pathlist.in")
for p in liste:
    k=p.split()
    path=k[0]
#ion_list=["He2+","He1+","C4+","C5+","C6+","13C6+","N5+","N6+","N7+","O5+","O6+","O7+","O8+","Ne8+","Ne7+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+","Si5+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+","S5+","S6+","S7+","S8+","S9+","S10+","S11+","S12+","Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+","Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+"]
#    ion_list=["O5+","O6+","O7+","O8+","Ne7+","Ne8+","N5+","N6+","N7+","C4+","C5+","C6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+","Fe18+","Fe19+","Fe20+","Fe21+","Fe22+","Fe23+","Fe24+"]
    ion_list=["He2+","C4+","C5+","C6+","N5+","N6+","N7+","O4+","O5+","O6+","O7+","O8+","Ne7+","Ne8+","Ne9+","Ne10+","Mg5+","Mg6+","Mg7+","Mg8+","Mg9+","Mg10+","Mg11+","Mg12+","Si6+","Si7+","Si8+","Si9+","Si10+","Si11+","Si12+","Si13+","Si14+","S5+","S6+","S7+","S8+","S9+","S10+","S11+","S12+","S13+","S14+","Ca6+","Ca7+","Ca8+","Ca9+","Ca10+","Ca11+","Ca12+","Ca13+","Ca14+","Ca15+","Ca16+","Ca17+","Ca18+","Ca19+","Ca20+","Fe5+","Fe6+","Fe7+","Fe8+","Fe9+","Fe10+","Fe11+","Fe12+","Fe13+","Fe14+","Fe15+","Fe16+","Fe17+","Fe18+","Fe19+","Fe20+","Fe21+","Fe22+","Fe23+","Fe24+","Fe25+","Fe26+"]
    """
    filelist=open(path+"list.in")
    s=filelist.readline()    
    for s in filelist:
        k=s.split()
        print "k=",k
        data=lv2data(path,k[0],ion_list)
        data.calcfromlv1()
        data.write()
    """
    data=lv2data(path,argv[1],ion_list)
    data.calcfromlv1()
    data.write()
    
