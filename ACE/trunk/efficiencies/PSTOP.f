       SUBROUTINE PSTOP(Z1,M1,Z2,M2,E,PCOEF,SE)
c
       IMPLICIT REAL*4(A-H,M-Z)
       INTEGER Z1,Z2
       DIMENSION PCOEF(8)
c	
       PE0=25.
       PE=AMAX1(PE0,E)
       SL=(PCOEF(1)*PE**PCOEF(2))+PCOEF(3)*PE**PCOEF(4)
       SH=PCOEF(5)/PE**PCOEF(6)*ALOG((PCOEF(7)/PE)+PCOEF(8)*PE)
       SE=SL*SH/(SL+SH)
       IF (E.LE.PE0) THEN
          VELPWR=0.45
          IF (Z2.LE.6) VELPWR=0.25
          SE=SE*(E/PE0)**VELPWR
       END IF
       RETURN
       END
