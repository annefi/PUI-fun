      REAL FUNCTION PWID(DELTA1,DELTA2,WID,PAPSTOEPQ,GAMMA)
C ***
C ***
C **********************************************************************
C **********************************************************************
C ***
C *** Calculates the probability of an ion being in the angular interval
C *** [delta1,delta2], given the angular distribution function after the
C *** carbon foil in SWICS. Here it is modelled to be the convolution of
C *** a rectangular distribution with a full width of 4 degrees (2*gamma) 
C **  due to
C *** angular dispersion in the deflection system and of a Lorentzian  
C *** angular distribution due to scattering in the C-foil. (WID)
C ***
C *** cf. lab book III p. 213 for details
C ***
C **********************************************************************
C **********************************************************************
C ***
C ***
C ***6
C ***|7                                                               72
C ***||                                                                |
C *** this is a sample comment line. ***********************************

C *** declare variables

      IMPLICIT NONE
      REAL*4
     &  PLOR,                 ! returns Lorentzian probability (if WID = 0.
     &  ALPHA1, ALPHA2,       ! end points of rectangular distribution
     &  DELTA1, DELTA2,       ! end points of angular interval
     &  WID,                  ! Half width at half max of Lorentzian
     &  PI ,                  ! pi
     &  PAPSTOEPQ,            ! PAPS/EPQ ratio
     &  GAMMA,                ! angular halfwidth  at half max due to deflection system
     &  AUX1,AUX2,AUX3,AUX4   ! auxiliary variables

      PARAMETER( PI = 3.14159265359 )
C
C *** Beginning of algorithm. ******************************************

      IF (GAMMA .EQ. 0.) THEN
        PWID = 0.5*(PLOR(DELTA1/WID)-PLOR(DELTA2/WID))
        RETURN
      END IF
      
      if (papstoepq .eq. 0) then
        alpha1 = gamma
      end if
      
      if (papstoepq .ne. 0) then
      ALPHA1 = - atan(-TAN(GAMMA)*
     &                (papstoepq/(sqrt(1+2*papstoepq)-(1+2*papstoepq))))
      end if
      ALPHA2 = - ALPHA1
      AUX1 = (DELTA2 - ALPHA1)/WID
      AUX2 = (DELTA1 - ALPHA1)/WID
      AUX3 = (DELTA2 - ALPHA2)/WID
      AUX4 = (DELTA1 - ALPHA2)/WID
c      write(*,*) 'in pwid:',aux1,aux2,aux3,aux4
      AUX1 = AUX1*ATAN(AUX1)-0.5*LOG(1.+AUX1**2)
      AUX2 = AUX2*ATAN(AUX2)-0.5*LOG(1.+AUX2**2) 
      AUX3 = AUX3*ATAN(AUX3)-0.5*LOG(1.+AUX3**2)  
      AUX4 = AUX4*ATAN(AUX4)-0.5*LOG(1.+AUX4**2)
c      write(*,*) 'in pwid:',aux1,aux2,aux3,aux4
      PWID = (AUX1 - AUX2) - (AUX3 - AUX4)  
      PWID = -WID/(PI*(ALPHA2 - ALPHA1)) * PWID
c      write(*,*) pwid
      pwid = abs(pwid)

C *** End of algorithm. ************************************************

      RETURN
      END

