#!/usr/bin/python
from numpy import float
from scipy import zeros

class element:
    "Class element : contains data of a single element\n\t name -> elementname\n\t fitflux -> totalflux from fitresults\n\t numflux -> totalflux from numerical integration\n\t fitdens -> totaldensity from fitresults\n\t numdens -> totaldensity from numerical integration\n\t fittfreeze -> freezein temperature from fitresults\n\t numtfreeze -> freezein temperature from numerical integration results\n\t fitmeancharge -> mean charge state from fit results\n\t nummeancharge -> mean charge state from numerical integration results"
    def __init__(self,elemname):
        self.name=elemname
        self.flux=0.
        self.fluxcrerr=0.
        self.fluxefferr=0.
        self.dens=0.
        self.denscrerr=0.
        self.densefferr=0.
        self.tfreeze=0.
        self.tfreezecrerr=0.
        self.tfreezeefferr=0.
        self.meancharge=0.
        self.meanchargecrerr=0.
        self.meanchargeefferr=0.

    """
    method : write elemental data to outstream outfile
    input
    outfile -> already open stream for output
    """
    def writeelemelemfile(self,outfile):
        outfile.write("%s\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.2f\t%.2f\t%.2f\n" %(self.name,self.flux,self.fluxcrerr,self.fluxefferr,self.dens,self.denscrerr,self.densefferr,self.tfreeze,self.tfreezecrerr,self.tfreezeefferr,self.meancharge,self.meanchargecrerr,self.meanchargeefferr))


