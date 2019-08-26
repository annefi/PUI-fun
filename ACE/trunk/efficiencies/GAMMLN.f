C ***************************************************************

      FUNCTION GAMMLN(XX)

C ***************************************************************

C ***************************************************************
C ***                                                         ***
C *** returns the logarithm of the absolute value of the      ***
C *** gamma function.                                         ***
C *** from Numerical recipes, p. 157, ff.                     ***
C ***                                                         ***
C ***************************************************************
C      IMPLICIT NONE
      REAL*8 COF(6),STP,HALF,ONE,FPF,X,TMP,SER
      DATA COF,STP/76.18009173D0,-86.50532033D0,24.01409822D0,
     &     -1.231739516D0,.120858003D-2,-.536382D-5,2.50662827465D0/
      DATA HALF,ONE,FPF/0.5D0,1.0D0,5.5D0/
      X=XX-ONE
      TMP=X+FPF
      TMP=(X+HALF)*LOG(TMP)-TMP
      SER=ONE
      DO J=1,6
        X=X+ONE
        SER=SER+COF(J)/X
      END DO 
      GAMMLN=TMP+LOG(STP*SER)
      RETURN
      END
