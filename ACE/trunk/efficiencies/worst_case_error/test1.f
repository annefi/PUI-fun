        PROGRAM test1

        IMPLICIT NONE


        COMMON /CAL/
     .      eqstep,lpaps,lcharge,
     .      tau,tauchannel,tauchannelfloat,
     .      emeas,echannel,echannelfloat,
     .      fsrave,dcrave,tcrave

        REAL*4
     .      eqstep(100),        ! Energy-per-charge step
     .      lpaps,              ! PAPS during mission (PAPS=24.868179 kV)
     .      lcharge,            ! Variable ion charge during mission
     .      tau,                ! Time of flight
     .      tauchannel,         ! ToF-channel belonging to tau
     .      tauchannelfloat,    ! Not rounded ToF-channel (float)
     .      emeas,              ! Measured energy in detector
     .      echannel,           ! Energy-channel belonging to emeas
     .      echannelfloat,      ! Not rounded energy-channel
     .      FSRAVE,             ! Average fsr over all steps
     .      DCRAVE,             ! Average dcr over all steps
     .      TCRAVE              ! Average tcr over all steps

c+++++++Common variables with the geometry part++++++++++++++++++

        COMMON /GEOM/ C,V,VN,DELTAWIN,PHIWIN,DELTASTP,PHISTP,
     .                DELTASSD,PHISSD,DELTAMACOR,PHIMACOR,
     .                BRAIN,SSDC,STPC,MACORC,SSDI,STPI,
     .                COUNTER,WALKER,RUNNER,JUMPER,FITGEOM,
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
     .      FITGEOM(961,4)

     
        INTEGER*4 
     .      WALKER,             ! auxiliary loop variables
     .      RUNNER,
     .      JUMPER, 
     .      COUNTER,
     .      FITMODE,            ! 0 = alle , 1 = Jedes Ion einzeln
     .      TARGETSSD,
     .      CALDATSSD,
     .      GEOMMODE

c*******End of common-block /GEOM/*******************************

        COMMON /SETTINGS/ run1,run2,run3,run4,run5,run6,run7,run8

        INTEGER*4               ! Parameters to start different efficiency modi
     .      run1,               ! Test run for the dutycycle function
     .      run2,               ! Read the E/q steps
     .      run3,               ! Test run for swxeff
     .      run4,               ! Run for all elements in param/ionlist
                                ! Error estimation for worst case scenario
     .      run5,               ! Test run for random noise
     .      run6,               ! Run for error estimation (random noise)
     .      run7,               ! Monte Carlo Intergration
     .      run8                ! Different experiments

        REAL*4 
     .      bw,                 ! output of several subroutines
     .      e,                  ! loop variable for energy
     .      p(10),              ! buffer for instrument specific parameters 
     .      pr(100,10),         ! buffer for ion specific parameters
     .      eperm,              ! energy per mass [kev/amu]
     .      chargelow,          ! lower limit for charge-loop
     .      chargehigh,         ! upper limit for charge-loop
     .      chargestep,         ! step for charge-loop
     .      zion,               ! nuclear charge of ion
     .      mion,               ! mass of ion
     .      mionlow,            ! lower limit for mass-loop
     .      mionhigh,           ! upper limit for mass-loop
     .      mionstep,           ! step for mion-loop
     .      x(10),              ! dummy-buffer for scoef
     .      xx(8),              ! dummy-buffer for scoef
     .      ioncharlen,         ! lenght of character of ion
     .      thick,              ! thickness of carbon foil
     .      ft,                 ! loop variable for the foil thickness
     .      ftlow,              ! lower limit for thick-loop
     .      fthigh,             ! upper limit for thick-loop
     .      ftstep,             ! step for thick-loop
     .      dl,                 ! thickness of ssd deadlayer [A]
     .      dllow,              ! lower limit for deadlayer-loop
     .      dlhigh,             ! upper limit for deadlayer-loop
     .      dlstep,             ! step for deadlayer-loop
     .      pp(100000,10),      ! buffer for srim output-file
     .      mw,                 ! average energy value
     .      limit,              ! lower limit for the distribution calculation (angle or energy)
     .      tepe(101),          ! array for the counts in a particular interval
     .      tepe3d(-50:50,-50:50),  !array for the 3d angular distribution
     .      gesamtenergie(100), ! auxiliary array for the calculation of the average energy subject to angle
     .      denergie(100),      ! array for the calculation of the average energy subject to angle
     .      sumint,             ! interval for summation
     .      med,                ! median of the energy distribution
     .      defl,
     .      defldelta(2),
     .      C1,
     .      C1delta(2),
     .      C1R(2),
     .      C2,
     .      C2delta(2),
     .      C2R(2),
     .      C3,
     .      C3delta(2),
     .      C3R(2),
     .      pf1,
     .      pf1delta(2),
     .      pf1R(2),
     .      pf2,
     .      pf2delta(2),
     .      pf2R(2),
     .      FWHMEL,
     .      FWHMdelta(2),
     .      FWHMELR(2),
     .      Ethresh,
     .      Ethrdelta(2),
     .      EthreshR(2),
     .      thickdelta(2),
     .      thickR(2),
     .      charge,
     .      bw1,
     .      bw2,
     .      bwr,
     .      fehler(2),
     .      yanlis,
     .      oyanlis,
     .      WSSR,
     .      PROBMODE,
     .      AUXPAR1(2),
     .      AUXPAR2(2),
     .      AUXPAR3(2),
     .      AUXPAR1R(2),
     .      AUXPAR2R(2),
     .      AUXPAR3R(2)
        REAL*4                  ! Variables for the dutycycle function
     .      aspang,             ! Aspect angle
     .      thang,              ! thermal angle
     .      dutycycleth         ! Dutycycle function

        CHARACTER*20
     .      IONR(100),          ! buffer for element abbreviation for ION
     .      ION                 ! element abbreviation for ION

        CHARACTER*10
     .      stuff(10)           ! dummy buffer for unused information in
                                ! './param/ionlist' 

        CHARACTER*14
     .      qvz                 ! path to file (see code)

        CHARACTER*100
     .      qvze                ! path to file (see code)

        CHARACTER*100
     .      qvzf                ! path to file (see code)

        CHARACTER*100
     .      qvzeff              ! path to file (see code)

        CHARACTER*100
     .      qvzet               ! path to file (see code)

        CHARACTER*100
     .      qvzall              ! path to file (see code)

        CHARACTER*100
     .      qvzerror            ! path to file (see code)

        INTEGER f,g,h,i,j,k,l,  ! auxiliary loop variables
     .      dc1,dc2,dc3,dpf1,dpf2,dfwhm,dethr,dthick


c++++++ different variables and dummys to built the particular filename ++        
        CHARACTER*1
     .      XXX,lchargechar1,ionchar1,mionchar1,dummy1
        CHARACTER*2
     .      YYY,lpapschar,ftchar,ionchar2,mionchar2,
     .      lchargechar2,dummy2
        CHARACTER*3
     .      ZZZ,dlchar,mionchar3,dummy3

        INTEGER zionint,mionint,lchargeint,lpapsint,ftint,dlint

        REAL
     .      ran1,ran2,ran3      ! Zufallsgeneratoren


        REAL*4
     .  gg,xz,sigma,xy,res,step,pi,integral1,integral2,integral,
     .  randomtheta,randomphi,vd(3),vr(3),sp(3),buffer,
     .  sval(1000,2)


        CALL GEOMETRIE()
        write(*,*) FITMODE,GEOMMODE,targetssd,
     .                    run1,run2,run3,run4,run5,run6,run7,run8


c TEST RUN FOR THE DUTYCYCLE FUNCTION
      if (run1 .eq. 1) then
        do thang = 0., 10., 1.
            do aspang = 1., 65., 1. 
                bw = dutycycleth(aspang, thang)
c                write(*,*) aspang, thang, bw
            end do
        end do
      end if

c READ THE E/Q STEPS 
      if(run2 .eq. 1) then
        OPEN( UNIT=88,FILE=
     &'./eqsteps/steps')
        READ(88,*,END=200),(eqstep(i),i=1,58)
c        write(*,*) (eqstep(i),i=1,58) 
200     continue
        CLOSE( UNIT=88 )

        OPEN( UNIT=90,FILE=
     &'./param/parameters')
        READ(90,*,END=250), stuff(1), Ethresh
        READ(90,*,END=250), stuff(1), FWHMEL
        READ(90,*,END=250), stuff(1), pf1
        READ(90,*,END=250), stuff(1), pf2
        READ(90,*,END=250), stuff(1), C1
        READ(90,*,END=250), stuff(1), C2
        READ(90,*,END=250), stuff(1), C3
        READ(90,*,END=250), stuff(1), defl
        READ(90,*,END=250), stuff(1), thick
c        write(*,*)Ethresh,FWHMEL,pf1,pf2,C1,C2,C3,defl,thick
250     continue
        CLOSE( UNIT=90 )
      end if

c TEST RUN FOR SWXEFF
      if (run3 .eq. 1) then
        lpaps=24.868179
        mion=16
        zion=8
        ion="O"
        lcharge=10
        thick=2.5
        C1=0.085
        C2=0.85
        C3=1.0
        pf1=0.785
        pf2=0.785
        FWHMEL=13.9
        Ethresh=27.38
        defl=0.0
        PROBMODE=1

        do k=10,10
c          do defl=0.0,0.3,0.001
            eperm=((eqstep(k))+lpaps)*lcharge/mion
            call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl,
     .              PROBMODE,1.,1.,1.)
c          end do
c        write(*,*) eperm, bw
        end do
      end if


c Einlesen des Parameterfiles, Ionen, Massen, Ladungszustände
      if ( run4 .eq. 1 ) then

        C2=0.85
        C3=1.0
        pf1=0.785
        pf2=0.785
        FWHMEL=13.9549
        Ethresh=27.38
        thick=2.5
        defl=0.043

        pf1delta(1)=0.752
        pf1delta(2)=0.813
        pf2delta(1)=0.752
        pf2delta(2)=0.813
        auxpar1(1)=0.9
        auxpar1(2)=1.1
        auxpar2(1)=0.9
        auxpar2(2)=1.1
        auxpar3(1)=0.9
        auxpar3(2)=1.1

        write(*,*) " *** PARAMETER ERROR CALCULATION *** "
c Data source to calculate the parameter errors is the oxygen data
        mion=16
        zion=8
        ion="O"
        call paramerror(EPERM,ZION,MION,ION,
     .                  CHARGE,
     .                  C1,C1delta,
     .                  C2,C2delta,
     .                  C3,C3delta,
     .                  PF1,pf1delta,
     .                  PF2,pf2delta,
     .                  ETHRESH,Ethrdelta,
     .                  FWHMEL,FWHMdelta,
     .                  THICK,thickdelta,
     .                  DEFL, defldelta)

        write(*,*) " *** READING ION SPECIFIC DATA ***"
        OPEN( UNIT=99,FILE=
     &'./param/ionlist4')
        READ(99,*,END=300),(stuff(i),i=1,4)
        READ(99,*,END=300),(p(i),i=1,7)
        READ(99,*,END=300),(stuff(i),i=1,8)
        l=1
        do while (.true.)
            READ(99,*,END=300),ionr(l), (pr(l,i),i=1,7)
            l=l+1 
        end do       
300     continue
        CLOSE( UNIT=99 )


        lpaps=p(1)
        ftlow=p(2)
        fthigh=p(3)
        ftstep=p(4)
        dllow=p(5)
        dlhigh=p(6)
        dlstep=p(7) 
c        write(*,*) "l =", l-1
        do h=1,l-1
          ion=ionr(h)
          zion=pr(h,1) 
          mionlow=pr(h,2)
          mionhigh=pr(h,3) 
          mionstep=pr(h,4)
          chargelow=pr(h,5)
          chargehigh=pr(h,6)
          chargestep=pr(h,7)

          do dl=dllow,dlhigh,dlstep
            do ft=ftlow,fthigh,ftstep
              do lcharge=chargelow,chargehigh,chargestep
                do mion=mionlow,mionhigh,mionstep
                  dlint=int(dl)
                  thick=ft/10
                  ftint=int(ft)
                  lchargeint=int(lcharge)
                  mionint=int(mion)
                  zionint=int(zion)
                  lpapsint=int(lpaps)
                  call elname(zionint,ionchar1,ionchar2,ioncharlen)
                  if (lchargeint .le. 9) then
                    call ftos(lchargeint,lchargechar1,YYY,ZZZ,1)
                  else if (lchargeint .ge. 10) then
                    call ftos(lchargeint,XXX,lchargechar2,ZZZ,2)
                  end if
                  call ftos(ftint,XXX,ftchar,ZZZ,2)
                  call ftos(dlint,XXX,YYY,dlchar,3)
                  call ftos(mionint,mionchar1,YYY,ZZZ,1)
                  call ftos(mionint,XXX,mionchar2,ZZZ,2)
                  call ftos(mionint,XXX,YYY,mionchar3,3)
                  call ftos(lpapsint,XXX,lpapschar,ZZZ,2)
c                  qvz="./lars/paps"//lpapschar//"/"
                  qvz="./lars/error3/"

                  if (mionint .le. 9) then
                    if (ioncharlen .eq. 1) then
                      if (lchargeint .le. 9) then
                        qvze = qvz//mionchar1//ionchar1//
     &                  lchargechar1//"+.en"
                        qvzf = qvz//mionchar1//ionchar1//
     &                  lchargechar1//"+.tof"
                        qvzeff = qvz//mionchar1//ionchar1//
     &                  lchargechar1//"+.eff"
                        qvzet = qvz//mionchar1//ionchar1//
     &                  lchargechar1//"+_eff"
                      else if (lchargeint .ge. 10) then
                        qvze = qvz//mionchar1//ionchar1//
     &                  lchargechar2//"+.en"
                        qvzf = qvz//mionchar1//ionchar1//
     &                  lchargechar2//"+.tof"
                        qvzeff = qvz//mionchar1//ionchar1//
     &                  lchargechar2//"+.eff"
                        qvzet = qvz//mionchar1//ionchar1//
     &                  lchargechar2//"+_eff"
                      end if
                    else if (ioncharlen .eq. 2) then
                      if (lchargeint .le. 9) then
                        qvze = qvz//mionchar1//ionchar2//
     &                  lchargechar1//"+.en"
                        qvzf = qvz//mionchar1//ionchar2//
     &                  lchargechar1//"+.tof"
                        qvzeff = qvz//mionchar1//ionchar2//
     &                  lchargechar1//"+.eff"
                        qvzet = qvz//mionchar1//ionchar2//
     &                  lchargechar1//"+_eff"
                      else if (lchargeint .ge. 10) then
                        qvze = qvz//mionchar1//ionchar2//
     &                  lchargechar2//"+.en"
                        qvzf = qvz//mionchar1//ionchar2//
     &                  lchargechar2//"+.tof"
                        qvzeff = qvz//mionchar1//ionchar2//
     &                  lchargechar2//"+.eff"
                        qvzet = qvz//mionchar1//ionchar2//
     &                  lchargechar2//"+_eff"
                      end if
                    end if
                  else if ((mionint .ge. 10) .and. 
     &                     (mionint .le. 99)) then
                    if (ioncharlen .eq. 1) then
                      if (lchargeint .le. 9) then
                        qvze = qvz//mionchar2//ionchar1//
     &                  lchargechar1//"+.en"
                        qvzf = qvz//mionchar2//ionchar1//
     &                  lchargechar1//"+.tof"
                        qvzeff = qvz//mionchar2//ionchar1//
     &                  lchargechar1//"+.eff"
                        qvzet = qvz//mionchar2//ionchar1//
     &                  lchargechar1//"+_eff"
                      else if (lchargeint .ge. 10) then
                        qvze = qvz//mionchar2//ionchar1//
     &                  lchargechar2//"+.en"
                        qvzf = qvz//mionchar2//ionchar1//
     &                  lchargechar2//"+.tof"
                        qvzeff = qvz//mionchar2//ionchar1//
     &                  lchargechar2//"+.eff"
                        qvzet = qvz//mionchar2//ionchar1//
     &                  lchargechar2//"+_eff"
                      end if
                    else if (ioncharlen .eq. 2) then
                      if (lchargeint .le. 9) then
                        qvze = qvz//mionchar2//ionchar2//
     &                  lchargechar1//"+.en"
                        qvzf = qvz//mionchar2//ionchar2//
     &                  lchargechar1//"+.tof"
                        qvzeff = qvz//mionchar2//ionchar2//
     &                  lchargechar1//"+.eff"
                        qvzet = qvz//mionchar2//ionchar2//
     &                  lchargechar1//"+_eff"
                      else if (lchargeint .ge. 10) then
                        qvze = qvz//mionchar2//ionchar2//
     &                  lchargechar2//"+.en"
                        qvzf = qvz//mionchar2//ionchar2//
     &                  lchargechar2//"+.tof"
                        qvzeff = qvz//mionchar2//ionchar2//
     &                  lchargechar2//"+.eff"
                        qvzet = qvz//mionchar2//ionchar2//
     &                  lchargechar2//"+_eff"
                      end if
                    end if
                  else if (mionint .ge. 100) then
                    if (ioncharlen .eq. 1) then
                      if (lchargeint .le. 9) then
                        qvze = qvz//mionchar3//ionchar1//
     &                  lchargechar1//"+.en"
                        qvzf = qvz//mionchar3//ionchar1//
     &                  lchargechar1//"+.tof"
                        qvzeff = qvz//mionchar3//ionchar1//
     &                  lchargechar1//"+.eff"
                        qvzet = qvz//mionchar3//ionchar1//
     &                  lchargechar1//"+_eff"
                      else if (lchargeint .ge. 10) then
                        qvze = qvz//mionchar3//ionchar1//
     &                  lchargechar2//"+.en"
                        qvzf = qvz//mionchar3//ionchar1//
     &                  lchargechar2//"+.tof"
                        qvzeff = qvz//mionchar3//ionchar1//
     &                  lchargechar2//"+.eff"
                        qvzet = qvz//mionchar3//ionchar1//
     &                  lchargechar2//"+_eff"
                      end if
                    else if (ioncharlen .eq. 2) then
                      if (lchargeint .le. 9) then
                        qvze = qvz//mionchar3//ionchar2//
     &                  lchargechar1//"+.en"
                        qvzf = qvz//mionchar3//ionchar2//
     &                  lchargechar1//"+.tof"
                        qvzeff = qvz//mionchar3//ionchar2//
     &                  lchargechar1//"+.eff"
                        qvzet = qvz//mionchar3//ionchar2//
     &                  lchargechar1//"+_eff"
                      else if (lchargeint .ge. 10) then
                        qvze = qvz//mionchar3//ionchar2//
     &                  lchargechar2//"+.en"
                        qvzf = qvz//mionchar3//ionchar2//
     &                  lchargechar2//"+.tof"
                        qvzeff = qvz//mionchar3//ionchar2//
     &                  lchargechar2//"+.eff"
                        qvzet = qvz//mionchar3//ionchar2//
     &                  lchargechar2//"+_eff"
                      end if
                    end if
                  end if

                  write(*,*) qvze,qvzf,qvzeff,qvzet
                  open (unit=1, file= qvze)
                  if (mionint .eq. 1) then
                    C1=0.22
                    C1delta(1)=0.2
                    C1delta(2)=0.254
                    C1delta(1)=C1-
     .                      ((((C1-C1delta(1))/C1)**2+0.071**2)**0.5)*C1
                    C1delta(2)=C1+
     .                      ((((C1-C1delta(2))/C1)**2+0.071**2)**0.5)*C1
                  else if ((mionint .eq. 3) .or. (mionint .eq. 4)) then
                    C1=0.1496
                    C1delta(1)=0.136
                    C1delta(2)=0.172
                    C1delta(1)=C1-
     .                      ((((C1-C1delta(1))/C1)**2+0.071**2)**0.5)*C1
                    C1delta(2)=C1+
     .                      ((((C1-C1delta(2))/C1)**2+0.071**2)**0.5)*C1
                  else
                    C1=0.085
                    C1delta(1)=0.077
                    C1delta(2)=0.098
                    C1delta(1)=C1-
     .                      ((((C1-C1delta(1))/C1)**2+0.071**2)**0.5)*C1
                    C1delta(2)=C1+
     .                      ((((C1-C1delta(2))/C1)**2+0.071**2)**0.5)*C1
                  end if

                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,1.,
     .                          pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,
     .                          1.,1.,1.)
                    write(1,*) eqstep(k), emeas, 
     .                         ((echannelfloat+1.5)/2.)/1.137
                  end do  
                  close(unit=1)

                  open (unit=2, file= qvzf)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,1.,
     .                          pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,
     .                          1.,1.,1.)
                    if (mion .gt. 4) then
                        write(2,*) eqstep(k), tau,
     .                  ((tauchannelfloat+1.5)/2.)/
     .                  (-(eqstep(k)+lpaps)*lcharge/25000.+
     .                  (-0.0518858*exp(-0.0454703*mion)+1.03407))
                    else
                        write(2,*) eqstep(k), tau, 
     .                             ((tauchannelfloat+1.5)/2.)
                    end if
                  end do  
                  close(unit=2)


                  open (unit=3, file= qvzeff)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    if (eperm*mion .le. 1000.) then
                      if (mion .gt. 4) then
                        call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .                          pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,
     .                          1.,1.,1.)
                        call error(EPERM,ZION,MION,ION,
     .                  CHARGE,
     .                  C1,C1delta,
     .                  C2,C2delta,
     .                  C3,C3delta,
     .                  PF1,pf1delta,
     .                  PF2,pf2delta,
     .                  ETHRESH,Ethrdelta,
     .                  FWHMEL,FWHMdelta,
     .                  THICK,thickdelta,
     .                  DEFL, defldelta,
     .                  AUXPAR1,AUXPAR2,AUXPAR3,
     .                  yanlis,oyanlis)
                        if ((bw .gt. 1) .or. (bw .lt. 0)) then
                            write(*,*) "EFFICIENCY OUT OF RANGE!!!!"
                            write(*,*) "FOR ", zion
                        end if
                        write(3,*) eqstep(k), bw, yanlis, oyanlis
                      end if
                    else 
                        write(3,*) eqstep(k),0.0,0.0
                    end if
                  end do
                  close(unit=3)
                  

                  open (unit=4, file= qvzet)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,1.,
     .                          pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,
     .                          1.,1.,1.)
                    write(4,*) eqstep(k)*lcharge,
     .                         ((echannelfloat+1.5)/2.),
     .                          ((tauchannelfloat+1.5)/2.)
                  end do  
                  close(unit=4)

                end do
              end do
            end do
          end do
        end do
      end if

c RANDOM NOISE TEST
      if (run5 .eq. 1) then 
c Ich hatte keine Lust, für den Random Test extra neue Variablen einzuführen.
c Deswegen verwende ich bereists existierende Variablen.
c pf1 ist hier der Erwartungswert und pf2 das Sigma der Gaussverteilung.
c C1 und C2 sind zwei Zufallsvariablen
        pf1=0.
        pf2=1.
        do while (j .lt. 100000)
            call noise(pf1,pf2,C1,C2)
            j=j+1
            do i = -50,50,1
                k=i+51
                if (C1 .gt. (float(i)/10.*pf2+pf1) 
     .          .and. C1 .le. (float(i+1)/10.*pf2+pf1)) then
                    tepe(k)=tepe(k)+1
                end if
            end do
        end do
        do k=1,101
            write(*,*) float(k-51)/10.*pf2+pf1, tepe(k)
        end do
      end if


c RUN FOR ERROR ESTIMATION (RANDOM NOISE)
      if (run6 .eq. 1) then

        auxpar1(1)=0.9
        auxpar1(2)=1.1
        auxpar2(1)=0.9
        auxpar2(2)=1.1
        auxpar3(1)=0.9
        auxpar3(2)=1.1

        write(*,*) " *** PARAMETER ERROR CALCULATION *** "
c Data source to calculate the parameter errors is the oxygen data
        mion=16
        zion=8
        ion="O"
        call paramerror(EPERM,ZION,MION,ION,
     .                  CHARGE,
     .                  C1,C1delta,
     .                  C2,C2delta,
     .                  C3,C3delta,
     .                  PF1,pf1delta,
     .                  PF2,pf2delta,
     .                  ETHRESH,Ethrdelta,
     .                  FWHMEL,FWHMdelta,
     .                  THICK,thickdelta,
     .                  DEFL, defldelta)
        C2delta(1)=C2-((((C2-C2delta(1))/C2)**2+0.072**2)**0.5)*C2
        C2delta(2)=C2+((((C2-C2delta(2))/C2)**2+0.072**2)**0.5)*C2

        write(*,*) " *** READING ION SPECIFIC DATA ***"
        OPEN( UNIT=99,FILE=
     &'./param/ionlist4')
        READ(99,*,END=400),(stuff(i),i=1,4)
        READ(99,*,END=400),(p(i),i=1,7)
        READ(99,*,END=400),(stuff(i),i=1,8)
        l=1
        do while (.true.)
            READ(99,*,END=400),ionr(l), (pr(l,i),i=1,7)
c            write(*,*) (stuff(i),i=1,5)
c            write(*,*) (pr(l,i),i=1,7)
c            write(*,*) ionr(l)
            l=l+1 
        end do       
400     continue
        CLOSE( UNIT=99 )


        lpaps=p(1)
        ftlow=p(2)
        fthigh=p(3)
        ftstep=p(4)
        dllow=p(5)
        dlhigh=p(6)
        dlstep=p(7) 
c        write(*,*) "l =", l-1
        do h=1,l-1
          ion=ionr(h)
          zion=pr(h,1) 
          mionlow=pr(h,2)
          mionhigh=pr(h,3) 
          mionstep=pr(h,4)
          chargelow=pr(h,5)
          chargehigh=pr(h,6)
          chargestep=pr(h,7)

          do dl=dllow,dlhigh,dlstep
            do ft=ftlow,fthigh,ftstep
              do lcharge=chargelow,chargehigh,chargestep
                do mion=mionlow,mionhigh,mionstep
                  dlint=int(dl)
                  thick=ft/10
                  ftint=int(ft)
                  lchargeint=int(lcharge)
                  mionint=int(mion)
                  zionint=int(zion)
                  lpapsint=int(lpaps)
                  call elname(zionint,ionchar1,ionchar2,ioncharlen)
                  if (lchargeint .le. 9) then
                    call ftos(lchargeint,lchargechar1,YYY,ZZZ,1)
                  else if (lchargeint .ge. 10) then
                    call ftos(lchargeint,XXX,lchargechar2,ZZZ,2)
                  end if
                  call ftos(ftint,XXX,ftchar,ZZZ,2)
                  call ftos(dlint,XXX,YYY,dlchar,3)
                  call ftos(mionint,mionchar1,YYY,ZZZ,1)
                  call ftos(mionint,XXX,mionchar2,ZZZ,2)
                  call ftos(mionint,XXX,YYY,mionchar3,3)
                  call ftos(lpapsint,XXX,lpapschar,ZZZ,2)
c                  qvz="./lars/paps"//lpapschar//"/"
                  qvz="./lars/error5/"
                  do k =1,58
                   do g=-50,50,1
                        tepe(g+51)=0.
                   end do
    
                   if (k .le. 9) then
                    call ftos(k,dummy1,YYY,ZZZ,1)
                    if (mionint .le. 9) then
                      if (ioncharlen .eq. 1) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar1//ionchar1//
     &                  lchargechar1//"_step"//dummy1
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar1//ionchar1//
     &                  lchargechar2//"_step"//dummy1
                       end if
                      else if (ioncharlen .eq. 2) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar1//ionchar2//
     &                  lchargechar1//"_step"//dummy1
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar1//ionchar2//
     &                  lchargechar2//"_step"//dummy1
                       end if
                      end if
                    else if ((mionint .ge. 10) .and. 
     &                     (mionint .le. 99)) then
                      if (ioncharlen .eq. 1) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar2//ionchar1//
     &                  lchargechar1//"_step"//dummy1
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar2//ionchar1//
     &                  lchargechar2//"_step"//dummy1
                       end if
                      else if (ioncharlen .eq. 2) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar2//ionchar2//
     &                  lchargechar1//"_step"//dummy1
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar2//ionchar2//
     &                  lchargechar2//"_step"//dummy1
                       end if
                      end if
                    else if (mionint .ge. 100) then
                      if (ioncharlen .eq. 1) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar3//ionchar1//
     &                  lchargechar1//"_step"//dummy1
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar3//ionchar1//
     &                  lchargechar2//"_step"//dummy1
                       end if
                      else if (ioncharlen .eq. 2) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar3//ionchar2//
     &                  lchargechar1//"_step"//dummy1
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar3//ionchar2//
     &                  lchargechar2//"_step"//dummy1
                       end if
                      end if
                    end if
                   end if

                   if (k .ge. 10) then
                    call ftos(k,XXX,dummy2,ZZZ,2)
                    if (mionint .le. 9) then
                      if (ioncharlen .eq. 1) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar1//ionchar1//
     &                  lchargechar1//"_step"//dummy2
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar1//ionchar1//
     &                  lchargechar2//"_step"//dummy2
                       end if
                      else if (ioncharlen .eq. 2) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar1//ionchar2//
     &                  lchargechar1//"_step"//dummy2
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar1//ionchar2//
     &                  lchargechar2//"_step"//dummy2
                       end if
                      end if
                    else if ((mionint .ge. 10) .and. 
     &                     (mionint .le. 99)) then
                      if (ioncharlen .eq. 1) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar2//ionchar1//
     &                  lchargechar1//"_step"//dummy2
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar2//ionchar1//
     &                  lchargechar2//"_step"//dummy2
                       end if
                      else if (ioncharlen .eq. 2) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar2//ionchar2//
     &                  lchargechar1//"_step"//dummy2
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar2//ionchar2//
     &                  lchargechar2//"_step"//dummy2
                       end if
                      end if
                    else if (mionint .ge. 100) then
                      if (ioncharlen .eq. 1) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar3//ionchar1//
     &                  lchargechar1//"_step"//dummy2
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar3//ionchar1//
     &                  lchargechar2//"_step"//dummy2
                       end if
                      else if (ioncharlen .eq. 2) then
                       if (lchargeint .le. 9) then
                        qvzerror = qvz//mionchar3//ionchar2//
     &                  lchargechar1//"_step"//dummy2
                       else if (lchargeint .ge. 10) then
                        qvzerror = qvz//mionchar3//ionchar2//
     &                  lchargechar2//"_step"//dummy2
                       end if
                      end if
                    end if
                   end if
                   write(*,*) "filename =  ", qvzerror
                   if (mionint .eq. 1) then
                    C1=0.22
                    C1delta(1)=0.2
                    C1delta(2)=0.254
                    C1delta(1)=C1-
     .                      ((((C1-C1delta(1))/C1)**2+0.071**2)**0.5)*C1
                    C1delta(2)=C1+
     .                      ((((C1-C1delta(2))/C1)**2+0.071**2)**0.5)*C1
                   else if ((mionint .eq. 3) .or. (mionint .eq. 4)) then
                    C1=0.1496
                    C1delta(1)=0.136
                    C1delta(2)=0.172
                    C1delta(1)=C1-
     .                      ((((C1-C1delta(1))/C1)**2+0.071**2)**0.5)*C1
                    C1delta(2)=C1+
     .                      ((((C1-C1delta(2))/C1)**2+0.071**2)**0.5)*C1
                   else
                    C1=0.085
                    C1delta(1)=0.077
                    C1delta(2)=0.098
                    C1delta(1)=C1-
     .                      ((((C1-C1delta(1))/C1)**2+0.071**2)**0.5)*C1
                    C1delta(2)=C1+
     .                      ((((C1-C1delta(2))/C1)**2+0.071**2)**0.5)*C1
                   end if
                   do l=1,10000
c                    write(*,*) l
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .                          pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,
     .                          1.,1.,1.)
                    i=1
                    j=1
                    call noise(C1,abs(C1-C1delta(i)),C1R(1),C1R(2))
                    call noise(C2,abs(C2-C2delta(i)),C2R(1),C2R(2))
c                    call noise(C3,abs(C3-C3delta(i)),C3R(1),C3R(2))
                    call noise(pf1,abs(pf1-pf1delta(i)),pf1R(1),pf1R(2))
                    call noise(pf2,abs(pf2-pf2delta(i)),pf2R(1),pf2R(2))
                    call noise(Ethresh,abs(Ethresh-Ethrdelta(i)),
     .                         EthreshR(1),EthreshR(2))
                    call noise(FWHMEL,abs(FWHMEL-FWHMdelta(i)),
     .                         FWHMELR(1),FWHMELR(2))
                    call noise(thick,abs(thick-thickdelta(i)),
     .                         thickR(1),thickR(2))
                    call noise(1.,0.1,auxpar1R(1),auxpar1R(2))
                    call noise(1.,0.1,auxpar2R(1),auxpar2R(2))
                    call noise(1.,0.1,auxpar3R(1),auxpar3R(2))
                    call swxeff(bwr,eperm,zion,mion,ion,
     .                          C1R(j),C2R(j),1.,
     .                          pf1R(j),pf2R(j),
     .                          ETHRESHR(j),FWHMELR(j),
     .                          thickR(j),0.0,4.,
     .                          auxpar1R(j),auxpar2R(j),auxpar3R(j))
                    do f = -50,50,1
                        if (((bwr) .gt. (bw+(bw/100.)*float(f)))
     .                  .and. (bwr) .le. (bw+(bw/100.)*float(f+1)))
     .                  then
                            tepe(f+51)=tepe(f+51)+1
                        end if
                    end do
                   end do
                   open (unit=5, file = qvzerror)
                   do g=-50,50,1
                        write(5,*) (bw+(bw/100.)*(g+0.5)), tepe(g+51)
                   end do
                    close (unit=5)
                  end do
                end do
              end do
            end do
          end do
        end do
      end if


C ++++++++ Monte Carlo Integration ++++++++++++++++++++++++++++++
      if (run7 .eq. 1) then
c        do i=1,3
c          do j=1,4
c           write(*,*) (ssdi(i,j,k),k=1,3)
c           write(*,*) (ssdc(i,j,k),k=1,3)
c          end do
c        end do
c        write(*,*) c
        defl=0.0
        do sigma=0.01,0.3,0.01
        if (nint(sigma*100) .le. 9) then
            call ftos(nint(sigma*100),XXX,YYY,ZZZ,1)
            OPEN( UNIT=100,FILE=
     &'/home/kleopatra/mu/Desktop/sigma_defl_tab/exp19/s_'//XXX//'_d_0')
        else if ((nint(sigma*100) .ge. 10) 
     .          .and. (nint(sigma*100) .le. 99)) then
            call ftos(nint(sigma*100),XXX,YYY,ZZZ,2)
            OPEN( UNIT=100,FILE=
     &'/home/kleopatra/mu/Desktop/sigma_defl_tab/exp19/s_'//YYY//'_d_0')
        else if (nint(sigma*100) .ge. 100) then
            call ftos(nint(sigma*100),XXX,YYY,ZZZ,3)
            OPEN( UNIT=100,FILE=
     &'/home/kleopatra/mu/Desktop/sigma_defl_tab/exp19/s_'//ZZZ//'_d_0')
        end if
c        OPEN( UNIT=100,FILE=
c     &'/home/kleopatra/mu/Desktop/sigma_defl_tab/exp15/s_0.01_d_0.0')
        j=1
        do while (j .le. 1000)
            READ(100,*,END=500),(sval(j,i),i=1,2)
            j=j+1
        end do
500     continue
        CLOSE( UNIT=100 )
        pi=3.1415927
        limit=0.
        buffer=0.
        do h = 1,101,1
            tepe(h)=0.0
        end do 
c        write(*,*) sval
        do i=1,1000000
600        integral=rand()
c           write(*,*) integral
           buffer=buffer+1
          j=1
          do while (sval(j,2) .lt. integral)
            j=j+1
          end do
c          write(*,*) integral, sval(j,2), j
          if (j .ge. 1000) goto 600
          if (j .ge. 2) then
            randomtheta=sval(j-1,1)+(sval(j,1)-sval(j-1,1))/
     &      (sval(j,2)-sval(j-1,2))*(integral-sval(j-1,2))
          else if (j .eq. 1) then
            randomtheta=(sval(j,1))/(sval(j,2))*integral
          else
            write(*,*) " index out of range !!!"
          end if

          randomphi=rand()
          randomphi=randomphi*2.*pi

c            write(*,*) randomtheta
          do h = 1,101,1
            if ((randomtheta .gt. (float(h-1))/100.)
     .      .and. (randomtheta .le. (float(h))/100.))
     .      then
                tepe(h)=tepe(h)+1
            end if
          end do 

          call rotation(v(1),v(2),v(3),vn(1),vn(2),vn(3),
     .                  randomtheta,vd(1),vd(2),vd(3))
          call rotation(vd(1),vd(2),vd(3),v(1),v(2),v(3),
     .                  randomphi,vr(1),vr(2),vr(3))
c          write(*,*) v,vn,vd,randomtheta,randomphi,vr
          do j=1,3
            call schnittpunkt(c(1),c(2),c(3),vr(1),vr(2),vr(3),
     .                      ssdi(j,1,1),ssdi(j,1,2),ssdi(j,1,3),
     .                      ssdi(j,2,1),ssdi(j,2,2),ssdi(j,2,3),
     .                      ssdi(j,3,1),ssdi(j,3,2),ssdi(j,3,3),
     .                      sp(1),sp(2),sp(3))
c          write(*,*)  sp
            
            if (j .eq. 1) then
                if   ((sp(1) .ge. ssdi(j,4,1))
     .              .and. (sp(1) .le. ssdi(j,2,1))
     .              .and. (sp(2) .ge. ssdi(j,4,2))
     .              .and. (sp(2) .le. ssdi(j,3,2))
     .              .and. (sp(3) .ge. ssdi(j,4,3))
     .              .and. (sp(3) .le. ssdi(j,1,3)))
     .              then
                        limit=limit+1
c                        write(*,*) sp
                end if
            else if (j .eq. 2) then
                if   ((sp(1) .ge. ssdi(j,3,1))
     .              .and. (sp(1) .le. ssdi(j,1,1))
     .              .and. (sp(2) .ge. ssdi(j,4,2))
     .              .and. (sp(2) .le. ssdi(j,3,2))
     .              .and. (sp(3) .ge. ssdi(j,4,3))
     .              .and. (sp(3) .le. ssdi(j,2,3)))
     .              then
                        limit=limit+1
c                        write(*,*) sp
                end if
            else if (j .eq.3 ) then
                if   ((sp(1) .ge. ssdi(j,3,1))
     .              .and. (sp(1) .le. ssdi(j,1,1))
     .              .and. (sp(2) .ge. ssdi(j,4,2))
     .              .and. (sp(2) .le. ssdi(j,3,2))
     .              .and. (sp(3) .ge. ssdi(j,4,3))
     .              .and. (sp(3) .le. ssdi(j,2,3)))
     .              then
                        limit=limit+1
c                        write(*,*) sp
                end if
            end if
          end do
c        end do
        end do
        write(*,*) sigma,limit/buffer
        end do
c        do k=1,101,1
c            write(*,*) (float(k))/100., tepe(k)
c        end do
      end if
c DIFFERENT EXPERIMENTS
      if (run8 .eq. 1) then
        sumint=0.0
        lpaps=24.868179
        mion=16
        zion=8
        ion="O"
        lcharge=6
        thick=2.5
        thickdelta(1)=2.27
        thickdelta(2)=2.72
        C1=0.085
        C1delta(1)=0.077
        C1delta(2)=0.098
        C2=0.85
        C2delta(1)=0.44
        C2delta(2)=1.70
        C3=1.0
        pf1=0.785
        pf1delta(1)=0.752
        pf1delta(2)=0.813
        pf2=0.785
        pf2delta(1)=0.752
        pf2delta(2)=0.813
        FWHMEL=13.9549
        FWHMdelta(1)=11.72
        FWHMdelta(2)=15.35
        Ethresh=27.38
        Ethrdelta(1)=26.0109997
        Ethrdelta(2)=29.2965984
        defl=0.043
        auxpar1(1)=0.9
        auxpar1(2)=1.1
        auxpar2(1)=0.9
        auxpar2(2)=1.1
        auxpar3(1)=0.9
        auxpar3(2)=1.1
        defl=0.0

      pi=3.1415927
      res=0.
      defl=0.00
      sigma=0.03
c      do defl = 0.0,0.3,0.001
c      do sigma = 0.001,0.3,0.001
      do i=1,10000
      integral=rand()
      limit=0.
      res=0.
      do while (res .lt. integral)
      limit = limit + 0.001
      res=0.
      gg=defl
      xz=sigma
      xy=0.
      step=0.001
      do while (xy .lt. limit)
        if (defl .eq. 0.0) then
           res=res+abs(1/(4*pi*sigma**2
     &     *(1-0.137*sigma-2.57*sigma**2+2.85*sigma**3))
     &     *((1+xy**2/(4*sigma**2))**(-2))*sin(xy)*2*pi)
           xy=xy+step
        else
           res=res+abs((-(2*(-(gg/xz)+(xy/xz)))/
     &       (4+(-(gg/xz)+(xy/xz))**2)
     &       + 2*((gg/xz)+(xy/xz))/(4+((gg/xz)+(xy/xz))**2) 
     &       - atan(((xy/xz)-(gg/xz))/2)
     &       + atan(((xy/xz)+(gg/xz))/2))
     &       / (pi*xz**2*(4*(gg/xz)
     &       + 0.5*pi*(12+(gg/xz)**2) 
     &       - (12+(gg/xz)**2)*atan(2*xz/gg)+(-4+(gg/xz)**2)
     &       *atan(gg/(2*xz))))
     &       * sin(xy)*2*pi)
     &       /(0.998712-4.24825*xz**2+9.92229*xz**3-9.79119*xz**4)
           xy=xy+step
        end if
c        write(*,*) alpha,"  ",result
      end do
      res=res*step
c      write(*,*) defl,sigma,limit,res*step
c      write(*,*) limit,res
      end do
c      write(*,*) limit, integral, res
c        if ((limit .gt. 0.0)
c     .  .and. (limit .le.0.001))
c     .  then
c            print "juhu"
c        end if

      do h = 1,101,1
        if ((limit .gt. (float(h-1))/400.)
     .  .and. (limit .le. (float(h))/400.))
     .  then
            tepe(h)=tepe(h)+1
        end if
      end do 
      end do
      do k=1,101,1
            write(*,*) (float(k-1)+0.5)/400., tepe(k)
      end do

c      end do
c      end do



c        do defl = 0.0,0.3,0.001
c        do thick = 0.001,0.3,0.001
c        call integrationconv(1.,10.,10.,
c     .                 1.,-10.,10.,
c     .                 1.,-10.,-10.,
c     .                 1.,10.,-10.,
c     .                 -1.,0.,0.,1.,0.,0.,
c     .                 thick,thick,defl,bw1,bw2)
c        write(*,*) defl,thick,bw1, bw2
c        end do !sigmal
c        end do !defl
c        do i =1,100000
c        defl=ran1(defl)
c        write(*,*) defl
c        end do
c        pf1=-1
c        defl=ran2(int(pf1))
c        write(*,*) defl
c        pf1=-1
c        defl=ran3(int(pf1))
c        write(*,*) defl

                   do k=30,30
                    do l=1,10
c                    write(*,*) l
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .                          pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,
     .                          1.,1.,1.)
                    i=1
                    j=1
                    call noise(C1,abs(C1-C1delta(i)),C1R(1),C1R(2))
                    call noise(C2,abs(C2-C2delta(i)),C2R(1),C2R(2))
c                    call noise(C3,abs(C3-C3delta(i)),C3R(1),C3R(2))
                    call noise(pf1,abs(pf1-pf1delta(i)),pf1R(1),pf1R(2))
                    call noise(pf2,abs(pf2-pf2delta(i)),pf2R(1),pf2R(2))
                    call noise(Ethresh,abs(Ethresh-Ethrdelta(i)),
     .                         EthreshR(1),EthreshR(2))
                    call noise(FWHMEL,abs(FWHMEL-FWHMdelta(i)),
     .                         FWHMELR(1),FWHMELR(2))
                    call noise(thick,abs(thick-thickdelta(i)),
     .                         thickR(1),thickR(2))
                    call noise(1.,0.2,auxpar1R(1),auxpar1R(2))
                    call noise(1.,0.2,auxpar2R(1),auxpar2R(2))
                    call noise(1.,0.2,auxpar3R(1),auxpar3R(2))
                    call swxeff(bwr,eperm,zion,mion,ion,
     .                          C1R(j),C2R(j),1.,
     .                          pf1R(j),pf2R(j),
     .                          ETHRESHR(j),FWHMELR(j),
     .                          thickR(j),0.0,4.,
     .                          auxpar1R(j),auxpar2R(j),auxpar3R(j))
                    do h = -50,50,1
                        if (((bwr) .gt. (bw+(bw/100.)*float(h)))
     .                  .and. (bwr) .le. (bw+(bw/100.)*float(h+1)))
     .                  then
                            tepe(h+51)=tepe(h+51)+1
                        end if
                    end do
                    end do
                   end do
        do k=-50,50,1
c            write(*,*) (bw+(bw/100.)*(k+0.5)), tepe(k+51)
        end do


      end if



c ################ Ende (B) ################################

c##############Energiepeak-Berechnung#######################
c Als Einlesefile dient transmitfe500.f (leicht modifizierte 
c Version des TRIM outputs.

c++++++++ Daiei öffnen +++++++++++++++++++++++++++++++++++++

c        OPEN( UNIT=1,FILE=
c     &'./dedxint/'//
c     &'transmit_fe_500keV_110A.f')
c        do l=1,100000
c          READ(1,*,END=500),(pp(l,i),i=1,9)
c          write(*,*) (pp(l,i),i=1,9)
c        end do 
c500     continue
c        CLOSE( UNIT=1 )


c++++++++ Berechnung des Mittelwert ++++++++++++++++++++++++
c        mw=0.
c        do k=1,100000
c          mw=mw+pp(k,3)
c          write(*,*) k, mw/k
c        end do


c++++++++ Berechnung des Median ++++++++++++++++++++++++++++
c        med=500000.
c        k=0
c        do while (k .le. 100000/2)
c          k=0
c            do l=1,100000
c              if (pp(l,3) .ge. med) then
c                k=k+1
c              end if
c            end do
c            write(*,*) k, med
c            med=med-1
c        end do



c++++++++ Berechnung der Energieverteilung++++++++++++++++++         
c        do i=1,100
c          tepe(i)=0.0
c          denergie(i)=0.0
c          gesamtenergie(i)=0.0
c        end do
c
c        limit=400000.
c        do j=1,100
c          do k=1,100000
c            if ((pp(k,3) .ge. (limit+j*1000.)) .and. 
c     &         (pp(k,3) .lt. (limit+(j+1)*1000.))) then
c                 tepe(j)=tepe(j)+1
c                 write(*,*) tepe(j)
c            end if
c          end do
c          write(*,*) limit/1000.+float(j)/1, tepe(j)
c        end do


c++++++++ Berechnung der Winkelverteilung und 
c         Durchschnittsenergie als Funktion des Winkels+++++         
c        sumint=0.001
c        limit=-1.*sumint
c        do j=1,100
c          do k=1,99999
c            if ((ABS(acos(pp(k,7))) .ge. (limit+j*sumint)) .and. 
c     &         (ABS(acos(pp(k,7))) .lt. (limit+(j+1)*sumint))) then
c              tepe(j)=tepe(j)+1
c              gesamtenergie(j)=gesamtenergie(j)+pp(k,3)
c              write(*,*) tepe(j)
c            end if
c          end do
c          write(*,*) limit + float(j)*sumint, tepe(j)
c          if (tepe(j) .ne. 0) then
c            denergie(j)=gesamtenergie(j)/tepe(j)
c          end if
c          write(*,*) limit + float(j)*sumint, denergie(j)
c        end do
 
c++++++++ Berechnung der Winkelverteilung (3-dimensional)
c       do i=-50,50,1
c        do j=-50,50,1
c          tepe3d(i,j)=0
c        end do
c      end do

c        sumint=0.001
c        do i=-50,50,1
c          do j=-50,50,1
c            do k=1,99999
c              if ((((asin(pp(k,8))) .ge. (i*sumint)) .and. 
c     &           ((asin(pp(k,8))) .lt. ((i+1)*sumint))) .and. 
c     &          (((asin(pp(k,9))) .ge. (j*sumint)) .and. 
c     &           ((asin(pp(k,9))) .lt. ((j+1)*sumint)))) then
c                tepe3d(i,j)=tepe3d(i,j)+1
c              end if
c            end do
c            write(*,*) i,j,tepe3d(i,j)            
c          end do
c        end do


cc##############ende für lars################################            
       STOP 

       END
