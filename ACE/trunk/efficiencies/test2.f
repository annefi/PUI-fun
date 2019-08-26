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

        COMMON /GEOM/ C,V,DELTAWIN,PHIWIN,DELTASTP,PHISTP,
     .                DELTASSD,PHISSD,DELTAMACOR,PHIMACOR,
     .                BRAIN,SSDC,STPC,MACORC,SSDI,STPI,
     .                COUNTER,WALKER,RUNNER,JUMPER,FITGEOM,
     .                FITMODE
     
        REAL*4
     .      C(3),               ! entry point in C-foil
     .      V(3),               ! beam norm vector
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
     .      FITMODE             ! 0 = alle , 1 = Jedes Ion einzeln

c*******End of common-block /GEOM/*******************************


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
     .      tepe(100),          ! array for the counts in a particular interval
     .      tepe3d(-50:50,-50:50),  !array for the 3d angular distribution
     .      gesamtenergie(100), ! auxiliary array for the calculation of the average energy subject to angle
     .      denergie(100),      ! array for the calculation of the average energy subject to angle
     .      sumint,             ! interval for summation
     .      med,                ! median of the energy distribution
     .      defl,
     .      defldelta(2),
     .      C1,
     .      C1delta(2),
     .      C2,
     .      C2delta(2),
     .      C3,
     .      C3delta(2),
     .      pf1,
     .      pf1delta(2),
     .      pf2,
     .      pf2delta(2),
     .      FWHMEL,
     .      FWHMdelta(2),
     .      Ethresh,
     .      Ethrdelta(2),
     .      thickdelta(2),
     .      charge,
     .      bw1,
     .      bw2,
     .      fehler(2),
     .      yanlis,
     .      WSSR,
     .      PROBMODE

        REAL*4                  ! Variables for the dutycycle function
     .      aspang,             ! Aspect angle
     .      thang,              ! thermal angle
     .      dutycycleth         ! Dutycycle function

        CHARACTER*20
     .      IONR(100),          ! buffer for element abbreviation for ION
     .      ION                 ! element abbreviation for ION

        CHARACTER*10
     .      stuff(10)           ! dummy buffer for unused information in
                                ! './param/parameters' 

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

        INTEGER h,i,j,k,l,      ! auxiliary loop variables
     .      dc1,dc2,dc3,dpf1,dpf2,dfwhm,dethr,dthick


c++++++ different variables and dummys to built the particular filename ++        
        CHARACTER*1
     .      XXX,lchargechar1,ionchar1,mionchar1 
        CHARACTER*2
     .      YYY,lpapschar,ftchar,ionchar2,mionchar2,
     .      lchargechar2
        CHARACTER*3
     .      ZZZ,dlchar,mionchar3

        INTEGER zionint,mionint,lchargeint,lpapsint,ftint,dlint

        REAL*4                  ! Parameters to start different efficiency modi
     .  run1,                   ! Test run for the dutycycle function
     .  run2,                   ! Read the E/q steps
     .  run3,                   ! Test run for swxeff
     .  run4,                   ! E-T-positions and efficiencies of 13C
     .  run5,                   ! E-T-positions and efficiencies of 3He
     .  run6,                   ! E-T-positions and efficiencies of H
     .  run7,                   ! Run for all elements in param/parameters
     .  run8                    ! Different experiments


        CALL GEOMETRIE()

      run1=0                    ! Test run for the dutycycle function
      run2=1                    ! Read the E/q steps
      run3=0                    ! Test run for swxeff
      run4=0                    ! E-T-positions and efficiencies of 13C
      run5=0                    ! E-T-positions and efficiencies of 3He
      run6=0                    ! E-T-positions and efficiencies of H
      run7=0                    ! Run for all elements in param/parameters
      run8=1                    ! Different experiments


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
        C2=1.22
        C3=1.0
        pf1=0.785
        pf2=0.785
        FWHMEL=13.9
        Ethresh=27.3
        defl=0.069
        PROBMODE=1

        do k=1,58
            eperm=((eqstep(k))+lpaps)*lcharge/mion
            call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl,
     .              PROBMODE)
c        write(*,*) eperm, bw
        end do
      end if


c E-T-POSITIONS AND EFFICIENCIES OF 13C
      if (run4 .eq. 1) then
        do lcharge=1,6
            lchargeint=int(lcharge)
            call ftos(lchargeint,lchargechar1,YYY,ZZZ,1)
            open (unit=1, file="/home/kleopatra/mu/Desktop/swics/"//
     .                         "efficiencies/lars/paps24/13C"//
     .                         lchargechar1//"+.en")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/13.
                call swxeff(bw,eperm,6.,13.,"C",0.11,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(1,*) eqstep(k), emeas, 
     .                     ((echannelfloat+1.5)/2.)/1.137
            end do  
            close(unit=1)

            open (unit=2, file="/home/kleopatra/mu/Desktop/swics/"//
     .                     "efficiencies/lars/paps24/13C"//
     .                     lchargechar1//"+.tof")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/13.
                call swxeff(bw,eperm,6.,13.,"C",0.11,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(2,*) eqstep(k), tau, ((tauchannelfloat+1.5)/2.)/
     .                     (-(eqstep(k)+lpaps)*lcharge/25000.+
     .                     (-0.0518858*exp(-0.0454703*13.)+1.03407))
            end do  
            close(unit=2)

            open (unit=3, file="/home/kleopatra/mu/Desktop/swics/"//
     .                     "efficiencies/lars/paps24/13C"//
     .                     lchargechar1//"+.eff")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/13.
                call swxeff(bw,eperm,6.,13.,"C",0.11,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(3,*) eqstep(k),bw
            end do  
            close(unit=3)
        end do
      end if


c E-T-POSITIONS AND EFFICIENCIES OF 3He
      if (run5 .eq. 1) then
        do lcharge=1,2
            lchargeint=int(lcharge)
            call ftos(lchargeint,lchargechar1,YYY,ZZZ,1)
            open (unit=1, file="/home/kleopatra/mu/Desktop/swics/"//
     .                         "efficiencies/lars/paps24/3He"//
     .                         lchargechar1//"+.en")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/3.
                call swxeff(bw,eperm,2.,3.,"He",0.1496,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(1,*) eqstep(k), emeas, 
     .                     ((echannelfloat+1.5)/2.)/1.137
            end do  
            close(unit=1)

            open (unit=2, file="/home/kleopatra/mu/Desktop/swics/"//
     .                     "efficiencies/lars/paps24/3He"//
     .                     lchargechar1//"+.tof")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/3.
                call swxeff(bw,eperm,2.,3.,"He",0.1496,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(2,*) eqstep(k), tau, ((tauchannelfloat+1.5)/2.)
            end do  
            close(unit=2)

            open (unit=3, file="/home/kleopatra/mu/Desktop/swics/"//
     .                     "efficiencies/lars/paps24/3He"//
     .                     lchargechar1//"+.eff")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/3.
                call swxeff(bw,eperm,2.,3.,"He",0.1496,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(3,*) eqstep(k),bw
            end do  
            close(unit=3)
        end do
      end if

c E-T-POSITIONS AND EFFICIENCIES OF H
      if (run6 .eq. 1) then
        do lcharge=1,1
            lchargeint=int(lcharge)
            call ftos(lchargeint,lchargechar1,YYY,ZZZ,1)
            open (unit=1, file="/home/kleopatra/mu/Desktop/swics/"//
     .                         "efficiencies/lars/paps24/H"//
     .                         lchargechar1//"+.en")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/1.
                call swxeff(bw,eperm,1.,1.,"H",0.1496,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(1,*) eqstep(k), emeas, 
     .                     ((echannelfloat+1.5)/2.)/1.137
            end do  
            close(unit=1)

            open (unit=2, file="/home/kleopatra/mu/Desktop/swics/"//
     .                     "efficiencies/lars/paps24/H"//
     .                     lchargechar1//"+.tof")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/1.
                call swxeff(bw,eperm,1.,1.,"H",0.1496,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(2,*) eqstep(k), tau, ((tauchannelfloat+1.5)/2.)
            end do  
            close(unit=2)

            open (unit=3, file="/home/kleopatra/mu/Desktop/swics/"//
     .                     "efficiencies/lars/paps24/H"//
     .                     lchargechar1//"+.eff")
            do k=1,58
                eperm=((eqstep(k))+lpaps)*lcharge/1.
                call swxeff(bw,eperm,1.,1.,"H",0.1496,0.718,0.418,
     .                      0.785,0.785,28.6,10.,thick,0.0,4.)
                write(3,*) eqstep(k),bw
            end do  
            close(unit=3)
        end do
      end if




c Einlesen des Parameterfiles, Ionen, Massen, Ladungszustände
      if ( run7 .eq. 1 ) then


        C1=0.085
        C2=1.0
        C3=1.0
        pf1=0.785
        pf2=0.785
        FWHMEL=13.9
        Ethresh=27.3
        
        C1delta(1)=0.077
        C1delta(2)=0.098
        C2delta(1)=0.46
        C2delta(2)=3.0
        C3delta(1)=0.929
        C3delta(2)=1.071
        pf1delta(1)=0.752
        pf1delta(2)=0.813
        pf2delta(1)=0.752
        pf2delta(2)=0.813
        thickdelta(1)=2.45
        thickdelta(2)=2.75
        FWHMdelta(1)=12.5
        FWHMdelta(2)=14.86
        Ethrdelta(1)=26.7
        Ethrdelta(2)=28.97


        OPEN( UNIT=99,FILE=
     &'./param/parameters')
        READ(99,*,END=300),(stuff(i),i=1,4)
        READ(99,*,END=300),(p(i),i=1,7)
        READ(99,*,END=300),(stuff(i),i=1,8)
        l=1
        do while (.true.)
            READ(99,*,END=300),ionr(l), (pr(l,i),i=1,7)
c            write(*,*) (stuff(i),i=1,5)
c            write(*,*) (pr(l,i),i=1,7)
c            write(*,*) ionr(l)
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
                  qvz="./lars/efferr/"

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

                  write(*,*) qvze,qvzf,qvzeff, qvzet
                  open (unit=1, file= qvze)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,0.11,
     .                           pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.)
                    write(1,*) eqstep(k), emeas, 
     .                         ((echannelfloat+1.5)/2.)/1.137
                  end do  
                  close(unit=1)

                  open (unit=2, file= qvzf)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,0.11,
     .                           pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.)
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

                  open (unit=3, file= qvzeff)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    if (eperm*mion .le. 1000.) then
                      if (mion .gt. 4) then
                        call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .                           pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.)
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
     .                  yanlis)
                        if ((bw .gt. 1) .or. (bw .lt. 0)) then
                            write(*,*) "EFFICIENCY OUT OF RANGE!!!!"
                            write(*,*) "FOR ", zion
                        end if
                        write(3,*) eqstep(k), bw, yanlis
                      end if
                    else 
                        write(3,*) eqstep(k),0.0
                    end if
                  end do  
                  close(unit=3)

                  open (unit=4, file= qvzet)
                  do k=1,58
                    eperm=((eqstep(k))+lpaps)*lcharge/mion
                    call swxeff(bw,eperm,zion,mion,ion,C1,C2,0.11,
     .                           pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.)
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


c DIFFERENT EXPERIMENTS
      if (run8 .eq. 1) then
        sumint=0.0
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
        FWHMEL=13.9549
        Ethresh=27.38
        defl=0.043
        PROBMODE=2
        do k=1,runner-1
            eperm=(brain(k,13))/(brain(k,1))
c            write(*,*) eperm
c            eperm=((eqstep(k))+lpaps)*lcharge/mion
            call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,defl, 
     .              PROBMODE)
c            write(*,*) eperm, bw, brain(k,16), brain(k,34)
            sumint=sumint+((((bw-brain(k,15))/(brain(k,33)))**2))
        end do
        wssr=sumint
        write(*,*) "WSSR =", sumint
        sumint=sumint/(runner-1-1)
c        write(*,*) eperm,C1,C2,pf1,pf2,thick,FWHMEL,Ethresh,bw
        write(*,*) sumint

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
