      subroutine dedxmacor(zion,energy,bw)
c     Ausgabe "bw" ist der differenzielle Energieverlust in ev/A.
c     Calculates the electronic differential energy loss "bw [eV/A]" of an ion with
c     atomic number "zion" and energy "energy" impinging on the macor surface.
       
      real*4
     . brain(100,6),     ! Array for the macor dE/dx data 
     . sum(100),         ! Array for the electronic stopping
     . energy,           ! Energy of the ion
     . e,                ! Auxiliary variable for the energy
     . aux0,             ! Auxilary variable
     . aux1              ! Auxilary variable
     
      integer*4
     . i,j,k             ! Auxiliary loop variables
     
      integer
     . zion              ! Atomic number of the solar-wind ion
      

c++++ Starting read-in of the dE/dx data +++++++++++++++++++++     
           
        if (zion .eq. 1) then
            OPEN( UNIT=10, FILE='./macor/hydrogenmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
      
        if (zion .eq. 2) then
            OPEN( UNIT=10, FILE='./macor/heliummacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 6) then
            OPEN( UNIT=10, FILE='./macor/carbonmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
 
      
        if (zion .eq. 7) then
            OPEN( UNIT=10, FILE='./macor/nitrogenmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
     
      
        if (zion .eq. 8) then
            OPEN( UNIT=10, FILE='./macor/oxygenmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 10) then
            OPEN( UNIT=10, FILE='./macor/neonmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 12) then
            OPEN( UNIT=10, FILE='./macor/magnesiummacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 13) then
            OPEN( UNIT=10, FILE='./macor/aluminummacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 14) then
            OPEN( UNIT=10, FILE='./macor/siliconmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 16) then
            OPEN( UNIT=10, FILE='./macor/sulfurmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 18) then
            OPEN( UNIT=10, FILE='./macor/argonmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if

      
        if (zion .eq. 20) then
            OPEN( UNIT=10, FILE='./macor/calciummacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
            
        if (zion .eq. 26) then
            OPEN( UNIT=10, FILE='./macor/ironmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
      
        if (zion .eq. 36) then
            OPEN( UNIT=10, FILE='./macor/kryptonmacor.f')
            do i=1,79
                READ(10,*,END=9999), (brain(i,j),j=1,6)
c                write(*,*), (brain(i,j),j=1,6)
            end do
        end if
      
c++++ End of read in ++++++++++++++++++++++++++++++++++++++++++     
      
      
      
        do i=1,79
            sum(i)=brain(i,2)
c            write(*,*) sum(i)
        end do
      
        e=energy
        
        
c    1. Find i with brain(i,1) greater than energy "e" and 
c       brain(i-1,1) less than energy "e".
c    2. Find dE/dx belonging to the energy "e" through linear interpolation.

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
     .      *(e-brain(i-1,1))    
        end if

        bw=dedx
      
     
9999    CONTINUE
        CLOSE( UNIT=10 )
      
        RETURN
        END
