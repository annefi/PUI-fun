        subroutine sweffsrim(zion,energy,ssdenergy)
        
c     Calculates the part of the energy that is converted in electron-hole pairs        
      
        real*4
     .      brain(28,3),    ! Array for the pulse height defects
     .      energy,         ! Energy of the ion
     .      ssdenergy,      ! Energy that is converted in electron-hole pairs
     .      aux0,           ! Auxiliary variable
     .      aux1            ! Auxiliary variable
     
        integer*4
     .      i,j,k           ! Auxiliary loop variables
      
        integer
     .      zion            ! Atomic number of the solar-wind ion
     
     
     
c++++ Starting read-in of the phd (pulse height defect) data +++++++++++++++++++++     
           
        if (zion .eq. 1) then
            OPEN( UNIT=10, FILE='./sweff/hydrogen.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if
      
      
        if (zion .eq. 2) then
            OPEN( UNIT=10, FILE='./sweff/helium.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 6) then
            OPEN( UNIT=10, FILE='./sweff/carbon.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if
 
      
        if (zion .eq. 7) then
            OPEN( UNIT=10, FILE='./sweff/nitrogen.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if
     
      
        if (zion .eq. 8) then
            OPEN( UNIT=10, FILE='./sweff/oxygen.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 10) then
            OPEN( UNIT=10, FILE='./sweff/neon.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 12) then
            OPEN( UNIT=10, FILE='./sweff/magnesium.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 13) then
            OPEN( UNIT=10, FILE='./sweff/aluminum.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 14) then
            OPEN( UNIT=10, FILE='./sweff/silicon.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 16) then
            OPEN( UNIT=10, FILE='./sweff/sulfur.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 18) then
            OPEN( UNIT=10, FILE='./sweff/argon.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if

      
        if (zion .eq. 20) then
            OPEN( UNIT=10, FILE='./sweff/calcium.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if
      
            
        if (zion .eq. 26) then
            OPEN( UNIT=10, FILE='./sweff/iron.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if
      
      
        if (zion .eq. 36) then
            OPEN( UNIT=10, FILE='./sweff/krypton.f')
            do i=1,28
                READ(10,*,END=9999), (brain(i,j),j=1,3)
c                write(*,*), (brain(i,j),j=1,3)
            end do
        end if
      
c++++ End of read in ++++++++++++++++++++++++++++++++++++++++++     
      
      
c    1. Find i with brain(i,1) greater than energy "e" and 
c       brain(i-1,1) less than energy "e".
c    2. Find phd belonging to the energy "e" through linear interpolation.
      
        i=1
        do while (energy .gt. brain(i,1))
            i=i+1
        end do
      
        aux1=brain(i,2)+brain(i,3)
      
        if(i .eq. 1) then
            ssdenergy=(aux1)/(brain(i,1))
     .      *(energy)
        RETURN
        else
            aux0=brain(i-1,2)+brain(i-1,3)
        end if
      
        ssdenergy=aux0+(aux1-aux0)/(brain(i,1)-brain(i-1,1))
     .  *(energy-brain(i-1,1))
     
9999  CONTINUE
      CLOSE( UNIT=10 )
      
      RETURN
      END
