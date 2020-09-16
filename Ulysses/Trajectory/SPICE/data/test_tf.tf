


Heliocentric Inertial (HCI) Frame

     Definition of the Heliocentric Inertial frame:
 
              All vectors are geometric: no aberration corrections are
              used.
 
              The solar rotation axis is the primary vector: the Z axis points
	      in the solar north direction.
 
              The solar ascending node on the ecliptic of J2000 forms the X
              axis.
 
              The Y axis is Z cross X, completing the right-handed
              reference frame.

***
Just a copy from heliospheric.tf for testing

\begindata

        FRAME_HCI_COPY               =  1910420
        FRAME_1910420_NAME           = 'HCI_COPY'
        FRAME_1910420_CLASS          =  5
        FRAME_1910420_CLASS_ID       =  1910420
        FRAME_1910420_CENTER         =  10
        FRAME_1910420_RELATIVE       = 'J2000'
        FRAME_1910420_DEF_STYLE      = 'PARAMETERIZED'
        FRAME_1910420_FAMILY         = 'TWO-VECTOR'
        FRAME_1910420_PRI_AXIS       = 'Z'
        FRAME_1910420_PRI_VECTOR_DEF = 'CONSTANT'
        FRAME_1910420_PRI_FRAME      = 'IAU_SUN'
        FRAME_1910420_PRI_SPEC       = 'RECTANGULAR'
        FRAME_1910420_PRI_VECTOR     = ( 0, 0, 1 )
        FRAME_1910420_SEC_AXIS       = 'Y'
        FRAME_1910420_SEC_VECTOR_DEF = 'CONSTANT'
        FRAME_1910420_SEC_FRAME      = 'ECLIPJ2000'
        FRAME_1910420_SEC_SPEC       = 'RECTANGULAR'
        FRAME_1910420_SEC_VECTOR     = ( 0, 0, 1 )

\begintext


Heliocentric Inertial (HCI) Frame

     Definition of the Heliocentric Inertial frame:
 
            (...)

***
changed parameter "RELATIVE" to B1950

\begindata

        FRAME_HCI_T1                 =  1910421
        FRAME_1910421_NAME           = 'HCI_T1'
        FRAME_1910421_CLASS          =  5
        FRAME_1910421_CLASS_ID       =  1910421
        FRAME_1910421_CENTER         =  10
        FRAME_1910421_RELATIVE       = 'B1950'
        FRAME_1910421_DEF_STYLE      = 'PARAMETERIZED'
        FRAME_1910421_FAMILY         = 'TWO-VECTOR'
        FRAME_1910421_PRI_AXIS       = 'Z'
        FRAME_1910421_PRI_VECTOR_DEF = 'CONSTANT'
        FRAME_1910421_PRI_FRAME      = 'IAU_SUN'
        FRAME_1910421_PRI_SPEC       = 'RECTANGULAR'
        FRAME_1910421_PRI_VECTOR     = ( 0, 0, 1 )
        FRAME_1910421_SEC_AXIS       = 'Y'
        FRAME_1910421_SEC_VECTOR_DEF = 'CONSTANT'
        FRAME_1910421_SEC_FRAME      = 'ECLIPJ2000'
        FRAME_1910421_SEC_SPEC       = 'RECTANGULAR'
        FRAME_1910421_SEC_VECTOR     = ( 0, 0, 1 )

\begintext
