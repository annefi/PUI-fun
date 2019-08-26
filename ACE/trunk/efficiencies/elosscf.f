      subroutine elosscf(zion,mion,energy,thick,step,eresdl)

c    Calculates the residual energy "eresdl" of an ion with atomic number "zion" passing a carbonfoil
c    with thickness "thick" given in Angström. The initial energy must be given in keV.
c    "step" is the integration step (step=1 means 1-Angström-steps in integration).            
      real*4
     . brain(100,6),     ! Array for the carbonfoil dE/dx data
     . sum(100),         ! Array for the sum of electronic and nuclear stopping
     . energy,           ! Energy of the ion before reaching the carbonfoil
     . e,                ! Auxiliary variable for the energy
     . thick,            ! Thickness of the carbonfoil
     . t,                ! Auxiliary variable for the thickness of the carbonfoil
     . eresdl,           ! Residual energy after the carbonfoil
     . aux0,             ! Auxilary variable
     . aux1,             ! Auxilary variable
     . step,             ! Integration step given in Angström
     . mion              ! Mass of the solar wind ion in amu
          
      integer*4
     . i,j,k             ! Auxiliary loop variables
     
      integer
     . zion              ! Atomic number of the solar-wind ion
      
      
c++++ Starting read-in of the dE/dx data +++++++++++++++++++++     
           
        if (zion .eq. 1) then
            OPEN( UNIT=10, FILE='./carbonfoil/hydrogencf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
      
        if (zion .eq. 2) then
            if (nint(mion) .eq. 4) then
                OPEN( UNIT=10, FILE='./carbonfoil/heliumcf.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            else if (nint(mion) .eq. 3) then
                OPEN( UNIT=10, FILE='./carbonfoil/3heliumcf.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            end if
        end if

      
        if (zion .eq. 6) then
            if (nint(mion).eq.12) then
                OPEN( UNIT=10, FILE='./carbonfoil/carboncf.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            else if (nint(mion).eq.13) then
                OPEN( UNIT=10, FILE='./carbonfoil/13carboncf.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            end if
        end if
 
      
        if (zion .eq. 7) then
            OPEN( UNIT=10, FILE='./carbonfoil/nitrogencf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
     
      
        if (zion .eq. 8) then
            OPEN( UNIT=10, FILE='./carbonfoil/oxygencf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 10) then
            OPEN( UNIT=10, FILE='./carbonfoil/neoncf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 12) then
            OPEN( UNIT=10, FILE='./carbonfoil/magnesiumcf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 13) then
            OPEN( UNIT=10, FILE='./carbonfoil/aluminumcf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 14) then
            OPEN( UNIT=10, FILE='./carbonfoil/siliconcf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 16) then
            OPEN( UNIT=10, FILE='./carbonfoil/sulfurcf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 18) then
            OPEN( UNIT=10, FILE='./carbonfoil/argoncf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 20) then
            OPEN( UNIT=10, FILE='./carbonfoil/calciumcf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
            
        if (zion .eq. 26) then
            OPEN( UNIT=10, FILE='./carbonfoil/ironcf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
      
        if (zion .eq. 36) then
            OPEN( UNIT=10, FILE='./carbonfoil/kryptoncf.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
c++++ End of read in ++++++++++++++++++++++++++++++++++++++++++     
      
      

      
        do i=1,79
            sum(i)=brain(i,2)+brain(i,3)
c            write(*,*) sum(i)
        end do
      
        e=energy
        t=thick
c        write(*,*) energy, thick

c    1. Find i with brain(i,1) greater than energy "e" and 
c       brain(i-1,1) less than energy "e".
c    2. Find dE/dx belonging to the energy "e" through linear interpolation.
c    3. Integrate numerically the energy loss till the thickness of the
c       carbonfoil is reached
 
        do while (t.gt. 0)
            i=1
            do while (e .gt. brain(i,1))
                i=i+1
            end do
            
            aux1=sum(i)

            if(i .eq. 1) then
                dedx=(aux1)/(brain(i,1))*e
            else
                aux0=sum(i-1)
                dedx=aux0+(aux1-aux0)/(brain(i,1)-brain(i-1,1))
     .          *(e-brain(i-1,1))    
            end if

            e=e-(dedx/1000)*step
            t=t-step
c            write(*,*) i, e
        end do
        
        eresdl=e
c        write(*,*) eresdl
     
9999    CONTINUE
        CLOSE( UNIT=10 )
      
        RETURN
        END
