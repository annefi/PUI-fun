       subroutine noise(ew,sigma,res1,res2)

        real*4
     .      ew,
     .      sigma,
     .      v1,v2,
     .      r,fac,
     ,      res1,res2


1       v1=2.*rand()-1.
        v2=2.*rand()-1.
        r=v1**2+v2**2
        if (r .ge. 1. .or. r .eq. 0.) go to 1
        fac=sqrt(-2*log(r)/r)
        res1=v1*fac
        res2=v2*fac
        res1=res1*sigma+ew
        res2=res2*sigma+ew

        RETURN
        END