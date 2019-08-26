// File : ace.i
// $Id: ace.i,v 1.1.1.1 2000/06/02 13:37:24 jraines Exp $

%subsection "SWICS: DPU classification"
// TOF(E/q,PAPS,m/q) according to DPU algorithm
// Note: PAPS here is "real" voltage, not the one stripped by 1.5 kV.
//       The routine uses a constant "foil loss" of 1.5 kV, as the
//       Ulysses/SWICS DPU does. See also: adpumoq.
extern double adputof       (double eoq, double paps, double moq);

/* ESSD(TOF,m) according to DPU algorithm */
extern double adpuesd       (double tof, double mas);

// m/q(E/q,PAPS,TOF) according to DPU algorithm
// Note: Routine takes care of 1.5 kV "energy loss" in foil.
//       Input is normal PAPS value without modifications
//       (typically 22.8 kV).
//       This is important because the "energy loss" is not implemented
//       in the ACE DPU software. There, a reduced PAPS is often used
//       to compensate for this missing parameter.
// The routine uses the /default/ classification parameters;
// not the ones found in the Telemtry.
extern double adpumoq       (double eoq, double paps, double tof);

/* m(ESSD,TOF) according to DPU algorithm */
extern double adpumas       (double esd, double tof);

// E/q for nominal stepping
// N o t e: this routine uses a fixed stepping table; not the
//          table found in the telemetry.
extern double adpueoq       (int istep);

%subsection "SWICS forward model"
// The SWICS/ACE forward model
// Note: pav here is "real" voltage, not the one stripped by 1.5 kV.
//       See also: adpumoq.
extern double *xfm(double eoq, double pav, double mas, double crg);

%subsection "SWICS efficiencies",pre
// SWICS/ACE: first version of routine handling SWICS efficiency
// de  : total energy/keV
// dmas: mass/amu of ion of interest
extern double xeffv1(double de, double dmas);
