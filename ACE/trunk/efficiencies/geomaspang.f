        subroutine geomaspang(aspang,sigmal,defl,probse,probst)


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
     .      VN(3),              ! normal to norm beam vector
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
     .      FITMODE,
     .      TARGETSSD,
     .      CALDATSSD,
     .      GEOMMODE


        REAL*4 
     .      aspang,
     .      beta,
     .      beta2,
     .      defl,
     .      sigmal,
     .      auxprobst1,
     .      auxprobst2,
     .      auxprobse1,
     .      auxprobse2,
     .      probse,
     .      probst
c            write(*,*) "aspang =", aspang
            beta = (acos((cos((aspang)
     .              *(3.1415927/180.))-.2966)/.7034)-0.6021)
     .              /(3.1415927/180.)
            beta=abs(beta)
c            write(*,*) "beta =", beta
            call geombeta(float(int(beta)),sigmal,defl,
     .                      auxprobst1,auxprobse1)
c            write(*,*) auxprobst1, auxprobse1
            call geombeta(float(int(beta+1)),sigmal,defl,
     .                      auxprobst2,auxprobse2)
c            write(*,*) auxprobst2, auxprobse2
            probse=auxprobse1+(auxprobse2-auxprobse1)
     .                      *(beta-float(int(beta)))
            probst=auxprobst1+(auxprobst2-auxprobst1)
     .                      *(beta-float(int(beta)))
            beta2 = (acos((cos((aspang)
     .              *(3.1415927/180.))-.2966)/.7034)-0.6021)
            beta2=abs(beta2)
            if (((beta2.lt.0.5/60.)) .or.
     .      ((beta2.gt.11./60.).and.(beta2.lt.12./60.)).or.
     .      ((beta2.gt.24./60.).and.(beta2.lt.25./60.)).or.
     .      ((beta2.gt.38.8/60.))) then
                probse=0.0
                probst=0.0
            end if


        RETURN
        END
