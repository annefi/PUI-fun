
        SUBROUTINE SWXEFF_ERR(RESPROB,EPERM,ZIONF,MIONF,ION,CONST1,CONST2,
     .                 CONST3,PF1,PF2,ETHRESH,FWHMEL,THICK,DEFL,
     .                 DEDXCERR,DEDXSIERR,DEDXAUERR,SIGMAERR,PHDERR,FWHMNERR)

        IMPLICIT NONE

        REAL*4
     .      RESPROB,            ! Resulting probability
     .      EPERM,              ! Energy/amu
     .      ZIONF,              ! Nuclear charge of incident ion [e] (float)
     ,      MIONF,              ! Mass of the incident ion [amu] (float)
     .      CONST1,             ! Factor to convert etotf in # of sec. el. (carbonfoil)
     .      CONST2,             ! Factor to convert etotf in # of sec. el. (PIPS-surface)
     .      CONST3,             ! Factor to convert etotf in # of sec. el. (Macor-surface)
     .      PF1,                ! Probability of Failure of MCP 1
     .      PF2,                ! Probability of NON-Failure of MCP 2
     .      ETHRESH,            ! Threshold energy of MSS detector [keV]
     .      FWHMEL,             ! Electronic FWHM of MSS threshold [keV]
     .      THICK,              ! Foil thickness [microg/squarecm]
     .      DEFL,               ! Angular dispersion in deflection system
     .      DEDXCERR,
     .      DEDXSIERR,
     .      DEDXAUERR
     .      SIGMAERR,
     .      PHDERR,
     .      FWHMNERR

        CHARACTER*20
     .      ION                 ! element abbreviation for ION


c+++++++Common variables with the geometry part++++++++++++++++++
c       For explanation see geom.f
        COMMON /GEOM/ C,V,DELTAWIN,PHIWIN,DELTASTP,PHISTP,
     .                DELTASSD,PHISSD,DELTAMACOR,PHIMACOR,
     .                BRAIN,SSDC,STPC,MACORC,SSDI,STPI,
     .                COUNTER,WALKER,RUNNER,JUMPER,FITGEOM,
     .                FITMODE

        REAL*4
     .      C(3),
     .      V(3),           
     .      DELTAWIN(2,-33:32),
     .      PHIWIN(2,-33:32),
     .      DELTASTP(3,2),
     .      PHISTP(3,2),
     .      DELTASSD(3,2),
     .      PHISSD(3,2),
     .      DELTAMACOR(3,2),
     .      PHIMACOR(3,2),
     .      BRAIN(310,100),
     .      SSDC(3,4,3),
     .      STPC(3,4,3),
     .      MACORC(3,4,3),
     .      SSDI(3,4,3),
     .      STPI(3,4,3),
     .      FITGEOM(961,4)

        INTEGER*4 
     .      WALKER,             ! auxiliary loop variables
     .      RUNNER,
     .      JUMPER, 
     .      COUNTER,
     .      FITMODE             ! 0 = alle , 1 = Jedes Ion einzeln

c*******End of common-block /GEOM/*******************************



c+++++++Common variables with test1.f++++++++++++++++++++++++++++
        COMMON /CAL/
     .      eqstep,lpaps,lcharge,
     .      tau,tauchannel,tauchannelfloat,
     .      emeas,echannel,echannelfloat,
     .      fsrave, dcrave, tcrave

        REAL*4
     .      eqstep(100),        ! Energy-per-charge step
     .      lpaps,              ! PAPS during mission (PAPS=24.868179 kV)
     .      lcharge,            ! Variable ion charge during mission
     .      tau,                ! Time of flight
     .      tauchannel,         ! ToF-channel belonging to tau
     .      tauchannelfloat,    ! Not rounded ToF-channel (float)
     .      emeas,              ! Measured energy in detector
     .      emeas_corr,         ! Measured energy with Correction-factor (1.137)
     .      emeas_de,
     .      emeas_mi,
     .      echannel,           ! Energy-channel belonging to emeas
     .      echannelfloat       ! Not rounded energy-channel

c*******End of common-block /CAL/********************************     


        INTEGER
     .      ZION                ! nuclear charge of incident ion [e]


        REAL*4  !variables in order of appearance
     .      X(10),              ! dummy parameters for scoef
     .      XX(8),              ! dummy parameters for scoef        
     .      MION,               ! mass of incident ion [amu]  
     .      ETOT,               ! total energy before foil [keV]
     .      STEP,               ! parameter for accuracy of eloss      
     .      ELOSS,              ! function to calculate efoil     
     .      ETOTF,              ! total energy after foil [keV]
     .      EPERMF              ! energy per nucleon after foil [keV/amu]

        INTEGER
     .     ZTARG,               ! nuclear charge of target [e]        
     .     UCODE                ! unit code for stop

        REAL*4     
     .      EFOIL,              ! energy lost in foil [keV]     
     .      DEDX,               ! stopping power dE/dx
     .      SE1,                ! sec. electrons from foil
     .      SE2,                ! sec. electrons from detector          
     .      SE3,                ! sec. electrons from MACOR-area
     .      PROB1,              ! trigger prob. of start MCP
     .      PROB2,              ! trigger prob. of stop MCP
     .      PROB3,              ! prob. of ion counted in detector
     .      FSRAVE,             ! Average fsr over all steps
     .      DCRAVE,             ! Average dcr over all steps
     .      TCRAVE,             ! Average tcr over all steps
     .      SCATWID,            ! HWHM of scattering after foil [degrees]     
     .      SIGMAG,             ! SQRT(2) * width of Gaussian scattering 
     .      SIGMAL,             ! width of Lorentzian scattering after foil
     .      LSIGMAL
        INTEGER*4
     .      rest                ! auxiliary variable, only used for fitting   

        REAL*4
     .      paps,               ! postacceleration voltage, only used for fitting
     .      charge,             ! nuclear charge of incident ion [e], only used for fitting      
     .      ea,                 ! energy after paps, only used for fitting
     .      PAPSTOEPQ,          ! ratio of PAPS to EPQ     
     .      aux1,               ! auxiliary variable
     .      aux2,               ! auxiliary variable
     .      aux3,               ! auxiliary variable
     .      aux4,               ! auxiliary variable
     .      aux5,               ! auxiliary variable
     .      aux6,               ! auxiliary variable
     .      aux7,               ! auxiliary variable
     .      auxdefl             ! auxiliary variable

        INTEGER*4
     .      GAMMA,              ! angle for det collim. in xz plane
     .      GAMMAMIN,           ! MAX angle for det collim. in xz plane
     .      GAMMAMAX,           ! MAX angle for det collim. in xz plane
     .      I,J,K,L             ! auxiliary loop variables     

        REAL*4
     .      ERF,                ! error function (recipes.lib)
     .      pwid,               ! angular dispersion probability distribution             
     .      PROBSE,             ! scattering prob. for producing sec. el. on STP-area
     .      PROBMACOR,          ! scattering prob. for producing sec. el. on MACOR-area
     .      PROBST,             ! scattering probability to hit active area
     .      delta1,             ! first horizontal integration limit 
     .      delta2,             ! second horizontal integration limit 
     .      phi1,               ! first vertical integration limit 
     .      phi2,               ! second vertical integration limit
     .      bwg,                ! result of gaussian integration
     .      bwl,                ! result of lorentzian integration     
     .      SWEFF,              ! nuclear defect in solid state detector      
     .      eresdl,             ! total energy after the detector deadlayer [keV]
     .      FWHMTOT,            ! total FWHM of MSS threshold [keV]           
     .      PROBT,              ! prob. for triggering detector
     .      GEOFACP,            ! angular dependence due to reduced effs of det
     .      GEOFAC              ! value of angular dependence due to reduced effs of det

        INTEGER*4
     .      FACT                ! FACTorial (function)

        EXTERNAL
     .      FWHM,               ! subroutine for FWHM in MSS detectors
     .      SCOEF,              ! subroutine for atomic parameters
     .      STOP                ! subroutine for calculating dE/dx


C     set values of fixed parameters
        PARAMETER(
     .      STEP = 0.2,
     &      GEOFAC = 0.0225,     ! geometry factor from proton MSS calibration data
C     ***                          cf. lab book III, p. 225.
     .      UCODE = 2 )

        DATA
     &      GAMMAMIN /-28/,
     &      GAMMAMAX / 28/


c        write(*,*) "zionf = ", zionf
c        write(*,*) "eperm = ", eperm
c        write(*,*) "const1 = ", const1
c        write(*,*) "const2 = ", const2
c        write(*,*) "const3 = ", const3
c        write(*,*) "pf1 = ", pf1
c        write(*,*) "pf2 = ", pf2
c        write(*,*) "ethresh = ", ethresh
c        write(*,*) "fwhmel = ", fwhmel
c        write(*,*) "thick = ", thick
c        write(*,*) "ion = ", ion
c        write(*,*) "defl = ", defl
c        write(*,*) "rde = ", rde
c        write(*,*) "v = ", (v(i),i=1,3)
c        write(*,*) "c = ", (c(i),i=1,3)

c        Get "mion" by "zion" with scoef.f
c        scoef.f needs zion as an integer
c        write(*,*) runner, counter
c        fitmode = 0
c        write(*,*) "fitmode =", fitmode
        if (fitmode .eq. 0) then
            counter=counter+1
            rest = mod(counter, runner-1)
            if (rest .eq. 0) then
                rest = (runner-1)
            end if
c            write(*,*) rest
            etot = brain(rest,13)
c            write(*,*) etot
            paps = brain(rest,4)
            charge = brain(rest,2)
            ea = brain(rest,3)*brain(rest,2)
            papstoepq = paps/(ea/charge)
            papstoepq=papstoepq/2 

            if (rest .le. 57) then
                zionf = 8
                mion = 16
            else if ((rest .ge. 58 ) .and. (rest .le. 68)) then
                zionf = 10
                mion = 20
            else if ((rest .ge. 69 ) .and. (rest .le. 120)) then
                zionf = 12
                mion = 24
            else if ((rest .ge. 121 ) .and. (rest .le. 219)) then
                zionf = 14
                mion = 28
            else if ((rest .ge. 220 ) .and. (rest .le. 306)) then
                zionf = 26
                mion = 56
            end if
            eperm=etot/mion
        end if

        if (fitmode .eq. 2) then
            counter=counter+1
            rest = mod(counter, runner-1)
            if (rest .eq. 0) then
                rest = (runner-1)
            end if
c            write(*,*) rest
            etot = brain(rest,13)
c            write(*,*) etot
            paps = brain(rest,4)
            charge = brain(rest,2)
            ea = brain(rest,3)*brain(rest,2)
            papstoepq = paps/(ea/charge)
            papstoepq=papstoepq/2 

            if (rest .le. 57) then
                zionf = 8
                mion = 16
                defl = CONST3
            else if ((rest .ge. 58 ) .and. (rest .le. 144)) then
                zionf = 26
                mion = 56
            end if
            eperm=etot/mion
        end if


        if (fitmode .eq. 3) then
            counter=counter+1
            rest = mod(counter, runner-1)
            if (rest .eq. 0) then
                rest = (runner-1)
            end if
c            write(*,*) rest
            etot = brain(rest,13)
c            write(*,*) etot
            paps = brain(rest,4)
            charge = brain(rest,2)
            ea = brain(rest,3)*brain(rest,2)
            papstoepq = paps/(ea/charge)
            papstoepq=papstoepq/2 

            if (rest .le. 57) then
                zionf = 8
                mion = 16
                defl = CONST3
            else if ((rest .ge. 58 ) .and. (rest .le. 109)) then
                zionf = 12
                mion = 24
            end if
            eperm=etot/mion
        end if

        if (fitmode .eq. 4) then
            counter=counter+1
            rest = mod(counter, runner-1)
            if (rest .eq. 0) then
                rest = (runner-1)
            end if
c            write(*,*) rest
            etot = brain(rest,13)
c            write(*,*) etot
            paps = brain(rest,4)
            charge = brain(rest,2)
            ea = brain(rest,3)*brain(rest,2)
            papstoepq = paps/(ea/charge)
            papstoepq=papstoepq/2 

            if (rest .le. 57) then
                zionf = 8
                mion = 16
                defl = CONST3
            else if ((rest .ge. 58 ) .and. (rest .le. 68)) then
                zionf = 10
                mion = 20
            end if
            eperm=etot/mion
        end if

        ZION=int(ZIONF)        
        CALL SCOEF(ZION,X(1),MION,X(2),X(3),X(4),X(5),X(6),XX)
c        mion=mionf
c        write(*,*) "mion = ", mion
        ETOT = EPERM * MION
c        write(*,*) "etot = ", etot

c        subtract energy loss in foil
c        EFOIL = ELOSS( ETOT, ZION, MION, THICK, STEP )
c        ETOTF = ETOT - EFOIL     
        call elosscf(zion,mion,etot,((thick/2.2661)*100),1.,etotf)
        etotf=etot-(etot-etotf)*CONST3
c        write(*,*) "etotf = ",etotf
c        write(*,*) etot, etotf, etot-etotf, etotf/etot
        EPERMF = ETOTF / MION

c        find mean number of electrons ejected from carbon foil,
c        assume it to be proportional to dE/dx after foil
c        ZTARG = 6
c        CALL STOP( ZION, MION, ZTARG, ETOTF, DEDX, X, UCODE )
c        SE1 = CONST1 * (DEDX * 22.661) !stopping in eV/A
        call dedxcf(zion,mion,etotf,dedx) ! here dedx is in eV/A
        SE1 = CONST1 * DEDX * DEDXCERR
c        write(*,*) "dedx = ", dedx
c        write(*,*) "se1 = ", se1


c        find probability for these to trigger start MCP,
c        assuming them to be Poisson-distributed.
c        German: Eigentlich sollte hier folgendes stehen:
c        English: Actually prob1 resultung from poisson distribution is:
c        PROB1 = 1.-exp(-PF1*SE1)
c        German: Robert hat aber durch Messungen eine wesentlich bessere 
c        analytische Darstellung gefunden.
c        English: By measurements Robert found an analytical functions that 
c        fits much better
c        *** New expression for FSR efficiency: PF1 is Failure Probability of Start MCP
        PROB1 = (1-(1+SE1)*EXP(-SE1))*(1-PF1**SE1)
c        write(*,*) "prob1 = ", prob1
c        *** (1-(1+SE1)*EXP(-SE1)) is probability that at least one sec. el. will hit
c        *** Start MCP assuming Poisson distribution

c        for the scattering after the foil we assume Lorentzian scattering 
c        above 1.5keV/amu and Gaussian scattering below 0.5keV/amu, 
c        interpolating logarithmically in-between.
        SIGMAG = (0.01745*SCATWID(EPERM,MION,THICK)/1.177)*SIGMAERR
        SIGMAL = (0.01745*SCATWID(EPERM,MION,THICK))*SIGMAERR
c        write(*,*) "etot = ", etot
c        write(*,*) "sigmag = ", sigmag
c        write(*,*) "sigmal = ", sigmal
c        write(*,*) etot, sigmal
c        sigmal=0.01
c        sigmag=0.01

c        do sigmal=0.0,0.3,0.005

c        do lsigmal=0.0,0.3,0.01
c        if (lsigmal .eq. 0.0) then
c            sigmal=0.0001
c        else 
c            sigmal=lsigmal
c        end if

c     *** include dispersion of beam infront of foil (due to deflection system)
c++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c++++ G: Hier erfolgt die Bercksichtigung von verschiedenen papstoepq Werten 
c     in Abh�gigkeit der tats�hlichen Eingangsenergie und der
c     Nachbescheleunigung paps. Die Kalibrationsdaten werden im Geometrieteil
c     geom.f eingelesen und als common-Variablen gespeichert.++++++++++++++++
c++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c++++ E: Calculation of the papstoepq values considering the entrance energy
c     and the PAPS voltage during calibration.
c     The calibration data are read in in the geometry part geom.f and saved
c     as common variables.+++++++++++++++++++++++++++++++++++++++++++++++++++
c++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        
c+++++++Calculation of papstoepq for fitting+++++++++++++++++++++++++++++++++

        paps=0
        charge=0 
        ea=0
        if (fitmode .eq. 1) then
            counter=counter+1
            rest = mod(counter,(runner-1))
            if (rest .eq. 0) then
                rest = (runner-1)
            end if
            paps = brain(rest,4)
            charge = brain(rest,2)
            ea = brain(rest,3)*brain(rest,2)
            papstoepq = paps/(ea/charge)
            papstoepq=papstoepq/2 
c            write(*,*) papstoepq
c            write(*,*) etot, ea, rest, runner, brain(rest,2)
c       G: Ge�dert 18.09.06 nach Nachrechnung der Lab-Bucheintr�e (III,Seite 193 f.)
c       E: Changed 18.09.06 after reading the Lab-Book (III,page 193 f.)
        end if


c+++++++Calculation of papstoepq without fitting++++++++++++++++++++++++++++++ 
c       change papstoepq if necessary
c        paps=24.868179
c        paps=18.
c        charge=1.
c        papstoepq=paps/((eperm*mion)/charge-24.868179)
c        papstoepq=paps/((eperm*mion)/charge)
c        write(*,*) "papstoepq = ", papstoepq
c        papstoepq=18./((eperm*mion)/charge-18.)

c+++++++Include focussing effect of the post acceleration voltage+++++++++++++        
        aux2 = papstoepq
        if (papstoepq .eq. 0) then
            aux1 = 0
            auxdefl=defl
        end if        
c       Ge�dert 18.09.06 nach Nachrechnung der Lab-Bucheintr�e (III,Seite 193 f.)        	
        if (papstoepq .ne. 0) then
            aux1 = atan(-(tan(defl))*(aux2/(sqrt(1+2*aux2)-(1+2*aux2))))
            auxdefl = atan(-(tan(defl))*(aux2
     .                /(sqrt(1+2*aux2)-(1+2*aux2))))
        end if
c        write(*,*) "aux1 = ",aux1        
        sigmag = sqrt(sigmag**2 + aux1**2) !Add quadratically
c        write(*,*) "sigmag = ", sigmag

C     *** now compute fraction of beam hitting active areas
C     *** begin by determining which detector collimator windows are needed

c++++++Start of MACOR-Integration++++++++++++++++++++++++++++++++++

        AUX1 = 0.
        AUX2 = 0.
        AUX3 = 0.
        AUX4 = 0.

        DO GAMMA = GAMMAMIN,GAMMAMAX  
            DO I = 1,3             !loop over all three detectors
C     *** Decide which deltas and phis to use              
                IF (DELTAWIN(2,GAMMA) .GE. DELTAMACOR(I,1) .AND.
     .              DELTAWIN(1,GAMMA) .LE. DELTAMACOR(I,2) 
     .              ) THEN
                    DELTA1=MAX(DELTAWIN(1,GAMMA),DELTAMACOR(I,1))
                    DELTA2=MIN(DELTAWIN(2,GAMMA),DELTAMACOR(I,2))
                    PHI1=MAX(PHIWIN(1,GAMMA),PHIMACOR(I,1))
                    PHI2=MIN(PHIWIN(2,GAMMA),PHIMACOR(I,2))
                    AUX3 =  0.5*ABS(ERF(delta1/SIGMAG) -
     .                      ERF(delta2/SIGMAG))
                    AUX4 =  PWID(delta1,DELTA2,SIGMAL,PAPSTOEPQ,DEFL)
                    AUX3 =  AUX3 * 0.5*ABS(ERF(PHI1/SIGMAG) -
     .                      ERF(PHI2/SIGMAG))
                    AUX1 = AUX1 + AUX3         
                    AUX4 = AUX4 * PWID(PHI1,PHI2,SIGMAL,PAPSTOEPQ,DEFL)
                    AUX2 = AUX2 + AUX4
                END IF              !(DELTAWIN(2,GAMMA) .GE. ....)
            END DO                 !(I = 1,3)
        END DO                    !(GAMMA = GAMMAMIN,GAMMAMAX)

        IF ( EPERMF .LE. 0.5 ) THEN
            PROBMACOR = AUX1
        ELSE IF ( EPERMF .GE. 1.5 ) THEN
            PROBMACOR = AUX2
        ELSE
            PROBMACOR = AUX1**(1.5-EPERMF) * AUX2**(EPERMF-0.5)
        END IF
c        write(*,*) "probmacor = ", probmacor

c++++++End of MACOR-Integration+++++++++++++++++++++++++++++++++++++      


c++++++Start of stp-Integration+++++++++++++++++++++++++++++++++++++

        AUX1 = 0.
        AUX2 = 0.
        AUX3 = 0.
        AUX4 = 0.

        DO GAMMA = GAMMAMIN,GAMMAMAX  
            DO I = 1,3             !loop over all three detectors
C     *** Decide which deltas and phis to use              
                IF (DELTAWIN(2,GAMMA) .GE. DELTASTP(I,1) .AND.
     .              DELTAWIN(1,GAMMA) .LE. DELTASTP(I,2) 
     .              ) THEN
                    DELTA1=MAX(DELTAWIN(1,GAMMA),DELTASTP(I,1))
                    DELTA2=MIN(DELTAWIN(2,GAMMA),DELTASTP(I,2))
                    PHI1=MAX(PHIWIN(1,GAMMA),PHISTP(I,1))
                    PHI2=MIN(PHIWIN(2,GAMMA),PHISTP(I,2))
                    AUX3 =  0.5*ABS(ERF(delta1/SIGMAG) -
     .                      ERF(delta2/SIGMAG))
                    AUX4 =  PWID(delta1,DELTA2,SIGMAL,PAPSTOEPQ,DEFL)
                    AUX3 =  AUX3 * 0.5*ABS(ERF(PHI1/SIGMAG) -
     .                      ERF(PHI2/SIGMAG))
                    AUX1 = AUX1 + AUX3         
                    AUX4 = AUX4 * PWID(PHI1,PHI2,SIGMAL,PAPSTOEPQ,DEFL)
                    AUX2 = AUX2 + AUX4
                END IF              !(DELTAWIN(2,GAMMA) .GE. ....)
            END DO                 !(I = 1,3)
        END DO                    !(GAMMA = GAMMAMIN,GAMMAMAX)

        IF ( EPERMF .LE. 0.5 ) THEN
            PROBSE = AUX1
        ELSE IF ( EPERMF .GE. 1.5 ) THEN
            PROBSE = AUX2
        ELSE
            PROBSE = AUX1**(1.5-EPERMF) * AUX2**(EPERMF-0.5)
        END IF
c        write(*,*) "probse = ", probse

c++++++End of stp-Integration+++++++++++++++++++++++++++++++++++++++

c++++++Start of ssd-Integration+++++++++++++++++++++++++++++++++++++    
C     *** Now find fraction of ions hitting TCR active area of detector  
        AUX1 = 0.
        AUX2 = 0.
        AUX3 = 0.
        AUX4 = 0.

        DO GAMMA = GAMMAMIN,GAMMAMAX !loop over relevant gammas
            DO I = 1,3             !loop over all three detectors
C     *** Decide which deltas and phis to use              
                IF (DELTAWIN(2,GAMMA) .GE. DELTASSD(I,1) .AND.
     .              DELTAWIN(1,GAMMA) .LE. DELTASSD(I,2)) THEN
                    DELTA1=MAX(DELTAWIN(1,GAMMA),DELTASSD(I,1))
                    DELTA2=MIN(DELTAWIN(2,GAMMA),DELTASSD(I,2))
                    PHI1=MAX(PHIWIN(1,GAMMA),PHISSD(I,1))
                    PHI2=MIN(PHIWIN(2,GAMMA),PHISSD(I,2))
                    AUX3 =  0.5*ABS(ERF(delta1/SIGMAG) -
     .                      ERF(delta2/SIGMAG))
                    AUX4 =  PWID(delta1,DELTA2,SIGMAL,PAPSTOEPQ,DEFL)
                    AUX3 =  AUX3 * 0.5*ABS(ERF(PHI1/SIGMAG) -
     .                      ERF(PHI2/SIGMAG))
                    AUX1 = AUX1 + AUX3
                    AUX4 = AUX4 * PWID(PHI1,PHI2,SIGMAL,PAPSTOEPQ,DEFL)
                    AUX2 = AUX2 + AUX4
                END IF              !(DELTAWIN(2,GAMMA).GE. ...)
            END DO                 !(I = 1,3)
        END DO                    !(GAMMA = GAMMAMIN,GAMMAMAX)


        IF ( EPERMF .LE. 0.5 ) THEN
            PROBST = AUX1
        ELSE IF ( EPERMF .GE. 1.5 ) THEN
            PROBST = AUX2
        ELSE
            PROBST = AUX1**(1.5-EPERMF) * AUX2**(EPERMF-0.5)
        END IF 

c        write(*,*) "probst = ", probst

c++++++End of ssd-Integration+++++++++++++++++++++++++++++++++++++++


c******Start of comparing stp-Integration*********************************

c        aux1=0.0
c        aux2=0.0
c        bwg=0.0
c        bwl=0.0
c        do i=1,3      
c            call integrationconv(stpi(i,1,1),stpi(i,1,2),stpi(i,1,3),
c     .                 stpi(i,2,1),stpi(i,2,2),stpi(i,2,3),
c     .                 stpi(i,3,1),stpi(i,3,2),stpi(i,3,3),
c     .                 stpi(i,4,1),stpi(i,4,2),stpi(i,4,3),
c     .                 c(1),c(2),c(3),v(1),v(2),v(3),
c     .                 sigmal,sigmag,defl,bwl,bwg)
c            aux1=aux1+bwg
c            aux2=aux2+bwl
c        end do


c        IF ( EPERMF .LE. 0.5 ) THEN
c            PROBSE = AUX1
c        ELSE IF ( EPERMF .GE. 1.5 ) THEN
c            PROBSE = AUX2
c        ELSE
c            PROBSE = AUX1**(1.5-EPERMF) * AUX2**(EPERMF-0.5)
c        END IF

c*****End of comparing stp-Integration************************************

c*****Start of comparing ssd-Integration**********************************

c        aux5=0.0
c        aux6=0.0
c        aux7=0.0
c        bwg=0.0
c        bwl=0.0
c        do i=1,3
c           call integrationconv(ssdi(i,1,1),ssdi(i,1,2),ssdi(i,1,3),
c     .                 ssdi(i,2,1),ssdi(i,2,2),ssdi(i,2,3),
c     .                 ssdi(i,3,1),ssdi(i,3,2),ssdi(i,3,3),
c     .                 ssdi(i,4,1),ssdi(i,4,2),ssdi(i,4,3),
c     .                 c(1),c(2),c(3),v(1),v(2),v(3),
c     .                 sigmal,sigmag,defl,bwl,bwg)
c           aux5=aux5+bwg
c           aux6=aux6+bwl

c        end do

c      IF ( EPERMF .LE. 0.5 ) THEN
c         PROBST = AUX5
c      ELSE IF ( EPERMF .GE. 1.5 ) THEN
c         PROBST = AUX6
c      ELSE
c         PROBST = AUX5**(1.5-EPERMF) * AUX6**(EPERMF-0.5)
c      END IF 
c*****End of comparing ssd-Integration************************************      

c Die folgende Integration wurde zu Testzwecken gebaut
c        aux5=0.0
c        aux6=0.0
cc        aux7=0.0
c        bwg=0.0
c        bwl=0.0
c        do i=1,3
c           call integrationconv2(ssdi(i,1,1),ssdi(i,1,2),ssdi(i,1,3),
c     .                 ssdi(i,2,1),ssdi(i,2,2),ssdi(i,2,3),
c     .                 ssdi(i,3,1),ssdi(i,3,2),ssdi(i,3,3),
c     .                 ssdi(i,4,1),ssdi(i,4,2),ssdi(i,4,3),
c     .                 c(1),c(2),c(3),v(1),v(2),v(3),
c     .                 sigmal,sigmag,defl,bwl,bwg)
c           aux5=aux5+bwg
c           aux6=aux6+bwl
c
c        end do
c
c      IF ( EPERMF .LE. 0.5 ) THEN
c         PROBST = AUX5
c         aux7 = AUX5
c      ELSE IF ( EPERMF .GE. 1.5 ) THEN
c         PROBST = AUX6
cc         aux7 = AUX6
c      ELSE
c         PROBST = AUX5**(1.5-EPERMF) * AUX6**(EPERMF-0.5)
cc         aux7 = AUX5**(1.5-EPERMF) * AUX6**(EPERMF-0.5)
c      END IF 
c      write(*,*) "VORHER =", sigmal,defl, probst, probse
        call geomforfit(sigmal,auxdefl,probst,probse)
c       write(*,*) "NACHHER =",sigmal,defl, probst, probse

c        if (probst .gt. 1.0) then
c            probst=1.0
c        end if 
c        if (probse .gt. 1.0) then
c            probse=1.0
c        end if 

c        if (defl .eq. 0.0) then
c            if (sigmal .eq. 0.0001) then
c                write(*,*) "0.0  0.0", probst, probse
c            else 
c                write(*,*) sigmal, defl, probst, probse
c            end if
c        else if  (defl .gt. 0.0) then
c            if (sigmal .eq. 0.0001) then
c                write(*,*) "0.0", defl, probst, probse
c            else 
c               write(*,*) sigmal,defl, probst, probse
c            end if
c        end if
c      write(*,*) sigmal,"  ",sigmag,"  ",aux7

c  Ende der Testintegration
c        end do

c*****Check if everything is allright*************************************
c       do j=1,3
c            do k=1,4
c                write(*,*) (stpi(j,k,i),i=1,3)
c                write(*,*) (ssdi(j,k,i),i=1,3)
c            end do
c       end do
***************************************************************************

C     find mean number of electrons ejected from MSS detector,
C     assume it proportional to dE/dx of gold, scale it to be
C     of the same order of magnitude as for carbon

c        ZTARG = 14
c        CALL STOP( ZION, MION, ZTARG, ETOTF, DEDX, X, UCODE )
c        SE2 = CONST2 * (DEDX*23.29) !stopping in eV/A
c        write(*,*) eperm*mion, dedx
        call dedxdl(zion,mion,etotf,dedx) !stopping dedx is in eV/A already
        SE2 = CONST2 * DEDX *DEDXSIERR
c        write(*,*) eperm*mion, dedx
c        write(*,*) "dedx = ", dedx
c        write(*,*) "se2 = ", se2
        call dedxmacor(zion,etotf,dedx)
c        SE3 = CONST3 * DEDX
c        write(*,*) "dedx = ", dedx
c        write(*,*) "se1 = ", se1

c     find probability of these to trigger stop MCP, 
c     assuming them to be Poisson-distributed 

c        PROB2 = PROBMACOR*(1.-exp(-PF2*SE2)) 
cc     .        + (PROBMACOR-PROBST)*(1.-exp(-PF2*SE3))
        PROB2 = PROBSE*(1-(1+SE2)*EXP(-SE2))*(1-PF2**SE2)
c        write(*,*) eperm, probse, probmacor,
c     .   PROBSE*(1-(1+SE2)*EXP(-SE2))*(1-PF2**SE2),
c     .   PROBMACOR*(1-(1+SE2)*EXP(-SE2))*(1-PF2**SE2)
c        write(*,*) "prob2 = ", prob2
c     *** Caution: above may need to be changed

c     find probability for ion to trigger the detector

c        EMEAS = SWEFF( EPERMF, MION ) * ETOTF 
c        call deadlayer(zion,mion,etotf,400.,1.,eresdl)
c        write(*,*) "eresdl = ", eresdl
c        call sweffsrim(zion,eresdl,emeas)
c        write(*,*) "emeas = ", emeas
c        emeas_de=emeas*eresdl/100.
c        write(*,*) "emeas_de", emeas
c        write(*,*) zion, epermf
        call (phd(zion,epermf,emeas))*PHDERR

c        emeas_mi=emeas*etotf/100.
c        write(*,*) etot, emeas_de, emeas_mi
        emeas=emeas*etotf/100.
c       emeas_corr ist die gemessene Energie mit Korrekturfaktor
c       bestimmt aus Larsens gefitteten Positionen (26.02.2007)
c       siehe Laborbuch (2007-) Seite 8
        emeas_corr=emeas/1.137-0.4329
c        write(*,*) "emeas = ", emeas        

        CALL FWHM_ERR( ETOTF, MION, FWHMEL, FWHMTOT, FWHMNERR )
c        PROBT = ( ERF( 2E0*SQRT(0.5)*(EMEAS-ETHRESH)/FWHMTOT )
c     .          + 1E0 ) / 2E0
        PROBT = ( ERF( 2E0*SQRT(0.5)*(EMEAS_CORR-ETHRESH)/FWHMTOT )
     .          + 1E0 ) / 2E0

c        write(*,*) "probt = ",probt
C        combine      
        PROB3 = PROBST * PROBT
c        write(*,*) "prob3 = ", prob3        


c +++++ For comparison with calibration and flight data
c       calculation of E- and T-channels+++++++++++++++++++++++++++

        tau=(((mion*1.66053886e-27/(2*etotf/(6.24150974e15)))**0.5)
     .      *0.1)*1e9
c        write(*,*) "tau = ", tau
        tauchannelfloat=tau*1023./200. 
c        write(*,*) "tauchannelfloat = ", tauchannelfloat        
        tauchannel = int(tauchannelfloat)
c        write(*,*) "tauchannel = ", tauchannel
        echannelfloat=emeas*255./610.78
c        write(*,*) "echannelfloat = ", echannelfloat        
        echannel = int(echannelfloat)
c        write(*,*) "echannel = ", echannel

c        sigmal=1.
c        do while (sigmal .ge. 0.0001)
c            call integrationconv(10.,-0.75,4.,
c     .                 10.,0.75,4.,
c     .                 10.,0.75,-8.,
c     .                 10.,-0.75,-8.,
c     .                 0.,0.,0.,5.,0.,0.,
c     .                 sigmaL,sigmal,1.,bwl,bwg)
c        write(*,*) sigmal, bwl,bwg
c        sigmal=sigmal*0.9
c        end do

c+++++++ Resulting probabilities ++++++++++++++++++++++++++++++++++

c        STARTsignal probability
c        write(*,*) PROB1

c        STOPsignal probability
c        write(*,*) PROB2

c        ENERGYmeasurement probability
c        write(*,*) PROB3

c        DCR/FSR
c        RESPROB=PROB2
c        write(*,*) etot, RESPROB 

c        TCR/DCR
c        RESPROB=PROB3*(1-(1+SE2)*EXP(-SE2))*(1-PF2**SE2)/PROB2
c        RESPROB=PROB3/PROBSE
c        write(*,*) eperm*mion, RESPROB

c        TCR/FSR
c        RESPROB=PROB3*(1.-exp(-PF2*SE2))*PROB1
c        RESPROB=PROB3*(1-(1+SE2)*EXP(-SE2))*(1-PF2**SE2)
c        write(*,*) eperm*mion, RESPROB

c        TCR
        RESPROB=PROB3*(1-(1+SE2)*EXP(-SE2))*(1-PF2**SE2)*PROB1

c        E-Channel-Fit
c        RESPROB=echannelfloat

c        Tau-Channel-Fit
c        RESPROB=tauchannelfloat


c        resprob=prob1+prob2+prob3
c        write(*,*) prob1, prob2*prob1, 
c     .  prob1*probt*probst*(1.-exp(-PF2*SE2))
        fsrave=fsrave+prob1
        dcrave=dcrave+prob1*prob2
        tcrave=tcrave+prob1*probt*probst*(1.-exp(-PF2*SE2))

c        write(*,*) fsrave, dcrave, tcrave
c        write(*,*) resprob
        END

C     *********************************************************************

      SUBROUTINE VECTOR(AUXV,MATRIX,COMPONENT)

C     *** fill auxiliary vector auxv with component COMPONENT of MATRIX

      IMPLICIT NONE

      REAL*4
     &     AUXV(3),MATRIX(3,3)

      INTEGER*4
     &     COMPONENT , I

      DO I = 1,3
         AUXV(I) = MATRIX(COMPONENT,I)
      END DO

      RETURN
      END
C     *********************************************************************

      SUBROUTINE VECTORS(AUXV1,AUXV2,MATRIX,DET,A,B)

C     *** fill auxiliary vectorS auxv1 AND 2 with components DET, A, B of MATRIX

      IMPLICIT NONE

      REAL*4
     &     AUXV1(3),AUXV2(3),MATRIX(3,4,3)

      INTEGER*4
     &     DET,A,B, I

      DO I = 1,3
         AUXV1(I) = MATRIX(DET,A,I)
         AUXV2(I) = MATRIX(DET,B,I)
      END DO

      RETURN
      END
C     *********************************************************************

      SUBROUTINE WINVECS(AUXV1,AUXV2,MATRIX,GAMMA,A,B)

C     *** fill auxiliary vectorS auxv1 AND 2 with components GAMMA, A, B of MATRIX

      IMPLICIT NONE

      REAL*4
     &     AUXV1(3),AUXV2(3),MATRIX(3,4,-33:32)

      INTEGER*4
     &     GAMMA,A,B, I

      DO I = 1,3
         AUXV1(I) = MATRIX(I,A,GAMMA)
         AUXV2(I) = MATRIX(I,B,GAMMA)
      END DO

      RETURN
      END
C     *********************************************************************

      SUBROUTINE VECSUB(VECTOR1, VECTOR2, RESULT)

C     *** subtract VECTOR2 from VECTOR1: RESULT = VECTOR1 - VECTOR2

      IMPLICIT NONE

      REAL*4
     &     VECTOR1(3), VECTOR2(3), RESULT(3)

      INTEGER*4
     &     I

      DO I = 1,3
         RESULT(I) = VECTOR1(I)-VECTOR2(I)
      END DO

      RETURN
      END
C     *********************************************************************

      SUBROUTINE VECMUL(VECTOR, k, RESULT)

C     *** Multiply VECTOR with scalar: RESULT = k*VECTOR

      IMPLICIT NONE

      REAL*4
     &     VECTOR(3),k, RESULT(3)

      INTEGER*4
     &     I

      DO I = 1,3
         RESULT(I) = k*VECTOR(I)
      END DO

      RETURN
      END


C     *********************************************************************

      SUBROUTINE VECADD(VECTOR1, VECTOR2, RESULT)

C     *** add VECTOR2 to VECTOR1: RESULT = VECTOR1 + VECTOR2

      IMPLICIT NONE

      REAL*4
     &     VECTOR1(3), VECTOR2(3), RESULT(3)

      INTEGER*4
     &     I

      DO I = 1,3
         RESULT(I) = VECTOR1(I)+VECTOR2(I)
      END DO

      RETURN
      END

C *********************************************************************

      SUBROUTINE VECPUT(VECTOR1, RESULT)

C     *** put vector into result: RESULT = VECTOR1 

      IMPLICIT NONE

      REAL*4
     &     VECTOR1(3),  RESULT(3)

      INTEGER*4
     &     I

      DO I = 1,3
         RESULT(I) = VECTOR1(I)
      END DO

      RETURN
      END

C     ********************************************************************

      SUBROUTINE SCALPR(VECTOR1,VECTOR2,RESULT)

C     *** compute the scalar product of VECTOR1 and VECTOR2

      IMPLICIT NONE

      REAL*4
     &     VECTOR1(3), VECTOR2(3), RESULT

      INTEGER*4
     &     I


      RESULT = 0.
      DO I = 1,3
         RESULT = RESULT + VECTOR1(I)*VECTOR2(I)
      END DO

      RETURN
      END

C     *********************************************************************

      SUBROUTINE VCROSS(VECTOR1,VECTOR2,RESULT)

C     *** Compute the cross product RESULT = VECTOR1 X VECTOR2

      IMPLICIT NONE

      REAL*4
     &     VECTOR1(3),VECTOR2(3),RESULT(3)

      RESULT(1) = VECTOR1(2)*VECTOR2(3)-VECTOR1(3)*VECTOR2(2) 
      RESULT(2) = VECTOR1(3)*VECTOR2(1)-VECTOR1(1)*VECTOR2(3) 
      RESULT(3) = VECTOR1(1)*VECTOR2(2)-VECTOR1(2)*VECTOR2(1) 

      RETURN
      END

C     *********************************************************************

      INTEGER*4 FUNCTION FACT(I)

C     *** returns the factorial (use only for small numbers, this doesn't *
C     *** store and compute efficiently). *********************************

      IMPLICIT NONE

      INTEGER*4 
     &     I,J


C     *********************************************************************

      FACT = 1
      DO J = 1,I
         FACT = J  *FACT
      END DO

      RETURN
      END


