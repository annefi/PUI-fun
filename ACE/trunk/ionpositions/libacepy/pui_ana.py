import pylab
from numpy import *

class pui_ana(object):
    def __init__(self,dbd):
        self.dbd = dbd

    def _set_std_mask(self):
        self.dbd.set_mask("Master","mq",3.8,4.3,reset=True)
        self.dbd.set_mask("Master","wHe1+",0.8,10.,reset=True)
        self.dbd.set_mask("Master","epq",1,58,reset=True)
        self.dbd.set_mask("perp","Bphi",70,90,reset=True)
        self.dbd.set_mask("perp","Bphi",-90,-70)
        self.dbd.set_mask("perp","Btheta",-20,20,reset=True)
        self.dbd.set_mask("para","Bphi",-180,-170,reset=True)
        self.dbd.set_mask("para","Bphi",-10,10)
        self.dbd.set_mask("para","Bphi",170,180)
        self.dbd.set_mask("para","Btheta",-20,20,reset=True)
        self.dbd.set_mask("left","Bphi",30,50,reset=True)
        self.dbd.set_mask("left","Bphi",-150,-130)
        self.dbd.set_mask("left","Btheta",-20,20,reset=True)
        self.dbd.set_mask("right","Bphi",-50,-30,reset=True)
        self.dbd.set_mask("right","Bphi",130,150)
        self.dbd.set_mask("right","Btheta",-20,20,reset=True)
        self.dbd.set_mask("perpooe","Bphi",-90,-70)
        self.dbd.set_mask("perpooe","Btheta",-20,20,reset=True)
        self.dbd.set_mask("paraooe","Bphi",-180,-170,reset=True)


    def torus_ana(self,wbins = arange(0.8,4.,.1)):
        tpara = self.dbd.get_data("para","doy")
        tperp = self.dbd.get_data("perp","doy")
        nfpara = unique(tpara).shape[0]*1.
        nfperp = unique(tperp).shape[0]*1.
        wpara = self.dbd.get_data("para","wHe1+")
        wperp = self.dbd.get_data("perp","wHe1+")
        wgtspara = self.dbd.get_data("para","twt")
        wgtsperp = self.dbd.get_data("perp","twt")
        
        wspecpara, bins = histogram(wpara,bins = wbins)
        wspecperp, bins = histogram(wperp,bins = wbins)

        # Normalization
        wspecpara=wspecpara/nfpara*1.
        wspecperp=wspecperp/nfperp*1.

        # Ratio
        R = wspecperp / wspecpara

        # Plot
        fig = pylab.figure()
        ax = fig.gca()

        ax.plot(wbins[:-1],R,marker="o",markersize=5)
        ax.set_xlabel(r"$w_{He+}$")
        ax.set_ylabel("Ratio")

    def hist_aspphi_sec(self,wrange=(1.8,2.),binaspphi=arange(-15.,18.1,3.),binsec=arange(0.,10.,1.)):
        self.dbd.set_mask("Master","wHe1+",wrange[0],wrange[1],reset=True)
        nfpara = array([])
        nfperp = array([])
        nfleft = array([])
        nfright = array([])
        for i in range(binaspphi.shape[0]-1):
            self.dbd.set_mask("Master","aspphi",binaspphi[i],binaspphi[i+1],reset=True)
            tpara = self.dbd.get_data("para","doy")
            tperp = self.dbd.get_data("perp","doy")
            tleft = self.dbd.get_data("left","doy")
            tright = self.dbd.get_data("para","doy")
            nfpara = append(nfpara,unique(tpara).shape[0]*1.)
            nfperp = append(nfperp,unique(tperp).shape[0]*1.)
            nfleft = append(nfleft,unique(tleft).shape[0]*1.)
            nfright = append(nfright,unique(tright).shape[0]*1.)

        self.dbd.remove_submask("Master","aspphi")
        secpara = self.dbd.get_data("para","sec")
        secperp = self.dbd.get_data("perp","sec")
        secleft = self.dbd.get_data("left","sec")
        secright = self.dbd.get_data("right","sec")
        aspphipara = self.dbd.get_data("para","aspphi")
        aspphiperp = self.dbd.get_data("perp","aspphi")
        aspphileft = self.dbd.get_data("left","aspphi")
        aspphiright = self.dbd.get_data("right","aspphi")

        self.dbd.remove_submask("Master","wHe1+")

        Hpara, binx, biny = histogram2d(aspphipara,secpara, bins = (binaspphi,binsec))
        Hperp, binx, biny = histogram2d(aspphiperp,secperp, bins = (binaspphi,binsec))
        Hleft, binx, biny = histogram2d(aspphileft,secleft, bins = (binaspphi,binsec))
        Hright, binx, biny = histogram2d(aspphiright,secright, bins = (binaspphi,binsec))

        # Normalization
        Hpara=divide(Hpara.T,nfpara)
        Hperp=divide(Hperp.T,nfperp)
        Hleft=divide(Hleft.T,nfleft)
        Hright=divide(Hright.T,nfright)
        Hpara[isnan(Hpara)]=0.
        Hpara[isinf(Hpara)]=0.
        Hperp[isnan(Hperp)]=0.
        Hperp[isinf(Hperp)]=0.
        Hleft[isnan(Hleft)]=0.
        Hleft[isinf(Hleft)]=0.
        Hright[isnan(Hright)]=0.
        Hright[isinf(Hright)]=0.
        Hperppara = Hperp/Hpara
        Hleftright = Hleft/Hright
        Hleftright[isnan(Hleftright)]=0.
        Hleftright[isinf(Hleftright)]=0.
        Hperppara[isnan(Hperppara)]=0.
        Hperppara[isinf(Hperppara)]=0.
        
        # Plot
        fig = pylab.figure()
        fig.add_subplot(3,2,1)
        ax1 = fig.gca()
        fig.add_subplot(3,2,2)
        ax2 = fig.gca()
        fig.add_subplot(3,2,3)
        ax3 = fig.gca()
        fig.add_subplot(3,2,4)
        ax4 = fig.gca()
        fig.add_subplot(3,2,5)
        ax5 = fig.gca()
        fig.add_subplot(3,2,6)
        ax6 = fig.gca()
        
        colormap = pylab.cm.get_cmap("jet")
        colormap.set_under("white")
        
        im1 = ax1.pcolormesh(binx[:-1],biny[:-1],Hpara,cmap = colormap, vmin = 0.00000001)
        ax1.set_xlabel(r"Aspect Phi")
        ax1.set_ylabel("Sector")
        ax1.set_title("Para")

        im2 = ax2.pcolormesh(binx[:-1],biny[:-1],Hperp,cmap = colormap, vmin = 0.00000001)
        ax2.set_xlabel(r"Aspect Phi")
        ax2.set_ylabel("Sector")
        ax2.set_title("Perp")

        im3 = ax3.pcolormesh(binx[:-1],biny[:-1],Hleft,cmap = colormap, vmin = 0.00000001)
        ax3.set_xlabel(r"Aspect Phi")
        ax3.set_ylabel("Sector")
        ax3.set_title("Left")

        im4 = ax4.pcolormesh(binx[:-1],biny[:-1],Hright,cmap = colormap, vmin = 0.00000001)
        ax4.set_xlabel(r"Aspect Phi")
        ax4.set_ylabel("Sector")
        ax4.set_title("Right")

        
        
        im5 = ax5.pcolormesh(binx[:-1],biny[:-1],Hperppara,cmap = colormap, vmin = 0.00000001, vmax = 5.)
        ax5.set_xlabel(r"Aspect Phi")
        ax5.set_ylabel("Sector")
        ax5.set_title("perp/para")

        im6 = ax6.pcolormesh(binx[:-1],biny[:-1],Hleftright,cmap = colormap, vmin = 0.00000001, vmax = 5.)
        ax6.set_xlabel(r"Aspect Phi")
        ax6.set_ylabel("Sector")
        ax6.set_title("Left/Right")

        pylab.colorbar(im1, ax = ax1)
        pylab.colorbar(im2, ax = ax2)
        pylab.colorbar(im3, ax = ax3)
        pylab.colorbar(im4, ax = ax4)
        pylab.colorbar(im5, ax = ax5)
        pylab.colorbar(im6, ax = ax6)
        
