; new_axis.pro -- plots in color somehow
; Received from Nathan Schwandron, 25Jan00
;==================================================
pro new_axis,xax,yax,xtickv,xtickname,ytickv,ytickname,blk = blk, $
    xtit = xtit, ytit = ytit
;==================================================

if not keyword_set(blk) then blk = 0

nx = n_elements(xax) & ny = n_elements(yax)
oplot,[xax[0],xax[nx-1]],[yax[0],yax[0]],color = blk
oplot,[xax[0],xax[0]],[yax[0],yax[ny-1]], color = blk
oplot,[xax[nx-1],xax[nx-1]],[yax[0],yax[ny-1]],color = blk 
oplot,[xax[0],xax[nx-1]],[yax[ny-1],yax[ny-1]],color = blk

nticx = n_elements(xtickv) & nticy = n_elements(ytickv)
dytic = (yax[ny-1]-yax[0])/70.0

for i=0,nticx-1 do begin
  oplot,[xtickv[i],xtickv[i]],[yax[0],yax[0]+dytic],/noclip,color = blk
  xyouts,xtickv[i],yax[0],'!C' + xtickname[i],/noclip,charsize = 1.5,color = blk
end
if (keyword_set(xtit)) then begin
 xyouts,(xax[0]+xax[nx-1])/2.0,yax[0],'!C!C'+xtit,charsize = 1.5,color = blk
end

dxtic = (xax[nx-1]-xax[0])/70.0
for i=0,nticy-1 do begin
  oplot,[xax[0],xax[0]+dxtic],[ytickv[i],ytickv[i]],/noclip,color = blk
  xyouts,xax[0],ytickv[i], ytickname[i]+' ',/noclip,charsize = 1.5,align=1,color = blk
end

d = convert_coord([xax[0]],[(yax[0]+yax[ny-1])/2.0],/data,/to_device)

if (keyword_set(ytit)) then begin
  xyouts,d[0,0]-3.0*!D.Y_CH_SIZE,d[1,0],ytit,charsize = 1.5,$
    orientation = 90,/device,color = blk
end

return
end
