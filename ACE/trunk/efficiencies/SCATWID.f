      REAL*4 FUNCTION SCATWID( EPERM, MASS, THICK )
C
C     Calculates the half width at half maximum of angular distribution
C     of ions passing through a thin carbon foil.
C     The program uses data of M. Oetliker's diploma thesis at
C     2 microg/squarecm, makes an exponential best fit in energy,
C     inter- or extrapolates logarithmically at unknown masses,
C     and scales the result with the foil thickness.
C
C     Written by r.v.steiger, July 25, 1990
C
C     Version 2: Using best fits in E/M, not interpolation (8-3-90).
C     Version 3: Using TRIM guesses for H and Kr (8-8-90).
C
C     INPUT: EPERM: energy per mass in keV/amu
C            MASS: mass of incident ions in amu
C            THICK: carbon foil thickness in microg/squarecm
C     OUTPUT: SCATWID: half width at half maximum in degrees (????????????)
C                                                             I think it's in 
C                                                             rad or something
C                                                             else (rfws)
C
      IMPLICIT NONE
C     number of masses with known values for scatwid
      INTEGER NMASS
      PARAMETER( NMASS=8 )
C     indices of left point in interpolation interval
      INTEGER IMASS
C     input parameters
      REAL*4 EPERM, MASS, THICK
C     masses at which scatwid is known
C     CAUTION: Values for H and Kr have been guessed from TRIM 
C              simulations!
      REAL*4 MASSES(NMASS) / 1, 4, 12, 14, 16, 20, 40, 84 /
C     parameters for best fit in energy/mass
      REAL*4 A(NMASS) / 19.579, 16.055, 13.027, 12.911, 13.305, 11.460,
     .                  8.453, 6.931 /
      REAL*4 ALPHA(NMASS) / -0.9398, -0.9398, -0.8113, -0.9787, -0.9296, 
     .                      -0.9209, -0.9753, -0.9753 /
C     auxiliary values for interpolation
      REAL*4 SCATWLO, SCATWHI, H

C     look for mass interval to use for interpolation
      IMASS = 1
      DO WHILE( MASS.GT.MASSES(IMASS+1) .AND. IMASS.LT.NMASS-1 )
         IMASS = IMASS + 1
      END DO

C     find values of scatwid at lower and upper end of interval
      SCATWLO = A(IMASS) * EPERM ** ALPHA(IMASS)
      SCATWHI = A(IMASS+1) * EPERM ** ALPHA(IMASS+1)

C     perform interpolation in mass direction
      H = (MASS - MASSES(IMASS)) / (MASSES(IMASS+1) - MASSES(IMASS))
      SCATWID = SCATWLO ** (1E0-H) * SCATWHI ** H

C     scale result (for 2 microg/squarecm foils) with foil thickness
      SCATWID = SCATWID * THICK / 2E0

      RETURN
      END
