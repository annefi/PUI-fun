;; ----------------------------------------------------------------------
;; *** SUBROUTINES/FUNCTIONS --- MAIN PROGRAM BELOW ***
;; ----------------------------------------------------------------------
function qual_color, qual_factor, qual_grades, qual_colors
fit_color = qual_colors[0]      ; default to worst

for icolor = 0, n_elements(qual_colors)-1 do begin
  if ( qual_factor le qual_grades[icolor]) then begin
    ;; acceptable comparision with fit
    fit_color = qual_colors[icolor]
  endif
endfor

return, fit_color
end

function array2str, array, fmt

str = ''

for i=0,n_elements(array)-1 do begin
  str += string(format=fmt, array[i]) + ' '
endfor

return, str
end
;; ----------------------------------------------------------------------
;; *** MAIN PROGRAM ***
;; ----------------------------------------------------------------------
; Filename: 
;
; Description:
;   
;
; Author: Jim Raines (jmr)
;
; Method:
;
;   
; Major Modification History
;     Nov2003   jmr   initial coding
;   08Nov2004   jmr   Added fit function display
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   dffile      axlv2_distfunc_*.dat file
; I   nvtfile     axlv2_nvt_*.dat file
; O   dfdata      dist. func. data structure
; O   nvtdata     nvt data structure
; [I] /noread     do not read data (use dfdata and nvtdata)
; [I] tag         text tag for plot name (no spaces)
; [I] ions        array of ions to process, e.g. ions=['He2+','O6+']
pro axlv2_distfunc, dffile=dffile, dfdata=df, $
                    nvtfile=nvtfile, nvtdata=dnvt, $
                    noread=noread, tag=tag, ions=ions

;; set up
thisprog = 'axlv2_distfunc'

;; ----------------------------------------------------------------------
;; ===> configure <===
;; ----------------------------------------------------------------------
;; location of error line as frac. of plot ht.
ERR_LOC_FRAC = 0.66            

;; v/fit_v levels
COMP_VEL_FRAC = [1.,.1,.05]

;; vth/fit_vth level
COMP_VTH_FRAC = [1.,.1,.05]

;; error levels
COMP_ERR_FRAC = [1.,.3,.1]

;; colors (depends on color table)
ct =  27
black  = 0                      ; forced with fix_ct_ends
white  = 1                      ; forced with fix_ct_ends
red    = 158
yellow = 95
green  = 58

;; colors used to describe quality, ordered worst to best
QUAL_COLORS = [red, yellow, green]

;; plot variables
!p.thick = 3.0

;; ----------------------------------------------------------------------
;; read data
;; ----------------------------------------------------------------------
;; read data
if (not keyword_set(noread)) then begin
  restore, file='axlv2_distfunc_template.save'
  df = read_ascii(dffile, template=template, header=h)

  restore, file='axlv2_nvt_template.save'
  nvt = read_ascii(nvtfile, template=template)
endif

;; set up matrix rate array

;; ----------------------------------------------------------------------
;; make uniq arrays
;; ----------------------------------------------------------------------
if (not keyword_set(doyfrs)) then begin
  doyfrs = df.doyfr[uniq(df.doyfr, sort(df.doyfr))]
endif
ndoyfrs = n_elements(doyfrs)

if (not keyword_set(ions)) then begin
  ;; grab list from first edb and first  beginning to keep in file order
  ions = df.ion[where(df.edb eq 2 and df.doyfr eq doyfrs[0])]
endif
nions = n_elements(ions)

eqtab = df.eoq[uniq(df.eoq, sort(df.eoq))]
eqtab = reverse(eqtab)          ; max(step) should be min(eqtab)
nsteps = n_elements(eqtab)

;; not currently used
;; load generic ions for mass and charge values later
;; sw_ions = loadIons_sw()

;;----------------------------------------------------------------------
;; set up plotting stuff
;;----------------------------------------------------------------------
;; set up PS file
file_parse, file=dffile, dir=dir, base=base, ext=ext
;psfile = dir + '/' + base + '.ps'
if (keyword_set(tag)) then begin
    sep='_' 
endif else begin 
    sep=''
    tag=''
endelse
psfile = base + sep + tag + '.ps'
psplt, file=psfile, /color
npp = !p.multi[1]*!p.multi[2]   ; number of plots per page

;; removed !p.multi stuff; set outside of program
;; Some useful settings:
;; 9 plots per page: !p.multi = [0,3,3]
;; 4 plots per page: !p.multi = [0,1,2]
;; 1 plot per page:  !p.multi = 0

;; set up color table
loadct, ct
;; 33 -- blue background
;; 27 -- white background
fix_ct_ends, black=black, white=white

nplot = 1

;;----------------------------------------------------------------------
;; Loop over ions, plotting DF versus EDB and velocity for each timestep
;;----------------------------------------------------------------------
for nion=0,nions-1 do begin
  ;; force a new page at start of ion
  !p.multi[0] = 0

  print, thisprog + ' -I- working on ion = ' + ions[nion]

  ;; convert E/q scale to velocity for this ion
;  ion_parse, ion=ions[nion], elem=elem, state=charge, iso=iso
;  this_ion = where(sw_ions.name eq ions[nion], nwhere)
;  if (nwhere le 0) then begin
;    print, thisprog+' -I- no loadIons data for '+ions[nion]+' at '+doyfr_str
;    goto,next
;  endif
;  mass = sw_ions[this_ion[0]].mass
;  if (iso ne -1.0) then mass = iso  ;; fixes problem in elem. matching above
;  v_edb=438.*sqrt(df.eoq*charge/mass)

  ;; loop over days
  for ndoyfr=0,ndoyfrs-1 do begin

    doyfr = doyfrs[ndoyfr]
    doyfr_str = string(format='(F11.2)',doyfr)
    ;print, thisprog + ' -I- working on doyfr = ' + doyfr_str

    ;; find ion in DF data
    i_df = where( (df.doyfr eq doyfr) and (df.ion eq ions[nion]), ni_df)
    if (ni_df le 0) then begin
      print, thisprog+' -I- no DF data for '+ions[nion]+' at '+doyfr_str
      goto,next
    endif

    ;; find ion in NVT data
    i_nvt = where( (nvt.doyfr eq doyfr) and (nvt.ion eq ions[nion]), ni_nvt)
    ;; WORKAROUND: handle repeated doyfr in data 
    if (n_elements(i_nvt) gt 1) then i_nvt = i_nvt[0]
    if (ni_nvt le 0) then begin
      print, thisprog+' -I- no NVT data for '+ions[nion]+' at '+doyfr_str
      goto,next
    endif
    
    ;; plot df vs. edb
    if (0) then begin
      plot, df.edb[i_df], df.df[i_df],$
            xtitle = 'Deflection Voltage Step',ytitle='A[edb] for '+ions[nion],$
            subtitle='doy = '+doyfr_str
      nplot = nplot + 1
      
      if (fix(nplot)/fix(npp) eq float(nplot)/float(npp)) then begin
        tagplot, line1=tag ,line2='University of Michigan'
        nplot = 1               ; reset
      endif
    endif

    ;; calculate comparisons and form strings
    ;; ------------------------------------------------------------
    ;; --- calculate comparisons
    comp_v = nvt.v[i_nvt]/nvt.fit_v[i_nvt]
    comp_vth = nvt.vth[i_nvt]/nvt.fit_vth[i_nvt]
    comp_n = nvt.n[i_nvt]/nvt.fit_n[i_nvt]

    ;; --- assemble NVT strings (moment, fit and comp) for plot subtitle
    format = '("n=",G9.3," v=",G9.3," vth=",G9.3)'
    mom_nvt_str = 'mom: '+string(format=format, nvt.n[i_nvt], $
                                    nvt.v[i_nvt], nvt.vth[i_nvt])
    fit_nvt_str = 'fit: '+string(format=format, nvt.fit_n[i_nvt],$
                                 nvt.fit_v[i_nvt],nvt.fit_vth[i_nvt])

    format = '("n/fit_n=",G9.3," v/fit_v=",G9.3," vth/fit_vth=",G9.3)'
    comp_nvt_str = 'comp: '+string(format=format, comp_n,$
                                 comp_v, comp_vth)

    ;; plot versus velocity
    ;; ---------------------------------------------------------
    plot, df.v[i_df], df.df[i_df],$
          xtitle = 'Velocity (km/s)     DOY='+doyfr_str,$
          ytitle='A[edb] for '+ions[nion],$
          subtitle= mom_nvt_str + '!C' + comp_nvt_str
    nplot = nplot + 1

    ;; add center lines to actual and fit distribution function,
    ;; colored by quality
    ;; ---------------------------------------------------------
    ;; --- determine color
    qual_factor = abs(1 - comp_v)
    fit_color = qual_color(qual_factor, COMP_VEL_FRAC, QUAL_COLORS)

    ;; --- draw center lines
    ;; moment
    y = max(df.df[i_df])
    plots, [nvt.v[i_nvt],nvt.v[i_nvt]], [0., y], color=black
    ;; fit
    y = max(df.fit_df[i_df])
    plots, [nvt.fit_v[i_nvt],nvt.fit_v[i_nvt]], [0., y], color=fit_color

    ;; overplot fit function colored by quality
    ;; ---------------------------------------------------
    ;; --- determine color
    qual_factor = abs(1 - comp_vth)
    fit_color = qual_color(qual_factor, COMP_VTH_FRAC, QUAL_COLORS)

    ;; over-plot fit function
    oplot, df.v[i_df], df.fit_df[i_df], color=fit_color, thick=3.0

    ;; plot errors centered on a line toward the top of the df plot
    ;; ------------------------------------------------------------
    ;; --- throw out zero relative errors (from zero A)
    rel_err = df.df_err[i_df]
    i_a_nonzero = where(df.df[i_df] gt 0.,nwhere)
    if (nwhere le 1) then goto, next  ; need at least two for moment later
    rel_err = rel_err[i_a_nonzero]

    ;; --- convert fraction to actual error
    err = df.df_err[i_df]*df.df[i_df]

    ;; --- determine error bar color based on error level
    err_mom = moment(rel_err)
    err_color = qual_color(err_mom[0], COMP_ERR_FRAC, QUAL_COLORS)
    print, 'ion='+ions[nion]+', doyfr='+doyfr_str+', moment:'
    print, '+ ',err_mom

    ;; --- plot
    errlevel = ERR_LOC_FRAC*max(df.df[i_df])
    errline = make_array(n_elements(df.df[i_df]), /float, $
                         value=errlevel)
    errplot, df.v[i_df],errlevel - err, errlevel + err
    oplot, df.v[i_df], errline, color=err_color

    if (fix(nplot)/fix(npp) eq float(nplot)/float(npp)) then begin
      tagplot, line1=tag ,line2='University of Michigan'
      nplot = 1                 ; reset
    endif

    next:
  endfor
endfor

;; write quality parameters to a blank page
;; ----------------------------------------

;; --- save incoming plotting parameters and set some for this info
old_p = !p
!p.charthick = 3.0

;; --- force a new page
!p.multi = [0,1,1]
zero = [0.,0.]
plot, zero, /nodata, color=white

;; --- print actual message
x0 = .1
y0 = .9
ffmt = '(F6.2)'
ifmt = '(I3)'

;; --- for output lines
out_str = 'Quality parameters:'
out_str += '!C!C'
out_str += 'QUAL_COLORS = ' + array2str(QUAL_COLORS,ifmt)
out_str += '!C'
out_str += '(nominally red, yellow, green)'
out_str += '!C!C'
out_str += 'COMP_VEL_FRAC = ' + array2str(COMP_VEL_FRAC,ffmt)
out_str += '!C!C'
out_str += 'COMP_VTH_FRAC = ' + array2str(COMP_VTH_FRAC,ffmt)
out_str += '!C!C'
out_str += 'COMP_ERR_FRAC = ' + array2str(COMP_ERR_FRAC,ffmt)

xyouts, /normal, x0, y0, out_str

;; --- put back p.multi
!p = old_p


ficlose
return
end


