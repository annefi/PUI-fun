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
 
            (...)

***
HCI_T1
changed parameters: both "SEC_FRAME" and freeze to B1950

\begindata

        FRAME_HCI_T1                 =  1910421
        FRAME_1910421_NAME           = 'HCI_T1'
        FRAME_1910421_CLASS          =  5
        FRAME_1910421_CLASS_ID       =  1910421
        FRAME_1910421_CENTER         =  10
        FRAME_1910421_RELATIVE       = 'J2000'
        FRAME_1910421_DEF_STYLE      = 'PARAMETERIZED'
        FRAME_1910421_FAMILY         = 'TWO-VECTOR'
	FRAME_1810421_FREEZE_EPOCH   = @1949-DEC-31/22:09:47
        FRAME_1910421_PRI_AXIS       = 'Z'
        FRAME_1910421_PRI_VECTOR_DEF = 'CONSTANT'
        FRAME_1910421_PRI_FRAME      = 'IAU_SUN'
        FRAME_1910421_PRI_SPEC       = 'RECTANGULAR'
        FRAME_1910421_PRI_VECTOR     = ( 0, 0, 1 )
        FRAME_1910421_SEC_AXIS       = 'Y'
        FRAME_1910421_SEC_VECTOR_DEF = 'CONSTANT'
        FRAME_1910421_SEC_FRAME      = 'ECLIPB1950'
        FRAME_1910421_SEC_SPEC       = 'RECTANGULAR'
        FRAME_1910421_SEC_VECTOR     = ( 0, 0, 1 )




\begintext

***
HCI_T2
changed parameters: both "SEC_FRAME" and freeze to B1950

\begindata

        FRAME_HCI_T2                 =  1910422
        FRAME_1910422_NAME           = 'HCI_T2'
        FRAME_1910422_CLASS          =  5
        FRAME_1910422_CLASS_ID       =  1910422
        FRAME_1910422_CENTER         =  10
        FRAME_1910422_RELATIVE       = 'J2000'
        FRAME_1910422_DEF_STYLE      = 'PARAMETERIZED'
        FRAME_1910422_FAMILY         = 'TWO-VECTOR'
        FRAME_1910422_PRI_AXIS       = 'Z'
        FRAME_1910422_PRI_VECTOR_DEF = 'CONSTANT'
        FRAME_1910422_PRI_FRAME      = 'IAU_SUN'
        FRAME_1910422_PRI_SPEC       = 'RECTANGULAR'
        FRAME_1910422_PRI_VECTOR     = ( 0, 0, 1 )
        FRAME_1910422_SEC_AXIS       = 'Y'
        FRAME_1910422_SEC_VECTOR_DEF = 'CONSTANT'
        FRAME_1910422_SEC_FRAME      = 'ECLIPB1950'
        FRAME_1910422_SEC_SPEC       = 'RECTANGULAR'
        FRAME_1910422_SEC_VECTOR     = ( 0, 0, 1 )



\begintext

***
HCI_NEW
changed parameters:  "SEC_FRAME"

\begindata

        FRAME_HCI_NEW                =  1910423
        FRAME_1910423_NAME           = 'HCI_NEW'
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

\begintext
