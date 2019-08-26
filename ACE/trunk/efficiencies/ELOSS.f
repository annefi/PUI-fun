      REAL*4 FUNCTION ELOSS( EIN, ZION, MION, THICK, STEP )
C
C     calculate energy loss in carbon foil by numerical integration with
C     adjustable precision.
C     INPUT: EIN: incident energy of ion [keV]
C            ZION: nuclear charge of ion [e]
C            MION: mass of ion [amu]
C            THICK: carbon foil thickness [microg/squarecm]
C            STEP:  max. fraction of e to be lost per step
C                   (0<STEP<=1, typically 0.2) 
C     OUTPUT: ELOSS: energy loss in foil [keV]
C
C     written by r.v.steiger, July 28, 1990
C
      IMPLICIT NONE
      REAL*4
     .   E,             ! actual energy of ion [keV]
     .   EIN,           ! incident energy of ion [keV]
     .   MION,          ! mass of ion [amu]
     .   SE, SN,        ! el., nuc. stopping power [keV*squarecm/microg]
     .   STEP,          ! maximum e-loss allowed per integration step 
     .   THICK,         ! carbon foil thickness [microg/squarecm]
     .   X, DX          ! position, step width in foil [microg/squarecm]
       INTEGER
     .   ZION           ! nuclear charge of ion
      EXTERNAL
     .   STOP           ! stopping power after Ziegler et al.
C
C     initialize integration
      X = 0E0
      E = EIN
C
C     integrate path through foil, calculate new stopping power each time 
C     energy has decreased by fraction given in step
      DO WHILE ( X .LT. THICK .AND. E .GT. 0E0 )
C
C        calculate step length and new energy,
C        use only electronic part of stopping power
         CALL STOP( ZION, MION, 6, E, SE, SN, 2 )
c         step ist hier 0.2
c         --> DX ist immer die strecke, auf der das teilchen 20% seiner energie verliert
         DX = STEP * E / (SE+SN)
         X = X + DX
         IF ( X .LT. THICK ) THEN
            E = E * ( 1E0 - STEP )
         ELSE
            E = E - (SE+SN) * ( THICK - X + DX )
         END IF
C
C        escape when ion appears to stick in foil
         IF ( DX/X .LT. STEP/1E1 )  THEN
            E = 0E0
         END IF
C
      END DO
C 
C     find energy lost in foil
      ELOSS = EIN - E 
C
      RETURN
      END

      