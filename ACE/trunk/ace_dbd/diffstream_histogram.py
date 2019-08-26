from numpy import loadtxt, array, arange,sqrt,exp,histogram2d,meshgrid,ravel,swapaxes,sin,around,in1d,searchsorted,hstack
import matplotlib.pyplot as plt
from matplotlib import gridspec
from matplotlib.colors import LogNorm
#from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
	
	
	
def plot_ionvelhists(velrange_ion,velrange_vsw,velbinsize,ionname,element,charge,vion_sync,vsw_sync,robustmin=1,norm=False,plot_aellig=True):

    #probably useful functions

    #define Hefti diffstream function for Fe9+:
    def Hefti_O6(vmean_proton):
        return 1.13*vmean_proton-46

    def Hefti_Si7(v_proton):
        return 0.92*(1.13*v_proton-46)+21

    def Hefti_Fe9(v_proton):
        return 0.90*(1.13*v_proton-46)+28


    #def psd_correction(v_proton):#only quick estimation, but should be accurate at least to 3km/s
        #return -(10.-13.)/(600-300)*v_proton-7.0


    #timedict= {"Fe7+": time_Fe7,"Fe8+": time_Fe8,"Fe9+": time_Fe9,"Fe10+": time_Fe10,"Fe11+": time_Fe11}
    #vdict= {"Fe7+": v_Fe7,"Fe8+": v_Fe8,"Fe9+": v_Fe9,"Fe10+": v_Fe10,"Fe11+": v_Fe11}

    
    velrange_ion=arange(velrange_ion[0],velrange_ion[-1],velbinsize)
    velrange_vsw=arange(velrange_vsw[0],velrange_vsw[-1],velbinsize)

    #plot velocity histogram
    my_cmap = cm.get_cmap('jet')
    #my_cmap = cm.get_cmap("Spectral_r",1024*16)
    my_cmap.set_under('w')
    h1,bx1,by1=histogram2d(vsw_sync,vion_sync,[velrange_vsw,velrange_ion])		
    h1=h1.T*1.
    Id=velrange_vsw
    """
    #plot unnormalized histogram
    plt.pcolor(bx1,by1,h1,cmap=my_cmap,vmin=.001)	
    #plt.pcolor(bx1,by1,h1,norm=LogNorm(vmin=1, vmax=1000))
    #plt.pcolor(X, Y, Z1, norm=LogNorm(vmin=Z1.min(), vmax=Z1.max()), cmap='PuBu_r')
    #cbar=plt.colorbar(ticks=[200, 400, 600, 800, 1000])
    cbar=plt.colorbar()
    cbar.set_label('Absolute number of Cases')
    plt.plot(Id,Id,color="k", linewidth=2.0)
    plt.ylabel(r"$\rm{v_{Fe^{10+}}[km/s]}$",fontsize=18, color='black')
    plt.xlabel(r"$\rm{v_{proton}[km/s]}$",fontsize=18, color='black')
    plt.axis([velrange_vsw[0],velrange_vsw[-1],velrange_vsw[0],velrange_vsw[-1]])
    plt.show()
    """

    #normalize histogram within each vproton_bin and calculate ion mean velocities per proton bin (=col_ymeans,coly_robustmeans)
    #print h1
    hmax=max(ravel(h1))
    #print "hmax:"
    #print hmax
    h1=swapaxes(h1,0,1)
    h1_new=[]
    col_ymeans=[]
    col_yrobustmeans=[]
    col_yUs=[]

    for col in h1:
        print col
        colmax=float(max(col))
        if colmax>0:
            col_ymean=sum(col*by1[:-1])/sum(col)	
        #print "col-select"	
        #print len(col[col>=10])		
        if len(col[col>=robustmin])>1:
            print len(col[col>=robustmin])
            col_yrobustmean=sum(col[col>=robustmin]*by1[:-1][col>=robustmin])/sum(col[col>=robustmin])	
            #col_yrobustmean=around(col_yrobustmean,decimals=-1)		
            col_yU=sqrt(sum(col[col>=robustmin]/sum(col[col>=robustmin])*(col_yrobustmean-by1[:-1][col>=robustmin])**2)/(len(col[col>=robustmin])*(len(col[col>=robustmin])-1)))
            #calculate robust standard error of the mean, line above
        else:				
            col_ymean=0
            col_yrobustmean=0
            col_yU=0			
        h1_new.append(col)
        col_ymeans.append(col_ymean)
        col_yrobustmeans.append(col_yrobustmean)
        col_yUs.append(col_yU)
    h1_new=array(h1_new)
    col_ymeans=array(col_ymeans)
    velrange_ion=array(velrange_ion)
    velrange_vsw=array(velrange_vsw)			
    col_yrobustmeans=array(col_yrobustmeans)
    col_yUs=array(col_yUs)
    h1_norm=h1_new/float(hmax)
    h1_norm=swapaxes(h1_norm,0,1)

    """
    #plot normed histogram 
    my_cmap = cm.get_cmap("Spectral_r",1024*16)
    my_cmap.set_under('w')
    plt.figure()	 
    plt.pcolor(bx1,by1,h1_norm,cmap=my_cmap,vmin=0.0001)
    cbar=plt.colorbar(ticks=[0.2, 0.4, 0.6, 0.8, 1.0])
    cbar.set_label('Relative number of Cases (normalized to the maximum\ncase number within proton velocity bin)')
    plt.plot(Id,Id,color="k", linewidth=2.0)
    plt.show()
    """

    #create plotgrid
    f, axarr = plt.subplots(2, sharex=True,figsize =(10,10))
    #gs = gridspec.GridSpec(2, 1,height_ratios=[3,1])
    gs = gridspec.GridSpec(2, 1,height_ratios=[2.4,1])
    axarr[0] = plt.subplot(gs[0])
    axarr[1] = plt.subplot(gs[1])


    #plot unnormed histogram with logarithmic colorscale
    h1,bx1,by1=histogram2d(vsw_sync,vion_sync,[velrange_vsw,velrange_ion])		
    h1=h1.T
    #bx1=bx1+0.5*velbinsize
    #by1=by1+0.5*velbinsize
    if norm==True:
        hT=h1.T
        hT_norm=array([])
        for colvp in hT:
            colvp_max=float(max(colvp))
            if colvp_max>0:
                colvp_norm=colvp/colvp_max
            else:
                colvp_norm=colvp#if colvp consists entirely of zeros
            hT_norm=hstack((hT_norm,colvp_norm))
        hT_norm=hT_norm.reshape(len(hT),len(colvp))	
        h_norm=hT_norm.T
        hnorm_max=max(ravel(h_norm))
        hnorm_min=min(ravel(h_norm)[ravel(h_norm)>0])
        print "check normed histogram"
        print len(h1),len(h1[0])
        print len(h_norm),len(h_norm[0])
        print "hnorm_max, hnorm_min_nonzero:", hnorm_max, hnorm_min			
        im=axarr[0].pcolor(bx1,by1,h_norm,norm=LogNorm(vmin=min(h_norm[h_norm>0]), vmax=h_norm.max()))
    else:		
        #return bx1,by1,h1
        im=axarr[0].pcolor(bx1,by1,h1,norm=LogNorm(vmin=1, vmax=h1.max()))

    #im=axarr[0].pcolor(bx1,by1,h1,norm=LogNorm(vmin=1, vmax=h1.max()))
    Id=arange(velrange_vsw[0],velrange_vsw[-1],0.1)

    axarr[0].plot(Id,Id,color="k", linewidth=2.5)
    #axarr[0].set_ylabel(r"$v_{%s}\ \mathrm{[km/s]}$"%(ion),fontsize=18)
    axarr[0].axis([velrange_vsw[0],velrange_vsw[-1],velrange_ion[0],velrange_ion[-1]])
    #axarr[0].plot(velrange_vsw[col_yrobustmeans>0]+velbinsize,col_yrobustmeans[col_yrobustmeans>0]+velbinsize,linewidth=2.0,color="m")#plot robust 
    #mean ion velocity
    #return col_yrobustmeans, [col_yrobustmeans>0]
    axarr[0].plot(velrange_vsw[col_yrobustmeans>0]+0.5*velbinsize,col_yrobustmeans[col_yrobustmeans>0]+0.5*velbinsize,linewidth=2.5,color="b",label="robust mean ion velocity")#plot robust 
    #axarr[0].plot(Id,Hefti_Fe9(Id),color=(0.4,0.4,0.4),linestyle="-",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")

    if plot_aellig==True:
        #plot aellig results for respective ions
        if ionname=="O6+":
            axarr[0].plot(Id,Hefti_O8(Id),color="k",linestyle="--",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")	
        if ionname=="Si7+":
            axarr[0].plot(Id,Hefti_Si7(Id),color="k",linestyle="--",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")
        if ionname=="Fe9+":
            axarr[0].plot(Id,Hefti_Si7(Id),color="k",linestyle="--",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")

    #axarr[0].legend(loc="lower right",prop={'size':13})
    axarr[0].legend(loc="lower right",prop={'size':13})
    axarr[0].axis([velrange_vsw[0],velrange_vsw[-1],velrange_ion[0],velrange_ion[-1]])
    axarr[0].set_ylabel(r"$\rm{v_{%s}}\ [km/s]$"%(ionname),fontsize=31)
    axarr[0].tick_params(axis='both', which='major', labelsize=20)
    #axarr[0].text(280,600,r"$\mathrm{Fe}^{8+}$", fontsize=45)
    axarr[0].text(350,800,r"$\mathrm{%s}^{%i+}$"%(element,charge), fontsize=40)
    #axarr[0].text(280,600,r"$\mathrm{Fe}^{10+}$", fontsize=45)
    plt.show()

    #plot velocity difference
    veldiff=col_yrobustmeans[col_yrobustmeans>0]-velrange_vsw[col_yrobustmeans>0]
    axarr[1].bar(velrange_vsw[col_yrobustmeans>0],veldiff,width=velbinsize,color="b",label=r"${v_{{O}^{6+}}-v_{proton}}$")
    #axarr[1].bar(velrange_vsw[col_yrobustmeans>0],veldiff,width=velbinsize,color="m")
    if plot_aellig==True:
        axarr[1].bar(velrange_vsw[col_yrobustmeans>0],Hefti_Fe9(velrange_vsw[col_yrobustmeans>0])-velrange_vsw[col_yrobustmeans>0],width=velbinsize,color="k",alpha=0.5)
    axarr[1].plot([velrange_vsw[0],velrange_vsw[-1]],[0,0],color="k")
    #plt.legend(loc="upper left",prop={'size':18})
    """
    axarr[1].set_xlabel(r"$\rm{v_{proton}\ [km/s]}$",fontsize=18, color='black')
    axarr[1].set_ylabel(r"$v_{diff}\ \mathrm{[km/s]}$",fontsize=18, color='black')
    #axarr[1].axis([velrang_vswe[0],velrange_vsw[-1],min(veldiff)-5,max(veldiff)+5])
    axarr[1].axis([velrange_vsw[0],velrange_vsw[-1],-25,65])
    """
    axarr[1].set_xlabel(r"$\rm{v_{proton}\ [km/s]}$",fontsize=31, color='black')
    axarr[1].set_ylabel(r"$\rm{v_{diff}\ [km/s]}$",fontsize=33, color='black')
    axarr[1].axis([velrange_vsw[0],velrange_vsw[-1],-25,65])
    axarr[1].tick_params(axis='both', which='major', labelsize=20)
    plt.show()


    #plot robust standard error of the mean for ion-velocities
    col_yUs=col_yUs[col_yUs>0]
    ##print "robust_standard error of the mean"
    ##print len(col_yUs)
    ##print len(col_yrobustmeans[col_yrobustmeans>0]-velrange_vsw[col_yrobustmeans>0])
    ##print len(velrange_vsw[col_yrobustmeans>0])


    axarr[1].errorbar(velrange_vsw[col_yrobustmeans>0]+0.5*velbinsize,col_yrobustmeans[col_yrobustmeans>0]-velrange_vsw[col_yrobustmeans>0],yerr=col_yUs,
linestyle="None",marker="_",markersize=10,color="k")
    plt.show()


    """
    f.subplots_adjust(right=0.8)
    #cbar_ax = f.add_axes([0.85, 0.35, 0.05, 0.55])#for 3:1 format
    #cbar_ax = f.add_axes([0.85, 0.415, 0.05, 0.485])#for 2:1 format
    cbar_ax = f.add_axes([0.85, 0.387, 0.05, 0.51])#for 2.4:1 format
    cb=f.colorbar(im,cax=cbar_ax)
    cb.set_label('Number of cases', rotation=90, fontsize=13)
    plt.show()
    """

    #adjust plots and colorbar
    f.subplots_adjust(right=0.8)
    #cbar_ax = f.add_axes([0.85, 0.35, 0.05, 0.55])#3:1 format
    cbar_ax = f.add_axes([0.85, 0.387, 0.05, 0.51])#for 2.4:1 format
    cb=f.colorbar(im,cax=cbar_ax)
    for t in cb.ax.get_yticklabels():
        t.set_fontsize(20)
    #cb.set_label(r'$\mathrm{Number\ of\ cases\ per\ bin}$', rotation=90, fontsize=27)
    if norm==True:
        cb.set_label(r'$\mathrm{Relative\ frequency\ of\ occurrence\ per\ bin}$', rotation=90, fontsize=27)
    else:
        cb.set_label(r'$\mathrm{Number\ of\ occurrence\ per\ bin}$', rotation=90, fontsize=27)
    plt.show()


def plot_ionvelalfhists(velrange_ion,velrange_vsw,velbinsize,ionname,element,charge,vion_sync,vsw_sync,robustmin=1,norm=False,plot_aellig=True):

    #probably useful functions

    #define Hefti diffstream function for Fe9+:
    def Hefti_O6(vmean_proton):
        return 1.13*vmean_proton-46

    def Hefti_Si7(v_proton):
        return 0.92*(1.13*v_proton-46)+21

    def Hefti_Fe9(v_proton):
        return 0.90*(1.13*v_proton-46)+28


    #def psd_correction(v_proton):#only quick estimation, but should be accurate at least to 3km/s
        #return -(10.-13.)/(600-300)*v_proton-7.0


    #timedict= {"Fe7+": time_Fe7,"Fe8+": time_Fe8,"Fe9+": time_Fe9,"Fe10+": time_Fe10,"Fe11+": time_Fe11}
    #vdict= {"Fe7+": v_Fe7,"Fe8+": v_Fe8,"Fe9+": v_Fe9,"Fe10+": v_Fe10,"Fe11+": v_Fe11}

    
    velrange_ion=arange(velrange_ion[0],velrange_ion[-1],velbinsize[0])
    velrange_vsw=arange(velrange_vsw[0],velrange_vsw[-1],velbinsize[1])

    #plot velocity histogram
    my_cmap = cm.get_cmap('jet')
    #my_cmap = cm.get_cmap("Spectral_r",1024*16)
    my_cmap.set_under('w')
    h1,bx1,by1=histogram2d(vsw_sync,vion_sync,[velrange_vsw,velrange_ion])		
    h1=h1.T*1.
    Id=velrange_vsw
    """
    #plot unnormalized histogram
    plt.pcolor(bx1,by1,h1,cmap=my_cmap,vmin=.001)	
    #plt.pcolor(bx1,by1,h1,norm=LogNorm(vmin=1, vmax=1000))
    #plt.pcolor(X, Y, Z1, norm=LogNorm(vmin=Z1.min(), vmax=Z1.max()), cmap='PuBu_r')
    #cbar=plt.colorbar(ticks=[200, 400, 600, 800, 1000])
    cbar=plt.colorbar()
    cbar.set_label('Absolute number of Cases')
    plt.plot(Id,Id,color="k", linewidth=2.0)
    plt.ylabel(r"$\rm{v_{Fe^{10+}}[km/s]}$",fontsize=18, color='black')
    plt.xlabel(r"$\rm{v_{proton}[km/s]}$",fontsize=18, color='black')
    plt.axis([velrange_vsw[0],velrange_vsw[-1],velrange_vsw[0],velrange_vsw[-1]])
    plt.show()
    """

    #normalize histogram within each vproton_bin and calculate ion mean velocities per proton bin (=col_ymeans,coly_robustmeans)
    #print h1
    hmax=max(ravel(h1))
    #print "hmax:"
    #print hmax
    h1=swapaxes(h1,0,1)
    h1_new=[]
    col_ymeans=[]
    col_yrobustmeans=[]
    col_yUs=[]

    """
    for col in h1:
        print col
        colmax=float(max(col))
        if colmax>0:
            col_ymean=sum(col*by1[:-1])/sum(col)	
        #print "col-select"	
        #print len(col[col>=10])		
        if len(col[col>=robustmin])>1:
            print len(col[col>=robustmin])
            col_yrobustmean=sum(col[col>=robustmin]*by1[:-1][col>=robustmin])/sum(col[col>=robustmin])	
            #col_yrobustmean=around(col_yrobustmean,decimals=-1)		
            col_yU=sqrt(sum(col[col>=robustmin]/sum(col[col>=robustmin])*(col_yrobustmean-by1[:-1][col>=robustmin])**2)/(len(col[col>=robustmin])*(len(col[col>=robustmin])-1)))
            #calculate robust standard error of the mean, line above
        else:				
            col_ymean=0
            col_yrobustmean=0
            col_yU=0			
        h1_new.append(col)
        col_ymeans.append(col_ymean)
        col_yrobustmeans.append(col_yrobustmean)
        col_yUs.append(col_yU)
    h1_new=array(h1_new)
    col_ymeans=array(col_ymeans)
    velrange_ion=array(velrange_ion)
    velrange_vsw=array(velrange_vsw)			
    col_yrobustmeans=array(col_yrobustmeans)
    col_yUs=array(col_yUs)
    h1_norm=h1_new/float(hmax)
    h1_norm=swapaxes(h1_norm,0,1)
    """
    col_yrobustmeans=[]
    for h in h1:
        if sum(h):
            col_yrobustmeans.append(average(velrange_ion[:-1],weights=h))
        else:
            col_yrobustmeans.append(0.)
        
    print "ave :", col_yrobustmeans
    col_yrobustmeans=array(col_yrobustmeans)
    col_yUs=0.1*col_yrobustmeans
    
        
    """
    #plot normed histogram 
    my_cmap = cm.get_cmap("Spectral_r",1024*16)
    my_cmap.set_under('w')
    plt.figure()	 
    plt.pcolor(bx1,by1,h1_norm,cmap=my_cmap,vmin=0.0001)
    cbar=plt.colorbar(ticks=[0.2, 0.4, 0.6, 0.8, 1.0])
    cbar.set_label('Relative number of Cases (normalized to the maximum\ncase number within proton velocity bin)')
    plt.plot(Id,Id,color="k", linewidth=2.0)
    plt.show()
    """

    #create plotgrid
    f, axarr = plt.subplots(2, sharex=True,figsize =(10,10))
    #gs = gridspec.GridSpec(2, 1,height_ratios=[3,1])
    gs = gridspec.GridSpec(2, 1,height_ratios=[2.4,1])
    axarr[0] = plt.subplot(gs[0])
    axarr[1] = plt.subplot(gs[1])


    #plot unnormed histogram with logarithmic colorscale
    h1,bx1,by1=histogram2d(vsw_sync,vion_sync,[velrange_vsw,velrange_ion])		
    h1=h1.T*1.
    #bx1=bx1+0.5*velbinsize
    #by1=by1+0.5*velbinsize
    if norm==True:
        hT=h1.T
        hT_norm=array([])
        for colvp in hT:
            colvp_max=float(max(colvp))
            if colvp_max>0:
                colvp_norm=colvp/colvp_max
            else:
                colvp_norm=colvp#if colvp consists entirely of zeros
            hT_norm=hstack((hT_norm,colvp_norm))
        hT_norm=hT_norm.reshape(len(hT),len(colvp))	
        h_norm=hT_norm.T
        hnorm_max=max(ravel(h_norm))
        hnorm_min=min(ravel(h_norm)[ravel(h_norm)>0])
        print "check normed histogram"
        print len(h1),len(h1[0])
        print len(h_norm),len(h_norm[0])
        print "hnorm_max, hnorm_min_nonzero:", hnorm_max, hnorm_min			
        im=axarr[0].pcolor(bx1,by1,h_norm,norm=LogNorm(vmin=min(h_norm[h_norm>0]), vmax=h_norm.max()))
    else:		
        #return bx1,by1,h1
        im=axarr[0].pcolor(bx1,by1,h1,norm=LogNorm(vmin=1, vmax=h1.max()))

    #im=axarr[0].pcolor(bx1,by1,h1,norm=LogNorm(vmin=1, vmax=h1.max()))
    Id=arange(velrange_vsw[0],velrange_vsw[-1],0.1)

    axarr[0].plot(Id,Id,color="k", linewidth=2.5)
    #axarr[0].set_ylabel(r"$v_{%s}\ \mathrm{[km/s]}$"%(ion),fontsize=18)
    axarr[0].axis([velrange_vsw[0],velrange_vsw[-1],velrange_ion[0],velrange_ion[-1]])
    #axarr[0].plot(velrange_vsw[col_yrobustmeans>0]+velbinsize,col_yrobustmeans[col_yrobustmeans>0]+velbinsize,linewidth=2.0,color="m")#plot robust 
    #mean ion velocity
    #return col_yrobustmeans, [col_yrobustmeans>0]
    axarr[0].plot(velrange_vsw[col_yrobustmeans>0]+0.5*velbinsize[0],col_yrobustmeans[col_yrobustmeans>0]+0.5*velbinsize[1],linewidth=2.5,color="b",label="robust mean ion velocity")#plot robust 
    axarr[0].plot(velrange_vsw[:-1]+0.5*velbinsize[0],col_yrobustmeans+0.5*velbinsize[1],linewidth=2.5,color="b",label="robust mean ion velocity")#plot robust 
    #axarr[0].plot(Id,Hefti_Fe9(Id),color=(0.4,0.4,0.4),linestyle="-",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")

    if plot_aellig==True:
        #plot aellig results for respective ions
        if ionname=="O6+":
            axarr[0].plot(Id,Hefti_O8(Id),color="k",linestyle="--",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")	
        if ionname=="Si7+":
            axarr[0].plot(Id,Hefti_Si7(Id),color="k",linestyle="--",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")
        if ionname=="Fe9+":
            axarr[0].plot(Id,Hefti_Si7(Id),color="k",linestyle="--",linewidth=2.5, label="mean ion velocity obtained\nby Hefti (1998)")

    #axarr[0].legend(loc="lower right",prop={'size':13})
    axarr[0].legend(loc="lower right",prop={'size':13})
    axarr[0].axis([velrange_vsw[0],velrange_vsw[-1],velrange_ion[0],velrange_ion[-1]])
    axarr[0].set_ylabel(r"$\rm{v_{%s}}\ [km/s]$"%(ionname),fontsize=31)
    axarr[0].tick_params(axis='both', which='major', labelsize=20)
    #axarr[0].text(280,600,r"$\mathrm{Fe}^{8+}$", fontsize=45)
    axarr[0].text(350,800,r"$\mathrm{%s}^{%i+}$"%(element,charge), fontsize=40)
    #axarr[0].text(280,600,r"$\mathrm{Fe}^{10+}$", fontsize=45)
    plt.show()

    #plot velocity difference
    veldiff=col_yrobustmeans[col_yrobustmeans>0]-velrange_vsw[col_yrobustmeans>0]
    axarr[1].bar(velrange_vsw[col_yrobustmeans>0],veldiff,width=velbinsize[1],color="b",label=r"${v_{{O}^{6+}}-v_{proton}}$")
    #axarr[1].bar(velrange_vsw[col_yrobustmeans>0],veldiff,width=velbinsize,color="m")
    if plot_aellig==True:
        axarr[1].bar(velrange_vsw[col_yrobustmeans>0],Hefti_Fe9(velrange_vsw[col_yrobustmeans>0])-velrange_vsw[col_yrobustmeans>0],width=velbinsize,color="k",alpha=0.5)
    axarr[1].plot([velrange_vsw[0],velrange_vsw[-1]],[0,0],color="k")
    #plt.legend(loc="upper left",prop={'size':18})
    """
    axarr[1].set_xlabel(r"$\rm{v_{proton}\ [km/s]}$",fontsize=18, color='black')
    axarr[1].set_ylabel(r"$v_{diff}\ \mathrm{[km/s]}$",fontsize=18, color='black')
    #axarr[1].axis([velrang_vswe[0],velrange_vsw[-1],min(veldiff)-5,max(veldiff)+5])
    axarr[1].axis([velrange_vsw[0],velrange_vsw[-1],-25,65])
    """
    axarr[1].set_xlabel(r"$\rm{v_{proton}\ [km/s]}$",fontsize=31, color='black')
    axarr[1].set_ylabel(r"$\rm{v_{diff}\ [km/s]}$",fontsize=33, color='black')
    axarr[1].axis([velrange_vsw[0],velrange_vsw[-1],-25,65])
    axarr[1].tick_params(axis='both', which='major', labelsize=20)
    plt.show()


    #plot robust standard error of the mean for ion-velocities
    col_yUs=col_yUs[col_yUs>0]
    ##print "robust_standard error of the mean"
    ##print len(col_yUs)
    ##print len(col_yrobustmeans[col_yrobustmeans>0]-velrange_vsw[col_yrobustmeans>0])
    ##print len(velrange_vsw[col_yrobustmeans>0])


    axarr[1].errorbar(velrange_vsw[col_yrobustmeans>0]+0.5*velbinsize[1],col_yrobustmeans[col_yrobustmeans>0]-velrange_vsw[col_yrobustmeans>0],yerr=col_yUs,
linestyle="None",marker="_",markersize=10,color="k")
    plt.show()


    """
    f.subplots_adjust(right=0.8)
    #cbar_ax = f.add_axes([0.85, 0.35, 0.05, 0.55])#for 3:1 format
    #cbar_ax = f.add_axes([0.85, 0.415, 0.05, 0.485])#for 2:1 format
    cbar_ax = f.add_axes([0.85, 0.387, 0.05, 0.51])#for 2.4:1 format
    cb=f.colorbar(im,cax=cbar_ax)
    cb.set_label('Number of cases', rotation=90, fontsize=13)
    plt.show()
    """

    #adjust plots and colorbar
    f.subplots_adjust(right=0.8)
    #cbar_ax = f.add_axes([0.85, 0.35, 0.05, 0.55])#3:1 format
    cbar_ax = f.add_axes([0.85, 0.387, 0.05, 0.51])#for 2.4:1 format
    cb=f.colorbar(im,cax=cbar_ax)
    for t in cb.ax.get_yticklabels():
        t.set_fontsize(20)
    #cb.set_label(r'$\mathrm{Number\ of\ cases\ per\ bin}$', rotation=90, fontsize=27)
    if norm==True:
        cb.set_label(r'$\mathrm{Relative\ frequency\ of\ occurrence\ per\ bin}$', rotation=90, fontsize=27)
    else:
        cb.set_label(r'$\mathrm{Number\ of\ occurrence\ per\ bin}$', rotation=90, fontsize=27)
    plt.show()
