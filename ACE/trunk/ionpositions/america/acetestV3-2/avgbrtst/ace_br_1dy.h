/* $Id: ace_br_1dy.h,v 1.6 2000/06/07 00:35:34 asc Exp $ */

#include "hdfi.h"

struct ace_br_1dy_avg {
    uint32  ACE_epoch_time;  /* time at start of bin */
    uint8   timestr[30];     /* time at start of bin */

    uint16  year;          /* year at start of bin */
    float64 fp_year;       /* floating_pt year at start of bin */
    float32 DOY;           /* day of year at start of bin */
    float32 doy_curr_year; /* day of year at start of bin, relative */
                           /* to the current year (goes negative for */
			   /* past years) */

    float32 B_rtn_r_MAG;  /* AVG Magnetic field, RTN coordinate, R component */
    float32 B_rtn_t_MAG;  /* AVG Magnetic field, RTN coordinate, T component */
    float32 B_rtn_n_MAG;  /* AVG Magnetic field, RTN coordinate, N component */
    float32 B_rtn_theta_MAG; /* AVG Magnetic field, RTN coordinate, latitude*/
    float32 B_rtn_phi_MAG; /* AVG Magnetic field, RTN coordinate, longitude */
    float32 B_gse_x_MAG;  /* AVG Magnetic field, GSE coordinate, R component */
    float32 B_gse_y_MAG;  /* AVG Magnetic field, GSE coordinate, T component */
    float32 B_gse_z_MAG;  /* AVG Magnetic field, GSE coordinate, N component */
    float32 B_gse_theta_MAG; /* AVG Magnetic field, GSE coordinate, latitude*/
    float32 B_gse_phi_MAG; /* AVG Magnetic field, GSE coordinate, longitude */
    float32 B_magnitude_MAG;  /* AVG Magnetic field, magnitude <|B|> */
    uint32 B_weight; /* number of vectors used in this average */

    float32 H_lo_SEP;    /* H rate, 0.1-0.8 Mev/n from SEPICA */
    float32 H_hi_SEP;    /* H rate, 0.8-6.0 Mev/n from SEPICA */
    float32 He_lo_SEP;   /* He rate, 0.025-0.75 Mev/n from SEPICA */
    float32 He_hi_SEP;   /* He rate, 0.75-6.0 Mev/n from SEPICA */
    float32 C_SEP;       /* C rate, 1.5-10.7 Mev/n from SEPICA */
    float32 O_SEP;       /* O rate, 1.25-12.6 Mev/n from SEPICA */
    float32 MgSi_SEP;    /* MgSi rate, 0.77-11.54 Mev/n from SEPICA */
    float32 Fe_SEP;      /* Fe rate, 0.36-5.36 Mev/n from SEPICA */
    float32 SEP_livetime; /* SEPICA livetime, if 0 ignore SEP data */

    float32 H_EPAM;      /* H rate,  0.761-0.122 Mev from EPAM */
    float32 Ion_vlo_EPAM; /* Ion rate, 47-65 keV from EPAM */
    float32 Ion_lo_EPAM; /* Ion rate, 112-187 keV from EPAM */
    float32 Ion_mid_EPAM; /* Ion rate, 310-580 keV from EPAM */
    float32 Ion_hi_EPAM; /* Ion rate, 1060-1910 KeV from EPAM */
    float32 e_lo_EPAM;   /* electron rate, 38-53 keV from EPAM */
    float32 e_hi_EPAM;  /* electron rate, 175-315 keV from EPAM */
    float32 EPAM_livetime; /* EPAM livetime. if 0 ignore EPM data */

    float32 H_lo_ULS;    /* H rate, 0.16-0.32 Mev/n from ULEIS */
    float32 H_hi_ULS;    /* H rate, 0.64-1.28 Mev/n from ULEIS */
    float32 He3_ULS;  /* He3 rate, 0.64-1.28 Mev/n from ULEIS */
    float32 He4_lo_ULS;   /* He4 rate, 0.08-0.113 Mev/n from ULEIS */
    float32 He4_hi_ULS;  /* He4 rate, 0.64-0.905 Mev/n from ULEIS */
    float32 O_lo_ULS;    /* O rate, 0.09-0.160 Mev/n from ULEIS */
    float32 O_hi_ULS;    /* O rate,  0.64-1.28 Mev/n from ULEIS */
    float32 Fe_lo_ULS;   /* Fe rate, 0.08-0.160 Mev/n from ULEIS */
    float32 Fe_hi_ULS;   /* Fe rate, 0.64-0.905 Mev/n from ULEIS */
    float32 ULS_livetime; /* ULEIS livetime. if 0 ignore ULS data */

		/* Negative values are non-physical */
    float32 H_den_SWP;     /* proton number density, cm^-3, from SWEPAM */
    float32 He_ratio_SWP;  /* nHe++/nH+, from SWEPAM */
    float32 SW_spd_SWP;    /* Solar Wind bulk (H) speed from SWEPAM */
    float32 Trr_SWP;       /* (1,1) component of temp tensor along */
			   /* radial direction from SWEPAM */
    float32 SWP_weight;    /* Number of values in average */

    float32 HiZ_Sum_CRIS;    /* Z>=10 nuclei with 100-400 Mev/nuc from CRIS */
    float32 HiZ_Pen_CRIS;    /* Flux of Z>=10, E>300Mev/n nuclei, from CRIS */

    float32 H_lo_SIS;       /* H rate , > 10 Mev/n from SIS */
    float32 H_hi_SIS;       /* H rate , > 30 Mev/n from SIS */
    float32 He_SIS;       /* He rate , 3.7-4.8 Mev/n from SIS */
    float32 CNO_lo_SIS;   /* CNO rate , 7-10 Mev/n from SIS */
    float32 CNO_hi_SIS;   /* CNO rate , 10-15 Mev/n from SIS */
    float32 HiZ_SIS;   /* Flux of Z>=10, 9-21Mev/n nuclei, from CRIS */

    float32 V_He_SWICS;
    float32 Vth_He_SWICS;
    float32 Vth_He_err_SWICS;
    float32 Vth_O6_SWICS;
    float32 Vth_O6_err_SWICS;
    float32 Ctemp_SWICS;
    float32 Ctemp_err_SWICS;
    float32 He_O_SWICS;
    float32 He_O_err_SWICS;
    float32 Fe_O_SWICS;
    float32 Fe_O_err_SWICS;
};
