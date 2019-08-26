       subroutine ftos(x,a,b,c,y) 

c    Macht aus dem Float x ein String a,b oder c
c    y=1 --> a wird beschrieben (String hat die Länge 1)
c    y=2 --> b wird beschrieben (String hat die Länge 2)
c    y=3 --> c wird beschrieben (String hat die Länge 3)

c    Gives the string a,b or c of the float x
c    y=1 --> output is written in string a (length of string is 1)
c    y=2 --> output is written in string b (length of string is 2)
c    y=3 --> output is written in string c (length of string is 3)

       integer
     .  x,y
     
       character*1
     .  a
          
       character*2
     .  b
     
       character*3
     .  c
     
          
       OPEN( UNIT=2,FILE=
     &'/tmp/buffer')
	 write(2,*) x
       CLOSE( UNIT=2 )
       
       
        if (y .eq. 1) then
         
       OPEN( UNIT=2,FILE=
     &'/tmp/buffer')
	 read(2,*,END=400) a
400      continue
       CLOSE( UNIT=2 )
       
       end if        
       
       
       if (y .eq. 2) then
         
       OPEN( UNIT=2,FILE=
     &'/tmp/buffer')
	 read(2,*,END=500) b
500      continue
       CLOSE( UNIT=2 )
       
       end if
       
         
       if (y .eq. 3) then
         
       OPEN( UNIT=2,FILE=
     &'/tmp/buffer')
	 read(2,*,END=600) c
600      continue
       CLOSE( UNIT=2 )
       
       end if
       
       
        RETURN
        END