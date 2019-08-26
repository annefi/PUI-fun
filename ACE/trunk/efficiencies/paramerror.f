        SUBROUTINE paramerror(zion,mion,ion,
     .                  C1,C1delta,
     .                  C2,C2delta,
     .                  C3,C3delta,
     .                  PF1,pf1delta,
     .                  PF2,pf2delta,
     .                  ETHRESH,Ethrdelta,
     .                  FWHMEL,FWHMdelta,
     .                  THICK,thickdelta,
     .                  DEFL, defldelta,errormode)

        IMPLICIT NONE

        COMMON /GEOM/ C,V,VN,DELTAWIN,PHIWIN,DELTASTP,PHISTP,
     .                DELTASSD,PHISSD,DELTAMACOR,PHIMACOR,
     .                BRAIN,SSDC,STPC,MACORC,SSDI,STPI,
     .                COUNTER,WALKER,RUNNER,JUMPER,FITGEOM,
     .                FITGEOMALL,
     .                FITMODE,TARGETSSD,CALDATSSD,GEOMMODE
     
        REAL*4
     .      C(3),               ! entry point in C-foil
     .      V(3),               ! beam norm vector
     .      VN(3),              ! normal to beam norm vector
     .      DELTAWIN(2,-33:32), ! deltas for detector collimator window
     .      PHIWIN(2,-33:32),   ! phis for detector collimator window
     .      DELTASTP(3,2),      ! horizontal angular integration limits for stop
     .      PHISTP(3,2),        ! vertical angular integration limits for stop
     .      DELTASSD(3,2),      ! horizontal angular integration limits for SSD
     .      PHISSD(3,2),        ! vertical angular integration limits for SSD
     .      DELTAMACOR(3,2),    ! horizontal angular integration limits for MACOR-area
     .      PHIMACOR(3,2),      ! vertical angular integration limits for MACOR-area
     .      BRAIN(310,100),     ! buffer for the calibration data
     .      SSDC(3,4,3),        ! corners of ssd area 
     .      STPC(3,4,3),        ! corners of stp area
     .      MACORC(3,4,3),      ! corners of macor area
     .      SSDI(3,4,3),        ! Eckpunkte für die Integration des Teils des Strahls, der auf 
                                ! die sensitive Fläche fällt. Erster Index: Detektornummer
                                ! Zweiter Index: Ecke(Beginn links oben, Uhrzeigersinn)
                                ! Dritter Index: Komponente
     .      STPI(3,4,3),        ! Analog ssdi: hier für die stp-Flächen
     .      FITGEOM(961,4),
     .      FITGEOMALL(38440,4)

        INTEGER*4 
     .      WALKER,             ! auxiliary loop variables
     .      RUNNER,
     .      JUMPER, 
     .      COUNTER,
     .      FITMODE,            ! 0 = alle , 1 = Jedes Ion einzeln
     .      TARGETSSD,
     .      CALDATSSD,
     .      GEOMMODE

        INTEGER*4 errormode     ! 0 = berechnet alle Fehler hier und schreibt sie in './param/errors'
                                ! 1 = liest vorberechnete Fehler aus './param/errors'

        REAL*4
     .      EPERM,              ! Energy/amu
     .      ZION,               ! Nuclear charge of incident ion [e] (float)
     .      MION,               ! Mass of the incident ion [amu] (float)
     .      LADUNG,             ! Charge of the incident ion [e]
     .      C1,                 ! Factor to convert etotf in number of sec. el. (carbonfoil)
     .      C1delta(3),         ! Error of Const1
     .      C2,                 ! Factor to convert etotf in number of sec. el. (PIPS-surface)
     .      C2delta(3),         ! Error of Const2
     .      C3,                 ! Factor to convert etotf in number of sec. el. (Macor-surface)
     .      C3delta(3),         ! Error of Const3
     .      PF1,                ! Probability of Failure of MCP 1
     .      pf1delta(3),        ! Error of PF1
     .      PF2,                ! Probability of NON-Failure of MCP 2
     .      pf2delta(3),        ! Error of PF2
     .      ETHRESH,            ! Threshold energy of MSS detector [keV]
     .      Ethrdelta(3),       ! Error of ETHRESH
     .      FWHMEL,             ! Electronic FWHM of MSS threshold [keV]
     .      FWHMdelta(3),       ! Error of FWHMEL
     .      THICK,              ! Foil thickness [microg/squarecm]
     .      thickdelta(3),      ! Error of THICK
     .      DEFL,               ! Angular dispersion in deflection system
     .      defldelta(3),       ! Error of DEFL
     .      bw,
     .      SUMINT,
     .      WSSR,
     .      var,
     .      step,
     .      fsr_cal_dat(33,2),
     .      x,y,z,e


        CHARACTER*20
     .      ION                 ! element abbreviation for ION

        INTEGER h,i,j,k,l,      ! auxiliary loop variables
     .      dc1,dc2,dc3,dpf1,dpf2,dfwhm,dethr,dthick


       if (errormode .eq. 0) then
        write(*,*) "Source fsr_cal_o_He data"
        open (unit=1, file="fsr_cal_o_He")
        do l=1,33
            READ(1,*,END=10),(fsr_cal_dat(l,i),i=1,2)
        end do
10      continue
        CLOSE( UNIT=1 )

        wssr=0.0
        sumint=0.0
        do k=1,33
            x=fsr_cal_dat(k,1)*C1*22.661
c            write(*,*) x
            z=fsr_cal_dat(k,2)
c            write(*,*) z
            y=(1-(1+x)*exp(-x))*(1-pf1**x)
            sumint=sumint+(y-z)**2
        end do
        wssr=sumint

C########### C1 ################################################
        write(*,*) " Calculating C1 error"
        sumint=0.0
        var=c1
        step=c1*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,33
            x=fsr_cal_dat(k,1)*var*22.661
c            write(*,*) x
            z=fsr_cal_dat(k,2)
c            write(*,*) z
            y=(1-(1+x)*exp(-x))*(1-pf1**x)
            sumint=sumint+(y-z)**2
          end do
          if (var .le. 0.0) then
            c1delta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          c1delta(1)=var
        end do
c        write(*,*) wssr, sumint


        sumint=0.0
        var=c1
        step=c1*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,33
            x=fsr_cal_dat(k,1)*var*22.661
c            write(*,*) x
            z=fsr_cal_dat(k,2)
c            write(*,*) z
            y=(1-(1+x)*exp(-x))*(1-pf1**x)
            sumint=sumint+(y-z)**2
          end do
          if (var .ge. 2.*c1) then
            c1delta(2)=2.*c1
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          c1delta(2)=var
        end do
        write(*,*) C1, c1delta


C########### pf1 (pf2) ###############################################
        write(*,*) " Calculating pf1 (pf2) error"

        sumint=0.0
        var=pf1
        step=pf1*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,33
            x=fsr_cal_dat(k,1)*C1*22.661
c            write(*,*) x
            z=fsr_cal_dat(k,2)
c            write(*,*) z
            y=(1-(1+x)*exp(-x))*(1-var**x)
            sumint=sumint+(y-z)**2
          end do
          if (var .le. 0.0) then
            pf1delta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          pf1delta(1)=var
        end do
c        write(*,*) wssr, sumint


        sumint=0.0
        var=pf1
        step=pf1*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,33
            x=fsr_cal_dat(k,1)*C1*22.661
c            write(*,*) x
            z=fsr_cal_dat(k,2)
c            write(*,*) z
            y=(1-(1+x)*exp(-x))*(1-var**x)
            sumint=sumint+(y-z)**2
          end do
          if (var .ge. 2.*pf1) then
            pf1delta(2)=2.*pf1
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          pf1delta(2)=var
        end do
c        write(*,*) pf1delta

        pf2delta(1)=pf1delta(1)
        pf2delta(2)=pf1delta(2)
        write(*,*) pf1, pf1delta
        write(*,*) pf2, pf2delta

c ################################################################


        write(*,*) " Source DCR/FSR data"
        wssr=0.0
        sumint=0.0
        do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl,1.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
        end do
        wssr=sumint

        write(*,*) " WSSR von DCR/FSR =", wssr

C###########  THICK ################################################
        write(*,*) " Calculating thick error"
        sumint=0.0
        var=thick
        step=thick*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,var,defl,1.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
          end do
          if (var .le. 0.0) then
            thickdelta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          thickdelta(1)=var
        end do
c        write(*,*) wssr, sumint


        sumint=0.0
        var=thick
        step=thick*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,var,defl,1.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
          end do
          if (var .ge. 2.*thick) then
            thickdelta(2)=2.*thick
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          thickdelta(2)=var
        end do
c        write(*,*) wssr, sumint

        write(*,*) thick, thickdelta

C########## C2 ######################################################
        write(*,*) " Calculating C2 error"
        sumint=0.0
        var=C2
        step=C2*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,var,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl,1.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
          end do
          if (var .le. 0.0) then
            C2delta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          C2delta(1)=var
        end do
c        write(*,*) wssr, sumint

        sumint=0.0
        var=C2
        step=C2*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,var,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl,1.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
          end do
          if (var .ge. 2.*C2) then
            C2delta(2)=2.*C2
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          C2delta(2)=var
        end do
c        write(*,*) wssr, sumint
        write(*,*) C2, c2delta

C#########################################################################
        write(*,*) " Source TCR/DCR data"
        wssr=0.0
        sumint=0.0
        do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,15))/(brain(k,33)))**2))
        end do
        wssr=sumint
        write(*,*) " WSSR von TCR/DCR =", wssr

C########## defl ######################################################
        write(*,*) " Calculating defl error"
        sumint=0.0
        var=defl
        step=defl*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,var,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
          end do
c          write(*,*) sumint, wssr
          if (var .le. 0.0) then
            defldelta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          defldelta(1)=var
        end do
c        write(*,*) wssr, sumint

        sumint=0.0
        var=defl
        step=defl*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,var,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,16))/(brain(k,34)))**2))
          end do
          if (var .ge. 2.*defl) then
            defldelta(2)=2.*defl
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          defldelta(2)=var
        end do
c        write(*,*) wssr, sumint
        write(*,*) defl, defldelta

C########## ETHRESH ######################################################
        write(*,*) " Calculating Ethresh error"
        sumint=0.0
        var=Ethresh
        step=Ethresh*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,var,FWHMEL,thick,defl,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,15))/(brain(k,33)))**2))
          end do
          if (var .le. 0.0) then
            Ethrdelta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          Ethrdelta(1)=var
        end do
c        write(*,*) wssr, sumint

        sumint=0.0
        var=Ethresh
        step=Ethresh*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,var,FWHMEL,thick,defl,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,15))/(brain(k,33)))**2))
          end do
          if (var .ge. 2.*Ethresh) then
            Ethrdelta(2)=2.*Ethresh
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          Ethrdelta(2)=var
        end do
c        write(*,*) wssr, sumint
        write(*,*) Ethresh, Ethrdelta

C########## FWHMEL ######################################################
        write(*,*) " Calculating FWHMEL error"
        sumint=0.0
        var=FWHMEL
        step=FWHMEL*0.01
        do while (sumint .lt. wssr*2.)
          var=var-step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,var,thick,defl,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,15))/(brain(k,33)))**2))
          end do
          if (var .le. 0.0) then
            FWHMdelta(1)=0.0
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          FWHMdelta(1)=var
        end do
c        write(*,*) wssr, sumint

        sumint=0.0
        var=FWHMEL
        step=FWHMEL*0.01
        do while (sumint .lt. wssr*2.)
          var=var+step
          sumint=0.0
c          write(*,*) var
          do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
            ladung=brain(k,2)
c            write(*,*) var
            call swxeff(bw,eperm,zion,mion,ladung,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,var,thick,defl,2.,
     .              1.,1.,1.)
            sumint=sumint+((((bw-brain(k,15))/(brain(k,33)))**2))
          end do
          if (var .ge. 2.*FWHMEL) then
            FWHMdelta(2)=2.*FWHMEL
            sumint=3.*wssr
          end if
c          write(*,*) sumint
          FWHMdelta(2)=var
        end do
c        write(*,*) wssr, sumint
        write(*,*) FWHMEL, FWHMdelta

        thickdelta(3)=(abs(thickdelta(1)-thickdelta(2)))/2.+thick
        C1delta(3)=(abs(C1delta(1)-C1delta(2)))/2.+C1
        C2delta(3)=(abs(C2delta(1)-C2delta(2)))/2.+C2
        pf1delta(3)=(abs(pf1delta(1)-pf1delta(2)))/2.+pf1
        pf2delta(3)=(abs(pf2delta(1)-pf2delta(2)))/2.+pf2
        defldelta(3)=(abs(defldelta(1)-defldelta(2)))/2.+defl
        Ethrdelta(3)=(abs(Ethrdelta(1)-Ethrdelta(2)))/2.+Ethresh
        FWHMdelta(3)=(abs(FWHMdelta(1)-FWHMdelta(2)))/2.+FWHMEL

        open(unit=25,file='./param/errors')
        write(25,*) thick, thickdelta
        write(25,*) C1, C1delta
        write(25,*) C2, C2delta
        write(25,*) pf1, pf1delta
        write(25,*) pf2, pf2delta
        write(25,*) defl, defldelta
        write(25,*) Ethresh, Ethrdelta
        write(25,*) FWHMEL, FWHMdelta
        close(unit=25)
       end if

       if (errormode .eq. 1) then
        open(unit=25,file='./param/errors')
        READ(25,*) thick, thickdelta
        READ(25,*) C1, C1delta
        READ(25,*) C2, C2delta
        READ(25,*) pf1, pf1delta
        READ(25,*) pf2, pf2delta
        READ(25,*) defl, defldelta
        READ(25,*) Ethresh, Ethrdelta
        READ(25,*) FWHMEL, FWHMdelta
        close(unit=25)
       end if

        write(*,*) thick, thickdelta
        write(*,*) C1, C1delta
        write(*,*) C2, C2delta
        write(*,*) pf1, pf1delta
        write(*,*) pf2, pf2delta
        write(*,*) defl, defldelta
        write(*,*) Ethresh, Ethrdelta
        write(*,*) FWHMEL, FWHMdelta
       RETURN
       END