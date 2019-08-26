#!/usr/bin/python
from sys import stdin
#from libacepy.lv1data import lv1data
from scipy import zeros
from numpy import float
from Gnuplot import Gnuplot,Data

"""
function : returns position of ion in given step
input
lv1data : class lv1data
ionname : name of ion
step : defines step
"""
def getionpos(lv1data,ionname,step):
    ionpos=0
    for ion in range(len(lv1data.name[step])):
        if (lv1data.name[step][ion]==ionname):
            ionpos=ion
    return ionpos

def overlapplist(lv1data,ionname,step):
    lv1data.overlapplist.append(ionname)
    ionpos=getionpos(lv1data,ionname,step)
    orng=2.
    for ion in range(len(lv1data.name[step])):
        if ((lv1data.xpos[step][ion]+orng*lv1data.sigxp[step][ion]>lv1data.xpos[step][ionpos]-orng*lv1data.sigxm[step][ionpos])and(lv1data.xpos[step][ion]-orng*lv1data.sigxm[step][ion]<lv1data.xpos[step][ionpos]+orng*lv1data.sigxp[step][ionpos])and(lv1data.ypos[step][ion]+orng*lv1data.sigyp[step][ion]>lv1data.ypos[step][ionpos]-orng*lv1data.sigym[step][ionpos])and(lv1data.ypos[step][ion]-orng*lv1data.sigym[step][ion]<lv1data.ypos[step][ionpos]+orng*lv1data.sigyp[step][ionpos])):
            if (ion!=ionpos):
                lv1data.overlapplist.append(lv1data.name[step][ion])


def gethistogram(error):
    for ion in range(len(error.name)):
        maxval=int(max(error.normerg[ion])+1.5)
        minval=int(max(0.,min(error.normerg[ion])-.5))
        dim=maxval-minval+1
        tmphist=[]
        for i in range(dim):
            tmphist.append([minval+i,0])
        for val in error.normerg[ion]:
            for i in range(len(tmphist)):
                if (int(val+0.5)==tmphist[i][0]):
                    tmphist[i][1]+=1
        error.histogram.append(tmphist)


