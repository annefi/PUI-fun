        FUNCTION ran3(idum)
c            Returns a uniform random deviate between 0.0 and 1.0. Set idum to any negative value
c            to initialize or reinitialize the sequence.
        INTEGER idum
        INTEGER MBIG,MSEED,MZ
C        REAL MBIG,MSEED,MZ
        REAL ran3,FAC
        PARAMETER (MBIG=1000000000,MSEED=161803398,MZ=0,FAC=1./MBIG)
C        PARAMETER (MBIG=4000000.,MSEED=1618033.,MZ=0.,FAC=1./MBIG)
c            According to Knuth, any large mbig, and any smaller (but still large) mseed can be sub-
c            stituted for the above values.
        INTEGER i,iff,ii,inext,inextp,k
        INTEGER mj,mk,ma(55)                    !The value 55 is special and should not be modified; see
C        REAL mj,mk,ma(55)                      !Knuth.
        SAVE iff,inext,inextp,ma
        DATA iff /0/
        if(idum.lt.0.or.iff.eq.0)then
            iff=1                               !Initialization.
            mj=abs(MSEED-abs(idum))             !Initialize ma(55) using the seed idum and the large num-
            mj=mod(mj,MBIG)                     !ber mseed.
            ma(55)=mj
            mk=1
            do i=1,54                           !Now initialize the rest of the table,
                ii=mod(21*i,55)                 !in a slightly random order,
                ma(ii)=mk                       !with numbers that are not especially random.
                mk=mj-mk
                if(mk.lt.MZ)mk=mk+MBIG
                mj=ma(ii)
            enddo
            do k=1,4                            !We randomize them by "warming up the generator."
                do i=1,55
                    ma(i)=ma(i)-ma(1+mod(i+30,55))
                    if(ma(i).lt.MZ)ma(i)=ma(i)+MBIG
                enddo
            enddo
            inext=0                             !Prepare indices for our first generated number.
            inextp=31                           !The constant 31 is special; see Knuth.
            idum=1
        endif
        inext=inext+1                           !Here is where we start, except on initialization. Increment
        if(inext.eq.56)inext=1                  !inext, wrapping around 56 to 1.
        inextp=inextp+1                         !Ditto for inextp.
        if(inextp.eq.56)inextp=1
        mj=ma(inext)-ma(inextp)                 !Now generate a new random number subtractively.
        if(mj.lt.MZ)mj=mj+MBIG                  !Be sure that it is in range.

        ma(inext)=mj                            !Store it,
        ran3=mj*FAC                             !and output the derived uniform deviate.
        return
        END
