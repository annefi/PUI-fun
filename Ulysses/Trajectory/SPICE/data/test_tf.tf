Dynamic Heliospheric Coordinate Frames developed for the NASA STEREO mission

The coordinate frames in this file all have ID values based on the pattern
18ccple, where

	18 = Prefix to put in the allowed 1400000 to 2000000 range
	cc = 03 for geocentric, 10 for heliocentric
	p  = Pole basis: 1=geographic, 2=geomagnetic, 3=ecliptic, 4=solar
	l  = Longitude basis: 1=Earth-Sun, 2=ecliptic
	e  = Ecliptic basis: 0=J2000, 1=mean, 2=true

     Author:  William Thompson
	      NASA Goddard Space Flight Center
	      Code 612.1
	      Greenbelt, MD 20771

	      William.T.Thompson.1@gsfc.nasa.gov

History

    Version 1, 18-Feb-2005, WTT, initial release
	GSE and ECLIPDATE definitions from examples in frames.req by C.H. Acton
	HEE definition is based on the GSE example

    Version 2, 22-Feb-2005, WTT
	Modified HCI definition to tie to IAU_SUN frame
	Use RECTANGULAR specification in HEEQ frame

    Version 3, 23-Feb-2005, WTT
	Correct GSE and HEE definitions to use ECLIPDATE axis

    Version 4, 08-Aug-2008, WTT
	Add GEORTN coordinate system (comment added 30-Aug-2010)



Heliocentric Inertial (HCI) Frame

     Definition of the Heliocentric Inertial frame:
 
              All vectors are geometric: no aberration corrections are
              used.
 
              The solar rotation axis is the primary vector: the Z axis points
              in the solar north direction (IAU_SUN frozen at J2000 epoch).
 
              The ascending node on the ecliptic of J2000 of the IAU_SUN
              equator forms the X axis.  *** N.B this is accomplished by
              using the +Z axis of the ecliptic of J2000 as the secondary
              vector and HCI +Y as the secondary axis
 
              The Y axis is Z cross X, completing the right-handed
              reference frame.

\begindata

        FRAME_HCI_J2000              =  1810421
        FRAME_1810421_NAME           = 'HCI_J2000'
        FRAME_1810421_CLASS          =  5
        FRAME_1810421_CLASS_ID       =  1810421
        FRAME_1810421_CENTER         =  10
        FRAME_1810421_RELATIVE       = 'J2000'
        FRAME_1810421_DEF_STYLE      = 'PARAMETERIZED'
        FRAME_1810421_FAMILY         = 'TWO-VECTOR'
        FRAME_1810421_FREEZE_EPOCH   = @2000-JAN-01/12:00:00
        FRAME_1810421_PRI_AXIS       = 'Z'
        FRAME_1810421_PRI_VECTOR_DEF = 'CONSTANT'
        FRAME_1810421_PRI_FRAME      = 'IAU_SUN'
        FRAME_1810421_PRI_SPEC       = 'RECTANGULAR'
        FRAME_1810421_PRI_VECTOR     = ( 0, 0, 1 )
        FRAME_1810421_SEC_AXIS       = 'Y'
        FRAME_1810421_SEC_VECTOR_DEF = 'CONSTANT'
        FRAME_1810421_SEC_FRAME      = 'ECLIPJ2000'
        FRAME_1810421_SEC_SPEC       = 'RECTANGULAR'
        FRAME_1810421_SEC_VECTOR     = ( 0, 0, 1 )

\begintext



***
HCI_B1950
changed parameters:  "SEC_FRAME"

\begindata

        FRAME_HCI_B1950                =  1910423
        FRAME_1910423_NAME           = 'HCI_B1950'
        FRAME_1910423_CLASS          =  5
        FRAME_1910423_CLASS_ID       =  1910423
        FRAME_1910423_CENTER         =  10
        FRAME_1910423_RELATIVE       = 'B1950'
        FRAME_1910423_DEF_STYLE      = 'PARAMETERIZED'
        FRAME_1910423_FAMILY         = 'TWO-VECTOR'
        FRAME_1910423_PRI_AXIS       = 'Z'
        FRAME_1910423_PRI_VECTOR_DEF = 'CONSTANT'
        FRAME_1910423_PRI_FRAME      = 'IAU_SUN'
        FRAME_1910423_PRI_SPEC       = 'RECTANGULAR'
        FRAME_1910423_PRI_VECTOR     = ( 0, 0, 1 )
        FRAME_1910423_SEC_AXIS       = 'Y'
        FRAME_1910423_SEC_VECTOR_DEF = 'CONSTANT'
        FRAME_1910423_SEC_FRAME      = 'ECLIPB1950'
        FRAME_1910423_SEC_SPEC       = 'RECTANGULAR'
        FRAME_1910423_SEC_VECTOR     = ( 0, 0, 1 )


