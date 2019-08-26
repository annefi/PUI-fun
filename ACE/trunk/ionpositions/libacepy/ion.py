#!/usr/bin/python
from numpy import float
from scipy import zeros

class ion:
    "Class ion: contains data for a single ion\n\t name = ionsname\n\t charge = ionscharge\n\t velocity = array[steps] velocity of ion\n\t counts = array[steps] raw counts from fit\n\t flux = array[steps] fluxes from rawcounts\n\t dens = array[steps] densities from rawcounts\n\t totflux = .... to be continued"
    def __init__(self,ionname):
        dim=58                                  #  temporal variable used to initialize arrays (number of E/q-steps)
        # some ion specific values  
        self.name=ionname                       #  name of ionspecies 
        self.mass=0.                            #  mass of ion in atomic mass units
        self.charge=0.                          #  charge of ion in elemtal charge units
        self.cycles=0.                          #  number of spacecraft cycles. 
        self.aspang=0.                          #  mean aspect angle for dutycycle calculation 
        # arrays containing lvl1 data
        self.velocity=zeros([dim],float)        #  ion velocity for each E/q-step
        self.counts=zeros([dim],float)          #  countrate for each E/q-step
        self.countserror=zeros([dim],float)     #  countrate-error for each E/q-step
        # differential ion quantities 
        self.flux=zeros([dim],float)            #  differential flux for each E/q-step
        self.fluxerror=zeros([dim],float)       #  differential flux-errors from countrate-errors for each E/q-step
        self.fluxefferrlow=zeros([dim],float)   #  differential flux-errors from efficiency-errors for each E/q-step (assuming minimum efficiency)
        self.fluxefferrhigh=zeros([dim],float)  #  differential flux-errors from efficiency-errors for each E/q-step (assuming maximum efficiency)
        self.dens=zeros([dim],float)            #  differential density for each E/q-step
        self.denserror=zeros([dim],float)       #  differential density-errors from countrate-errors for each E/q-step
        self.densefferrlow=zeros([dim],float)   #  differential dens-errors from efficiency-errors for each E/q-step (assuming minimum efficiency)
        self.densefferrhigh=zeros([dim],float)  #  differential dens-errors from efficiency-errors for each E/q-step (assuming maximum efficiency)
        # calculated ion quantities
        self.totfluxnumint=0.                   #  total flux from numerical integration
        self.totfluxnuminterror=0.              #  total flux-error from numerical integration
        self.totfluxefferror=0.                 #  total flux-error from efficiencies
        self.totdensnumint=0.                   #  total density from numerical integration
        self.totdensnuminterror=0.              #  total density-error from numerical integration
        self.totdensefferror=0.                 #  total density-error from efficiencies
        self.iontempfluxnumint=0.               #  ion temperature from flux numint
        self.iontempfluxnuminterror=0.          #  ion temperature-error from flux numint
        self.iontempdensnumint=0.               #  ion temperature from dens numint
        self.iontempdensnuminterror=0.          #  ion temperature-error from dens numint
        self.iontempdensefferror=0.             #  ion temperature-error from dens efficiencies
        self.bulkspeeddensnumint=0.             #  bulkspeed from dens numint
        self.bulkspeeddensnuminterror=0.        #  bulkspeed-error from dens numint
        self.bulkspeeddensefferror=0.           #  bulkspeed-error from dens efficiencies
        self.bulkspeedfluxnumint=0.             #  bulkspeed from flux numint
        self.bulkspeedfluxnuminterror=0.        #  bulkspeed-error from flux numint

    """
    method : write ion data to outstream outfile (differential fluxes and densities)
    input
    outfile -> already open stream for output
    """
    def writeionfluxfile(self,outfile):
        outfile.write("%s\n" %(self.name))
        outfile.write("Mass   : %.0f\n" %(self.mass))
        outfile.write("Charge : %.0f\n" %(self.charge))
        outfile.write("vel\tnormcr\t\t+-\t\tdiffflux\t+-cr\t\t+eff\t\t-eff\t\tdiffdens\t+-cr\t\t+eff\t\t-eff\n")
        for step in range(len(self.velocity)):
            outfile.write("%.2f\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\n" %(self.velocity[step],self.counts[step],self.countserror[step],self.flux[step],self.fluxerror[step],(self.fluxefferrlow[step]-self.flux[step]),(self.flux[step]-self.fluxefferrhigh[step]),self.dens[step],self.denserror[step],(self.densefferrlow[step]-self.dens[step]),(self.dens[step]-self.densefferrhigh[step])))

    """
    method : write ion data to outstream outfile (total fluxes and densities)
    input
    outfile -> already open stream for output
    """
    def writeionresfile(self,outfile):
        outfile.write("%s\t%.1f\t%.1f\t%.1f\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\t%.4e\n" %(self.name,self.bulkspeeddensnumint,self.bulkspeeddensnuminterror,self.bulkspeeddensefferror,self.iontempdensnumint,self.iontempdensnuminterror,self.iontempdensefferror,self.totfluxnumint,self.totfluxnuminterror,self.totfluxefferror,self.totdensnumint,self.totdensnuminterror,self.totdensefferror))
    

