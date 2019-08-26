c ***********************************************************************

       SUBROUTINE GEOMETRIESCAN()

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
     .      AUX5,AUX6,AUX7,AUX8,
     .      ASPECT_ANGLE,       ! ASPECT ANGLE
     .      BETA,               ! angle of norm-trajectory w.r.t. xz plane
     .      ENTRY_ANGLE         ! angle of norm-trajectory w.r.t. xy plane

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
     .      EPERMF,
     .      PROBSE,
     .      PROBST,
     .      bwl,bwg,
     .      sigmal,sigmag,
     .      lsigmal,
     .      defl,
     .      step, stepcounter,
     .      auxprobse, auxprobst


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
     .      MACORC /                                      !STOP active areas 
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
     .      STPC /                   !Macor areas
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



c        sigmal=0.01
        sigmag=0.01
        do beta=0.0*0.01745, 0.0*0.01745, 1.*0.01745
c        entry_angle=0.0
        do defl=0.05,0.05,0.01
        if (defl .gt. 0.0) then
            step=defl*0.01
        else 
            step=0.1
        end if
        do lsigmal=0.02,0.02,0.01
            if (lsigmal .eq. 0.0) then
                sigmal=0.0001
            else 
                sigmal=lsigmal
            end if


        auxprobse=0.0
        auxprobst=0.0
        stepcounter=0.0
        do entry_angle=-1.*defl, defl, step
        stepcounter=stepcounter+1

C *** Initialize geometry from entry point
c        ASPANG = 29
c        ASPECT_ANGLE = 1.*ASPANG
c        beta = acos((cos((aspect_angle)*(Pi/180))-.2966)/.7034)-0.6021
c        beta = -24.94*(Pi/180)
c        beta=0.
c        write(*,*) beta/(Pi/180)

c        ENTRY_ANGLE = 1.36                     ! may need to be varied
        v(1) = -cos(beta)*cos(entry_angle)     ! beam norm vector
        v(2) = -sin(beta)
        v(3) = -cos(beta)*sin(entry_angle)
        if (abs(v(3)) .lt. 1e-6) then 
            v(3)=0.0
        end if
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

C *** End of preparations, geometry initialization. ********************
            EPERMF=5.0
            aux1=0.0
            aux2=0.0
            bwg=0.0
            bwl=0.0
            do i=1,3
              call integrationconv(stpi(i,1,1),stpi(i,1,2),stpi(i,1,3),
     .                 stpi(i,2,1),stpi(i,2,2),stpi(i,2,3),
     .                 stpi(i,3,1),stpi(i,3,2),stpi(i,3,3),
     .                 stpi(i,4,1),stpi(i,4,2),stpi(i,4,3),
     .                 c(1),c(2),c(3),v(1),v(2),v(3),
     .                 sigmal,sigmag,0.0,bwl,bwg)
              aux1=aux1+bwg
              aux2=aux2+bwl
            end do


            IF ( EPERMF .LE. 0.5 ) THEN
                PROBSE = AUX1
            ELSE IF ( EPERMF .GE. 1.5 ) THEN
                PROBSE = AUX2
            ELSE
                PROBSE = AUX1**(1.5-EPERMF) * AUX2**(EPERMF-0.5)
            END IF

c*****End of comparing stp-Integration************************************

c*****Start of comparing ssd-Integration**********************************

            aux5=0.0
            aux6=0.0
            aux7=0.0
            bwg=0.0
            bwl=0.0
            do i=1,3
              call integrationconv(ssdi(i,1,1),ssdi(i,1,2),ssdi(i,1,3),
     .                 ssdi(i,2,1),ssdi(i,2,2),ssdi(i,2,3),
     .                 ssdi(i,3,1),ssdi(i,3,2),ssdi(i,3,3),
     .                 ssdi(i,4,1),ssdi(i,4,2),ssdi(i,4,3),
     .                 c(1),c(2),c(3),v(1),v(2),v(3),
     .                 sigmal,sigmag,0.0,bwl,bwg)
              aux5=aux5+bwg
              aux6=aux6+bwl

            end do

            IF ( EPERMF .LE. 0.5 ) THEN
                PROBST = AUX5
            ELSE IF ( EPERMF .GE. 1.5 ) THEN
                PROBST = AUX6
            ELSE
                PROBST = AUX5**(1.5-EPERMF) * AUX6**(EPERMF-0.5)
            END IF


c*****End of comparing ssd-Integration************************************

            if (probst .gt. 1.0) then
                probst=1.0
            end if
            if (probse .gt. 1.0) then
                probse=1.0
            end if 
            write(*,*) entry_angle, probst, probse
c            write(*,*) v(1), v(2), v(3)

            auxprobse=auxprobse+probse
            auxprobst=auxprobst+probst
            end do
            probse=auxprobse/stepcounter
            probst=auxprobst/stepcounter

            if (defl .eq. 0.0) then
                if (sigmal .eq. 0.0001) then
                    write(*,*) "0.0  0.0", probst, probse
                else 
                    write(*,*) sigmal, defl, probst, probse
                end if
            else if  (defl .gt. 0.0) then
                if (sigmal .eq. 0.0001) then
                    write(*,*) "0.0", defl, probst, probse
                else 
                    write(*,*) sigmal,defl, probst, probse
                end if
            end if

        end do !defl
        end do !lsigmal
        end do !beta

        RETURN
        END

