       REAL FUNCTION CFOILZ(EPN,Z)
c
c	equivalent function to CFOIL, but using new program STOP of 
c	Ziegler et al., only using electronic stopping power.
c	INPUT: EPN: energy per nucleon in keV/amu of ions
c              Z: nuclear charge of ions
c	OUTPUT: dE/dx in carbon foil in keV/microgram/cm**2
c	r.v.steiger, july 9, 1990
c
       IMPLICIT NONE
       INTEGER Z
       REAL*4 EPN, MAMU, SE, X, XX(8)
c
       CALL SCOEF(Z, X, MAMU, X, X, X, X, X, XX)
       CALL STOP(Z, MAMU, 6, EPN*MAMU, SE, X, 2)
       CFOILZ = SE
c
       RETURN
       END
