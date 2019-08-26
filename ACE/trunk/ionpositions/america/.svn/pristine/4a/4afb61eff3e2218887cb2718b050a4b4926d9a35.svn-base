; from Nathan Schwandron, Jan00
pro open_postform,tit=tit,bw=bw,co=co

if not keyword_set(tit) then tit = 'temp.eps'

set_plot,'ps'
device,file=tit,/ENCAPS,/portrait

if keyword_set(bw) then loadct,0
if keyword_set(co) then begin
   device,bits_per_pixel=8,/color
   loadct,27 
end

!P.CHARTHICK = 2
!P.CHARSIZE = 1.2
!P.FONT =  0
!P.THICK = 2
!X.THICK = 2
!Y.THICK = 2

return
end

