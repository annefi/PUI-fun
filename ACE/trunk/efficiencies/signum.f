c        signum gives the algebraic sign of the number "zahl"
        
        real*4 function signum(zahl)
      
        real*4 zahl

        if(zahl .lt. 0.0) then
            signum=-1
        else if(zahl .ge. 0.0) then
            signum=1
        end if
        return
        end