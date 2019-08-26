#!/usr/bin/python
from numpy import float
from math import sqrt
from libacepy.ancil import ion2elem,ionname2charge
from libacepy.freezeintemp import calcfreezein
from random import Random
    
"""
subroutine : uses data from ions to calculate total fluxes and densities for given element
input
elemdata -> class element (s. element.py)
ions -> array of class ion (s. ion.py)
"""
def elemsum(elemdata,ions):
    for ion in ions:
        if (elemdata.name==ion2elem(ion.name)):
            elemdata.flux+=ion.totfluxnumint
            elemdata.fluxcrerr+=ion.totfluxnuminterror**2
            elemdata.fluxefferr+=ion.totfluxefferror
            elemdata.dens+=ion.totdensnumint
            elemdata.denscrerr+=ion.totdensnuminterror**2
            elemdata.densefferr+=ion.totdensefferror
    elemdata.fluxcrerr=sqrt(elemdata.fluxcrerr)
    elemdata.denscrerr=sqrt(elemdata.denscrerr)

"""
subroutine : uses data from ions to calculate mean charge state for given element
input
elemdata -> class element (s. element.py)
ions -> array of class ion (s. ion.py)
"""
def meancharge(elemdata,ions):
    rnd=Random()
    # meancharge
    for ion in ions:
        if (ion2elem(ion.name)==elemdata.name):
            if (elemdata.dens>0.):
                elemdata.meancharge+=ion.charge*ion.totdensnumint/elemdata.dens
    # cr errors 
    for i in range(100):
        tmpmeancharge=0.
        tmpelemsum=0.
        for ion in ions:
            tmpval=0.
            if (ion2elem(ion.name)==elemdata.name):
                if (ion.totdensnuminterror>0.):
                    tmpval=max(0.,rnd.gauss(ion.totdensnumint,ion.totdensnuminterror))
                    tmpmeancharge+=ion.charge*tmpval
                    tmpelemsum+=tmpval
        if (tmpelemsum>0.):
            tmpmeancharge=(tmpmeancharge/tmpelemsum-elemdata.meancharge)**2
            elemdata.meanchargecrerr+=tmpmeancharge
    elemdata.meanchargecrerr=sqrt(elemdata.meanchargecrerr/100.)
    # eff errors
    tmpmeanchargeefflow=0.
    tmpmeanchargeeffhigh=0.
    for ion in ions:
        if (ion2elem(ion.name)==elemdata.name):
            if (elemdata.dens-elemdata.densefferr>0.):
                tmpmeanchargeefflow+=ion.charge*(ion.totdensnumint-ion.totdensefferror)/(elemdata.dens-elemdata.densefferr)
            if (elemdata.dens+elemdata.densefferr>0.):
                tmpmeanchargeeffhigh+=ion.charge*(ion.totdensnumint+ion.totdensefferror)/(elemdata.dens+elemdata.densefferr)
    if (tmpmeanchargeefflow>0.):
        elemdata.meanchargeefferr+=sqrt((tmpmeanchargeefflow-elemdata.meancharge)**2)
        if (tmpmeanchargeeffhigh>0.):
            elemdata.meanchargeefferr+=sqrt((tmpmeanchargeeffhigh-elemdata.meancharge)**2)
            elemdata.meanchargeefferr=elemdata.meanchargeefferr*0.5
    elif (tmpmeanchargeeffhigh>0.):
        elemdata.meanchargeefferr+=sqrt((tmpmeanchargeeffhigh-elemdata.meancharge)**2)
        
"""
subroutine : uses data from ions to calculate total fluxes and densities + mean charge states for given element
input
elemdata -> class element (s. element.py)
ions -> array of class ion (s. ion.py)
"""
def calcelement(elemdata,ions):
    elemsum(elemdata,ions)
    meancharge(elemdata,ions)
    calcfreezein(elemdata,ions)

