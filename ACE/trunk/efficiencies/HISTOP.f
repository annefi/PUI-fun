       SUBROUTINE HISTOP(Z1,M1,Z2,M2,E,EE,VFERMI,LFCTR,PCOEF,SE)
c
       IMPLICIT REAL*4(A-Z)
       INTEGER I,Z1,Z2
       DIMENSION PCOEF(5)
c
       YRMIN=0.13
       VRMIN=1.0
       V=SQRT(E/25.)/VFERMI
       IF (V.LT.1) THEN
          VR=(3*VFERMI/4)*(1+(2*V*V/3)-V**4/15)
       ELSE
          VR=V*VFERMI*(1+1/(5*V*V))
       END IF
       YR=AMAX1(YRMIN,VR/Z1**.6667)
       YR=AMAX1(YR,VRMIN/Z1**.6667)
       A=-.803*YR**0.3+1.3167*YR**0.6+.38157*YR+.008983*YR*YR
       Q=AMIN1(1.,AMAX1(0.,1.-EXP(-AMIN1(A,50.))))
       B=(AMIN1(0.43,AMAX1(.32,.12+.025*Z1)))/Z1**.3333
       L0=(.8-Q*(AMIN1(1.2,0.6+Z1/30.)))/Z1**.3333
       IF (Q.LT.0.2) THEN
          L1=0
       ELSE IF (Q.LT.AMAX1(0.,.9-.025*Z1)) THEN
          Q1=0.2
          L1=B*(Q-.2)/ABS(AMAX1(0.,.9-.025*Z1)-.2000001)
       ELSE IF (Q.LT.AMAX1(0.,1.-.025*AMIN1(16.,1.*Z1))) THEN
          L1=B
       ELSE
          L1=B*(1.-Q)/(.025*AMIN1(16.,1.*Z1))
       END IF
       L=AMAX1(L1,L0*LFCTR)
       ZETA=Q+(1./(2.*VFERMI**2))*(1.-Q)*ALOG(1+(4*L*VFERMI/1.919)**2)
       A=-(7.6-AMAX1(0.,ALOG(E)))**2
       ZETA=ZETA*(1.+(1./Z1**2)*(.18+.0015*Z2)*EXP(A))
       IF (YR.GT.AMAX1(YRMIN,VRMIN/Z1**.6667)) THEN
          CALL PSTOP(Z1,M1,Z2,M2,E,PCOEF,SP)
          SE=SP*(ZETA*Z1)**2
       ELSE
          VRMIN=AMAX1(VRMIN,YRMIN*Z1**.6667)
          VMIN=.5*(VRMIN+SQRT(AMAX1(0.,VRMIN**2-0.8*VFERMI**2)))
          EEE=25*VMIN**2
          CALL PSTOP(Z1,M1,Z2,M2,EEE,PCOEF,SP)
          POWER=0.5
          IF ((Z2.EQ.6).OR.(((Z2.EQ.14).OR.(Z2.EQ.32)).AND.(Z1.LE.19)))
     1       POWER=0.375
          SE=(SP*(ZETA*Z1)**2)*(E/EEE)**POWER
       END IF
       RETURN
       END
