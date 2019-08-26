       SUBROUTINE SCOEF(Z1,MM1,M1,M2,RHO,ATRHO,VFERMI,LFCTR,PCOEF)
c
       IMPLICIT NONE
       REAL*4 A,MM1,M1,M2,RHO,ATRHO,VFERMI,LFCTR,PCOEF,BUF(8,100)
       INTEGER Z,Z1,I,J,N
       DIMENSION PCOEF(8)
       LOGICAL*1 FOUND, FIRSTCALL /.TRUE./
C
       SAVE BUF,N
C
c       write(*,*) 'scoef called with zion = ', z1
       IF ( FIRSTCALL ) THEN
	  FIRSTCALL = .FALSE.
	  OPEN(20,FILE='SCOEF.DAT',STATUS='OLD')
	  N = 1
	  DO WHILE( .TRUE. )
c             write(*,*)'N= ', n
	     READ(20,*,END=9998)(BUF(I,N),I=1,8)
	     N = N + 1
	  END DO
 9998     CONTINUE
	  N = N - 1
c          write(*,*)'N= ', n
       END IF
C
       A=0
       I=1
       FOUND=.FALSE.
       DO WHILE(A.LE.92 .AND. .NOT.FOUND)
c          write(*,*) 'in scoef.f z1 is: ', z1,' and buf is ',
c     &   buf(1,i),'and nint(buf) is:',nint(BUF(1,I)),'N= ',N
	  IF ( NINT(BUF(1,I)).EQ.Z1 ) THEN
c             write(*,*) 'ok, writing data'
             A = BUF(1,I)
	     MM1 = BUF(2,I)
	     M1 = BUF(3,I)
	     M2 = BUF(4,I)
	     RHO = BUF(5,I)
	     ATRHO = BUF(6,I)
	     VFERMI = BUF(7,I)
	     LFCTR = BUF(8,I)
	     DO J = 1, 8
                PCOEF(J) = BUF(J,I+1)
	     END DO
             FOUND=.TRUE.
	  END IF
	  I=I+2
	  IF ( I.GT.N ) GOTO 9999
       END DO
       ATRHO=ATRHO*1E22
       RETURN
 9999  STOP ' REQUESTED ELEMENT NOT IN SCOEF.DAT '
       END
