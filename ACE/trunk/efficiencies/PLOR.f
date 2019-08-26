      REAL FUNCTION PLOR( T )
C
C     calculates the probability of a Lorentz-distributed random
C     variable of UNIT width to be smaller or equal T in absolute value.
C
C     written by r.v.steiger, august 7, 1990
C
      IMPLICIT NONE
      REAL T, T2, PI
      PARAMETER( PI = 3.14159265359 )
C
c      T2 = T / 2E0
c      PLOR = ( T2/(1E0+T2**2) + ATAN(T2) ) * 2E0 / PI
      plor = 2.*atan(t)/pi
C
      RETURN
      END
