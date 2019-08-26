        subroutine phd(zion,eperm,res)


c    Calculates the part of the energy that is measured by the SSD


        CHARACTER*100
     .      stuff(20)       ! dummy buffer for unused header information

        REAL*4
     .      brain(22,13),   ! Array for the pulse height defects
     .      eperm,          ! energy per mass of the ion
     .      res,            ! resulting pulse height defect
     .      res0,res1,      ! Auxiliary phds for interpolation
     .      aux1,           ! auxilary variable
     .      zion0,zion1     ! Auxiliary nuclear charges for interpolation

        INTEGER
     .      zion,           ! Nuclear charge of the ion
     .      z,              ! Index for the different elements
                            ! z=3 for protons, z=4 for helium, z=5 for carbon etc.
     .      z0,z1           ! Auxiliary indices for interpolation

        res = 0.
        z = 0
        OPEN( UNIT=10, FILE='./sweff/PIPSDFEC.TXT')
        READ(10,*,END=9999), (stuff(i),i=1,20)
c        write(*,*), (stuff(i),i=1,20)
        do i=1,22
            READ(10,*,END=9999), (brain(i,j),j=1,13)
c            write(*,*), (brain(i,j),j=1,13)
        end do
9999    CONTINUE
        CLOSE( UNIT=10)

        if (zion .eq. 1) z=3
        if (zion .eq. 2) z=4
        if (zion .eq. 6) z=5
        if (zion .eq. 7) z=6
        if (zion .eq. 8) z=7
        if (zion .eq. 10) z=8
        if (zion .eq. 18) z=9
        if (zion .eq. 26) z=10
        if (zion .eq. 36) z=12
        if (zion .eq. 54) z=13

        if (z .gt. 0) then
c       1. Find i with brain(i,1) greater than eperm and 
c           brain(i-1,1) less than eperm.
c       2. Find phd belonging to the eperm through logarithmic interpolation.

            i=1
            do while (eperm .gt. brain(i,1))
                i=i+1
            end do
c            write(*,*) i
c            write(*,*) eperm, zion

            aux1=brain(i,z)
            aux3=brain(i,1)
            if(i .eq. 1) then
                aux0=0.
                aux2=0.
            else
                aux0=brain(i-1,z)
                aux2=brain(i-1,1)
            end if

c            write(*,*) "aux0 =", aux0
c            write(*,*) "aux1 =", aux1
c            write(*,*) "aux2 =", aux2
c            write(*,*) "aux3 =", aux3


c           Logarithmische Interpolation
c           f(x)=ln(x)
            res=((alog(eperm)-alog(aux2))/(alog(aux3)-alog(aux2)))*
     .      (aux1-aux0) + aux0
        end if


        if (z .eq.0) then
            if ((zion .gt. 2) .and. (zion .lt. 6)) then
                z0=4
                z1=5
                zion0=2
                zion1=6
            end if
            if (zion .eq. 9) then
                z0=7
                z1=8
                zion0=8
                zion1=10
            end if
            if ((zion .gt. 10) .and. (zion .lt. 18)) then
                z0=8
                z1=9
                zion0=10
                zion1=18
            end if
            if ((zion .gt. 18) .and. (zion .lt. 26)) then
                z0=9
                z1=10
                zion0=18
                zion1=26
            end if
            if ((zion .gt. 26) .and. (zion .lt. 36)) then
                z0=10
                z1=12
                zion0=26
                zion1=36
            end if
            if ((zion .gt. 36) .and. (zion .lt. 54)) then
                z0=12
                z1=13
                zion0=36
                zion1=54
            end if
            if (zion .gt. 54) then 
                write(*,*) "Nuclear charge of ion too high"
            end if

            i=1
            do while (eperm .gt. brain(i,1))
                i=i+1
            end do
c            write(*,*) i
c            write(*,*) eperm, zion

            aux1=brain(i,z0)
            aux3=brain(i,1)
            if(i .eq. 1) then
                aux0=0.
                aux2=0.
            else
                aux0=brain(i-1,z0)
                aux2=brain(i-1,1)
            end if

c            write(*,*) "aux0 =", aux0
c            write(*,*) "aux1 =", aux1
c            write(*,*) "aux2 =", aux2
c            write(*,*) "aux3 =", aux3


c           Logarithmische Interpolation
c           f(x)=ln(x)
            res0=((alog(eperm)-alog(aux2))/(alog(aux3)-alog(aux2)))*
     .      (aux1-aux0) + aux0

            i=1
            do while (eperm .gt. brain(i,1))
                i=i+1
            end do
c            write(*,*) i
c            write(*,*) eperm, zion

            aux1=brain(i,z1)
            aux3=brain(i,1)
            if(i .eq. 1) then
                aux0=0.
                aux2=0.
            else
                aux0=brain(i-1,z1)
                aux2=brain(i-1,1)
            end if

c            write(*,*) "aux0 =", aux0
c            write(*,*) "aux1 =", aux1
c            write(*,*) "aux2 =", aux2
c            write(*,*) "aux3 =", aux3


c           Logarithmic Interpolation
c           f(x)=ln(x)
            res1=((alog(eperm)-alog(aux2))/(alog(aux3)-alog(aux2)))*
     .      (aux1-aux0) + aux0

c            write(*,*) zion, zion0,zion1, res0,res1


c           Interpolation for the assumption that phd(zion) ~ exp(zion)
            res=res0*exp((float(zion)-zion0)/(zion1-zion0)*
     .      (alog(res1)-alog(res0)))

        end if
c        WRITE(*,*) RES
        RETURN
        END
