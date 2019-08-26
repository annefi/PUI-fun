#!/usr/bin/python
from scipy import sqrt,zeros
from numpy import float
from libacepy.ancil import ion2elem,ionname2charge
from random import Random

"""
function : returns a table containing the fraction of each charge state of a given element at several temperatures (tables are from Mazotta et al)
"""
def readtable(elemname):
    infile=open("/home/ivar/berger/projects/ionpositions/freezein/"+elemname+".tab")
    table=[]
    for s in infile:
        k=s.split()
        tmpdat=[]
        for i in range(len(k)-1):
            if (float(k[i+1])!=99.999):
                tmpdat.append(10.**float(k[i+1]))
            else:
                tmpdat.append(10.**-15.)
        table.append(tmpdat)
    return table


def linint(table,frac,charge,lval):
    temp=0.
    a=(table[lval+1][charge+1]-table[lval][charge+1])/(table[lval+1][0]-table[lval][0])
    if (a!=0.):
        temp=((frac-table[lval][charge+1])/a)+table[lval][0]
    return temp

def linint2(table,charge,lval,step):
    frac=0.
    a=(table[lval+1][charge+1]-table[lval][charge+1])/(table[lval+1][0]-table[lval][0])
    frac=a*(table[lval+1][0]-table[lval][0])*0.1*float(step)+table[lval][charge+1]
    temp=(table[lval+1][0]-table[lval][0])*0.1*float(step)+table[lval][0]
    retval=[temp,frac]
    return retval

def getminxsq(table):
    min=0
    minval=table[0][1]
    for i in range(len(table)):
        if (table[i][1]<minval):
            minval=table[i][1]
            min=i
    retval=[min,table[min][0],minval]
    return retval

def getfreezintemp(chisq):
    minval=0
    for i in range(len(chisq)):
        if (chisq[i][1]<chisq[minval][1]):
            minval=i
    return chisq[minval][0]

def gettemp(table,charge,frac):
    lborder=[0,0]
    temp=[0.,0.]
    border=0
    for i in range(len(table)):
        if ((table[i][charge+1]<=frac) and (border==0)):
            lborder[0]=i
        if ((table[i][charge+1]>frac) and (border==0)):
            border=1
        if ((table[i][charge+1]>=frac) and (border==1)):
            lborder[1]=i
    if (lborder[0]==len(table)-1):
        lborder[0]=0
    if (lborder[1]==len(table)-1):
        lborder[1]=len(table)-2
    temp[0]=linint(table,frac,charge,lborder[0])
    temp[1]=linint(table,frac,charge,lborder[1])
    return temp

def calcxsq(table,ratios):
    axsq=[]
    for i in range(len(table)):
        xsq=0.
        for j in range(len(ratios)):
            xsq=xsq+(table[i][ratios[j][0]+1]-ratios[j][1])**2
        axsq.append([table[i][0],xsq])
    return axsq
      
def calcxsq2(table,ratios,min):
    axsq=[]
    for k in range(len(table)-1):
        for i in range(11):
            xsq=0.
            if (len(ratios)==0):
                intval=[0.,0.]
            for j in range(len(ratios)):
                intval=linint2(table,ratios[j][0],k,i)
                xsq=xsq+(intval[1]-ratios[j][1])**2
            axsq.append([intval[0],xsq])
    return axsq

"""
subroutine : calculates freezein-temperature for given element using the ionic data from ions to get the different ratios
input
elemdata -> class element
ions     -> array of class ion
"""
def calcfreezein(elemdata,ions):
    rnd=Random()
    ratios=[]
    table=readtable(elemdata.name)
    for ion in ions:
        if (ion2elem(ion.name)==elemdata.name):
            if (elemdata.dens>0.):
                ratio=ion.totdensnumint/elemdata.dens
            else:
                ratio=0.
            ratios.append([int(ion.charge),ratio])

    chisq=calcxsq(table,ratios)
    minvec=getminxsq(chisq)
    chisq2=calcxsq2(table,ratios,minvec[0])
    elemdata.tfreeze=getfreezintemp(chisq2)

    tfreezecrerr=0.
    for i in range(100):
        tmpratios=[]
        tmpsum=0.
        for ion in ions:
            tmpval=0.
            if (ion2elem(ion.name)==elemdata.name):
                if (ion.totdensnuminterror>0.):
                    tmpval=max(0.,rnd.gauss(ion.totdensnumint,ion.totdensnuminterror))
                    tmpsum+=tmpval
                    tmpratios.append([int(ion.charge),tmpval])
        if (tmpsum>0.):
            for j in range(len(tmpratios)):
                tmpratios[j][1]=tmpratios[j][1]/tmpsum
        chisq=calcxsq(table,tmpratios)
        minvec=getminxsq(chisq)
        chisq2=calcxsq2(table,tmpratios,minvec[0])
        tmptfreeze=getfreezintemp(chisq2)
        tfreezecrerr+=(tmptfreeze-elemdata.tfreeze)**2
    elemdata.tfreezecrerr=sqrt(tfreezecrerr/100.)

    ratioslow=[]
    ratioshigh=[]
    table=readtable(elemdata.name)
    for ion in ions:
        if (ion2elem(ion.name)==elemdata.name):
            if (elemdata.dens-elemdata.densefferr>0. and ion.totdensnumint-ion.totdensnuminterror>0.):
                ratiolow=(ion.totdensnumint-ion.totdensnuminterror)/(elemdata.dens-elemdata.densefferr)
            else:
                ratiolow=0.
            if (elemdata.dens+elemdata.densefferr>0. and ion.totdensnumint+ion.totdensnuminterror>0.):
                ratiohigh=(ion.totdensnumint+ion.totdensnuminterror)/(elemdata.dens+elemdata.densefferr)
            else:
                ratiohigh=0.
            ratioslow.append([int(ion.charge),ratiolow])
            ratioshigh.append([int(ion.charge),ratiolow])

    chisq=calcxsq(table,ratioslow)
    minvec=getminxsq(chisq)
    chisq2=calcxsq2(table,ratioslow,minvec[0])
    tfreezelow=getfreezintemp(chisq2)
    chisq=calcxsq(table,ratioshigh)
    minvec=getminxsq(chisq)
    chisq2=calcxsq2(table,ratioshigh,minvec[0])
    tfreezehigh=getfreezintemp(chisq2)
    elemdata.tfreezeefferr=0.5*(sqrt((elemdata.tfreeze-tfreezelow)**2)+sqrt((elemdata.tfreeze-tfreezelow)**2))
