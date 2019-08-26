C ***************************************************************

      SUBROUTINE GSER(GAMSER,A,X,GLN)

C ***************************************************************

C ***************************************************************
C ***                                                         ***
C *** returns the incomplete gamma function.                  ***
C *** from Numerical recipes, p. 162, ff.                     ***
C ***                                                         ***
C ***************************************************************

      PARAMETER (ITMAX=100,EPS=3.E-7)
      GLN=GAMMLN(A)

      IF(X.LE.0.)THEN
        IF(X.LT.0.)PAUSE
          GAMSER=0.
          RETURN
      END IF
      AP=A
      SUM = 1./A
      DEL=SUM
      DO N=1,ITMAX
        AP=AP+1.
        DEL=DEL*X/AP
        SUM=SUM+DEL
        IF(ABS(DEL).LT.ABS(SUM)*EPS)GO TO 1
      END DO
      PAUSE 'A too large, ITMAX too small'
  1   GAMSER=SUM*EXP(-X+A*LOG(X)-GLN)
      RETURN
      END
