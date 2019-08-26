      subroutine deadlayer(zion,mion,energy,thick,step,eresdl)
      
c    Calculates the residual energy "eresdl" of an ion with atomic number "zion" passing the deadlayer of
c    a silicon detector with thickness "thick" given in Angström. The initial energy must be given in keV.
c    "step" is the integration step (step=1 means 1-Angström-steps in integration).
      
      real*4
     . brain(100,6),     ! Array for the deadlayer dE/dx data
     . sum(100),         ! Array for the sum of electronic and nuclear stopping
     . energy,           ! Energy of the ion in the ToF-section
     . e,                ! Auxiliary variable for the energy
     . thick,            ! Thickness of the deadlayer
     . t,                ! Auxiliary variable for the thickness of the deadlayer
     . eresdl,           ! Residual energy after the deadlayer
     . aux0,             ! Auxilary variable
     . aux1,             ! Auxilary variable
     . step,             ! Integration step given in Angström
     . mion              ! Mass of the solar wind ion
     
      integer*4
     . i,j,k             ! Auxiliary loop variables
     
      integer
     . zion              ! Atomic number of the solar-wind ion
      

c++++ Starting read-in of the dE/dx data +++++++++++++++++++++     
           
        if (zion .eq. 1) then
            OPEN( UNIT=10, FILE='./deadlayer/hydrogendl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
        if (zion .eq. 2) then
            if (nint(mion) .eq. 4) then
                OPEN( UNIT=10, FILE='./deadlayer/heliumdl.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            else if (nint(mion) .eq. 3) then
                OPEN( UNIT=10, FILE='./deadlayer/3heliumdl.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            end if
        end if

      
        if (zion .eq. 6) then
            if (nint(mion) .eq. 12) then
                OPEN( UNIT=10, FILE='./deadlayer/carbondl.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            else if (nint(mion) .eq. 13) then
                OPEN( UNIT=10, FILE='./deadlayer/13carbondl.f')
                do i=1,79
                    READ(10,*,END=9999), (brain(i,j),j=1,6)
c                    write(*,*), (brain(i,j),j=1,6)
                end do
            end if
        end if

      
        if (zion .eq. 7) then
            OPEN( UNIT=10, FILE='./deadlayer/nitrogendl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
     
      
        if (zion .eq. 8) then
            OPEN( UNIT=10, FILE='./deadlayer/oxygendl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 10) then
            OPEN( UNIT=10, FILE='./deadlayer/neondl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 12) then
            OPEN( UNIT=10, FILE='./deadlayer/magnesiumdl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 13) then
            OPEN( UNIT=10, FILE='./deadlayer/aluminumdl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 14) then
            OPEN( UNIT=10, FILE='./deadlayer/silicondl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 16) then
            OPEN( UNIT=10, FILE='./deadlayer/sulfurdl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 18) then
            OPEN( UNIT=10, FILE='./deadlayer/argondl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 20) then
            OPEN( UNIT=10, FILE='./deadlayer/calciumdl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
            
        if (zion .eq. 26) then
            OPEN( UNIT=10, FILE='./deadlayer/irondl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
      
        if (zion .eq. 36) then
            OPEN( UNIT=10, FILE='./deadlayer/kryptondl.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
c++++ End of read in ++++++++++++++++++++++++++++++++++++++++++     
      
      

      
c    Umrechnung von keV/(microgramm/quadratcentimeter) in eV/A.
c    Conversion of the dE/dx values from keV/(micrograms/squarecentimeter) to eV/A.
        do i=1,79
            brain(i,2)=(brain(i,2))*23.211
            brain(i,3)=(brain(i,3))*23.211
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
c       deadlayer is reached
 
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
      
     
9999    CONTINUE
        CLOSE( UNIT=10 )
      
        RETURN
        END
