        subroutine geomforfit(sigma,defl,resprobst, resprobse)


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
     .      res,
     .      res0,
     .      res1,
     .      resprobst,
     .      resprobse,
     .      aux0,
     .      aux1,
     .      aux2,
     .      aux3,
     .      sigma,
     .      defl

        INTEGER
     .      i,j,k


c        do i=1,961
c            write(*,*) runner, (fitgeom(i,j),j=1,4)
c        end do

        res = 0.
        resprobst=0.
        resprobse=0.
c        write(*,*) "sigma =", sigma
c        write(*,*) "defl =", defl
        i=0
        do while (nint(sigma*1000) .gt. nint(fitgeom(i+1,1)*1000))
            i=i+1
c            write(*,*) "i =", i, nint(fitgeom(i,1)*1000)
        end do
        j=0
        do while (nint(defl*1000) .gt. nint(fitgeom(j+1,2)*1000))
            j=j+1
c            write(*,*) "j =", j, nint(fitgeom(j+1,2)*1000)
        end do
c            write(*,*) "i =",i,"  j =", j
c            write(*,*) sigma, defl

        if (i .eq. 0) then
            i=1
        end if
        if (j .eq. 0) then
            j=31
        end if

        aux1=fitgeom(i+1+j-31,3)
        aux3=fitgeom(i+1+j-31,1)

        aux0=fitgeom(i+j-31,3)
        aux2=fitgeom(i+j-31,1)


c        write(*,*) "aux0 =", aux0
c        write(*,*) "aux1 =", aux1
c        write(*,*) "aux2 =", aux2
c        write(*,*) "aux3 =", aux3

        res0=aux0+(aux1-aux0)/(aux3-aux2)*(sigma-aux2)
c        res0=aux0*exp((sigma-aux2)/(aux3-aux2)*
c     .  (alog(aux1)-alog(aux0)))
c        write(*,*) "res0 =", res0

        aux1=fitgeom(i+j+1,3)
        aux3=fitgeom(i+j+1,1)

        aux0=fitgeom(i+j,3)
        aux2=fitgeom(i+j,1)


c        write(*,*) "aux0 =", aux0
c        write(*,*) "aux1 =", aux1
c        write(*,*) "aux2 =", aux2
c        write(*,*) "aux3 =", aux3

        res1=aux0+(aux1-aux0)/(aux3-aux2)*(sigma-aux2)
c        res1=aux0*exp((sigma-aux2)/(aux3-aux2)*
c     .  (alog(aux1)-alog(aux0)))
c        write(*,*) "res1 =", res1

        aux0=res0
        aux1=res1
        aux3=fitgeom(i+j,2)
        aux2=fitgeom(i+j-31,2)


c            write(*,*) "aux0 =", aux0
c            write(*,*) "aux1 =", aux1
c            write(*,*) "aux2 =", aux2
c            write(*,*) "aux3 =", aux3

        resprobst=aux0+(aux1-aux0)/(aux3-aux2)*(defl-aux2)
c        resprobst=((alog(defl)-alog(aux2))/(alog(aux3)-alog(aux2)))*
c     .      (aux1-aux0) + aux0
c        write(*,*) resprobst

        aux1=fitgeom(i+1+j-31,4)
        aux3=fitgeom(i+1+j-31,1)

        aux0=fitgeom(i+j-31,4)
        aux2=fitgeom(i+j-31,1)


c        write(*,*) "aux0 =", aux0
c        write(*,*) "aux1 =", aux1
c        write(*,*) "aux2 =", aux2
c        write(*,*) "aux3 =", aux3

        res0=aux0+(aux1-aux0)/(aux3-aux2)*(sigma-aux2)
c        res0=aux0*exp((sigma-aux2)/(aux3-aux2)*
c     .  (alog(aux1)-alog(aux0)))
c        write(*,*) "res0 =", res0

        aux1=fitgeom(i+j+1,4)
        aux3=fitgeom(i+j+1,1)

        aux0=fitgeom(i+j,4)
        aux2=fitgeom(i+j,1)


c        write(*,*) "aux0 =", aux0
c        write(*,*) "aux1 =", aux1
c        write(*,*) "aux2 =", aux2
c        write(*,*) "aux3 =", aux3

        res1=aux0+(aux1-aux0)/(aux3-aux2)*(sigma-aux2)
c        res1=aux0*exp((sigma-aux2)/(aux3-aux2)*
c     .  (alog(aux1)-alog(aux0)))
c        write(*,*) "res1 =", res1

        aux0=res0
        aux1=res1
        aux3=fitgeom(i+j,2)
        aux2=fitgeom(i+j-31,2)


c            write(*,*) "aux0 =", aux0
c            write(*,*) "aux1 =", aux1
c            write(*,*) "aux2 =", aux2
c            write(*,*) "aux3 =", aux3

        resprobse=aux0+(aux1-aux0)/(aux3-aux2)*(defl-aux2)
c        resprobst=((alog(defl)-alog(aux2))/(alog(aux3)-alog(aux2)))*
c     .      (aux1-aux0) + aux0
c        write(*,*) resprobst



        RETURN
        END
