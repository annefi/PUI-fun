; Filename: read_fmc.pro
;
; Description:
;   Read forward model comparison (fmc) file into an intelligently
;   organized structure.  Returns array of fmc structures where index
;   is simply number of the structure (not E/q step for example).
;
; Author: Jim Raines (jmr)
;
; Method:
;
; Arguments
;   file -- name of a file in the fmcomp format, produced by axlv2
;   or axfmtweak (or the like).
;
;   fmc -- array of fmc structures, one for each ion at each step
;
;   ions -- list of unique ions contained in fmc array (above)
;
;   eqtab -- E/q table indexed by step
;  
; Revision controlled by CVS:
; $Id: read_fmc.pro,v 1.3 2004/01/22 14:34:30 jraines Exp $
;
; Major Modification History
;   15Nov2002   jmr   Adapted from fmcomp.pro
;
pro read_fmc, file=file, fmc=fmc, ions=fmc_ions, eqtab=eoqtable

;; read center data
if (not keyword_set(file)) then fmcfile = 'axlv2_fmcomp.dat'
restore, file='axlv2_fmcomp_template.save'
fmc_bycol = read_ascii(file,template=template)

;; build unique list of fmc ions -- needed to figure out number of fmc ions
fmc_ions = fmc_bycol.ion(sort(fmc_bycol.ion ))   ; sort fmc_ions
fmc_ions = fmc_ions(uniq(fmc_ions))         ; remove duplicates
nfmc_ions = n_elements(fmc_ions)        ; store number of fmc_ions

;; re-organize forward model data into array of structures
;; -------------------------------------------------------
;; This organization, rather than the structure of arrays as read in
;; by read_ascii, makes misalignments (e.g. pairing ion with wrong
;; tof, esd, etc.) more much difficult

;; define structure
fmc_element = $
                 { fmc,       $ ;name of structure
                   step: 0,    $ ;deflection voltage step (DVS)
                   eoq: 0.0,   $ ;E/q
                   ion: '',    $ ;name of ion (e.g. He1+, Fe15+)
                   tof: 0.0,   $ ;forward model (fm) time of flight
                   tofsig: 0.0,$ ;fm tof sigma (1/2 width of gaussian)
                   esd: 0.0,   $ ;forward model (fm) time of flight
                   esdsig: 0.0 $ ;fm esd sigma (1/2 width of gaussian)
                 }

;; build array of structures
fmc = replicate( fmc_element, n_elements(fmc_bycol.ion))

;; fill structures in fmc array
for i=0,n_elements(fmc_bycol.ion)-1 do begin
  fmc[i].step = fmc_bycol.edb[i]
  fmc[i].eoq  = fmc_bycol.eoq[i]
  fmc[i].ion  = fmc_bycol.ion[i]
  fmc[i].tof  = fmc_bycol.tof[i]
  fmc[i].tofsig  = fmc_bycol.tofsig[i]
  fmc[i].esd  = fmc_bycol.esd[i]
  fmc[i].esdsig  = fmc_bycol.esdsig[i]
endfor

;; build eoqtable in case requested
eoqtable = fmc.eoq
eoqtable = eoqtable[uniq(eoqtable)]
eoqtable = eoqtable[reverse(sort(eoqtable))] ; ensure E/q in descending order
eoqtable = [-1.0,-1.0,eoqtable] ; steps 0 and 1 are not in fmc

return
end
