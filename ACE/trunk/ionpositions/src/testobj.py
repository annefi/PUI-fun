#!/usr/bin/python
from libacepy.lv2data import lv2data
from libacepy.lv1data import lv1data

ion=0
datafilename="axlv2_et_slices_280_001.dat"
bla=lv2data(datafilename,["He2+","C4+","C5+","C6+"])
bla.calcfromlv1()
bla.write()
print bla.ions[ion].flux    
print bla.ions[ion].dens    
print bla.ions[ion].velocity    
print "numflux = ",bla.ions[ion].totfluxnumint    
print "numdens = ",bla.ions[ion].totdensnumint    
print "fitflux = ",bla.ions[ion].totfluxfit    
print "fitdens = ",bla.ions[ion].totdensfit    
print "tempflux = ",bla.ions[ion].iontempfluxfit
print "bulkvflux = ",bla.ions[ion].bulkspeedfluxfit
print "tempdens = ",bla.ions[ion].iontempdensfit
print "bulkvdens = ",bla.ions[ion].bulkspeeddensfit
print bla.__doc__


