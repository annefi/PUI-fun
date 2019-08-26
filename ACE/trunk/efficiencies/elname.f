        subroutine elname(z,a,b,c) 

c    Macht aus der Kernladungszahl z de Elementnamen.
c    Gives the elementname subject to the atomic number.
        integer
     .  z
        character*1
     .  a
          
        character*2
     .  b
       
        real*4
     .  c
     
     
     
        if (z .eq. 1) then
            a="H"
            c=1
        end if
     
        if (z .eq. 2) then
            b="He"
            c=2
        end if
       
        if (z .eq. 6) then
            a="C"
            c=1
        end if
        
        if (z .eq. 7) then
            a="N"
            c=1       
        end if 
       
        if (z .eq. 8) then
            a="O"
            c=1       
        end if
       
        if (z .eq. 10) then
            b="Ne"
            c=2       
        end if
       
        if (z .eq. 12) then
            b="Mg"
            c=2        
        end if
                       
        if (z .eq. 14) then
            b="Si"
            c=2        
        end if
       
        if (z .eq. 16) then
            a="S"
            c=1       
        end if

        if (z .eq. 18) then
            b="Ar"
            c=2       
        end if
       
        if (z .eq. 20) then
            b="Ca"
            c=2        
        end if
              
        if (z .eq. 26) then
            b="Fe"
            c=2        
        end if

        RETURN
        END