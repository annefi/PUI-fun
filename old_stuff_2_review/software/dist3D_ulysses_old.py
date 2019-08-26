from swics_collimator import collimator
#from libacepy.ancil import getvelocity_allsteps
from libulpy.uswiutils import getvelocity
from libacepy.ace_utils import calc_day00
from pylib.etCoord import rotate
from numpy import *

'''
Dist3D class for Ulysses SWICS
Lars' ACE-version modified by Anne
'''


class Dist3D(object):
    def __init__(self,d,mass = 4., charge = 1., aspphistep=1.,aspthetastep=1.,vswbins=arange(300.,800.1,10.),ion="He1+"):
        """
        d : dbData instance with species predifined by Master mask
        m : Ion mass in amu
        q : Ion charge in e
        """
        self.d = d
        self.aspphistep = aspphistep
        self.aspthetastep = aspthetastep
        self.mass = mass
        self.charge = charge
        self.ion = ion
        self.aspphi = arange(around(min(self.d.data["aspphi"])),around(max(self.d.data["aspphi"]))+aspphistep+0.0001,aspphistep)
        self.asptheta = arange(around(min(self.d.data["asptheta"])),around(max(self.d.data["asptheta"]))+aspthetastep+0.0001,aspthetastep)
        self.vels = getvelocity(self.mass, self.charge, arange(0, 64, 1, ))
        # Todo: doesn't make sense for Ulysses?
        if not "d00" in self.d.data.keys():
            self.d.add_data("d00",calc_day00(self.d.data["year"],self.d.data["doy"]))
        else:
            self.d.data["d00"]=calc_day00(self.d.data["year"],self.d.data["doy"])
        self.geomfac = 0.0225*1e-10
        self.vswbins = vswbins
        self._calc_FoV()
        self._calc_vspace()
        self._add_3Dv()
        #self._add_w()
        #self._calc_wspace()
        #self._calc_phspeff_wgt()
        #self._calc_pitchangle()
        #self._calc_sw_bulk_properties()

    def _calc_FoV(self):
        '''
        Creates one collimator for every asp-phi-combination.
        Last dimension is for detector resolution (=1 if calc_full = False: one point per detector)
        '''
        self.FoV = zeros((self.aspphi.shape[0],self.asptheta.shape[0],3,8,3,1))
        for iphi,phi in enumerate(self.aspphi):
            for itheta,theta in enumerate(self.asptheta):
                c = collimator(aspphi=phi,asptheta=theta,calc_full = False)
                self.FoV[iphi,itheta]=c.FoV

    def _calc_vspace(self):
        """
        Calculates vx,vy,vz for all epqsteps and given aspect angles
        """
        self.vspace = zeros((self.aspphi.shape[0],self.asptheta.shape[0],64,3,8,3,1))
        for iv,v in enumerate(self.vels):
            self.vspace[:,:,iv,:,:,:,:] = -self.FoV*v
        self.vspace[:,:,:,:,:,1,:] -= 30. # Eigenvelocity
        self.vspace[:,:,:,:,:,0,:] =- self.vspace[:,:,:,:,:,0,:]
        self.vspace[:,:,:,:,:,1,:] =- self.vspace[:,:,:,:,:,1,:]

    def _calc_wspace(self,):
        """
        Calculates vx,vy,vz for all epqsteps and given aspect angles
        """
        self.w3dspace = zeros((self.vswbins.shape[0],self.aspphi.shape[0],self.asptheta.shape[0],60,3,8,3,1))
        self.wspace = zeros((self.vswbins.shape[0],self.aspphi.shape[0],self.asptheta.shape[0],60,3,8,1,1))
        for iv,v in enumerate(self.vswbins[:-1]):
            tmpspace=1.*self.vspace
            tmpspace[...,0,:]-=(v+5.)
            tmpspace/=(v+5.)
            self.w3dspace[iv,...]=tmpspace
            self.wspace[iv,...,0,:]=sqrt(sum(tmpspace**2,axis=5))
            
    def _add_3Dv(self):
        """
        Adds vx,vy,vz in SC-frame and vxsw,vysw,vzsw in SW-frame based on aspect angles to pha data
        Also adds vxsw2,vysw2,vzsw2 in SW-frame based on aspect angles and rounded vsw to pha data 
        In the current version vsw is taken to be stricly radial, i.e. along vx!
        """
        self.phiind = searchsorted(self.aspphi,around(self.d.data["aspphi"]))
        self.thetaind = searchsorted(self.asptheta,around(self.d.data["asptheta"]))
        self.epqind = self.d.data["epq"].astype(int) #Todo: notwendig?
        self.detind = self.d.data["det"].astype(int) #Todo: notwendig?
        # set DCR to det 0 
        # detind[detind==7] = 0 #??
        # secind = self.d.data["sec"].astype(int)
        # if not "vx" in self.d.data.keys():
        #     self.d.add_data("vx",self.vspace[phiind,thetaind,epqind,detind,secind,0,0])
        # else:
        #     self.d.data["vx"]=self.vspace[phiind,thetaind,epqind,detind,secind,0,0]
        # if not "vy" in self.d.data.keys():
        #     self.d.add_data("vy",self.vspace[phiind,thetaind,epqind,detind,secind,1,0])
        # else:
        #     self.d.data["vy"]=self.vspace[phiind,thetaind,epqind,detind,secind,1,0]
        # if not "vz" in self.d.data.keys():
        #     self.d.add_data("vz",self.vspace[phiind,thetaind,epqind,detind,secind,2,0])
        # else:
        #     self.d.data["vz"]=self.vspace[phiind,thetaind,epqind,detind,secind,2,0]
        #
        # # Now in SW-frame under the assumption that v_sw is stricly along v_x:
        # if not "vxsw" in self.d.data.keys():
        #     self.d.add_data("vxsw",self.d.data["vx"]-self.d.data["vsw"])
        # else:
        #     self.d.data["vxsw"]=self.d.data["vx"]-self.d.data["vsw"]
        # if not "vysw" in self.d.data.keys():
        #     self.d.add_data("vysw",self.d.data["vy"])
        # else:
        #     self.d.data["vysw"]=self.d.data["vy"]
        # if not "vzsw" in self.d.data.keys():
        #     self.d.add_data("vzsw",self.d.data["vz"])
        # else:
        #     self.d.data["vzsw"]=self.d.data["vz"]
        #
        # # index 2 in names means vsw speed has been rounded
        # if not "vxsw2" in self.d.data.keys():
        #     self.d.add_data("vxsw2",self.d.data["vx"]-around(self.d.data["vsw"],-1))
        # else:
        #     self.d.data["vxsw"]=self.d.data["vx"]-around(self.d.data["vsw"],-1)
        # if not "vysw2" in self.d.data.keys():
        #     self.d.add_data("vysw2",self.d.data["vy"])
        # else:
        #     self.d.data["vysw2"]=self.d.data["vy"]
        # if not "vzsw2" in self.d.data.keys():
        #     self.d.add_data("vzsw2",self.d.data["vz"])
        # else:
        #     self.d.data["vzsw2"]=self.d.data["vz"]


    def _add_w(self):
        """
        Adds wxsw,wysw,wzsw and wsw in SW-frame to pha data
        Adds wxsw2,wysw2,wzsw2 and wsw2 in SW-frame to pha data based on rounded vsws!
        """
        if not "wxsw" in self.d.data.keys():
            self.d.add_data("wxsw",self.d.data["vxsw"]/self.d.data["vsw"])
        else:
            self.d.data["wxsw"]=self.d.data["vxsw"]/self.d.data["vsw"]
        if not "wysw" in self.d.data.keys():
            self.d.add_data("wysw",self.d.data["vysw"]/self.d.data["vsw"])
        else:
            self.d.data["wysw"]=self.d.data["vysw"]/self.d.data["vsw"]
        if not "wzsw" in self.d.data.keys():
            self.d.add_data("wzsw",self.d.data["vzsw"]/self.d.data["vsw"])
        else:
            self.d.data["wzsw"]=self.d.data["vzsw"]/self.d.data["vsw"]
        if not "wsw" in self.d.data.keys():
            self.d.add_data("wsw",sqrt(self.d.data["wxsw"]**2+self.d.data["wysw"]**2+self.d.data["wzsw"]**2))
        else:
            self.d.data["wsw"]=sqrt(self.d.data["wxsw"]**2+self.d.data["wysw"]**2+self.d.data["wzsw"]**2)
        if not "wxsw2" in self.d.data.keys():
            self.d.add_data("wxsw2",self.d.data["vxsw2"]/self.d.data["vsw"])
        else:
            self.d.data["wxsw2"]=self.d.data["vxsw2"]/self.d.data["vsw"]
        if not "wysw2" in self.d.data.keys():
            self.d.add_data("wysw2",self.d.data["vysw2"]/self.d.data["vsw"])
        else:
            self.d.data["wysw2"]=self.d.data["vysw2"]/self.d.data["vsw"]
        if not "wzsw2" in self.d.data.keys():
            self.d.add_data("wzsw2",self.d.data["vzsw2"]/self.d.data["vsw"])
        else:
            self.d.data["wzsw2"]=self.d.data["vzsw2"]/self.d.data["vsw"]
        if not "wsw2" in self.d.data.keys():
            self.d.add_data("wsw2",sqrt(self.d.data["wxsw2"]**2+self.d.data["wysw2"]**2+self.d.data["wzsw2"]**2))
        else:
            self.d.data["wsw2"]=sqrt(self.d.data["wxsw2"]**2+self.d.data["wysw2"]**2+self.d.data["wzsw2"]**2)
        if not "wHe1+2" in self.d.data.keys():
            self.d.add_data("wHe1+2",getvelocity_allsteps(4.,1.,self.d.data["epq"].astype(int))/around(self.d.data["vsw"],-1))
        else:
            self.d.data["wHe1+2"]=getvelocity_allsteps(4.,1.,self.d.data["epq"].astype(int))/around(self.d.data["vsw"],-1)
    def _calc_phspeff_wgt(self):
        """
        Loads ion efficiencies
        ion name, mass and charge must be given at the initialisation of the class object
        """
        fin = open("/data/etph/ace/efficencies/%s.eff"%(self.ion),"r")
        dat = loadtxt(fin)
        eff = dat[:,1]
        eff = append(array([0]),eff)
        if not "eff" in self.d.data.keys():
            self.d.add_data("eff",eff[self.d.data["epq"].astype(int)])
        else:
            self.d.data["eff"] = eff[self.d.data["epq"].astype(int)]
        vs = self.vels[self.d.data["epq"].astype(int)]
        if not "wgteffphsp" in self.d.data.keys():
            self.d.add_data("wgteffphsp",(1./vs**4)/self.d.data["eff"])
        else:
            self.d.data["wgteffphsp"] = (1./vs**4)/self.d.data["eff"]
        
        #### space volume in km**3 (12s for whole spin, but each sec is only scanned for 1.5s)*solid angle coverage(4*69 whole)*dv from deltaE/Q*efficiencies
        wgts_all = 1./(vs*1.5*self.geomfac)*1./(vs**2*(pi**2/180**2.*4.*69))*1./(0.03*vs)*1./self.d.data["eff"]
        #### space volume in km**3 (1.5s for sec)*solid angle coverage(4*33 for sec)*dv from deltaE/Q*efficiencies
        wgts_sec = 1./(vs*1.5*self.geomfac)*1./(vs**2*(pi**2/180**2.*4.*23))*1./(0.03*vs)*1./self.d.data["eff"]
        if not "wgteffphsp" in self.d.data.keys():
            self.d.add_data("wgteffphsp",(1./vs**4)/self.d.data["eff"])
        else:
            self.d.data["wgteffphsp"] = (1./vs**4)/self.d.data["eff"]
        if not "wgts_all" in self.d.data.keys():
            self.d.add_data("wgts_all",wgts_all)
        else:
            self.d.data["wgts_all"] = wgts_all
        if not "wgts_sec" in self.d.data.keys():
            self.d.add_data("wgts_sec",wgts_sec)
        else:
            self.d.data["wgts_sec"] = wgts_sec
    def _calc_pitchangle(self):
        # recalc abs(B)
        absB = sqrt(self.d.data["Bx"]**2+self.d.data["By"]**2+self.d.data["Bz"]**2)
        # Calculate unit Vector along B-field
        if not "eBx" in self.d.data.keys():
            self.d.add_data("eBx",self.d.data["Bx"]/absB)
        else:
            self.d.data["eBx"] = self.d.data["Bx"]/absB
        if not "eBy" in self.d.data.keys():
            self.d.add_data("eBy",self.d.data["By"]/absB)
        else:
            self.d.data["eBy"] = self.d.data["By"]/absB
        if not "eBz" in self.d.data.keys():
            self.d.add_data("eBz",self.d.data["Bz"]/absB)
        else:
            self.d.data["eBz"] = self.d.data["Bz"]/absB
        # Calculate unit Vector along w vector in solar wind frame
        if not "ewx" in self.d.data.keys():
            self.d.add_data("ewx",self.d.data["wxsw"]/self.d.data["wsw"])
        else:
            self.d.data["ewx"] = self.d.data["wxsw"]/self.d.data["wsw"]
        if not "ewy" in self.d.data.keys():
            self.d.add_data("ewy",self.d.data["wysw"]/self.d.data["wsw"])
        else:
            self.d.data["ewy"] = self.d.data["wysw"]/self.d.data["wsw"]
        if not "ewz" in self.d.data.keys():
            self.d.add_data("ewz",self.d.data["wzsw"]/self.d.data["wsw"])
        else:
            self.d.data["ewz"] = self.d.data["wzsw"]/self.d.data["wsw"]
        # Calculate cosine of pitch angle mu by scalar product of eB and and ew. Cosmup stands for B-field is still important,i.e. inward field cosmup=1 means the opposite direction compared to the solar wind bulk than for outward polarity!
        if not "cosmup" in self.d.data.keys():
            self.d.add_data("cosmup",self.d.data["eBx"]*self.d.data["ewx"]+self.d.data["eBy"]*self.d.data["ewy"]+self.d.data["eBz"]*self.d.data["ewz"])
        else:
            self.d.data["cosmup"]=self.d.data["eBx"]*self.d.data["ewx"]+self.d.data["eBy"]*self.d.data["ewy"]+self.d.data["eBz"]*self.d.data["ewz"]
        # Cosmu is the cosine on the outward projected B field, i.e. if the polarity is inward cosmu 1 is now pointing away from the Sun
        if not "cosmu" in self.d.data.keys():
            self.d.add_data("cosmu",self.d.data["cosmup"])
        else:
            self.d.data["cosmu"]=self.d.data["cosmup"]
        # inmask very brutally assumes each polarity to be separated in hemispheres (out -45(~parker angle)+-90 degree -> in 135+-90 degree)
        inmask = ~((self.d.data["Bphi"]>-135)*(self.d.data["Bphi"]<45))
        self.d.data["cosmu"][inmask]=-self.d.data["cosmu"][inmask]
    def _calc_sw_bulk_properties(self):
        """
        Calculate the solar wind Bulk vector, assuming that the proton core is shifted along B by the alfven speed from the radial axis
        """
        # Add alfven speed
        if not "valf" in self.d.data.keys():
            self.d.add_data("valf",21.8*self.d.data["B"]/sqrt(self.d.data["dsw"]))
        else:
            self.d.data["valf"]=21.8*self.d.data["B"]/sqrt(self.d.data["dsw"])
        vswy = self.d.data["valf"]*self.d.data["eBy"]
        vswz = self.d.data["valf"]*self.d.data["eBz"]
        phi = self.d.data["Bphi"]
        vswy[(phi>-135)*(phi<45)]*=-1.
        vswz[(phi>-135)*(phi<45)]*=-1.
        vswx = sqrt(self.d.data["vsw"]**2-vswy**2-vswz**2)
        if not "vswx" in self.d.data.keys():
            self.d.add_data("vswx",vswx)
        else:
            self.d.data["vswx"]=vswx
        if not "vswy" in self.d.data.keys():
            self.d.add_data("vswy",vswy)
        else:
            self.d.data["vswy"]=vswy
        if not "vswz" in self.d.data.keys():
            self.d.add_data("vswz",vswz)
        else:
            self.d.data["vswz"]=vswz
        if not "vxswa" in self.d.data.keys():
            self.d.add_data("vxswa",self.d.data["vx"]-vswx)
        else:
            self.d.data["vxswa"]=self.d.data["vx"]-vswx
        if not "vyswa" in self.d.data.keys():            
            self.d.add_data("vyswa",self.d.data["vy"]-vswy)
        else:
            self.d.data["vyswa"]=self.d.data["vy"]-vswy
        if not "vzswa" in self.d.data.keys():            
            self.d.add_data("vzswa",self.d.data["vz"]-vswz)
        else:
            self.d.data["vzswa"]=self.d.data["vz"]-vswz
        if not "wxswa" in self.d.data.keys():
            self.d.add_data("wxswa",self.d.data["vxswa"]/self.d.data["vsw"])
        else:
            self.d.data["wxswa"]=self.d.data["vxswa"]/self.d.data["vsw"]
        if not "wyswa" in self.d.data.keys():
            self.d.add_data("wyswa",self.d.data["vyswa"]/self.d.data["vsw"])
        else:
            self.d.data["wyswa"]=self.d.data["vyswa"]/self.d.data["vsw"]
        if not "wzswa" in self.d.data.keys():
            self.d.add_data("wzswa",self.d.data["vzswa"]/self.d.data["vsw"])
        else:
            self.d.data["wzswa"]=self.d.data["vzswa"]/self.d.data["vsw"]
        if not "wswa" in self.d.data.keys():
            self.d.add_data("wswa",sqrt(self.d.data["wxswa"]**2+self.d.data["wyswa"]**2+self.d.data["wzswa"]**2))
        else:
            self.d.data["wswa"]=sqrt(self.d.data["wxswa"]**2+self.d.data["wyswa"]**2+self.d.data["wzswa"]**2)
            
    def calc_wspec_norm(self,vsws=arange(495.,800.,10.),wbins=arange(-1.,5.1,.1),min_whe=0.9):
        """
        Calculates w spectra. Data preselected by Master mask, i.e. Magnetic field direction.
        vsws -> bins for solar wind speed that are taken to calculate the instrumental coverage at w-bins
        """
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        self.d.set_mask("He1+","wHe1+2",min_whe,10.,reset=True)
        #for each combination of aspect angles and solar wind velocity the phase space coverage has to be calculated to calculate the weights for normalising the final histograms.
        norm_arr = zeros((wbins.shape[0]-1))
        cts_arr = zeros((wbins.shape[0]-1))
        for v in vsws.astype(int):
            self.d.set_mask("Master","vsw",v,v+10.,reset=True)
            print v
            for phi in self.aspphi[:-1]:
                self.d.set_mask("Master","aspphi",phi-0.5,phi+0.5,reset=True)
                for theta in self.asptheta[:-1]:
                    self.d.set_mask("Master","asptheta",theta-0.5,theta+0.5,reset=True)
                    # All times (after Master mask) under which particles could have been measured under given aspect angle and solar wind speed
                    uTall,Tallind = unique(self.d.get_data("Master","d00"),return_index=True)
                    if uTall.shape[0]==0.:
                        pass
                    else:
                        phiind = searchsorted(self.aspphi,phi)
                        thetaind = searchsorted(self.asptheta,theta)
                        whe = self.vels/(v+5.)
                        epqs=arange(0,60,1)[whe>min_whe]
                        wspace=self.vspace[phiind,thetaind,epqs]
                        wspace[:,:,:,0,:]-=(v+5.)
                        wspace/=(v+5.)
                        wcov = sqrt(sum(wspace**2,axis=3))
                        wcov[wspace[:,:,:,0,:]<0]*=-1.
                        H,xbins = histogram(wcov.flatten(),bins=wbins)
                        norm_arr+=H*uTall.shape[0]
                        wgts=self.d.get_data("He1+","wgts_sec")
                        ws=self.d.get_data("He1+","wsw2")
                        wxsw=self.d.get_data("He1+","wxsw2")
                        ws[wxsw<0]*=-1.
                        swgt=self.d.get_data("He1+","swt")
                        H,xbins = histogram(ws,bins=wbins,weights=wgts*swgt)
                        cts_arr+=H
        self.d.remove_submask("He1+","wHe1+2")
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        return cts_arr,norm_arr

    def calc_muspec(self,vsws=arange(495.,800.,10.),wbins=arange(0.,5.1,.1),min_whe=0.9,bphi=90.,btheta=0.,dbphi=10.,dbtheta=10.,cosmubins=arange(-1.,1.01,.1)):
        """
        Calculates pitch-angle over w spectra. Data preselected by Master mask.
        vsws -> bins for solar wind speed that are taken to calculate the instrumental coverage at w-bins
        """
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        self.d.remove_submask("Master","Bphi")
        self.d.remove_submask("Master","Btheta")
        self.d.set_mask("He1+","wHe1+2",min_whe,10.,reset=True)
        self.d.set_mask("Master","Bphi",bphi-dbphi,bphi+dbphi,reset=True)
        self.d.set_mask("Master","Btheta",btheta-dbtheta,btheta+dbtheta,reset=True)
        #for each combination of aspect angles and solar wind velocity the phase space coverage has to be calculated to calculate the weights for normalising the final histograms.
        norm_arr = zeros((wbins.shape[0]-1,cosmubins.shape[0]-1))
        cts_arr = zeros((wbins.shape[0]-1,cosmubins.shape[0]-1))
        B0 = array([1.,0.,0.])
        rphiax = array([0.,0.,1.])
        rthetaax = rotate(array([0.,1.,0]),rphiax,bphi,deg=True)
        B = rotate(B0,rphiax,bphi,deg=True)
        B = rotate(B,rthetaax,btheta,deg=True)

        for v in vsws.astype(int):
            self.d.set_mask("Master","vsw",v,v+10.,reset=True)
            print v
            for phi in self.aspphi[:-1]:
                self.d.set_mask("Master","aspphi",phi-0.5,phi+0.5,reset=True)
                for theta in self.asptheta[:-1]:
                    self.d.set_mask("Master","asptheta",theta-0.5,theta+0.5,reset=True)
                    # All times (after Master mask) under which particles could have been measured under given aspect angle and solar wind speed
                    uTall,Tallind = unique(self.d.get_data("Master","d00"),return_index=True)
                    if uTall.shape[0]==0.:
                        pass
                    else:
                        phiind = searchsorted(self.aspphi,phi)
                        thetaind = searchsorted(self.asptheta,theta)
                        whe = self.vels/(v+5.)
                        epqs=arange(0,60,1)[whe>min_whe]
                        wspace=self.vspace[phiind,thetaind,epqs]
                        wspace[:,:,:,0,:]-=(v+5.)
                        wspace/=(v+5.)
                        wcov = sqrt(sum(wspace**2,axis=3))
                        ewspace=1.*wspace
                        ewspace[:,:,:,0]=wspace[:,:,:,0]/wcov[:,:,:]
                        ewspace[:,:,:,1]=wspace[:,:,:,1]/wcov[:,:,:]
                        ewspace[:,:,:,2]=wspace[:,:,:,2]/wcov[:,:,:]
                        cosmu = ewspace[:,:,:,0,:]*B[0]+ewspace[:,:,:,1,:]*B[1]+ewspace[:,:,:,2,:]*B[2]
                        H,xbins,ybins = histogram2d(wcov.flatten(),cosmu.flatten(),bins=(wbins,cosmubins))
                        norm_arr+=H*uTall.shape[0]
                        wgts=self.d.get_data("He1+","wgts_sec")
                        ws=self.d.get_data("He1+","wsw2")
                        wxsw=self.d.get_data("He1+","wxsw2")
                        cmu =self.d.get_data("He1+","cosmu") 
                        swgt=self.d.get_data("He1+","swt")
                        H,xbins,ybins = histogram2d(ws,cmu,bins=(wbins,cosmubins),weights=wgts*swgt)
                        cts_arr+=H
        self.d.remove_submask("He1+","wHe1+2")
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        self.d.remove_submask("Master","Bphi")
        self.d.remove_submask("Master","Btheta")
        return cts_arr,norm_arr,xbins,ybins
    def calc_wpecs2(self,vswbins=arange(500.,800.1,10.),wbins=arange(-1.,2.01,0.1),min_whe=0.9):
        """
        Calculates w spectra. Data preselected by Master mask, i.e. Magnetic field direction.
        vsws -> bins for solar wind speed that are taken to calculate the instrumental coverage at w-bins
        """
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        self.d.set_mask("He1+","wHe1+2",min_whe,10.,reset=True)
        #for each combination of aspect angles and solar wind velocity the phase space coverage has to be calculated to calculate the weights for normalising the final histograms.
        norm_arr = zeros((wbins.shape[0]-1))
        cts_arr = zeros((wbins.shape[0]-1))
        self.d.set_mask("Master","vsw",vswbins[0],vswbins[-1],reset=True)
        #self.d.set_mask("Master","wxsw",0.,10000,reset=True)
        uTall,Tallind = unique(self.d.get_data("Master","d00"),return_index=True)
        uasphi = self.d.get_data("Master","aspphi")[Tallind]
        uasptheta = self.d.get_data("Master","asptheta")[Tallind]
        uvsw = self.d.get_data("Master","vsw")[Tallind]
        H,bs=histogramdd((uvsw,uasphi,uasptheta),bins=(vswbins,self.aspphi,self.asptheta))
        ivoffset = int(around(vswbins[0]-300,-1)/10)
        for iv,v in enumerate(vswbins[:-1]):
            for ip,p in enumerate(self.aspphi[:-1]):
                for it,t in enumerate(self.asptheta[:-1]):
                    if H[iv,ip,it]>0:
                        whe = self.vels/(v+5.)
                        epqs=arange(0,60,1)[whe>min_whe]
                        mask=self.w3dspace[iv+ivoffset,ip,it,epqs,:,:,0,0]<0
                        wspace=self.wspace[iv+ivoffset,ip,it,epqs]
                        wspace[mask]*=-1.
                        #H2,xb = histogram(self.wspace[iv,ip,it,epqs][mask],bins=wbins)
                        H2,xb = histogram(wspace,bins=wbins)
                        norm_arr+=H2*H[iv,ip,it]
        wgts=self.d.get_data("He1+","wgts_sec")
        swgt=self.d.get_data("He1+","swt")
        ws=self.d.get_data("He1+","wsw2")
        wxsw=self.d.get_data("He1+","wxsw2")
        ws[wxsw<0]*=-1.
        H2,xb = histogram(ws,bins=wbins,weights=wgts*swgt)
        self.d.remove_submask("He1+","wHe1+2")
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        return norm_arr,H2
        
    def calc_w3dspecs(self,vswbins=arange(500.,800.1,10.),wxbins=arange(-2.,2.01,0.2),wybins=arange(-2.,2.01,0.2),wzbins=arange(-2.,2.01,0.2),min_whe=0.9):
        """
        Calculates w spectra. Data preselected by Master mask, i.e. Magnetic field direction.
        vsws -> bins for solar wind speed that are taken to calculate the instrumental coverage at w-bins
        """
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        self.d.set_mask("He1+","wHe1+2",min_whe,10.,reset=True)
        #for each combination of aspect angles and solar wind velocity the phase space coverage has to be calculated to calculate the weights for normalising the final histograms.
        norm_arr = zeros((wxbins.shape[0]-1,wybins.shape[0]-1,wzbins.shape[0]-1))
        cts_arr = zeros((wxbins.shape[0]-1,wybins.shape[0]-1,wzbins.shape[0]-1))
        self.d.set_mask("Master","vsw",vswbins[0],vswbins[-1],reset=True)
        uTall,Tallind = unique(self.d.get_data("Master","d00"),return_index=True)
        uasphi = self.d.get_data("Master","aspphi")[Tallind]
        uasptheta = self.d.get_data("Master","asptheta")[Tallind]
        uvsw = self.d.get_data("Master","vsw")[Tallind]
        H,bs=histogramdd((uvsw,uasphi,uasptheta),bins=(vswbins,self.aspphi,self.asptheta))
        ivoffset = int(around(vswbins[0]-300,-1)/10)
        for iv,v in enumerate(vswbins[:-1]):
            for ip,p in enumerate(self.aspphi[:-1]):
                for it,t in enumerate(self.asptheta[:-1]):
                    if H[iv,ip,it]>0:
                        whe = self.vels/(v+5.)
                        epqs=arange(0,60,1)[whe>min_whe]
                        H2,bs = histogramdd((self.w3dspace[iv+ivoffset,ip,it,epqs,...,0,0].flatten(),self.w3dspace[iv+ivoffset,ip,it,epqs,...,1,0].flatten(),self.w3dspace[iv+ivoffset,ip,it,epqs,...,2,0].flatten()),bins=(wxbins,wybins,wzbins))
                        norm_arr+=H2*H[iv,ip,it]
        wgts=self.d.get_data("He1+","wgts_sec")
        swgt=self.d.get_data("He1+","swt")
        wxsw2=self.d.get_data("He1+","wxsw2")
        wysw2=self.d.get_data("He1+","wysw2")
        wzsw2=self.d.get_data("He1+","wzsw2")
        H2,bs = histogramdd((wxsw2,wysw2,wzsw2),bins=(wxbins,wybins,wzbins),weights=(wgts*swgt))
        self.d.remove_submask("He1+","wHe1+2")
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        return norm_arr,H2
    def calc_cosmuspecs(self,vswbins=arange(500.,800.1,10.),cosmubins=arange(-1.,1.01,.2),wbins=arange(-0.,2.1,.2),min_whe=0.9,bphibins=arange(-110,-69.9,10.),bthetabins=arange(-20,20.1,10.)):
        """
        Calculates w spectra. Data preselected by Master mask, i.e. Magnetic field direction.
        vsws -> bins for solar wind speed that are taken to calculate the instrumental coverage at w-bins
        """
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        self.d.set_mask("He1+","wHe1+2",min_whe,10.,reset=True)
        #for each combination of aspect angles and solar wind velocity the phase space coverage has to be calculated to calculate the weights for normalising the final histograms.
        norm_arr = zeros((wbins.shape[0]-1,cosmubins.shape[0]-1))
        cts_arr = zeros((wbins.shape[0]-1,cosmubins.shape[0]-1))
        ivoffset = int(around(vswbins[0]-500,-1)/10)
        self.d.set_mask("Master","vsw",vswbins[0],vswbins[-1],reset=True)
        for iphi,bphi in enumerate(bphibins[:-1]):
            for itheta,btheta in enumerate(bphibins[:-1]):
                self.d.set_mask("Master","Bphi",bphi,bphibins[iphi+1],reset=True)
                self.d.set_mask("Master","Btheta",btheta,bthetabins[iphi+1],reset=True)
                uTall,Tallind = unique(self.d.get_data("Master","d00"),return_index=True)
                uasphi = self.d.get_data("Master","aspphi")[Tallind]
                uasptheta = self.d.get_data("Master","asptheta")[Tallind]
                uvsw = self.d.get_data("Master","vsw")[Tallind]
                H,bs=histogramdd((uvsw,uasphi,uasptheta),bins=(vswbins,self.aspphi,self.asptheta))
                B0 = array([1.,0.,0.])
                rphiax = array([0.,0.,1.])
                rthetaax = rotate(array([0.,1.,0]),rphiax,bphi+5,deg=True)
                B = rotate(B0,rphiax,bphi+5,deg=True)
                B = rotate(B,rthetaax,btheta+5,deg=True)
                for iv,v in enumerate(vswbins[:-1]):
                    for ip,p in enumerate(self.aspphi[:-1]):
                        for it,t in enumerate(self.asptheta[:-1]):
                            if H[iv,ip,it]>0:
                                whe = self.vels/(v+5.)
                                epqs=arange(0,60,1)[whe>min_whe]
                                w3dspace=self.w3dspace[iv+ivoffset,ip,it,epqs]
                                wspace=self.wspace[iv+ivoffset,ip,it,epqs]
                                w3dspace[...,0,0]/=wspace[...,0,0]
                                w3dspace[...,1,0]/=wspace[...,0,0]
                                w3dspace[...,2,0]/=wspace[...,0,0]
                                cosmuspace=w3dspace[...,0,0]*B[0]+w3dspace[...,1,0]*B[1]+w3dspace[...,2,0]*B[2]
                                H2,xb,yb = histogram2d(wspace.flatten(),cosmuspace.flatten(),bins=(wbins,cosmubins))
                                norm_arr+=H2*H[iv,ip,it]
        self.d.set_mask("Master","Bphi",bphibins[0],bphibins[-1],reset=True)
        self.d.set_mask("Master","Btheta",bthetabins[0],bthetabins[-1],reset=True)
        wgts=self.d.get_data("He1+","wgts_sec")
        swgt=self.d.get_data("He1+","swt")
        wsw2=self.d.get_data("He1+","wsw2")
        cosmu=self.d.get_data("He1+","cosmu")
        H2,xb,yb = histogram2d(wsw2,cosmu,bins=(wbins,cosmubins),weights=(wgts*swgt))
        self.d.remove_submask("Master","Bphi")
        self.d.remove_submask("Master","Btheta")
        self.d.remove_submask("He1+","wHe1+2")
        self.d.remove_submask("Master","vsw")
        self.d.remove_submask("Master","aspphi")
        self.d.remove_submask("Master","asptheta")
        return norm_arr,H2
        
