from math import sin,asin,cos,acos,tan,atan,exp,pi,sqrt,log
from Gnuplot import Gnuplot
from libacepy.fluxes import getdeltav
from libacepy.ancil import int2str
from numpy import array

class dutycycle:
    "Class dutycycle : Calculates the dutycycle for ACE/SWICS. The assumption of double streaming aligned with the magnetic field is made. The velocity distribution is aproximated by a distribution consiting of two gaussians. The center of the first peak is at x=SWspeed in the SE frame of reference. The center of the second is shifted along the X-axis by the local alfven speed. Both are gyrotropic and stronger heated perpendicular to the magnetic field in respect to the parallel temperature (same vths for both). Additionally the ratio of the volume P2/P1 is needed."   
    def __init__(self,vsw,vc,va,bxy,bz,axy,az,dens,peakr,vth,vthr,countspec,ionname,ionmass,ioncharge,effpath):
        "Input : \n vsw(float) -> solar wind speed from SWEPAM Protons , X-Position of Peak1 in SE frame\n va(float) -> Alfven speed from SWEPAM Protons density , Shift between X-Position of Peak1 and Peak2 in MAG frame\n bxy(float) -> angle between SE and MAG frame in XY Plane (Rotation around Z-Axis)\n bz(float) -> angle between SE and MAG frame in ZX Plane (Rotation aorund Y-Axis)\n axy(float) -> angle between SE and SC frame in XY Plane (Rotation around Z-Axis)\n az(float) -> angle between SE and SC frame in ZX Plane (Rotation aorund Y-Axis)\n dens (float) -> absolute density in cm^-3\npeakr(float) -> ratio of Peak heights P2/P1\n vth(float) -> thermal speed parallel to Magnetic field\n vthr(float) -> ratio of perpendicular to parallel thermal speed. vthper/vthpara\n varr -> up to now without use (shall contain velocities for wich the dutycycle will be calculated."
        # input is set
        self.vsw=vsw                         # solar wind speed from SWEPAM Protons ; X-Position of centre of mass from protons (origin of mag coord.)
        self.vc=vc                           # position of core in mag coord. (in respect to vsw along the mag direction)
        self.va=va                           # Alfven speed from SWEPAM Protons density ; Shift between X-Position of Peak1 and Peak2 in MAG frame
        self.bxy=bxy                         # angle between SE and MAG frame in XY Plane (Rotation around Z-Axis) 
        self.bz=bz                           # angle between SE and MAG frame in ZX Plane (Rotation aorund Y-Axis)
        self.axy=axy                         # angle between SE and SC frame in XY Plane (Rotation around Z-Axis)
        self.az=az                           # angle between SE and SC frame in ZX Plane (Rotation aorund Y-Axis)
        self.dens=dens                       # absolute density cm^-3
        self.peakr=peakr                     # ratio of Peak heights P2/P1
        self.vth=vth                         # thermal speed parallel to Magnetic field
        self.vthr=vthr                       # ratio of perpendicular to parallel thermal speed. vthper/vthpara
        self.countspec=countspec             # array [[steps][vel,counts,cr-error]]
        self.ionname=ionname                 # name of ion for efficiencies
        self.ionmass=ionmass                 # mass of ion for getdeltav (He2+ = 4.)
        self.ioncharge=ioncharge             # charge of ion for getdeltav (he2+ = 2.)
        self.effpath=effpath                 # path of efficiencies files
        self.projection=[]                   # container for calculated projection of the two Peaks to the X-Axis of the SE Frame
        self.virtualspec=[]                  # container for calculated virtual spectrum of the two Peaks to the X-Axis of the SE Frame
        self.dutycycle=[]                    # container for calculated dutycycle
        self.efficiencies=[]                 # container for efficiencies
        self.entr_thetaarr=[]                # container for integration space
        self.entr_phiarr=[]                  # container for integration space
        self.rcut_thetaarr=[]                # container for integration space
        self.rcut_phiarr=[]                  # container for integration space
        self.rot_angarr=[]                   # container for rotation angles
        self.x0m1=0.                         # X-Position of Peak1 in MAG frame (calculated by calc_peakpos)
        self.y0m1=0.                         # Y-Position of Peak1 in MAG frame (calculated by calc_peakpos)
        self.z0m1=0.                         # Z-Position of Peak1 in MAG frame (calculated by calc_peakpos)
        self.x0m2=0.                         # X-Position of Peak2 in MAG frame (calculated by calc_peakpos)
        self.y0m2=0.                         # Y-Position of Peak2 in MAG frame (calculated by calc_peakpos)
        self.z0m2=0.                         # Z-Position of Peak2 in MAG frame (calculated by calc_peakpos)
        self.intfrac=2.
        self.intangstep=(pi/180.)/self.intfrac # anglestep for integration (=1/intfrac : intfrac=2. -> intangstep = 0.5 degrees) 
        self.rotfrac=.25
        self.rotangstep=(pi/180.)/self.rotfrac # anglestep for rotation of the entrance system (=1/rotfrac : rotfrac=.5 -> rotangstep = 2. degrees)
        # frequently used quantities are derived! this is done to minimize computing time 
        self.dxy=bxy-axy                     # angle between SC and MAG frame in XY Plane (Rotation around Z-Axis)
        self.dz=bz-az                        # angle between SC and SE frame in ZX Plane (Rotation aorund Y-Axis)
        self.geomfac=0.0225*1e-10            # instrumental geometry factor in km^2
        self.denskm=self.dens*1e15           #    ""      ""    km^-3
        self.Vp1p2=(2.*pi)**1.5*self.vth*(self.vth*self.vthr)**2
        self.p1hight=self.denskm/(1.+self.peakr)/self.Vp1p2
        self.p2hight=self.denskm*self.peakr/(1.+self.peakr)/self.Vp1p2
        self.cosbxy=cos(bxy)
        self.sinbxy=sin(bxy)
        self.cosbz=cos(bz)
        self.sinbz=sin(bz)
        self.cosaxy=cos(axy)
        self.sinaxy=sin(axy)
        self.cosaz=cos(az)
        self.sinaz=sin(az)
        self.cosdxy=cos(self.dxy)
        self.sindxy=sin(self.dxy)
        self.cosdz=cos(self.dz)
        self.sindz=sin(self.dz)
        self.calc_peakpos()                  # x0m1,y0m1,z0m1,x0m2,y0m2,z0m2 are calcuated
        self.calc_rcut_angles()
        self.calc_entrances_angles()
        self.calc_rot_angles()
        self.load_efficiencies()
        self.entrances=[]                    # used to visualize entrance system 
        for i in range(180):
            self.entrances.append([])
        self.cut=[]                          # used to visualize rcut
        self.countspec2=[]                   # all zero counts are sorted out. Projection is calculated only for the nonzero points 
        for val in self.countspec:
            if (val[1]>0.):
                self.countspec2.append(val)
                
    # load efficiencies into memory
    def load_efficiencies(self):
        dim=58
        for i in range(dim):
            self.efficiencies.append([])
        dir=""
        for i in range(580/5):
            filename=self.effpath+int2str(i*5)+"/"+self.ionname+".eff"
            effin1=open(filename)
            filename=self.effpath+int2str(i*5+1)+"/"+self.ionname+".eff"
            effin2=open(filename)
            filename=self.effpath+int2str(i*5+2)+"/"+self.ionname+".eff"
            effin3=open(filename)
            filename=self.effpath+int2str(i*5+3)+"/"+self.ionname+".eff"
            effin4=open(filename)
            filename=self.effpath+int2str(i*5+4)+"/"+self.ionname+".eff"
            effin5=open(filename)
            for j in range(dim):
                s1=effin1.readline()
                k1=s1.split()
                s2=effin2.readline()
                k2=s2.split()
                s3=effin3.readline()
                k3=s3.split()
                s4=effin4.readline()
                k4=s4.split()
                s5=effin5.readline()
                k5=s5.split()
                self.efficiencies[j].append((float(k1[1])+float(k2[1])+float(k3[1])+float(k4[1])+float(k5[1]))/5.)
            effin1.close()
            effin2.close()
            effin3.close()
            effin4.close()
            effin5.close()
        self.efficiencies=array(self.efficiencies)
            
    # sets bxy to a new value and recalculates all associated quantities 
    def set_bxy(self,bxy):
        "sets bxy to a new value and recalculates all associated quantities"
        self.bxy=bxy
        self.cosbxy=cos(bxy)
        self.sinbxy=sin(bxy)
        self.dxy=bxy-self.axy
        self.cosdxy=cos(self.dxy)
        self.sindxy=sin(self.dxy)
        
    # sets bz to a new value and recalculates all associated quantities 
    def set_bz(self,bz):
        "sets bz to a new value and recalculates all associated quantities" 
        self.bz=bz
        self.cosbz=cos(bz)
        self.sinbz=sin(bz)
        self.dz=bz-self.az
        self.cosdz=cos(self.dz)
        self.sindz=sin(self.dz)

    # sets axy to a new value and recalculates all associated quantities 
    def set_axy(self,axy):
        "sets axy to a new value and recalculates all associated quantities"
        self.axy=axy
        self.cosaxy=cos(axy)
        self.sinaxy=sin(axy)
        self.dxy=self.bxy-axy
        self.cosdxy=cos(self.dxy)
        self.sindxy=sin(self.dxy)
        
    # sets az to a new value and recalculates all associated quantities 
    def set_az(self,az):
        "sets az to a new value and recalculates all associated quantities"
        self.az=az
        self.cosaz=cos(az)
        self.sinaz=sin(az)
        self.dz=self.bz-az
        self.cosdz=cos(self.dz)
        self.sindz=sin(self.dz)

        
    # calculates Peak positions of the two peaks in MAG frame
    def calc_peakpos(self):
        "calculates Peak positions of the two peaks in MAG frame"
        self.x0m1=self.vsw*self.cosbxy*self.cosbz+self.vc
        self.y0m1=-self.vsw*self.sinbxy
        self.z0m1=-self.vsw*self.cosbxy*self.sinbz
        self.x0m2=self.x0m1+self.va
        self.y0m2=self.y0m1
        self.z0m2=self.z0m1
        
    # simple gaussian. standardisation has to be done seperately!!!
    def gauss(self,pos,sigma):
        "simple gaussian : returns exp(-(pos)**2/(2.*sigma**2)) ; Standardization and shift of the peak position has to be done outside!"
        if ((pos < 3.*sigma) and (pos > -3.*sigma)):
            return exp(-(pos**2)/(2.*sigma**2))
        else:
            return 0.
        
    # Peak1 in MAG kartesian koordinates
    def peak1mag(self,x,y,z):
        return self.p1hight*self.gauss(x,self.vth)*self.gauss(y,self.vth*self.vthr)*self.gauss(z,self.vth*self.vthr)

    # Peak2 in MAG kartesian koordinates
    def peak2mag(self,x,y,z):
        return self.p2hight*self.gauss(x,self.vth)*self.gauss(y,(self.vth*self.vthr))*self.gauss(z,(self.vth*self.vthr))

    # Peak1 in SE spherical koordinates
    def peak1se(self,r,theta,phi):
        # tranform se to mag koordinates
        x=self.xse2mag(r,theta,phi)-self.x0m1
        y=self.yse2mag(r,theta,phi)-self.y0m1
        z=self.zse2mag(r,theta,phi)-self.z0m1
        return self.peak1mag(x,y,z)

    # Peak2 in SE spherical koordinates
    def peak2se(self,r,theta,phi):
        # tranform se to mag koordinates
        x=self.xse2mag(r,theta,phi)-self.x0m2
        y=self.yse2mag(r,theta,phi)-self.y0m2
        z=self.zse2mag(r,theta,phi)-self.z0m2
        return self.peak2mag(x,y,z)

    # Peak1 in SC spherical koordinates including a rotation with angle gamma (cosg=cos(gamma),sing=sin(gamma) around X-Axis 
    def peak1sc(self,r,theta,phi,cosg,sing):
        # rotate Spacecraft 
        xsc=self.xrotsc(r,theta,phi,cosg,sing)
        ysc=self.yrotsc(r,theta,phi,cosg,sing)
        zsc=self.zrotsc(r,theta,phi,cosg,sing)
        # tranform sc to mag koordinates
        x=self.xsc2mag(xsc,ysc,zsc)-self.x0m1
        y=self.ysc2mag(xsc,ysc,zsc)-self.y0m1
        z=self.zsc2mag(xsc,ysc,zsc)-self.z0m1
        return self.peak1mag(x,y,z)

    # Peak2 in SC spherical koordinates including a rotation with angle gamma (cosg=cos(gamma),sing=sin(gamma) around X-Axis 
    def peak2sc(self,r,theta,phi,cosg,sing):
        # rotate Spacecraft 
        xsc=self.xrotsc(r,theta,phi,cosg,sing)
        ysc=self.yrotsc(r,theta,phi,cosg,sing)
        zsc=self.zrotsc(r,theta,phi,cosg,sing)
        # tranform sc to mag koordinates
        x=self.xsc2mag(xsc,ysc,zsc)-self.x0m2
        y=self.ysc2mag(xsc,ysc,zsc)-self.y0m2
        z=self.zsc2mag(xsc,ysc,zsc)-self.z0m2
        return self.peak2mag(x,y,z)

    # Serves to check coordinate transformations without any use for the dutycycle calculation
    def check_transformations(self):
        for r in range(470,640,10):
            gamma=(pi/180.)*10.
            print "xse,xsc = ",self.xse2mag(float(r),pi/2.,0.),self.xsc2mag(float(r),pi/2.,0.,cos(gamma),sin(gamma))
            print "yse,ysc = ",self.yse2mag(float(r),pi/2.,0.),self.ysc2mag(float(r),pi/2.,0.,cos(gamma),sin(gamma))
            print "zse,zsc = ",self.zse2mag(float(r),pi/2.,0.),self.zsc2mag(float(r),pi/2.,0.,cos(gamma),sin(gamma))

    # integrates the distribution consitiong of the two Peaks over 2pi for a given |vges| (parameter r) 
    def calc_rcut(self,r):
        #print "calc ",float(r)," cut"
        integral=0.
        for theta in self.rcut_thetaarr:
            for phi in self.rcut_phiarr:
                #xt=self.xse2mag(r,theta,phi)
                #yt=self.yse2mag(r,theta,phi)
                #zt=self.zse2mag(r,theta,phi)
                #self.cut.append([xt,yt,zt])
                #print "cut : ",sqrt(xt**2+yt**2+zt**2)
                integral+=(self.peak1se(r,theta,phi)+self.peak2se(r,theta,phi))*r**2*sin(theta)*self.intangstep**2
        return integral

    # the projection of the two Peaks to the X-Axis of the SE frame is calculated
    def calc_projection(self):
        self.projection=[]
        self.diffprojection=[]
        step=-1
        for val in self.countspec:
            step+=1
            #if (val[0]>self.vsw-5*self.vth*self.vthr and val[0]<self.vsw+5*self.vth*self.vthr):
            #if (val[1]>0.):
            if (1):
                self.projection.append([float(val[0]),self.calc_rcut(float(val[0]))*getdeltav(self.ionmass,self.ioncharge,step),step])
                self.diffprojection.append([float(val[0]),self.calc_rcut(float(val[0]))/1e15,step])
        self.calc_projection_moments()

    def calc_projection_moments(self):
        "calculates moments of diffprojection"
        A=0.
        v0=0.
        vth=0.
        dv=[]
        for i in range(len(self.diffprojection)):
            if (i>0 and i<len(self.diffprojection)-1):
                tmpdv=(self.diffprojection[i-1][0]-self.diffprojection[i+1][0])*0.5
                #print "dutyc pr dv = ",tmpdv
                A+=self.diffprojection[i][1]*tmpdv
                dv.append(tmpdv)
            elif(i==0):
                tmpdv=(self.diffprojection[0][0]-self.diffprojection[i+1][0])*1.
                A+=self.diffprojection[i][1]*tmpdv
                dv.append(tmpdv)
            elif(i==len(self.diffprojection)-1):
                tmpdv=(self.diffprojection[i-1][0]-self.diffprojection[i][0])*1.
                A+=self.diffprojection[i][1]*tmpdv
                dv.append(tmpdv)
        for i in range(len(self.diffprojection)):
            v0+=self.diffprojection[i][0]*self.diffprojection[i][1]*dv[i]
        if (A>=0):
            v0=v0/A
        for i in range(len(self.diffprojection)):
            vth+=(self.diffprojection[i][0]-v0)**2*self.diffprojection[i][1]*dv[i]
        if (A>=0):
            vth=vth/A
        vth=sqrt(vth)
        self.prvth=vth
        self.prdens=A
        self.prvel=v0
        
    def calc_virtualspec_moments(self):
        A=0.     #-->  integral
        v0=0.    #-->  center of mass
        vth=0. #-->  sigma^2
        for i in range(len(self.virtualspec)):
            A=A+self.virtualspec[i][1]
        if (A>0.):
            for i in range(len(self.virtualspec)):
                v0=v0+self.virtualspec[i][0]*self.virtualspec[i][1]
            v0=v0/A
            for i in range(len(self.virtualspec)):
                vth+=self.virtualspec[i][1]*(self.virtualspec[i][0]-v0)**2
            vth=sqrt(vth/A)
        self.vsvth=vth
        self.vsdens=A
        self.vsvel=v0


    # integrates the distribution for a given |vges| (parameter r) along the acceptance of the collimator, that has been rotated in the SC frame, with angle gamma.   
    def calc_timestep(self,r,dr,gamma,step):
        #print "gamma = ",gamma
        cosg=cos(gamma)
        sing=sin(gamma)
        integral=0.
        i=-1
        for theta in self.entr_thetaarr:
            i+=1
            for phi in self.entr_phiarr:
                #xsc=self.xrotsc(r,theta,phi,cosg,sing)
                #ysc=self.yrotsc(r,theta,phi,cosg,sing)
                #zsc=self.zrotsc(r,theta,phi,cosg,sing)
                #xt=self.xsc2mag(xsc,ysc,zsc)
                #yt=self.ysc2mag(xsc,ysc,zsc)
                #zt=self.zsc2mag(xsc,ysc,zsc)
                #print "rot : ",sqrt(xt**2+yt**2+zt**2)
                #self.entrances[rotstep].append([xt,yt,zt])
                if (self.efficiencies[step][i]>0.):
                    #for i in range(-2,3):
                    #    if (i!=0):
                    #        dx=(dr/2.)/float(i)
                    #    else:
                    #        dx=0.
                    dx=0.
                    integral+=((self.peak1sc(r+dx,theta,phi,cosg,sing)+self.peak2sc(r+dx,theta,phi,cosg,sing))*(r+dx)**2*sin(theta)*self.intangstep**2)*self.efficiencies[step][i]
        #integral=integral/5.
        return integral

    # calculates the mean integral over a whole spacecraft spin
    def calc_rotation(self,r,step):
        integral=0.
        dt=12./float(len(self.rot_angarr))  
        dr=getdeltav(self.ionmass,self.ioncharge,step)
        for gamma in self.rot_angarr:
            integral+=self.calc_timestep(r,dr,gamma,step)*dt*r*self.geomfac
        #integral=(integral/(360.*self.rotfrac))*getdeltav(self.ionmass,self.ioncharge,step)
        integral=integral*getdeltav(self.ionmass,self.ioncharge,step)
        return integral


    # get integration space for entrance system (unrotated)
    def calc_entrances_angles(self):
        thetasteps=int(57*self.intfrac)
        phisteps=int(4*self.intfrac)
        entr_thetaarr=[]
        entr_phiarr=[]
        for i in range(thetasteps):
            theta=pi/2.-float(i)*self.intangstep-self.intangstep/2.
            entr_thetaarr.append(theta)
        for j in range(phisteps):
            phi=-pi/(90.)+float(j)*self.intangstep+self.intangstep/2.
            entr_phiarr.append(phi)
        self.entr_thetaarr=array(entr_thetaarr)
        self.entr_phiarr=array(entr_phiarr)
                
    # get integration space for rcut
    def calc_rcut_angles(self):
        self.rcut_thetaarr=[]
        self.rcut_phiarr=[]
        sigrange=3.
        # calc central angles from peak1 position
        ppeak1=[self.x0m1,self.y0m1,self.z0m1]
        x=self.xmag2se(ppeak1[0],ppeak1[1],ppeak1[2])
        y=self.ymag2se(ppeak1[0],ppeak1[1],ppeak1[2])
        z=self.zmag2se(ppeak1[0],ppeak1[1],ppeak1[2])
        if (z>0.):
            theta=atan(sqrt(x**2+y**2)/z)
        elif (z<0.):
            theta=atan(sqrt(x**2+y**2)/z)+pi
        else:
            theta=pi/2.
        if (x>0.):
            phi=atan(y/x)
        elif (x<0.):
            phi=atan(y/x)+pi
        elif (x==0. and y>0.):
            phi=pi/2.
        else:
            phi=-pi/2.
        theta1=theta
        theta2=theta
        phi1=phi
        phi2=phi
        # 
        point=[]
        point.append([self.x0m1+sigrange*self.vth,self.y0m1+sigrange*self.vth*self.vthr,self.z0m1+sigrange*self.vth*self.vthr])
        point.append([self.x0m1+sigrange*self.vth,self.y0m1+sigrange*self.vth*self.vthr,self.z0m1-sigrange*self.vth*self.vthr])
        point.append([self.x0m1+sigrange*self.vth,self.y0m1-sigrange*self.vth*self.vthr,self.z0m1+sigrange*self.vth*self.vthr])
        point.append([self.x0m1+sigrange*self.vth,self.y0m1-sigrange*self.vth*self.vthr,self.z0m1-sigrange*self.vth*self.vthr])
        point.append([self.x0m1-sigrange*self.vth,self.y0m1+sigrange*self.vth*self.vthr,self.z0m1+sigrange*self.vth*self.vthr])
        point.append([self.x0m1-sigrange*self.vth,self.y0m1+sigrange*self.vth*self.vthr,self.z0m1-sigrange*self.vth*self.vthr])
        point.append([self.x0m1-sigrange*self.vth,self.y0m1-sigrange*self.vth*self.vthr,self.z0m1+sigrange*self.vth*self.vthr])
        point.append([self.x0m1-sigrange*self.vth,self.y0m1-sigrange*self.vth*self.vthr,self.z0m1-sigrange*self.vth*self.vthr])
        point.append([self.x0m2+sigrange*self.vth,self.y0m2+sigrange*self.vth*self.vthr,self.z0m2+sigrange*self.vth*self.vthr])
        point.append([self.x0m2+sigrange*self.vth,self.y0m2+sigrange*self.vth*self.vthr,self.z0m2-sigrange*self.vth*self.vthr])
        point.append([self.x0m2+sigrange*self.vth,self.y0m2-sigrange*self.vth*self.vthr,self.z0m2+sigrange*self.vth*self.vthr])
        point.append([self.x0m2+sigrange*self.vth,self.y0m2-sigrange*self.vth*self.vthr,self.z0m2-sigrange*self.vth*self.vthr])
        point.append([self.x0m2-sigrange*self.vth,self.y0m2+sigrange*self.vth*self.vthr,self.z0m2+sigrange*self.vth*self.vthr])
        point.append([self.x0m2-sigrange*self.vth,self.y0m2+sigrange*self.vth*self.vthr,self.z0m2-sigrange*self.vth*self.vthr])
        point.append([self.x0m2-sigrange*self.vth,self.y0m2-sigrange*self.vth*self.vthr,self.z0m2+sigrange*self.vth*self.vthr])
        point.append([self.x0m2-sigrange*self.vth,self.y0m2-sigrange*self.vth*self.vthr,self.z0m2-sigrange*self.vth*self.vthr])
        #print point
        for p in point:
            x=self.xmag2se(p[0],p[1],p[2])
            y=self.ymag2se(p[0],p[1],p[2])
            z=self.zmag2se(p[0],p[1],p[2])
            if (z>0.):
                theta=atan(sqrt(x**2+y**2)/z)
            elif (z<0.):
                theta=atan(sqrt(x**2+y**2)/z)+pi
            else:
                theta=pi/2.
            if (x>0.):
                phi=atan(y/x)
            elif (x<0.):
                phi=atan(y/x)+pi
            elif (x==0. and y>0.):
                phi=pi/2.
            else:
                phi=-pi/2.
            if (theta<theta1):
                theta1=theta
            if (theta>theta2):
                theta2=theta
            if (phi<phi1):
                phi1=phi
            if (phi>phi2):
                phi2=phi
            #print p,theta,phi
        #print "max/min"
        #print theta1,theta2
        #print phi1,phi2
        thetasteps=int((theta2-theta1)/self.intangstep)+2
        phisteps=int((phi2-phi1)/self.intangstep)+2
        thetaarr=[]
        phiarr=[]
        for i in range(thetasteps):
            thetaarr.append(theta1+i*self.intangstep-self.intangstep/2.)
        for i in range(phisteps):
            phiarr.append(phi1+i*self.intangstep-self.intangstep/2.)
        self.rcut_thetaarr=array(thetaarr)
        self.rcut_phiarr=array(phiarr)
            
    # get rotation angles
    def calc_rot_angles(self):
        self.rot_angarr=[]
        rotangarr=[]
        for i in range(2*int(pi/self.rotangstep)):
            rotangarr.append(float(i)*self.rotangstep)
        self.rot_angarr=array(rotangarr)
        

    # calculates the projection and the corresponding dutycycle
    def calc_duty_cycle(self):
        self.virtualspec=[]
        self.dutycycle=[]
        self.calc_projection()
        for val in self.projection:
            tmpduty=0.
            #print val[0],step
            if (val[1]>1.):
                tmpval=self.calc_rotation(val[0],val[2])
            else:
                tmpval=0.
            #print val,tmpval
            if (val[1]>0.):
                tmpduty=tmpval/val[1]
            else:
                tmpduty=0.
            self.dutycycle.append([val[0],tmpduty])
            self.virtualspec.append([val[0],tmpval])
        self.calc_virtualspec_moments()
        #self.apply_duty_cycle()
        #self.norm_spec()
        
    # applies duty cycle to countratespectrum
    def apply_duty_cycle(self):
        self.countspecduty=[]
        step=-1
        for val in self.countspec:
            step+=1
            if (self.dutycycle[step][1]>0.):
                self.countspecduty.append([val[0],val[1]/self.dutycycle[step][1],val[2]/self.dutycycle[step][1]])
            else:
                self.countspecduty.append([val[0],0.,0.])

    # norms projection and dutycycle corrected countspecs to integral
    def norm_spec(self):
        summecounts=0.
        summeprojection=0.
        summevspec=0.
        for val in self.countspec:
            summecounts+=val[1]
        for val in self.projection:
            summeprojection+=val[1]
        for val in self.virtualspec:
            summevspec+=val[1]
        #if (summecounts>0.):
            #for val in self.countspecduty:
                #val[1]=val[1]/summecounts
                #val[2]=val[2]/summecounts
        if (summeprojection>0.):
            for val in self.projection:
                val[1]=val[1]/summeprojection
        if (summevspec>0.):
            for val in self.virtualspec:
                val[1]=val[1]*summecounts/summevspec

                

    def calc_chisq(self):
        chisq=0.
        for i in range(len(self.virtualspec)):
            #chisq += ymod - y[n][o]*log(ymod)
            if (self.virtualspec[i][1]>0.):
                chisq += self.virtualspec[i][1] - self.countspec2[i][1]*log(self.virtualspec[i][1])
        return chisq

    def fit(self):
        vtharr=[20.,25.,30.,35.,40.,45.,50.]
        vthrarr=[1.,1.2,1.4,1.6,1.8,2.,2.2,2.4,2.6,2.8,3.]
        peakrarr=[0.,.2,.4,.6,.8,1.,1.2,1.4,1.6,1.8,2.]
        self.chisqarr=[]
        for vth in vtharr:
            for vthr in vthrarr:
                for peakr in peakrarr:
                    self.vth=vth
                    self.vthr=vthr
                    self.peakr=peakr
                    print self.vth,self.vthr,self.peakr
                    self.calc_rcut_angles()
                    self.calc_duty_cycle()
                    chisq=self.calc_chisq()
                    print chisq
                    self.chisqarr.append([chisq,vth,vthr,peakr])
                    
    # transformation from Sun-Earth to mag coordinates :
    # r,theta,phi spherical coordinates in Sun-Earth frame of reference
    # bxy -> rotation angle in xy plane
    # bz  -> rotation angle z against xy plane
    # cos,sin denotes the corresponding quantities. Since all these angles are fixed for a given integration the values of the cos,sin are parameters not the angles. This serves to save computing time!!! 
    def xse2mag(self,r,theta,phi):
        return r*((sin(theta)*cos(phi)*self.cosbxy*self.cosbz)+(sin(theta)*sin(phi)*self.sinbxy*self.cosbz)+(cos(theta)*self.sinbz))

    def yse2mag(self,r,theta,phi):
        return r*(-sin(theta)*cos(phi)*self.sinbxy+sin(theta)*sin(phi)*self.cosbxy)

    def zse2mag(self,r,theta,phi):
        return r*(-sin(theta)*cos(phi)*self.cosbxy*self.sinbz-sin(theta)*sin(phi)*self.sinbxy*self.sinbz+cos(theta)*self.cosbz)


    # transformation from mag to Sun-Earth coordinates :
    # x,y,z kartesian coordinates in mag frame of reference
    # bxy -> rotation angle in xy plane (still mag against SE not the negative angle
    # bz  -> rotation angle z against xy plane
    # cos,sin denotes the corresponding quantities. Since all these angles are fixed for a given integration the values of the cos,sin are parameters not the angles. This serves to save computing time!!! 
    def xmag2se(self,x,y,z):
        return x*self.cosbxy*self.cosbz-y*self.sinbxy-z*self.cosbxy*self.sinbz

    def ymag2se(self,x,y,z):
        return x*self.sinbxy*self.cosbz+y*self.cosbxy-z*self.sinbxy*self.sinbz

    def zmag2se(self,x,y,z):
        return x*self.sinbz+z*self.cosbz


    # transformation from spacecraft to mag coordinates :
    # x,y,z kartesian coordinates in spacecraft frame of reference
    # dxy -> rotation angle in xy plane
    # dz  -> rotation angle z against xy plane
    def xsc2mag(self,x,y,z):
        return x*self.cosdxy*self.cosdz+y*self.sindxy*self.cosdz+z*self.sindz

    def ysc2mag(self,x,y,z):
        return -x*self.sindxy+y*self.cosdxy

    def zsc2mag(self,x,y,z):
        return -x*self.cosdxy*self.sindz-y*self.sindxy*self.sindz+z*self.cosdz

    # rotation of spacecraft by angle g :
    # r,theta,phi spherical coordinates in spacecraft frame of reference
    # g   -> rotation angle around rotated x-axis (this angle is used to rotate spacecraft (0. -> 2*pi)
    # cos,sin denotes the corresponding quantities. Since all these angles are fixed for a given integration the values of the cos,sin are parameters not the angles. This serves to save computing time!!! 
    def xrotsc(self,r,theta,phi,cosg,sing):
        return r*sin(theta)*cos(phi)

    def yrotsc(self,r,theta,phi,cosg,sing):
        return r*(sin(theta)*sin(phi)*cosg+cos(theta)*sing)

    def zrotsc(self,r,theta,phi,cosg,sing):
        return r*(-sin(theta)*sin(phi)*sing+cos(theta)*cosg)

    
    
    


