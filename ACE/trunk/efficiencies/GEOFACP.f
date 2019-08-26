C **********************************************************************

      REAL FUNCTION GEOFACP( ASPANG )

C *** This function computes the geometric factor of the SWICS       ***
C *** instrument as a function of the sun aspect angle, taking into  ***
C *** account the reduced efficiency between the detectors.          ***
C *** This routine is correct for a PENCIL beam only, as is usually  ***
C *** the case in the solar wind.


C **********************************************************************
C ***                                                                ***
C *** Interface with the main program:                               ***
C *** The main program must hand over:                               ***
C *** - a REAL*4 containing the sun aspect angle in degrees.         *** 
C *** Output is a REAL*4 between ~0.006 and ~0.017, the geometric    ***
C *** factor in cm^2                                                 ***
C ***                                                                ***
C **********************************************************************



C *** Author: Rudolf von Steiger, Physikalisches Institut, Univ. Bern,
C ***         Sidlerstr. 5, CH-3012 Bern, Switzerland
C ***
C *** Date:   January 23, 1992


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
     &  ALPHA, BETA,              ! angles of collimator
     &  GEOFACT_0,		  ! geometric factor at center of MSS2
     &  GEOFACTARR(0:69),         ! array for interpolation of geofact
     &	PI			  ! Just Pi as known
     
      DATA GEOFACTARR /0.5753, 0.7759, 0.9220, 1.0123, 1.0636, 1.0892, 
     &		       1.1003, 1.1037, 1.1037, 1.1059, 1.1115, 1.1148, 
     &		       1.1104, 1.0925, 1.0569, 1.0045, 0.9342, 0.8473, 
     &		       0.7492, 0.6499, 0.5630, 0.5006, 0.4738, 0.4861, 
     &		       0.5362, 0.6176, 0.7179, 0.8149, 0.8907, 0.9376, 
     &		       0.9588, 0.9677, 0.9766, 0.9900, 1.0000, 1.0000, 
     &		       0.9877, 0.9666, 0.9409, 0.9097, 0.8629, 0.7937, 
     &		       0.7035, 0.6042, 0.5128, 0.4404, 0.3980, 0.3868,
     &		       0.4091, 0.4627, 0.5396, 0.6265, 0.7101, 0.7804,
     &		       0.8328, 0.8685, 0.8885, 0.8963, 0.8941, 0.8874,
     &		       0.8841, 0.8841, 0.8829, 0.8718, 0.8473, 0.8094,
     &		       0.7625, 0.7001, 0.6076, 0.4705/
     
      DATA
     &	  PI/3.1415927/      
      PARAMETER
     &  ( ALPHA = 57.0,
     &    GEOFACT_0 = 0.0225 )
                                     
C *** End of declarations. *********************************************


C *** Algorithm. *******************************************************

      BETA = ACOS( ( COS((ASPANG)*(Pi/180)) - COS((ALPHA)*(Pi/180))**2 )
     &       / SIN((ALPHA)*(Pi/180))**2 )
      write(*,*) aspang, beta*180/pi
      GEOFACP = GEOFACT_0 * GEOFACTARR( INT(BETA) )

C *** End of algorithm. ************************************************

      RETURN
      END
