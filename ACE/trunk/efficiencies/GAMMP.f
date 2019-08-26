C ***************************************************************

      FUNCTION GAMMP(A,X)

C ***************************************************************

C ***************************************************************
C ***                                                         ***
C *** returns the incomplete gamma function.                  ***
C *** from Numerical recipes, p. 161, ff.                     ***
C ***                                                         ***
C ***************************************************************

      IF(X.LT.0..OR.A.LE.0.)PAUSE
      IF(X.LT.A+1.)THEN
        CALL GSER(GAMSER,A,X,GLN)
        GAMMP=GAMSER
      ELSE
        CALL GCF(GAMMCF,A,X,GLN)
        GAMMP=1.-GAMMCF
c        WRITE(*,*) 'GAMMCF!'
      END IF
      RETURN
      END
