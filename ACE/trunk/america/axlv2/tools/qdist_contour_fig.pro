; Filename: qdist_contour_fig.pro
;
; Description:
;   Make a charge distribution contour plot figure.
;
; Author: Jim Raines (jmr)
;
; Method:
;   This code sets up plot cosmetics and reads/massages data.
;   Calls axlv2_qdist_contour_plot to actually do the plot.
;
;   
; Revision controlled by CVS:
; $Id: qdist_contour_fig.pro,v 1.2 2005/04/01 20:06:36 jraines Exp $
;
; Major Modification History
;   ddmmmyyyy   jmr   initial coding
;
; Arguments:
;
; I/O Arg         Explanation
; --- ----------  -----------
; I   file        data file, e.g. 
;                   file='/shrg1/ace/calib/swics/SWXLIEB/SWXLIEB1.001'
; O   data        data structure, e.g., data=d001
; [I] elements    optionally specify list of elements
; [I] logsc       optionally specify log scale for z (rarely good)
; [I] tag         optionally specify text tag for filename (no spaces!)
; [I] error_level optionally set error acceptance level 

pro qdist_contour_fig, file=file, data=d, elements=elements, $
  tag=tag, logsc=logsc, error_level=error_level

;; save to put back later
orig_p = !p
orig_x = !x

;; determine year (and save x labels) -- FIX: move this later
file_parse, file=file, split_base=sb
tmp = split_ydoy(sb[2], /string)
year_str = tmp[0]
;; ----------------------------------------------------------------------
;; ===> configure <=== SOME WILL BECOME ARGS
;; ----------------------------------------------------------------------

!p.charsize = 2.0
!p.charthick = 2.0
!p.thick = 1.0
!p.font = 0

!x.title = 'DOY in '+year_str
switch_x_labels, /save
;; ----------------------------------------------------------------------
;; set up defaults
;; ----------------------------------------------------------------------
if (not keyword_set(elements)) then begin
  elements = ['C','N','O']
endif

if (not keyword_set(tag)) then begin
  tag = ''
  tagsep = ''
endif else tagsep = '_'
;; ----------------------------------------------------------------------
;; read, filter and prepare data
;; ----------------------------------------------------------------------
tplatefile = 'axlv2_nvt_template.save'
restore, file=tplatefile
d = read_ascii(file, template=template, comment='#')
filter_nvt_by_qual, nvtdata=d, error_level=error_level
i_fill = where(d.n eq -1.0, nwhere)
if (nwhere gt 0) then d.n[i_fill] = 0.0

;; set up plot file
file_parse, file=file, base=base
psfile=base+'_qcon'+tagsep+tag+'.ps'
psplt, file=psfile, /color

; color table 42 is 8 reversed and works particularly well with this plot
loadct, 42, file='~/idl/shrg_colors.tbl'
fix_ct_ends

PlotsPerPage = n_elements(elements)

positions=plot_positions(lmargin=0.05,rmargin=0.05,tmargin=0.05,bmargin=0.05,$
                         nplots=PlotsPerPage)
nplot = PlotsPerPage

;; ----------------------------------------------------------------------
;; do plots
;; ----------------------------------------------------------------------
for nelem=0,n_elements(elements)-1 do begin
  element = elements[nelem]

  if (nelem eq 0) then $
    title='ACE/SWICS Level II Data (ver. 2, pre-release)'$
  else $
    title=''

  !p.multi=[nplot,1,n_elements(elements),0,0]

  if (nelem eq n_elements(elements)-1) then switch_x_labels, /on $
    else switch_x_labels, /off

  axlv2_qdist_contour_plot, data=d, element=element, year=year, tag=tag,$
    position=positions[--nplot,*], logsc=logsc, title=title

  print, 'p.multi=',!p.multi

endfor

ficlose

!p = orig_p
!x = orig_x

end
