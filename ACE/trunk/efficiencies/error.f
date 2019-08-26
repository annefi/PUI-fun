        SUBROUTINE error(EPERM,ZION,MION,ION,
     .                  CHARGE,
     .                  C1,C1delta,
     .                  C2,C2delta,
     .                  C3,C3delta,
     .                  PF1,pf1delta,
     .                  PF2,pf2delta,
     .                  ETHRESH,Ethrdelta,
     .                  FWHMEL,FWHMdelta,
     .                  THICK,thickdelta,
     .                  DEFL, defldelta,
     .                  AUXPAR1,AUXPAR2,AUXPAR3,
     .                  fehler,mfehler)

        IMPLICIT NONE

        REAL*4
     .      EPERM,              ! Energy/amu
     .      ZION,               ! Nuclear charge of incident ion [e] (float)
     ,      MION,               ! Mass of the incident ion [amu] (float)
     .      CHARGE,             ! Charge of the incident ion [e]
     .      C1,                 ! Factor to convert etotf in number of sec. el. (carbonfoil)
     .      C1delta(2),         ! Error of Const1
     .      C2,                 ! Factor to convert etotf in number of sec. el. (PIPS-surface)
     .      C2delta(2),         ! Error of Const2
     .      C3,                 ! Factor to convert etotf in number of sec. el. (Macor-surface)
     .      C3delta(2),         ! Error of Const3
     .      PF1,                ! Probability of Failure of MCP 1
     .      pf1delta(2),        ! Error of PF1
     .      PF2,                ! Probability of NON-Failure of MCP 2
     .      pf2delta(2),        ! Error of PF2
     .      ETHRESH,            ! Threshold energy of MSS detector [keV]
     .      Ethrdelta(2),       ! Error of ETHRESH
     .      FWHMEL,             ! Electronic FWHM of MSS threshold [keV]
     .      FWHMdelta(2),       ! Error of FWHMEL
     .      THICK,              ! Foil thickness [microg/squarecm]
     .      thickdelta(2),      ! Error of THICK
     .      DEFL,               ! Angular dispersion in deflection system
     .      defldelta(2),       ! Error of DEFL
     .      bw,
     .      bw1,
     .      FEHLER,             ! Error of the Triple Coincidence Probability
     .      FEHLER1,
     .      FEHLER2,
     .      MFEHLER,            ! Average error of the Triple Coincidence Probability
     .      AUXPAR1(2),
     .      AUXPAR2(2),
     .      AUXPAR3(2)


        CHARACTER*20
     .      ION                 ! element abbreviation for ION

        INTEGER h,i,j,k,l,      ! auxiliary loop variables
     .      dc1,dc2,dc3,dpf1,dpf2,dfwhm,dethr,dthick,
     .      dauxpar1,dauxpar2,dauxpar3, errormode


        call swxeff(bw,eperm,zion,mion,ion,C1,C2,C3,
     .              pf1,pf2,ETHRESH,FWHMEL,thick,0.0,4.,1.,1.,1.)
        errormode = 2
        fehler1=0.
        fehler2=0.
        i=0
        mfehler=0.
        if (errormode .eq. 1) then
         do dc1=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1delta(dc1),C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  1.,1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dc2=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2delta(dc2),C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  1.,1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dpf1=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1delta(dpf1),pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  1.,1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dEthr=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  Ethrdelta(dEthr),FWHMEL,
     .                  thick,0.0,4.,
     .                  1.,1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dFWHM=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMdelta(dFWHM),
     .                  thick,0.0,4.,
     .                  1.,1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dthick=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thickdelta(dthick),0.0,4.,
     .                  1.,1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dauxpar1=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  auxpar1(dauxpar1),1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dauxpar1=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  auxpar1(dauxpar1),1.,1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dauxpar2=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  1.,auxpar2(dauxpar2),1.)
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         do dauxpar3=1,2
           call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1,C2,C3,
     .                  pf1,pf2,
     .                  ETHRESH,FWHMEL,
     .                  thick,0.0,4.,
     .                  1.,1.,auxpar3(dauxpar3))
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if

         end do
         mfehler=mfehler/20.
         fehler=(fehler1+fehler2)/2.
        end if

        if (errormode .eq. 2) then
         do dc1=1,2
          do dc2=1,2
c           do dc3=1,2
            do dpf1=1,2
             do dpf2=1,2
              do dthick=1,2
               do dFWHM=1,2
                do dEthr=1,2
                 do dauxpar1=1,2
                  do dauxpar2=1,2
                   do dauxpar3=1,2
                    i=i+1
                   call swxeff(bw1,eperm,zion,mion,ion,
     .                  C1delta(dc1),C2delta(dc2),C3delta(dc3),
     .                  pf1delta(dpf1),pf2delta(dpf2),
     .                  Ethrdelta(dEthr),FWHMdelta(dFWHM),
     .                  thickdelta(dthick),0.0,4.,
     .                  auxpar1(dauxpar1),
     .                  auxpar2(dauxpar2),
     .                  auxpar3(dauxpar3))
                        mfehler=mfehler+abs(bw1-bw)
                    if ((bw1-bw) .gt. fehler1) then
                        fehler1 = (bw1-bw)
                    end if
                    if ((bw-bw1) .gt. fehler2) then
                        fehler2 = (bw-bw1)
                    end if
                   end do
                  end do
                 end do
                end do
               end do
              end do
             end do
            end do
c           end do
          end do
         end do
        mfehler=mfehler/float(i)
        fehler=(fehler1+fehler2)/2.
        end if
c        write(*,*) eperm, bw, fehler1, fehler2
        RETURN
        END