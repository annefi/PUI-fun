c ***********************************************************************

       SUBROUTINE GEOMETRIE()

C ***********************************************************************
C ***
C *** Program adapted from SWICSEFF_NEW.FOR.
C ***
C *** Program adapted from Ruedi v. Steiger's SWICSEF2 program.
C ***
C *** It now includes non-central impact of ions onto SSDs and angular
C *** spread before ions hit C-foil , cf. comments in lab book III, p. 203
C *** angles are measured with respect to the horizontal. 
C ***
C *** I have now added nearly 3D aspects.
C ***
C ***
C ***  Current date: August 8, 1996
C ***
C *** Author: Robert F. Wimmer-Schweingruber


C *** Revisions, Adaptions:
C *** 
C *** - Added nearly three D aspects (May 5, 1995)
C *** - cleaned up a little (Nov 22, 1995)
C *** - Adapted from SWICSEFF_NEW.FOR (Aug 8,1996)

C
C     Calculates trigger probabilities for MCPs and MSSs of SWICS FM90.
C     Several parameters can be adjusted to fit the calibration data
C     taken in Bern in May 1990.
C
C     Written by r.v.steiger, July 29 - August 9, 1990
C

        IMPLICIT NONE

c+++++++Common variables with the geometry part++++++++++++++++++

        COMMON /GEOM/ C,V,VN,DELTAWIN,PHIWIN,DELTASTP,PHISTP,
     .                DELTASSD,PHISSD,DELTAMACOR,PHIMACOR,
     .                BRAIN,SSDC,STPC,MACORC,SSDI,STPI,
     .                COUNTER,WALKER,RUNNER,JUMPER,FITGEOM,
     .                FITGEOMALL,
     .                FITMODE,TARGETSSD,CALDATSSD,GEOMMODE

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
     .      FITGEOM(961,4),
     .      FITGEOMALL(38440,4)


        INTEGER*4 
     .      WALKER,             ! auxiliary loop variables
     .      RUNNER,
     .      JUMPER, 
     .      COUNTER,
     .      FITMODE,            ! 0 = papstoepq für alle gleich , 1 = Jedes Ion einzeln
     .                          ! 2 bis 5 = verschiedene Kombinationen
     .      TARGETSSD,
     .      CALDATSSD,
     .      GEOMMODE

c*******End of common-block /GEOM/*******************************

        COMMON /SETTINGS/ AB_SETTING,
     .                      run0,run1,run2,run3,run4,run5,run6,run7,run8

        INTEGER*4               ! Parameters to start different efficiency modi
     .      AB_SETTING,         ! 0=calculation for a defined beta
                                ! 1=calculation for a defined aspect_angle
     .      run0,               ! paramerror calculation
     .      run1,               ! Test run for the dutycycle function
     .      run2,               ! Read the E/q steps and fitted parameters
     .      run3,               ! Test run for swxeff
     .      run4,               ! Run for all elements in param/parameters
                                ! Error estimation for worst case scenario
     .      run5,               ! Test run for random noise
     .      run6,               ! Run for error estimation (random noise)
     .      run7,               ! Monte Carlo Intergration
     .      run8                ! Different experiments

        REAL*4
     .      a(3,3),             ! midpoints of SSDs   FIRST INDEX: DETECTOR #
     .      n(3,3),             ! normal vectors on SSDs        
     .      vn(3),              ! normal to beam norm vector
     .      iN(3,3),            ! intersection points of beam with SSD planes
     .      COLL(3),            ! intersection of beam and collimator
     .      collax(3),          ! collimator axis norm vector     
     .      c1(3),              ! point on collimator axis
     .      DETCOL(3,4,-33:32), ! "windows" for detector collimator
     .      mdetcol(3,4,-330:329),
     .      colnorm(3,-33:32),  ! normal vector to each of these "windows"
     .      mcolnorm(3,-330:329),
     .      colmid(3,-33:32),   ! center points of window
     .      mcolmid(3,-330:329),
     .      PARASSD, PARASTP,   ! length parameter for SSD and STP
     .      PARAMACOR,          ! length parameter for MACOR-area
     .      PARAWIN,            ! length parameter for WINDOWS
     .      t(3),               ! length parameter along beam vector 
     .      auxv1(3),auxv2(3),  ! auxiliary vectors
     .      auxv3(3),auxv4(3),  ! auxiliary vectors
     .      AUX1,AUX2,AUX3,AUX4,! AUXiliary real variables
     .      ASPECT_ANGLE,       ! ASPECT ANGLE
     .      BETA,               ! angle of norm-trajectory w.r.t. xz plane
     .      THANG,              ! Thermal Mach Angle
     .      ENTRY_ANGLE         ! angle of norm-trajectory w.r.t. xy plane


        CHARACTER*1
     .      XXX,aspect_anglechar1, thangchar1
        CHARACTER*2
     .      YYY,aspect_anglechar2, thangchar2
        CHARACTER*3
     .      ZZZ
        CHARACTER*100
     .      atf                 ! path to file (see code)

c++++ Variablen für meine Integration+++++++++++++++
        REAL*4  
     .      ssds(3,3),          ! Schnittpunkt eines Strahls in der x-y-Ebene ausgehend vom Nullpunkt
                                ! in Richtung Zentrum eines Detektors mit der Detektorebene
                                ! Für SSD2 ist dies ein Strahl mit dem Vektor (-1,0,0)
     .      ssdv(3,4,3),        ! Vektoren, die ssds mir den Eckpunkten der Detektoren verbinden
     .      ssdvb(3,4),         ! Beträge von ssdv-Vektoren
     .      coleck(-290:290,2,3),! Eckpunkte des Collimatorfensters, welches in 581 Unterfenster unterteilt ist
     .      dummyssd(3,4,3),    ! Dummyarray
     .      dummystp(3,4,3),    ! Dummyarray
     .      dummycol(-290:290,4,3),! Dummyarray
     .      mussd(3),           ! auch ein dummy
     .      mustp(3),           ! auch ein dummy
     .      mucol(3),           ! auch ein dummy          
     .      epsilonssd(3,4),    ! Winkel zwischen der Projektion des Strahlvektors auf die z-Ebene
                                ! und der Projektion der Vektoren, die c und die Ecken der Detektoren 
                                ! miteinander verbinden
     .      epsilonstp(3,4),    ! analog zu epsilonssd für die Ecken der stp-Regionen
     .      epsiloncol(-290:290,2),! analog zu epsilonssd für die 57*2 (oben und unten), die das Collimatorfenster definieren
     .      vz(3),              ! Projektion von v auf die z-Ebene
     .      zetassd(3,2),       ! Mittelwert aus epsilonssd(i,1) und epsilonssd(i,4) bzw
                                ! aus epsilonssd(i,2) und epsilonssd(i,3), i=1,2,3 für die Detektoren
     .      zetastp(3,2),       ! analog zetassd für die stp-Flächen
     .      zetacol(-290:290)   ! analog zetassd für die 57*2 (oben und unten) Collimator-begrenzenden Punkte

c*****Ende: Variablen für meine Integration


        REAL*4
     .      PI                  ! just that, pi = 3.14159...


        INTEGER*4
     .      GAMMA,              ! angle for det collim. in xz plane
     .      mgamma,
     .      GAMMAMIN, GAMMAMAX, ! MIN  and MAX angle for det collim. in xz plane
     .      mgammamin,mgammamax,
     .      I,J,K,L,            ! auxiliary loop variables
     .      ASPANG,             ! global loop variable for aspect angles
     .      kappassd(3,2),      
     .      kappastp(3,2)

        INTEGER
     .      CALDATZION                ! nuclear charge of incident ion [e]

        CHARACTER*20
     .      stuff

        DATA
     .      PI/3.1415927/

        DATA
     .      GAMMAMIN /-28/,
     .      GAMMAMAX / 28/


        DATA
     .      mgammamin /-290/,
     .      mgammamax / 289/

        DATA
     .      a  /-36.25,-40.,-36.25,16.90,0.,-16.90,3.37,3.37,3.37/,
     .      N  /-.903,-.997,-.903,.4211,0.,-.4211,.084,.084,.084/

        DATA
     .      C1 /17.,0.,0./,
     .      COLLAX /.02373,0.,.99972/


c Die SSD-Eckdaten für Ulyyses-SWICS sind auskommentiert und durch jene für ACE/SWICS ersetzt.

c       DATA
c     .      SSDC /                     !TCR active areas
c     .       -39.10,-40.10,-33.60,     !x-component of corner 1 for det 1,2,3
c     .       -33.60,-40.10,-39.10,     !x-component of corner 2 for det 1,2,3  
c     .       -33.34,-39.83,-39.10,     !x-component of corner 3 for det 1,2,3  
c     .       -38.83,-39.83,-33.60,     !x-component of corner 4 for det 1,2,3  
c     .        11.01,- 6.50,-22.80,     !y-component of corner 1 for det 1,2,3
c     .        22.80,  6.50,-11.01,     !y-component of corner 2 for det 1,2,3  
c     .        22.80,  6.50,-11.01,     !y-component of corner 3 for det 1,2,3  
c     .        11.01,- 6.50,-22.80,     !y-component of corner 4 for det 1,2,3  
c     .       - 3.57,- 3.55,- 3.70,     !z-component of corner 1 for det 1,2,3  
c     .       - 3.70,- 3.55,- 3.57,     !z-component of corner 2 for det 1,2,3  
c     .         7.29,  7.45,  7.42,     !z-component of corner 3 for det 1,2,3  
c     .         7.42,  7.45,  7.29/     !z-component of corner 4 for det 1,2,3  

        DATA
     .      SSDC /                     !TCR active areas
     .       -39.27,-40.11,-33.44,     !x-component of corner 1 for det 1,2,3
     .       -33.44,-40.11,-39.27,     !x-component of corner 2 for det 1,2,3  
     .       -33.16,-39.82,-38.99,     !x-component of corner 3 for det 1,2,3  
     .       -38.99,-39.82,-33.16,     !x-component of corner 4 for det 1,2,3  
     .        10.65,- 6.90,-23.16,     !y-component of corner 1 for det 1,2,3
     .        23.16,  6.90,-10.65,     !y-component of corner 2 for det 1,2,3  
     .        23.16,  6.90,-10.65,     !y-component of corner 3 for det 1,2,3  
     .        10.65,- 6.90,-23.16,     !y-component of corner 4 for det 1,2,3  
     .       - 4.02,- 4.00,- 4.16,     !z-component of corner 1 for det 1,2,3  
     .       - 4.16,- 4.00,- 4.02,     !z-component of corner 2 for det 1,2,3  
     .         7.74,  7.90,  7.88,     !z-component of corner 3 for det 1,2,3  
     .         7.88,  7.90,  7.74/     !z-component of corner 4 for det 1,2,3 

        DATA
     .      STPC /                                      !STOP active areas 
     .      -39.7159119, -40.1343651, -33.0411339,      !x-component of corner 1 for det 1,2,3
     .      -33.0411339, -40.1343651, -39.7159119,      !x-component of corner 2 for det 1,2,3  
     .      -32.7140884, -39.7956352, -39.3888664,      !x-component of corner 3 for det 1,2,3  
     .      -39.3888664, -39.7956352, -32.7140884,      !x-component of corner 4 for det 1,2,3 
     .        9.7436409,  -7.9000001, -24.0663586,      !y-component of corner 1 for det 1,2,3
     .       24.0663586,   7.9000001,  -9.7436409,      !y-component of corner 2 for det 1,2,3
     .       24.0663586,   7.9000001,  -9.7436409,      !y-component of corner 3 for det 1,2,3  
     .        9.7436409,  -7.9000001, -24.0663586,      !y-component of corner 4 for det 1,2,3  
     .       -5.00958014, -4.99970341, -5.16986656,     !z-component of corner 1 for det 1,2,3 
     .       -5.16986656, -4.99970341, -5.00958014,     !z-component of corner 2 for det 1,2,3 
     .        8.72957993,  8.89970303,  8.88986683,     !z-component of corner 3 for det 1,2,3 
     .        8.88986683,  8.89970303,  8.72957993/     !z-component of corner 4 for det 1,2,3 

        DATA
     .      MACORC /                   !Macor areas
     .       -39.39,-39.41,-32.07,     !x-component of corner 1 for det 1,2,3
     .       -32.07,-39.41,-39.39,     !x-component of corner 2 for det 1,2,3  
     .       -31.75,-39.09,-39.07,     !x-component of corner 3 for det 1,2,3  
     .       -39.07,-39.09,-31.75,     !x-component of corner 4 for det 1,2,3  
     .         8.66,- 8.66,-24.45,     !y-component of corner 1 for det 1,2,3
     .        24.45,  8.66,- 8.66,     !y-component of corner 2 for det 1,2,3  
     .        24.45,  8.66,- 8.66,     !y-component of corner 3 for det 1,2,3  
     .         8.66,- 8.66,-24.45,     !y-component of corner 4 for det 1,2,3  
     .       - 4.71,- 4.71,- 4.88,     !z-component of corner 1 for det 1,2,3  
     .       - 4.88,- 4.71,- 4.71,     !z-component of corner 2 for det 1,2,3  
     .         8.66,  8.83,  8.83,     !z-component of corner 3 for det 1,2,3  
     .         8.83,  8.83,  8.66/     !z-component of corner 4 for det 1,2,3 


c++++ Nach Rücksprache mit Robert (23.03.2006) habe ich neue Eckpunkte++++++++ 
c     für die SSD-Flächen bekommen.
c     Die neuen STP-Flächen sind nun dadurch gegeben, dass die 
c     Kanten der SSD-Flächen um "einen" Millimeter nach aussen verschoben werden.
c     Die Übergangsflächen bestehen aus Macor. 
c     Die Berechnung der neuen STP-Flächen erfolgte mit folgender Rechenvorschrift. 

c        do k=1,3
c            call vap(ssdc(k,1,1),ssdc(k,1,2),ssdc(k,1,3),
c     .             ssdc(k,4,1),ssdc(k,4,2),ssdc(k,4,3),
c     .             ssdc(k,2,1),ssdc(k,3,2),ssdc(k,2,3),
c     .             stpc(k,1,1),stpc(k,1,2),stpc(k,1,3))
c
c            call vap(ssdc(k,2,1),ssdc(k,2,2),ssdc(k,2,3),
c     .             ssdc(k,1,1),ssdc(k,1,2),ssdc(k,1,3),
c     .             ssdc(k,3,1),ssdc(k,3,2),ssdc(k,3,3),
c     .             stpc(k,2,1),stpc(k,2,2),stpc(k,2,3))
c
c            call vap(ssdc(k,3,1),ssdc(k,3,2),ssdc(k,3,3),
c     .             ssdc(k,2,1),ssdc(k,2,2),ssdc(k,2,3),
c     .             ssdc(k,4,1),ssdc(k,4,2),ssdc(k,4,3),
c     .             stpc(k,3,1),stpc(k,3,2),stpc(k,3,3))
c
c            call vap(ssdc(k,4,1),ssdc(k,4,2),ssdc(k,4,3),
c     .             ssdc(k,3,1),ssdc(k,3,2),ssdc(k,3,3),
c     .             ssdc(k,1,1),ssdc(k,1,2),ssdc(k,1,3),
c     .             stpc(k,4,1),stpc(k,4,2),stpc(k,4,3))
c        end do
c
c        do i=1,3
c           do j=1,4
c               write(*,*) (stpc(k,j,i),k=1,3)
c           end do
c        end do
c+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

c++++++ Hier begint das Einlesen den Kalibraionsdaten. ++++++++++


        walker=1
        runner=1
        jumper=1
        counter=0

c        FITMODE=1
c        GEOMMODE=2
c        targetssd=2
c        caldatssd=2
c        caldatzion=8
        OPEN( UNIT=9,FILE='runconfig.dat')
        READ(9,*,END=40),stuff, FITMODE
        READ(9,*,END=40),stuff, GEOMMODE
        READ(9,*,END=40),stuff, targetssd
        READ(9,*,END=40),stuff, caldatssd
        READ(9,*,END=40),stuff, caldatzion
        READ(9,*,END=40),stuff, AB_SETTING
        READ(9,*,END=40),stuff, ASPECT_ANGLE
        READ(9,*,END=40),stuff, BETA
        READ(9,*,END=40),stuff, THANG
        READ(9,*,END=40),stuff, ENTRY_ANGLE
        READ(9,*,END=40),stuff, run0
        READ(9,*,END=40),stuff, run1
        READ(9,*,END=40),stuff, run2
        READ(9,*,END=40),stuff, run3
        READ(9,*,END=40),stuff, run4
        READ(9,*,END=40),stuff, run5
        READ(9,*,END=40),stuff, run6
        READ(9,*,END=40),stuff, run7
        READ(9,*,END=40),stuff, run8
40      continue
        CLOSE( UNIT=9 )
c        write(*,*) FITMODE,GEOMMODE,targetssd,AB_SETTING,
c     .                    caldatssd,caldatzion,ASPECT_ANGLE,ENTRY_ANGLE,
c     .                    run1,run2,run3,run4,run5,run6,run7,run8
        if (AB_SETTING .eq. 0) then
            OPEN( UNIT=10, FILE='./fitgeom/fitgeomall.dat')
            do i=1,38440 
                READ(10,*,END=45),(fitgeomall(i,j),j=1,4)
c                write(*,*) i, (fitgeomall(i,j),j=1,4)
            end do

            do i =1,961
                do j =1,4
                    fitgeom(i,j)=fitgeomall((i+961*nint(beta)),j)
c                    write(*,*) "fitgeom =", fitgeom(i,j)
                end do
            end do
        else if (AB_SETTING .eq. 1) then
            if (nint(aspect_angle) .le. 9) then
                call ftos(nint(aspect_angle),
     .              aspect_anglechar1,YYY,ZZZ,1)
            else if (nint(aspect_angle) .ge. 10) then
                call ftos(nint(aspect_angle),XXX,
     .              aspect_anglechar2,ZZZ,2)
            end if
            if (nint(thang) .le. 9) then
                call ftos(nint(thang),thangchar1,YYY,ZZZ,1)
            else if (nint(thang) .ge. 10) then
                call ftos(nint(thang),XXX,thangchar2,ZZZ,2)
            end if
            if (nint(aspect_angle) .le. 9) then
                if (nint(thang) .le. 9) then
                    atf="aspang_"//aspect_anglechar1//
     .              "_thang_"//thangchar1
                else if (nint(thang) .ge. 10) then
                    atf="aspang_"//aspect_anglechar1//
     .              "_thang_"//thangchar2
                end if
            else if (nint(aspect_angle) .ge. 10) then
                if (nint(thang) .le. 9) then
                    atf="aspang_"//aspect_anglechar2//
     .              "_thang_"//thangchar1
                else if (nint(thang) .ge. 10) then
                    atf="aspang_"//aspect_anglechar2//
     .              "_thang_"//thangchar2
                end if
            end if
            write(*,*) atf
            OPEN( UNIT=10, FILE='aspang_thang/'//atf)
            do i=1,961
                READ(10,*,END=45),(fitgeom(i,j),j=1,4)
c                write(*,*) i, (fitgeom(i,j),j=1,4)
            end do
        end if
45      continue
        CLOSE( UNIT=10 )

c        if ((targetssd .eq. 1) .or. (targetssd .eq. 3))then
c            OPEN( UNIT=11,FILE='./fitgeom/'//
c     .      'ea0/macor/fitgeomssd13.dat')
c            do i=1,961
c                READ(11,*,END=50),(fitgeom(i,j),j=1,4)
cc                write(*,*) i, (fitgeom(i,j),j=1,4)
c            end do
c50          continue
c            CLOSE( UNIT=11 )
c        else if (targetssd .eq. 2) then
c            OPEN( UNIT=12,FILE='./fitgeom/'//
c     .      'ea0/macor/fitgeomssd2.dat')
cc            OPEN( UNIT=12,FILE='./fitgeom/'//
cc     .      'test3')
c
c            do i=1,961
c                READ(12,*,END=60),(fitgeom(i,j),j=1,4)
cc                write(*,*) i, (fitgeom(i,j),j=1,4)
c            end do
c60          continue
c            CLOSE( UNIT=12 )
c        end if 

        if (fitmode .eq. 1) then
          if (caldatssd .eq. 2) then

c HYDROGEN (SSD2) 
            if (CALDATZION .eq. 1) then    
                OPEN( UNIT=1,FILE='./caldat/h2.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34)
                end do
            end if


c OXYGEN (SSD2)
            if (CALDATZION .eq. 8) then  
                OPEN( UNIT=1,FILE='./caldat/o2_o_con.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if

 
c NEON (SSD2)
            if (CALDATZION .eq. 10) then 
                OPEN( UNIT=1,FILE='./caldat/ne2.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do	 
            end if
             

c MAGNESIUM (SSD2)
            if (CALDATZION .eq. 12) then
                OPEN( UNIT=1,FILE='./caldat/mg2.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if

 
c SILICON (SSD2)
            if (CALDATZION .eq. 14) then
                OPEN( UNIT=1,FILE='./caldat/si2.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if


c IRON (SSD2)
            if (CALDATZION .eq. 26) then
                OPEN( UNIT=1,FILE='./caldat/fe2_o_con.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if

          end if



          if (caldatssd .eq. 3) then	

c OXYGEN (SSD3)
            if (CALDATZION .eq. 8) then
                OPEN( UNIT=1,FILE='./caldat/o3.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if


c NEON (SSD3) 
            if (CALDATZION .eq. 10) then 
                OPEN( UNIT=1,FILE='./caldat/ne3.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if
 
 
c SULFUR (SSD3)
            if (CALDATZION .eq. 16) then
                OPEN( UNIT=1,FILE='./caldat/s3.txt')
                do runner=1,100
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34) 
                end do
            end if
          end if
        end if


        if (fitmode .eq. 2) then
           OPEN( UNIT=1,FILE='./caldat/ssd2_all.f')
                do runner=1,310
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34)
                end do 
        end if

        if (fitmode .eq. 3) then
           OPEN( UNIT=1,FILE='./caldat/o_fe_o_con.f')
                do runner=1,310
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34)
                end do 
        end if

        if (fitmode .eq. 4) then
           OPEN( UNIT=1,FILE='./caldat/o_mg.f')
                do runner=1,310
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34)
                end do 
        end if

        if (fitmode .eq. 5) then
           OPEN( UNIT=1,FILE='./caldat/o_ne.f')
                do runner=1,310
                    READ(1,*,END=100),(brain(runner,walker),walker=1,34)
c                    write(*,*) (brain(runner,walker),walker=1,34)
                end do 
        end if


100     continue
        CLOSE( UNIT=1 )

c++++++ Hier ist das Einlesen der Kalibrationsdaten beendet. +++

C *** Initialize geometry from entry point
c        ASPANG = 29
c        ASPECT_ANGLE = 1.*ASPANG
c        beta = acos((cos((aspect_angle)*(Pi/180))-.2966)/.7034)-0.6021
c        beta = -24.94*(Pi/180)
c        beta=0.
c        write(*,*) beta/(Pi/180)

c        ENTRY_ANGLE = 1.36                     ! may need to be varied
        beta=beta*0.01745
        entry_angle = -0.01745*entry_angle
        v(1) = -cos(beta)*cos(entry_angle)     ! beam norm vector
        v(2) = -sin(beta)
        v(3) = -cos(beta)*sin(entry_angle)
        vn(1) = -v(2)/sqrt(v(1)**2+v(2)**2)    ! normal to beam norm vector
        vn(2) = v(1)/sqrt(v(1)**2+v(2)**2) 
        vn(3) = 0.
        call vecput(v,auxv1)
        call vecput(vn,auxv2)
        CALL VCROSS(auxv1,auxv2,vn)            ! normal to plane containing 
                                               ! beam and tangent to C-foil

        c(1) = 60.*cos(beta)                   ! entry point in C-foil
        c(2) = 60.*sin(beta)                   ! modify if trajectory modelling 
        c(3) = 0.0                             ! shows c(3) <> 0 !!!!!

c        write(*,*) (c(i),i=1,3)
c        write(*,*) (v(i),i=1,3)


C *** compute corners of detector collimator "windows" as well as
C *** normal vectors to the approximating planes.

        DO GAMMA = GAMMAMIN,GAMMAMAX
            DETCOL(1,1,GAMMA) = -(45.*COS(PI/180*GAMMA)-17.)*0.99972
     .                          -0.08378 
            DETCOL(2,1,GAMMA) = 45.*SIN(PI/180*GAMMA)
            DETCOL(3,1,GAMMA) = (45.*COS(PI/180*GAMMA)-17.)*0.02373
     .                          -3.53
            DETCOL(1,2,GAMMA) = -(45.*COS(PI/180*(GAMMA+1.))-17.)
     .                          *0.99972-0.08378
            DETCOL(2,2,GAMMA) = 45.*SIN(PI/180*(GAMMA+1.))
            DETCOL(3,2,GAMMA) = (45.*COS(PI/180*(GAMMA+1.))-17.)
     .                          *0.02373-3.53
            DETCOL(1,3,GAMMA) = -(45.*COS(PI/180*(GAMMA+1.))-17.)
     .                          *0.99972+0.125
            DETCOL(2,3,GAMMA) = 45.*SIN(PI/180*(GAMMA+1.))
            DETCOL(3,3,GAMMA) = (45.*COS(PI/180*(GAMMA+1.))-17.)
     .                          *0.02373+5.28
            DETCOL(1,4,GAMMA) = -(45.*COS(PI/180*GAMMA)-17.)
     .                          *0.99972+0.125
            DETCOL(2,4,GAMMA) = 45.*SIN(PI/180*GAMMA)
            DETCOL(3,4,GAMMA) = (45.*COS(PI/180*GAMMA)-17.)
     .                          *0.02373+5.28

            COLNORM(1,GAMMA) = -COS(PI/180*GAMMA+0.5)*0.99972
            COLNORM(2,GAMMA) =  SIN(PI/180*GAMMA+0.5) 
            COLNORM(3,GAMMA) =  COS(PI/180*GAMMA+0.5)*0.02373

            COLMID(1,GAMMA) = -(45.*COS(PI/180*GAMMA+0.5)-17.)
     .                          *0.99972+0.02077
            COLMID(2,GAMMA) = 45.*SIN(PI/180*GAMMA+0.5)
            COLMID(3,GAMMA) = (45.*COS(PI/180*GAMMA+0.5)-17.)
     .                         *0.02373+0.87475

        END DO

c        DO GAMMA = GAMMAMIN,GAMMAMAX   
c            do i=1,3
c                write(*,*) colnorm(i,gamma)
c                write(*,*) colmid(i,gamma)
c                do j=1,4
c                    write(*,*) detcol(i,j,gamma)
c                end do
c            end do
c        END DO


C *** compute intersection of beam with collimator cylinder surface

        CALL SCALPR(COLLAX,V,AUX1)
        CALL VECMUL(COLLAX,AUX1,AUXV1)
        CALL VECSUB(V,AUXV1,AUXV1)
        CALL VECSUB(C,C1,AUXV2)
        CALL SCALPR(COLLAX,AUXV2,AUX2)
        CALL VECMUL(COLLAX,AUX2,AUXV2)
        CALL VECSUB(C,C1,AUXV3)
        CALL VECSUB(AUXV3,AUXV2,AUXV2)      
        CALL SCALPR(AUXV1,AUXV2,AUX1)
        CALL SCALPR(AUXV1,AUXV1,AUX2)
        CALL SCALPR(AUXV2,AUXV2,AUX3)
        AUX4 = (-AUX1 + SQRT(AUX1**2-AUX2**2*(AUX3-2025.)))/(AUX2)
        AUX3 = (-AUX1 - SQRT(AUX1**2-AUX2**2*(AUX3-2025.)))/(AUX2)
        AUX1 = MAX(AUX3,AUX4)
        DO I = 1,3
            COLL(I) = C(I) + AUX1*V(I)
        END DO

c        DO I = 1,3
c            write(*,*) COLL(I)
c        END DO

C *** compute intersection points of beam with each detector plane

        DO I = 1,3         !loop over all detectors
            call vector(auxv1,a,I)
            call vector(auxv2,n,I)
            call vecput(c,auxv3)
            call vecsub(auxv1,auxv3,auxv1)
            call scalpr(AUXV2,auxv1,aux1)
            call scalpr(AUXV2,v,aux2)
            t(I) = aux1/aux2
            DO J = 1,3
                IN(I,J) = T(I)*V(J) + auxv3(j)
c                write(*,*) IN(I,J)
            END DO
        END DO

C *** now find viewing angles of active areas


        DO I = 1,3
            DO J = 1,2
             ! begin with MACOR horizontal angles
                CALL VECTORS(AUXV1,AUXV2,MACORC,I,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARAMACOR = - AUX1/AUX2
                CALL VECTORS(AUXV1,AUXV2,MACORC,I,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL VECMUL(AUXV2,PARAMACOR,AUXV2)
                CALL VECADD(AUXV1,AUXV2,AUXV1)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(AUXV1,AUXV1,AUX1)
                CALL SCALPR(AUXV1,V,AUX2)
                DELTAMACOR(I,J) = ACOS(AUX2/SQRT(AUX1))
                IF (MACORC(I,J,2) .LT. IN(I,2))
     .              DELTAMACOR(I,J) = - DELTAMACOR(I,J)   
             ! begin with STP horizontal angles
                CALL VECTORS(AUXV1,AUXV2,STPC,I,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARASTP = - AUX1/AUX2
                CALL VECTORS(AUXV1,AUXV2,STPC,I,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL VECMUL(AUXV2,PARASTP,AUXV2)
                CALL VECADD(AUXV1,AUXV2,AUXV1)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(AUXV1,AUXV1,AUX1)
                CALL SCALPR(AUXV1,V,AUX2)
                DELTASTP(I,J) = ACOS(AUX2/SQRT(AUX1))
                IF (STPC(I,J,2) .LT. IN(I,2)) 
     .              DELTASTP(I,J) = - DELTASTP(I,J)   
               ! begin with SSD horizontal angles
                CALL VECTORS(AUXV1,AUXV2,SSDC,I,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARASSD = - AUX1/AUX2
                CALL VECTORS(AUXV1,AUXV2,SSDC,I,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL VECMUL(AUXV2,PARASSD,AUXV2)
                CALL VECADD(AUXV1,AUXV2,AUXV1)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(AUXV1,AUXV1,AUX1)
                CALL SCALPR(AUXV1,V,AUX2)
                DELTASSD(I,J) = ACOS(AUX2/SQRT(AUX1))
                IF (SSDC(I,J,2) .LT. IN(I,2)) 
     .           DELTASSD(I,J) = - DELTASSD(I,J)  

             ! begin with MACOR vertical angles
                CALL VECTORS(AUXV1,AUXV2,MACORC,I,1,4)
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECTOR(AUXV1,A,I)                !vector to midpoint of detector
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARAMACOR = - AUX1/AUX2
                CALL VECTORS(AUXV1,AUXV2,MACORC,I,1,4) !load corners 1 and 4
                CALL VECSUB(AUXV2,AUXV1,AUXV2)        !vector from 1 to 4
                CALL VECTOR(AUXV1,A,I)                !vector to midpoint of detector
                CALL VECMUL(AUXV2,PARAMACOR,AUXV3)      !
                CALL VECADD(AUXV1,AUXV3,AUXV3)        !add
                CALL VECSUB(AUXV3,C,AUXV4)            !vector from C to here
                CALL VECMUL(AUXV2,(-1.)**J*0.5,AUXV2)
                CALL VECADD(AUXV2,AUXV1,AUXV2)
                CALL VECSUB(AUXV2,C,AUXV2)            !vector from C to here
                CALL SCALPR(AUXV4,AUXV4,AUX1)
                CALL SCALPR(AUXV2,AUXV2,AUX2)
                CALL SCALPR(AUXV4,AUXV2,AUX3)
                PHIMACOR(I,J) = ACOS(AUX3/SQRT(AUX1*AUX2))
                IF (MACORC(I,1+J,3) .LT. auxv3(3))
     .              PHIMACOR(I,J) = - PHIMACOR(I,J)  
             ! begin with STP vertical angles
                CALL VECTORS(AUXV1,AUXV2,STPC,I,1,4)
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECTOR(AUXV1,A,I)                !vector to midpoint of detector
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARASTP = - AUX1/AUX2
                CALL VECTORS(AUXV1,AUXV2,STPC,I,1,4) !load corners 1 and 4
                CALL VECSUB(AUXV2,AUXV1,AUXV2)        !vector from 1 to 4
                CALL VECTOR(AUXV1,A,I)                !vector to midpoint of detector
                CALL VECMUL(AUXV2,PARASTP,AUXV3)      !
                CALL VECADD(AUXV1,AUXV3,AUXV3)        !add
                CALL VECSUB(AUXV3,C,AUXV4)            !vector from C to here
                CALL VECMUL(AUXV2,(-1.)**J*0.5,AUXV2)
                CALL VECADD(AUXV2,AUXV1,AUXV2)
                CALL VECSUB(AUXV2,C,AUXV2)            !vector from C to here
                CALL SCALPR(AUXV4,AUXV4,AUX1)
                CALL SCALPR(AUXV2,AUXV2,AUX2)
                CALL SCALPR(AUXV4,AUXV2,AUX3)
                PHISTP(I,J) = ACOS(AUX3/SQRT(AUX1*AUX2))
                IF (STPC(I,1+J,3) .LT. auxv3(3)) 
     .              PHISTP(I,J) = - PHISTP(I,J)  
                  ! begin with SSD vertical angles
                CALL VECTORS(AUXV1,AUXV2,SSDC,I,1,4)
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECTOR(AUXV1,A,I)                !vector to midpoint of detector
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARASSD = - AUX1/AUX2
                CALL VECTORS(AUXV1,AUXV2,SSDC,I,1,4) !load corners 1 and 4
                CALL VECSUB(AUXV2,AUXV1,AUXV2)        !vector from 1 to 4
                CALL VECTOR(AUXV1,A,I)                !vector to midpoint of detector
                CALL VECMUL(AUXV2,PARASSD,AUXV3)      !
                CALL VECADD(AUXV1,AUXV3,AUXV3)        !add
                CALL VECSUB(AUXV3,C,AUXV4)            !vector from C to here
                CALL VECMUL(AUXV2,(-1.)**J*0.5,AUXV2)
                CALL VECADD(AUXV2,AUXV1,AUXV2)
                CALL VECSUB(AUXV2,C,AUXV2)            !vector from C to here
                CALL SCALPR(AUXV4,AUXV4,AUX1)
                CALL SCALPR(AUXV2,AUXV2,AUX2)
                CALL SCALPR(AUXV4,AUXV2,AUX3)
                PHISSD(I,J) = ACOS(AUX3/SQRT(AUX1*AUX2))
                IF (SSDC(I,1+J,3) .LT. AUXV3(3)) 
     .              PHISSD(I,J) = - PHISSD(I,J)  
            END DO
        END DO

c        do i=1,3
c            do j=1,2
c                write(*,*) deltamacor(i,j)
c                write(*,*) deltastp(i,j)
c                write(*,*) deltassd(i,j)
c                write(*,*) phimacor(i,j)
c                write(*,*) phistp(i,j)
c                write(*,*) phissd(i,j)
c            end do
c        end do

C *** Compute viewing angles for all detector collimator windows

        DO GAMMA = GAMMAMIN,GAMMAMAX
            DO J = 1,2
          ! begin with WINDOWS horizontal angles
                CALL WINVECS(AUXV1,AUXV2,DETCOL,GAMMA,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARAWIN = - AUX1/AUX2
                CALL WINVECS(AUXV1,AUXV2,DETCOL,GAMMA,J,(4-J+1))
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL VECMUL(AUXV2,PARAWIN,AUXV2)
                CALL VECADD(AUXV1,AUXV2,AUXV1)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(AUXV1,AUXV1,AUX1)
                CALL SCALPR(AUXV1,V,AUX2)
                DELTAWIN(J,GAMMA) = ACOS(min(1.,AUX2/SQRT(AUX1)))
                IF (detcol(2,J,GAMMA) .LT. COLL(2)) 
     .              DELTAWIN(J,GAMMA) = - DELTAWIN(J,GAMMA)   
           ! begin with WINDOWS vertical angles
                CALL WINVECS(AUXV1,AUXV2,DETCOL,GAMMA,1,4)
                CALL VECSUB(AUXV2,AUXV1,AUXV2)
                CALL SCALPR(VN,AUXV2,AUX2)
                auxv1(1) = colmid(1,gamma)
                auxv1(2) = colmid(2,gamma)
                auxv1(3) = colmid(3,gamma)
                CALL VECSUB(AUXV1,C,AUXV1)
                CALL SCALPR(VN,AUXV1,AUX1)
                PARAWIN =  -AUX1/AUX2
                CALL WINVECS(AUXV1,AUXV2,DETCOL,GAMMA,1,4)
                CALL VECSUB(AUXV2,AUXV1,AUXV2)        !vector from 1 to 4
                auxv1(1) = colmid(1,gamma)
                auxv1(2) = colmid(2,gamma)
                auxv1(3) = colmid(3,gamma)
                CALL VECMUL(AUXV2,PARAWIN,AUXV3)
                CALL VECADD(AUXV1,AUXV3,AUXV3)        !add
                CALL VECSUB(AUXV3,C,AUXV4)            !vector from C to here
                CALL VECMUL(AUXV2,0.5*(-1.)**J,AUXV2)
                CALL VECADD(AUXV2,AUXV1,AUXV2)
                CALL VECSUB(AUXV2,C,AUXV2)            !vector from C to here
                CALL SCALPR(AUXV4,AUXV4,AUX1)
                CALL SCALPR(AUXV2,AUXV2,AUX2)
                CALL SCALPR(AUXV4,AUXV2,AUX3)
                if (aux3/sqrt(aux1*aux2) .gt. 1.) write(*,*) '???????'
                    PHIWIN(J,GAMMA) = ACOS(min(1.,AUX3/SQRT(AUX1*AUX2)))
                IF (DETCOL(3,1+J,GAMMA) .LT. AUXV3(3)) 
     .              PHIWIN(J,GAMMA) = - PHIWIN(J,GAMMA)  
            END DO !(J = 1,2)
        END DO !(GAMMA = GAMMAMIN,GAMMAMAX)

c        do gamma=gammamin,gammamax
c            do j=1,2
c                write(*,*) deltawin(j,gamma)
c                write(*,*) phiwin(j,gamma)
c            end do
c        end do

c************** Ende bisherige Geometrie-Berechnungen *******************

c++++++++++++++ Beginn: Meine Berechnungen ++++++++++++++++++++++++++++++

        DO mgamma = mgammamin,mgammamax
            mdetcol(1,1,mgamma) = -(45.*COS(PI/1800*mgamma)-17.)
     .                          *0.99972-0.08378 
            mdetcol(2,1,mgamma) = 45.*SIN(PI/1800*mgamma)
            mdetcol(3,1,mgamma) = (45.*COS(PI/1800*mgamma)-17.)
     .                          *0.02373-3.53
            mdetcol(1,2,mgamma) = -(45.*COS(PI/1800*(mgamma+1.))-17.)
     .                          *0.99972-0.08378
            mdetcol(2,2,mgamma) = 45.*SIN(PI/1800*(mgamma+1.))
            mdetcol(3,2,mgamma) = (45.*COS(PI/1800*(mgamma+1.))-17.)
     .                          *0.02373-3.53
            mdetcol(1,3,mgamma) = -(45.*COS(PI/1800*(mgamma+1.))-17.)
     .                          *0.99972+0.125
            mdetcol(2,3,mgamma) = 45.*SIN(PI/1800*(mgamma+1.))
            mdetcol(3,3,mgamma) = (45.*COS(PI/1800*(mgamma+1.))-17.)
     .                          *0.02373+5.28
            mdetcol(1,4,mgamma) = -(45.*COS(PI/1800*mgamma)-17.)
     .                          *0.99972+0.125
            mdetcol(2,4,mgamma) = 45.*SIN(PI/1800*mgamma)
            mdetcol(3,4,mgamma) = (45.*COS(PI/1800*mgamma)-17.)
     .                          *0.02373+5.28

            mcolnorm(1,mgamma) = -COS(PI/1800*mgamma+0.5)*0.99972
            mcolnorm(2,mgamma) =  SIN(PI/1800*mgamma+0.5) 
            mcolnorm(3,mgamma) =  COS(PI/1800*mgamma+0.5)*0.02373

            mcolmid(1,mgamma) = -(45.*COS(PI/1800*mgamma+0.5)-17.)
     .                          *0.99972+0.02077
            mcolmid(2,mgamma) = 45.*SIN(PI/1800*mgamma+0.5)
            mcolmid(3,mgamma) = (45.*COS(PI/1800*mgamma+0.5)-17.)
     .                          *0.02373+0.87475

        END DO

c        DO MGAMMA = MGAMMAMIN,MGAMMAMAX   
c            do i=1,3
c                write(*,*) mcolnorm(i,mgamma)
c                write(*,*) mcolmid(i,mgamma)               
c                do j=1,4
c                    write(*,*) mdetcol(i,j,mgamma)
c                end do
c            end do
c        END DO 

c       Berechnung der Winkel zwischen den der Projektion des Beamvektors
c       auf die Z-Ebene und der Projektion der Ecken der SSDs bzw. STPs 
c       auf die Z-Ebene

        vz(1)= v(1)
        vz(2)= v(2)
        vz(3)= 0.0

c        write(*,*) (v(i),i=1,3)      
c        write(*,*) (vz(i),i=1,3)       

        do k=1,3
            do j=1,4
                do i=1,3
                    dummyssd(k,j,i)=ssdc(k,j,i)-c(i)
                    dummystp(k,j,i)=stpc(k,j,i)-c(i)
                end do
            end do
        end do

c        write(*,*) (dummyssd(1,1,i), i=1,3)
c        write(*,*) (dummyssd(1,2,i), i=1,3)
c        write(*,*) (dummyssd(1,3,i), i=1,3)
c        write(*,*) (dummyssd(1,4,i), i=1,3)

c        write(*,*) (dummyssd(2,1,i), i=1,3)
c        write(*,*) (dummyssd(2,2,i), i=1,3)
c        write(*,*) (dummyssd(2,3,i), i=1,3)
c        write(*,*) (dummyssd(2,4,i), i=1,3)

c        write(*,*) (dummyssd(3,1,i), i=1,3)
c        write(*,*) (dummyssd(3,2,i), i=1,3)
c        write(*,*) (dummyssd(3,3,i), i=1,3)
c        write(*,*) (dummyssd(3,4,i), i=1,3)


c        write(*,*) (dummystp(1,1,i), i=1,3)
c        write(*,*) (dummystp(1,2,i), i=1,3)
c        write(*,*) (dummystp(1,3,i), i=1,3)
c        write(*,*) (dummystp(1,4,i), i=1,3)

c        write(*,*) (dummystp(2,1,i), i=1,3)
c        write(*,*) (dummystp(2,2,i), i=1,3)
c        write(*,*) (dummystp(2,3,i), i=1,3)
c        write(*,*) (dummystp(2,4,i), i=1,3)

c        write(*,*) (dummystp(3,1,i), i=1,3)
c        write(*,*) (dummystp(3,2,i), i=1,3)
c        write(*,*) (dummystp(3,3,i), i=1,3)
c        write(*,*) (dummystp(3,4,i), i=1,3)


        do k=1,3
            do j=1,4
                dummyssd(k,j,3)=c(3)
                dummystp(k,j,3)=c(3)
            end do
        end do


        do k=1,3
            do j=1,4
                call winkel(vz(1),vz(2),vz(3),
     .          dummyssd(k,j,1),dummyssd(k,j,2),dummyssd(k,j,3),
     .          epsilonssd(k,j))
                call winkel(vz(1),vz(2),vz(3),
     .          dummystp(k,j,1),dummystp(k,j,2),dummystp(k,j,3),
     .          epsilonstp(k,j))
            end do
        end do

c        write(*,*) (epsilonssd(1,j), j=1,4)
c        write(*,*) (epsilonssd(2,j), j=1,4)
c        write(*,*) (epsilonssd(3,j), j=1,4)

        do k=1,3
            do j=1,4
                do i=1,3
                    mussd(i)=0.0
                    mustp(i)=0.0
                end do             
                call kreuzprodukt(vz(1),vz(2),vz(3),
     .          dummyssd(k,j,1),dummyssd(k,j,2),dummyssd(k,j,3),
     .          mussd(1),mussd(2),mussd(3))
                if (mussd(3) .gt. 0.0) then
                    epsilonssd(k,j)=-epsilonssd(k,j)
                end if
                call kreuzprodukt(vz(1),vz(2),vz(3),
     .          dummystp(k,j,1),dummystp(k,j,2),dummystp(k,j,3),
     .          mustp(1),mustp(2),mustp(3))
                if (mustp(3) .gt. 0.0) then
                    epsilonstp(k,j)=-epsilonstp(k,j)
                end if
            end do
        end do

c        write(*,*) (epsilonssd(1,j), j=1,4)
c        write(*,*) (epsilonssd(2,j), j=1,4)
c        write(*,*) (epsilonssd(3,j), j=1,4)


c        write(*,*) (epsilonstp(1,j), j=1,4)
c        write(*,*) (epsilonstp(2,j), j=1,4)
c        write(*,*) (epsilonstp(3,j), j=1,4)

        do k=1,3
            zetassd(k,1)=(epsilonssd(k,1)+epsilonssd(k,4))/2
            zetassd(k,2)=(epsilonssd(k,2)+epsilonssd(k,3))/2
            zetastp(k,1)=(epsilonstp(k,1)+epsilonstp(k,4))/2
            zetastp(k,2)=(epsilonstp(k,2)+epsilonstp(k,3))/2
        end do

c        write(*,*) (zetassd(1,j), j=1,2)
c        write(*,*) (zetassd(2,j), j=1,2)
c        write(*,*) (zetassd(3,j), j=1,2)

c        write(*,*) (zetastp(1,j), j=1,2)
c        write(*,*) (zetastp(2,j), j=1,2)
c        write(*,*) (zetastp(3,j), j=1,2)

c       Berechnung der Winkel zwischen den der Projektion des Beamvektors
c       auf die Z-Ebene und der Projektion der Ecken der 57*2 Collimator-definierenden Punkte
c       auf die Z-Ebene



c        do k=mgammamin,mgammamax,1
c            write(*,*) k,"  ",(mdetcol(i,1,k), i=1,3)
c            write(*,*) k,"  ",(mdetcol(i,2,k), i=1,3)
c            write(*,*) k,"  ",(mdetcol(i,3,k), i=1,3)
c            write(*,*) k,"  ",(mdetcol(i,4,k), i=1,3)              
c        end do


c      Der Collimator wird unterteilt in 580 Fenster(mdetcol(-290:289), incl.0),
c      welche durch 581*2 Punkte gegeben sind (coleck(-290:290), incl. 0).
c      j=1 ist immer der untere Punkt
c      j=2 ist immer der obere Punkt


        do k=mgammamin,mgammamax,1
            do j=1,2
                do i=1,3
                    if(j .eq. 1) then
                        coleck(k,j,i)=mdetcol(i,j,k)
c                        write(*,*) coleck(k,j,i)
                    else if(j .eq. 2) then
                        coleck(k,j,i)=mdetcol(i,j+2,k)
c                        write(*,*) coleck(k,j,i)
                    end if
                end do
            end do
       end do


        do i=1,3
            coleck((mgammamax+1),1,i)=mdetcol(i,2,mgammamax)
c            write(*,*) coleck((mgammamax+1),1,i)
            coleck((mgammamax+1),2,i)=mdetcol(i,3,mgammamax)
c            write(*,*) coleck((mgammamax+1),2,i)
        end do


c        Berechnung der Vektoren, die c und die Eckpunkte "coleck" verbinden.
        do k=mgammamin,mgammamax,1
            do j=1,2
                do i=1,3
                    if(j .eq. 1) then
                        dummycol(k,j,i)=mdetcol(i,j,k)-c(i)
                    else if(j .eq. 2) then
                        dummycol(k,j,i)=mdetcol(i,j+2,k)-c(i)
                    end if
                end do
            end do
        end do

        do i=1,3
            dummycol((mgammamax+1),1,i)=mdetcol(i,2,mgammamax)-c(i)
            dummycol((mgammamax+1),2,i)=mdetcol(i,3,mgammamax)-c(i)
        end do

c        do k=mgammamin,(mgammamax+1),1
c            write(*,*) k,"  ",(dummycol(k,1,i), i=1,3)
c            write(*,*) k,"  ",(dummycol(k,2,i), i=1,3)
c        end do

        do k=mgammamin,(mgammamax+1),1
            do j=1,2
                dummycol(k,j,3)=c(3)
                dummycol(k,j,3)=c(3)
            end do
        end do


c        do k=mgammamin,(mgammamax+1),1
c            write(*,*) k,"  ",(dummycol(k,1,i), i=1,3)
c            write(*,*) k,"  ",(dummycol(k,2,i), i=1,3)
c        end do

        do k=mgammamin,(mgammamax+1),1
            do j=1,2
                call winkel(vz(1),vz(2),vz(3),
     .          dummycol(k,j,1),dummycol(k,j,2),dummycol(k,j,3),
     .          epsiloncol(k,j))
c                write(*,*) k,"  ",j,"  ", epsiloncol(k,j)
            end do
        end do

        do k=mgammamin,(mgammamax+1),1
            do j=1,2
                do i=1,3
                    mucol(i)=0.0
                end do             
                call kreuzprodukt(vz(1),vz(2),vz(3),
     .          dummycol(k,j,1),dummycol(k,j,2),dummycol(k,j,3),
     .          mucol(1),mucol(2),mucol(3))
                if (mucol(3) .gt. 0.0) then
                    epsiloncol(k,j)=-epsiloncol(k,j)
                end if
            end do
        end do

        do k=mgammamin,(mgammamax+1),1
            zetacol(k)=(epsiloncol(k,1)+epsiloncol(k,2))/2
c            write(*,*) k,"  ",zetacol(k)
        end do

        do j=1,3
            do i=1,2
                kappassd(j,i)=1000
c                write(*,*) kappassd(j,i)
            end do
        end do

        do j=1,3
            do i=1,2
                kappastp(j,i)=1000
c                write(*,*) kappastp(j,i)
            end do
        end do

        do j=1,3
            do i=1,2
                do k=mgammamin,(mgammamax+1),1
                    if (zetacol(k) .lt. zetassd(j,i)) then
                        kappassd(j,i)=k
                    end if
                end do
            end do
        end do

        do j=1,3
            do i=1,2
                do k=mgammamin,(mgammamax+1),1
                    if (zetacol(k) .lt. zetastp(j,i)) then
                        kappastp(j,i)=k
                    end if
                end do
            end do
        end do

        do i=1,2
            do j=1,3
                if(kappassd(j,i) .eq. 1000) then
                    kappassd(j,i)=-290
                end if
                if(kappastp(j,i) .eq. 1000) then
                    kappastp(j,i)=-290
                end if       
            end do
        end do

        do j=1,3
            do i=1,3
                ssdi(j,1,i)=coleck(kappassd(j,1),2,i)
                ssdi(j,2,i)=coleck(kappassd(j,2),2,i)
                ssdi(j,3,i)=coleck(kappassd(j,2),1,i)
                ssdi(j,4,i)=coleck(kappassd(j,1),1,i)
            end do
        end do

        do j=1,3
            do i=1,3
                stpi(j,1,i)=coleck(kappastp(j,1),2,i)
                stpi(j,2,i)=coleck(kappastp(j,2),2,i)
                stpi(j,3,i)=coleck(kappastp(j,2),1,i)
                stpi(j,4,i)=coleck(kappastp(j,1),1,i)
            end do
        end do

c        do j=1,3
c            do k=1,4
c                write(*,*) (stpi(j,k,i),i=1,3)
c                write(*,*) (ssdi(j,k,i),i=1,3)
c            end do
c        end do

c        write(*,*) ((kappassd(j,i),i=1,2),j=1,3)
c        write(*,*) ((kappastp(j,i),i=1,2),j=1,3)

c++++++++++++++ Ende: Meine Berechnungen +++++++++++++++++++++++++++++++      

        RETURN
        END
C *** End of preparations, geometry initialization. ********************




