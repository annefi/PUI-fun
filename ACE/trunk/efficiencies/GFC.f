C ***************************************************************

      SUBROUTINE GCF(GAMMCF,A,X,GLN)

C ***************************************************************

C ***************************************************************
C ***                                                         ***
C *** returns the incomplete gamma function.                  ***
C *** from Numerical recipes, p. 162, ff.                     ***
C ***                                                         ***
C ***************************************************************

      PARAMETER (ITMAX=100,EPS=3.E-7)
      GLN=GAMMLN(A)
      GOLD=0.
      A0=1.
      A1=X
      B0=0.
      B1=1.
      FAC=1.
      DO N=1,ITMAX
        AN=FLOAT(N)
        ANA=AN-A
        A0=(A1+A0*ANA)*FAC
        B0=(B1+B0*ANA)*FAC
        ANF=AN*FAC
        A1=X*A0+ANF*A1
        B1=X*B0+ANF*B1
        IF(A1.NE.0.)THEN
          FAC=1./A1
          G=B1*FAC
          IF(ABS((G-GOLD)/G).LT.EPS)GO TO 1
          GOLD=G
        END IF
      END DO
      PAUSE 'A too large, ITMAX too small'
  1   GAMMCF=min(38.,max(-38.,-X+A*ALOG(X)-GLN))
      GAMMCF=EXP(gammcf)*G
      RETURN
      END
