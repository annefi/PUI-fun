#!/usr/bin/python

"""
  Revision controlled by SVN:
  $Id: lv2data.py 7542 2009-04-24 13:26:55Z berger $
"""

from numpy import float
from scipy import zeros
from libacepy.lv1data import lv1data
from libacepy.ion import ion
from libacepy.element import element
from libacepy.fluxes import calcflux,numint,fitmaxwell,calcvelocities
from libacepy.ancil import buildelemlist
from libacepy.elements import calcelement

class lv2data:
    "Class lv2data : contains ion and element data\n\t ions[x] -> objects of calss ion (s. ion.py)\n\t elems[x] -> objects of class element (s. element.py)\n\t input :\n\t datafilename -> should be the name of the lv0 datafile (e.g.axlv2_et_slices_280_001.dat) even if old results are read in this name should be set, since all other names are build from it\n\t ion_list -> should be an array like ['He2+','C4+',...,'Fe16+'] containing all the ions(and therefrom the elemts) that are used\n\t If lv0 and lv1 are present lv2 data can be calculated and written using methods 'caclfromlv1()' and 'write()'"
    def __init__(self,pathname,datafilename,ion_list):
        self.path=pathname
        self.lv0filename=self.path+datafilename
        self.lv1filename=self.path+"erg_"+datafilename
        self.fluxfilename=self.path+"flux_"+datafilename
        self.resfilename=self.path+"res_"+datafilename
        self.elemfilename=self.path+"elem_"+datafilename
        self.cycles=0
        self.aspang=0
        self.ion_list=ion_list
        self.elem_list=buildelemlist(ion_list)
        self.ions=[]
        self.elems=[]

    """
    method : all results are written to the corresponding files (filenames s. __init__)
    """
    def write(self):
        self.writefluxfile()
        self.writeresfile()
        self.writeelemfile()
    """
    method : loads lv1 data and calculates everything
    """
    def calcfromlv1(self):
        self.checkionlistlv1()
        self.setions()
        self.setelems()
        self.loadionsfromlv1()
        self.calcvelocity()
        self.calcdifffluxes()
        self.numint()
#        self.fitmoments()
        self.calcelem()
        
    """
    method : initialises ions using ion_list
    """
    def setions(self):
        print "ion_list = ",self.ion_list
        for name in self.ion_list:
            tmpion=ion(name)
            self.ions.append(tmpion)
    """
    method : initialises elems using elem_list
    """
    def setelems(self):
        for elem in self.elem_list:
            self.elems.append(element(elem))
    """
    method : loads ion data from lv1file into ions
    """
    def loadionsfromlv1(self):
        lv1dat=lv1data(self.lv1filename)
        lv1dat.readlv1data()
        self.cycles=lv1dat.cycles
        self.aspang=lv1dat.aspang
#        lv1dat.calcerrors()
        for ion in range(len(self.ions)):
            for step in range(len(lv1dat.name)):
                for tmpion in range(len(lv1dat.name[step])):
                    if (lv1dat.name[step][tmpion]==self.ions[ion].name):
                        self.ions[ion].mass=lv1dat.mass[step][tmpion]
                        self.ions[ion].charge=lv1dat.charge[step][tmpion]
                        self.ions[ion].counts[step]=lv1dat.normerg[step][tmpion]
                        self.ions[ion].velocity[step]=lv1dat.vel[step][tmpion]
                        self.ions[ion].countserror[step]=lv1dat.errornormerg[step][tmpion]
                        self.ions[ion].cycles=lv1dat.cycles
                        self.ions[ion].aspang=lv1dat.aspang
    """
    method : calculates velocities for each step and ion in ions (this necessary to avoid possible nan results if velocity is zero)
    """
    def calcvelocity(self):
        calcvelocities(self.ions)
        
    """
    method : calculates elemental properties using ions (so ion properties should  be calculated first using calcdifffluxes(),numint(),fitmoments())
    """
    def calcelem(self):
        for elem in self.elems:
            calcelement(elem,self.ions)

    """
    method : calculates differential fluxes AND DENSITIES! from rawcounts (in ions)
    """
    def calcdifffluxes(self):
        for ion in self.ions:
            calcflux(ion,self.ions[0])

    """
    method : calculates totalfluxes AND DENSITIES! from differentialluxes by numerical integration (in ions)
    """
    def numint(self):
        for ion in self.ions:
            numint(ion)

    """
    method : calculates totalfluxes AND DENSITIES! and other properties from differentialluxes by fitting a maxwell-distribution (in ions)
    """
    def fitmoments(self):
        for ion in self.ions:
            fitmaxwell(ion)

    """
    method : checks if ions in ion_list are really present in lv1data. if ion is not present it is sorted out. this is necessary to avoid nan results because of missing mass and charge!!!
    """
    def checkionlistlv1(self):
        tmpion_list=[]
        lv1dat=lv1data(self.lv1filename)
        lv1dat.readlv1data()
        for ion in self.ion_list:
            da=0
            for step in range(len(lv1dat.name)):
                for tmpion in range(len(lv1dat.name[step])):
                    if (lv1dat.name[step][tmpion]==ion):
                        da=1
            if (da):
                tmpion_list.append(ion)
        self.ion_list=tmpion_list

    """
    method : writes fluxfile to fluxfilename (s. __init__)
    """
    def writefluxfile(self):
        print "writing ",self.fluxfilename
        outfile=open(self.fluxfilename,"w")
        for ion in self.ions:
            ion.writeionfluxfile(outfile)
        outfile.close()

    """
    method : writes resfile to fluxfilename (s. __init__)
    """
    def writeresfile(self):
        print "writing ",self.resfilename
        outfile=open(self.resfilename,"w")
        outfile.write("Ion\tVel\t+-cr\t+-eff\tTemp\t\t+-cr\t\t+-eff\t\tFlux\t\t+-cr\t\t+-eff\t\tDens\t\t+-cr\t\t+-eff\n") 
        for ion in self.ions:
            ion.writeionresfile(outfile)
        outfile.close()

    """
    method : writes elemfile to fluxfilename (s. __init__)
    """
    def writeelemfile(self):
        print "writing ",self.elemfilename
        outfile=open(self.elemfilename,"w")
        outfile.write("Element\tFlux\t\t+-cr\t\t+-eff\t\tDens\t\t+-cr\t\t+-eff\t\tTfreeze\t\t+-cr\t\t+-eff\t\tMCh\t+-cr\t+-eff\n") 
        for elem in self.elems:
            elem.writeelemelemfile(outfile)
        outfile.close()


