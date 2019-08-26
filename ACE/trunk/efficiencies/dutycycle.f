C **********************************************************************

      REAL FUNCTION DUTYCYCLE( ASPANG )

C *** This function computes the duty cycle of the SWICS instrument  ***
C *** as a function of the sun aspect angle.                         ***


C **********************************************************************
C ***                                                                ***
C *** Interface with the main program:                               ***
C *** The main program must hand over:                               ***
C *** - a REAL*4 containing the sun aspect angle in degrees.         *** 
C *** Output is a REAL*4 between ~0.01 and 0.5, the portion of a     ***
C *** spin during which the sensor sees the solar wind.              ***
C ***                                                                ***
C *** In this version, the effect of a nonzero solar wind            ***
C *** temperature is neglected.                                      ***    
C ***                                                                ***
C **********************************************************************



C *** Author: Rudolf von Steiger, Physikalisches Institut, Univ. Bern,
C ***         Sidlerstr. 5, CH-3012 Bern, Switzerland
C ***
C *** Date:   January 22, 1992


C **********************************************************************
C **********************************************************************
C **********************************************************************


C     7
C    6|                                                               72
C    ||                                                                |
C *** Beginning of the code. *******************************************
c *** Declaration part. ************************************************


      IMPLICIT NONE

      REAL*4
     &  ASPANG,			  ! solar aspect angle
     &  APLUS, AZERO, AMINUS,	  ! bounds of collimator
     &  PHIPLUS, PHIMINUS,        ! intermediate results
     &  PI,                       ! PI=3.1415927
     &  D                         ! = PI/180.

      PARAMETER
     &  ( APLUS = 59.0*3.1415927/180., 
     &    AZERO = 57.0*3.1415927/180., 
     &    AMINUS = 55.0*3.1415927/180. )

C *** Conversion of degrees into radian ********************************
      PI=3.1415927
      D=PI/180.
c      ASPANG=ASPANG*D
c      APLUS=APLUS*D
c      AMINUS=AMINUS*D
                                     
C *** End of declarations. *********************************************


C *** Algorithm. *******************************************************

      IF ( ASPANG .LE. (2.0) ) THEN
	 
	 DUTYCYCLE = 0.5

      ELSE

	 PHIPLUS = ACOS( ( COS(ASPANG*D)*COS(AZERO) - COS(APLUS) ) /
     &			  ( SIN(ASPANG*D)*SIN(AZERO) ) )
	 PHIMINUS = ACOS( ( COS(ASPANG*D)*COS(AZERO) - COS(AMINUS) ) /
     &			   ( SIN(ASPANG*D)*SIN(AZERO) ) )
	 DUTYCYCLE = ( PHIMINUS - PHIPLUS ) / (2*PI)

      END IF

C *** End of algorithm. ************************************************

      RETURN
      END
