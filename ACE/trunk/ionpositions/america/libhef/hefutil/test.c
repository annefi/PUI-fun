/* test.f -- translated by f2c (version 19970805).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__29 = 29;
static doublereal c_b33 = -.33333333333333331;
static doublereal c_b41 = -1.5;
static doublereal c_b45 = 3.;
static doublereal c_b46 = 2.5;
static doublereal c_b47 = 1.5;
static doublereal c_b51 = 2.64;
static doublereal c_b56 = .81;
static doublereal c_b57 = .77;
static doublereal c_b58 = 1.46;
static doublereal c_b59 = .86;
static doublereal c_b60 = .41;
static doublereal c_b61 = 1.41;
static doublereal c_b85 = 6.692e-7;

/* Subroutine */ int arnaud_share__(xz, xte, x, xreco, xrtot)
integer *xz;
doublereal *xte, *x, *xreco, *xrtot;
{
    /* Initialized data */

    static integer iz[15] = { 1,2,6,7,8,10,11,12,13,14,16,18,20,26,28 };

    /* Format strings */
    static char fmt_8010[] = "(1x,\002ARNAUD> Cannot handle this ion:\002,i5)"
	    ;

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(), do_fio(), e_wsfe(), s_wsle(), do_lio(), e_wsle();
    double log(), exp();
    /* Subroutine */ int s_stop();

    /* Local variables */
    static integer ilec;
    static doublereal diel[29], reco[29], rdir[29];
    static integer nion[30];
    static doublereal prod[30], rtot[29];
    static integer i__, s, z__;
    static doublereal rdiel;
    static integer index;
    static doublereal aktev, prodl, rauto[29], te, rr;
    extern /* Subroutine */ int recofe_(), recomb_();
    static integer mz;
    extern /* Subroutine */ int ionsub_();
    static doublereal alrtot, prodsu, rad[29];

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 6, 0, fmt_8010, 0 };
    static cilist io___6 = { 0, 6, 0, 0, 0 };
    static cilist io___25 = { 0, 6, 0, 0, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };


/* -----------------------------------------------------------------------
 */
/*     DESCRIPTION OF PARAMETERS */

/*     Z     Number of protons in element */
/*     TE    Electron temperature [K] */
/*     RTOT  Total ionisation rate */
/*     RDIR  Direct ionisation rate */
/*     RAUTO Autoionisation rate */
/*     RAD   Radiative recombination rate */
/*     DIEL  Dielectronic recombination rate */
/*     RECO  Total recombination rate */

/*     This routine is based on the original package of Arnaud and */
/*     Rothenflug (1985) */

/*     MODIFICATIONS: */
/*         June 20, 1994     initial version */
/*         August 24, 1994   make ARNMAIN into a subroutine (P.W.) */
/*         August 19, 1996   removed COMMON block (P.W.) */
/*         January 20, 1998  adapted for SUN/UNIX (P.W.) */
/* -----------------------------------------------------------------------
 */
/* Table of available ions */
/* Temperature of electrons in degrees Kelvin */
/* -----------------------------------------------------------------------
 */
/* 	IDL Interface */
/* .......................................................................
 */
    /* Parameter adjustments */
    --xrtot;
    --xreco;
    --x;

    /* Function Body */
    te = *xte;
    z__ = *xz;
/*     WRITE(*,*) xz, xte */
/* -----------------------------------------------------------------------
 */
/* 	Do initial check */
/* .......................................................................
 */
    for (i__ = 1; i__ <= 15; ++i__) {
	if (z__ == iz[i__ - 1]) {
	    goto L10;
	}
/* L33: */
    }
    s_wsfe(&io___5);
    do_fio(&c__1, (char *)&z__, (ftnlen)sizeof(integer));
    e_wsfe();
    return 0;
/*     CALL EXIT(-1) */
/* -----------------------------------------------------------------------
 */
/* 	Start processing */
/* .......................................................................
 */
L10:
    s_wsle(&io___6);
    do_lio(&c__3, &c__1, (char *)&(*xz), (ftnlen)sizeof(integer));
    do_lio(&c__5, &c__1, (char *)&(*xte), (ftnlen)sizeof(doublereal));
    do_lio(&c__3, &c__1, (char *)&z__, (ftnlen)sizeof(integer));
    do_lio(&c__5, &c__1, (char *)&te, (ftnlen)sizeof(doublereal));
    e_wsle();
/* L8011: */
    for (i__ = 1; i__ <= 30; ++i__) {
	rtot[i__ - 1] = 0.;
/* L19: */
    }
    ilec = 0;
    aktev = te / (float)11606.;
    ionsub_(&z__, &aktev, rauto, rdir, rtot);
/* -----------------------------------------------------------------------
 */

/* .......................................................................
 */
    prodsu = 1.;
    prod[0] = 1.;
    prodl = 0.;
    index = 0;
    for (i__ = 1; i__ <= 30; ++i__) {
	x[i__] = 0.;
/* L18: */
	reco[i__ - 1] = 0.;
    }
L50:
    i__1 = z__;
    for (i__ = 1; i__ <= i__1; ++i__) {
	s = i__ + 1;
	if (z__ != 26) {
	    recomb_(&z__, &s, &te, &rr, &rdiel);
	}
	if (z__ == 26) {
	    recofe_(&z__, &s, &te, &rr, &rdiel);
	}
	rad[i__ - 1] = rr;
	diel[i__ - 1] = rdiel;
	reco[i__ - 1] = rr + rdiel;
/* Computing MAX */
	d__1 = rtot[i__ - 1];
	alrtot = log((max(d__1,1e-30)));
	prodl = prodl + alrtot - log(reco[i__ - 1]);
	if (prodl < -70.) {
	    prod[i__] = 0.;
	}
	if (prodl >= -70.) {
	    prod[i__] = exp(prodl);
	}
	if (prodl >= 70. && index <= 2) {
	    if (prodl >= 70. && index > 2) {
		s_stop("", 0L);
	    }
	    ++index;
	    prodl = (doublereal) index * -70.;
	    prodsu = exp(prodl);
	    prod[0] = exp(prodl);
	    goto L50;
	}
	prodsu += prod[i__];
/* L20: */
    }

    mz = z__ + 1;
    i__1 = mz;
    for (i__ = 1; i__ <= i__1; ++i__) {
	nion[i__ - 1] = i__ - 1;
	if (prod[i__ - 1] == 0.) {
	    x[i__] = 0.;
	    goto L100;
	}
	if (log(prod[i__ - 1]) - log(prodsu) < -70.) {
	    x[i__] = 0.;
	}
	if (log(prod[i__ - 1]) - log(prodsu) >= -70.) {
	    x[i__] = prod[i__ - 1] / prodsu;
	}
L100:
	;
    }
/* -----------------------------------------------------------------------
 */
/* 	IDL Interface */
/* .......................................................................
 */
    for (i__ = 1; i__ <= 29; ++i__) {
	xreco[i__ + 1] = reco[i__ - 1];
	xrtot[i__] = rtot[i__ - 1];
/* L110: */
    }
    s_wsle(&io___25);
    do_lio(&c__5, &c__29, (char *)&reco[0], (ftnlen)sizeof(doublereal));
    e_wsle();
    s_wsle(&io___26);
    do_lio(&c__5, &c__29, (char *)&rtot[0], (ftnlen)sizeof(doublereal));
    e_wsle();
} /* arnaud_share__ */

/* Subroutine */ int recomb_(z__, s, te, rr, rdiel)
integer *z__, *s;
doublereal *te, *rr, *rdiel;
{
    /* Initialized data */

    static doublereal potli[28] = { 0.,0.,5.39,18.2,37.9,64.5,97.9,138.,185.,
	    239.,300.,367.,442.,523.,612.,700.,809.,918.,1034.,1157.,1288.,
	    1425.,1569.,1721.,1880.,2045.,2218.,2399. };
    static integer id[28] = { 0,1,0,0,0,2,8,15,0,23,0,33,0,45,0,59,0,75,0,93,
	    0,0,0,0,0,113,0,139 };
    static integer kstor[28] = { 0,0,0,0,0,4,5,6,0,0,0,2,3,4,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0 };
    static integer istor[28] = { 0,0,0,0,0,1,4,8,0,0,0,13,14,16,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0 };
    static doublereal astor[18] = { .0108,1.8267,2.3196,0.,.032,-.8806,.4134,
	    0.,-.0036,0.,.0061,-2.8425,1.2044,.071,.7086,-.0219,3.2163,.1203 }
	    ;
    static doublereal bstor[18] = { -.1075,4.1012,10.7328,.631,-.6624,11.2406,
	    -4.6319,.0238,.7519,21.879,.2269,.2283,-4.6836,-.4079,-3.1083,
	    .4364,-12.0571,-2.69 };
    static doublereal cstor[18] = { .281,4.8443,6.883,.199,4.3191,30.7066,
	    25.9172,.0659,1.5252,16.273,32.1419,40.4072,7.662,2.3487,7.0422,
	    .0684,16.2118,19.1943 };
    static doublereal dstor[18] = { -.0193,.2261,-.1824,-.0197,3e-4,-1.1721,
	    -2.229,.0349,-.0838,-.702,1.9939,-3.4956,-.593,-.1309,.5998,
	    -.0032,-.5886,-.1479 };
    static doublereal fstor[18] = { -.1127,.596,.4101,.4398,.5946,.6127,.236,
	    .5334,.2769,1.1899,-.0646,1.7558,1.626,.6126,.4194,.1342,.5613,
	    .1118 };
    static doublereal adi[166] = { 1.27,2.54,6.15,1.62,47.8,32.2,0.,2.98,7.41,
	    11.3,2.62,75.,46.1,0.,1.11,5.07,14.8,18.4,4.13,106.,47.2,0.,.977,
	    2.65,3.69,11.8,24.4,30.2,6.1,252.,71.4,0.,.449,1.95,5.12,7.74,
	    11.7,36.9,36.3,41.5,8.86,252.,92.8,0.,1.1,5.87,5.03,5.43,8.86,
	    16.8,24.9,31.3,42.5,61.8,13.8,327.,113.,0.,1.62,10.9,33.5,31.4,
	    12.7,14.7,13.4,23.8,31.9,71.3,80.,79.6,13.4,402.,145.,0.,1.,11.,
	    34.,48.,75.,63.5,26.,24.,21.,35.,43.,71.3,96.,85.,17.,476.,178.,
	    0.,.328,58.4,112.,132.,133.,126.,139.,95.5,40.2,41.9,25.7,44.5,
	    54.8,71.3,109.,110.,20.5,549.,268.,0.,1.58,8.38,15.4,37.5,117.,
	    254.,291.,150.,140.,100.,200.,240.,260.,190.,120.,350.,66.,100.,
	    130.,230.,140.,110.,41.,747.,369.,0.,1.41,5.2,13.8,23.,41.9,68.3,
	    122.,300.,150.,697.,709.,644.,525.,446.,363.,302.,102.,270.,46.7,
	    83.5,99.6,199.,240.,115.,31.6,803.,345.,0. };
    static doublereal bdi[166] = { 300.,44.2,58.8,343.,362.,315.,0.,0.,76.4,
	    164.,243.,350.,309.,0.,92.5,181.,305.,100.,162.,340.,0.,0.,73.,
	    242.,1010.,391.,2520.,445.,254.,304.,296.,0.,21.,74.,323.,636.,
	    807.,351.,548.,233.,318.,315.,0.,0.,0.,753.,188.,450.,0.,1800.,
	    1880.,2010.,1220.,303.,1420.,306.,286.,0.,0.,12.,65.9,68.9,187.,
	    129.,1040.,1120.,1400.,1e3,555.,1630.,304.,298.,281.,0.,5.,45.,
	    57.,87.,76.9,140.,120.,100.,1920.,1660.,1670.,1400.,1310.,1020.,
	    245.,294.,277.,0.,90.7,110.,17.4,132.,114.,162.,87.8,263.,62.7,
	    61.6,2770.,2230.,2e3,1820.,1740.,243.,185.,292.,0.,0.,456.,323.,
	    310.,411.,359.,97.5,229.,4200.,3300.,5300.,1500.,700.,600.,500.,
	    1e3,0.,7800.,6300.,5500.,3600.,4900.,1600.,4200.,284.,0.,0.,469.,
	    357.,281.,128.,41.7,55.8,34.6,0.,1900.,277.,135.,134.,192.,332.,
	    337.,121.,51.4,183.,7560.,4550.,4870.,2190.,1150.,1230.,132.,289.,
	    286.,0. };
    static doublereal t05[166] = { 4.7,1.57,1.41,.819,34.,40.6,0.,2.2,2.01,
	    1.72,1.02,47.5,54.4,0.,1.75,1.98,2.41,2.12,1.25,62.5,60.,0.,3.11,
	    2.84,2.24,2.7,3.09,2.83,1.68,140.,110.,0.,.501,6.06,4.69,3.74,
	    3.28,4.8,3.88,3.39,2.11,140.,145.,0.,.77,.963,.875,10.5,11.4,4.85,
	    4.15,3.66,3.63,3.88,2.51,188.,199.,0.,1.25,1.92,1.89,1.68,1.38,
	    18.,6.9,5.84,5.17,6.66,6.,5.09,2.91,241.,254.,0.,3.2,2.9,2.39,
	    2.56,2.5,2.1,1.8,27.,8.3,6.95,6.05,6.68,6.5,5.3,3.55,301.,313.,0.,
	    .346,3.85,4.08,3.82,3.53,3.19,3.22,2.47,2.29,37.3,9.26,7.96,6.9,
	    6.7,7.,5.67,4.21,365.,374.,0.,.6,1.94,3.31,4.32,6.28,7.5,7.73,
	    2.62,2.5,2.57,2.84,8.69,4.21,4.57,2.85,81.8,15.1,13.,11.9,10.9,
	    9.62,7.23,4.23,584.,600.,0.,.982,2.01,3.05,4.2,5.56,6.72,7.93,9.,
	    10.,7.81,7.64,7.44,6.65,5.97,5.24,4.96,4.46,84.9,13.6,12.3,10.6,
	    12.5,12.3,3.32,6.45,665.,681.,0. };
    static doublereal t15[166] = { .94,3.74,1.41,1.59,5.87,8.31,0.,0.,.737,
	    2.25,1.25,8.35,11.4,0.,1.45,3.35,2.83,2.83,2.27,11.2,14.7,0.,2.06,
	    3.07,2.94,5.5,9.91,17.3,6.13,18.,22.4,0.,.281,14.4,7.55,7.88,10.2,
	    9.73,7.38,3.82,15.4,26.4,30.9,0.,0.,.646,.471,7.98,0.,10.3,19.1,
	    21.1,21.4,11.2,39.3,36.,41.4,0.,0.,.18,1.59,.804,1.71,17.5,21.5,
	    25.9,29.1,23.2,24.1,63.7,10.4,46.7,53.,0.,3.1,5.5,6.,3.81,3.3,
	    2.15,2.15,33.,35.,36.,38.,29.,36.,28.,11.,60.5,65.4,0.,.164,2.45,
	    4.27,6.92,8.78,7.43,6.99,4.43,2.81,58.4,48.9,46.2,45.2,33.2,49.3,
	    44.1,22.7,72.5,76.8,0.,.897,1.71,2.73,3.49,5.29,4.69,6.54,13.2,
	    13.3,14.1,15.2,15.1,18.2,18.4,23.1,0.,99.8,99.8,100.,110.,83.4,
	    101.,107.,117.,99.7,0.,1.01,1.91,2.32,3.18,4.55,5.51,5.28,0.,5.5,
	    8.87,18.,12.5,18.9,8.84,12.9,6.24,15.9,80.1,93.2,94.5,94.5,80.1,
	    75.7,26.4,19.3,119.,90.8,0. };
    static doublereal ar[166] = { 4.3,4.7,23.,49.,91.6,170.,330.,4.1,22.,50.,
	    94.,157.,290.,480.,3.1,20.,51.,96.,159.,244.,720.,671.,2.2,15.,
	    44.,91.,150.,230.,346.,570.,860.,1160.,1.4,8.8,35.,77.,140.,230.,
	    320.,460.,683.,1130.,2160.,1810.,5.9,10.,37.,55.,120.,210.,300.,
	    430.,580.,770.,1430.,2150.,3200.,2640.,4.1,18.,27.,57.,120.,170.,
	    270.,400.,550.,740.,920.,1400.,2e3,2910.,4300.,3680.,3.77,19.5,
	    32.3,60.3,91.2,158.,269.,355.,490.,692.,955.,1230.,1580.,2140.,
	    3070.,4360.,5800.,4910.,1.12,6.78,39.6,70.8,107.,180.,240.,376.,
	    504.,646.,851.,1180.,1580.,2040.,2600.,3240.,4610.,5620.,8440.,
	    6350.,1.42,10.2,33.2,78.,151.,262.,412.,605.,813.,1090.,1330.,
	    1640.,2e3,2410.,2890.,3420.,3870.,4520.,5250.,6070.,6980.,7720.,
	    11500.,15800.,1.4e4,1.2e4,3.6,10.,14.,16.,38.5,90.5,175.,304.,
	    891.,1190.,1500.,1910.,2290.,2630.,3160.,3630.,4030.,4730.,5250.,
	    5750.,6380.,7080.,7940.,8710.,13600.,18700.,10600.,14500. };
    static doublereal eta[166] = { .672,.624,.645,.803,.791,.721,.726,.608,
	    .639,.676,.765,.78,.75,.726,.678,.646,.666,.67,.759,.774,.834,
	    .726,.759,.693,.675,.668,.684,.704,.742,.803,.769,.726,.855,.838,
	    .734,.718,.716,.695,.691,.711,.765,.829,.821,.726,.601,.786,.693,
	    .821,.735,.716,.702,.688,.703,.714,.823,.858,.818,.726,.63,.686,
	    .745,.755,.701,.849,.733,.696,.711,.716,.714,.755,.806,.84,.807,
	    .726,.651,.752,.869,.812,.811,.793,.744,.91,.801,.811,.793,.702,
	    .79,.774,.819,.854,.803,.726,.9,.8,.7,.78,.84,.82,.82,.81,.78,.9,
	    .82,.81,.8,.73,.8,.78,.833,.839,.819,.726,.891,.843,.746,.682,
	    .699,.728,.759,.79,.81,.829,.828,.834,.836,.84,.846,.85,.836,.824,
	    .816,.811,.808,.8,.852,.875,.787,.726,.7,.7,.7,.7,.746,.682,.699,
	    .728,.759,.79,.81,.829,.828,.834,.836,.84,.846,.85,.836,.824,.816,
	    .811,.808,.8,.842,.868,.732,.726 };

    /* Format strings */
    static char fmt_1099[] = "(1x,\002 THERE WAS AN ATTEMPT TO USE SUBROUTIN\
E \"RECOMB\"\002/\002FOR COMPUTING RECOMBINATION RATES FOR IRON. RECOMB IS NO\
\002/\002LONGER THE BEST SOURCE. USE \"RECOFE\" INSTEAD!\002/\002THE PROGRAM\
ME IS STOPPED!\002)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(), e_wsfe();
    double d_lg10(), sqrt(), log(), pow_dd(), exp();

    /* Local variables */
    static doublereal alam, fact, ktev, b, d__, u, x, t4, rstor, y1;
    static integer z1;
    static doublereal y2, y3, rdiel1, rdiel2, aa, ab, ff, as, za, zb, ax, kt, 
	    tl;
    static integer iz;
    static doublereal xx, xy, ff1, ff2;
    static integer iz1, iz2;
    static doublereal rr1, rr2, chi, arg;
    static integer ist;

    /* Fortran I/O blocks */
    static cilist io___42 = { 0, 6, 0, fmt_1099, 0 };


/* =======================================================================
 */
/* Ce sous-programme calcule le taux de recombinaison */
/* en utilisant Aldrovandi et Pequignot, Shull et al. */
/* SEATOJ, PRADHAJ, QIUJEER, QTIREY (BEDQ DUBAU,JACIBS */

/* S est le numero de l'ion qui va se recombiner */
/* ===================================================== */

/*     Original version of Arnaud and Rothenflug  should not be used */
/*     for iron */

/*     Implemented into ARNMAIN by Peter Bochsler June 20, 1994 */
/*     Adapted for SUN/UNIX by Peter Wurz January 22, 1998 */
/* -----------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------
 */
/*     CHECK IF Z.NE.26 */
/* .......................................................................
 */
    if (*z__ == 26) {
	s_wsfe(&io___42);
	e_wsfe();
	return 0;
/*         CALL EXIT(-1) */
    }

    ktev = *te / (float)11605.;
    kt = ktev / (float)1e3;
    tl = d_lg10(te);
    *rdiel = (float)0.;
    *rr = (float)0.;
    rstor = (float)0.;

    iz = id[*z__ - 1] + (*s - 2);
/* AIGUILLAGE POUR LES DIFFERENTS CAS */
    if (*s > *z__ || *z__ == 1) {
	goto L10;
    }
    z1 = *z__ - 1;
    goto L11;

/* =======================================================================
 */
/* RECOMBINAISON RADIATIVE */
/* ======================================================== */


/* IONS HYDROGENOIDES ( SEATON) */
/* -----------------------------------------------------------------------
 */

L10:
    alam = *z__ * (float)157890. * *z__ / *te;
    *rr = *z__ * 5.197e-14 * sqrt(alam) * (log(alam) * (float).5 + (float)
	    .4288 + pow_dd(&alam, &c_b33) * (float).469);
    goto L12;

/* AUTRES IONS */
/* --------------------------------------------- */

L11:
    if (*z__ == 11) {
	goto L51;
    }
    if (*z__ == 13) {
	goto L52;
    }
    d__1 = *te / 1e4;
    *rr = ar[iz - 1] * (float)1e-13 / pow_dd(&d__1, &eta[iz - 1]);
    goto L20;

/* CALCUL DE NA, AL PAR INTERPOLATION */

L51:
    iz1 = *s + 20;
    iz2 = *s + 32;
    if (*s == 2) {
	iz1 = 34;
    }
    if (*s == 2) {
	iz2 = 48;
    }
    goto L53;
L52:
    iz1 = *s + 30;
    iz2 = *s + 44;
    if (*s == 2) {
	iz1 = 46;
    }
    if (*s == 2) {
	iz2 = 62;
    }
L53:
    d__1 = *te / 1e4;
    rr1 = ar[iz1 - 1] * (float)1e-13 / pow_dd(&d__1, &eta[iz1 - 1]);
    if (rr1 < 1e-70) {
	rr1 = 1e-70;
    }
    d__1 = *te / 1e4;
    rr2 = ar[iz2 - 1] * (float)1e-13 / pow_dd(&d__1, &eta[iz2 - 1]);
    if (rr2 < 1e-70) {
	rr2 = 1e-70;
    }
    if (*s == 2) {
	*rr = rr1 * rr1 / rr2;
    }
    if (*s == 2) {
	goto L54;
    }
    aa = (doublereal) (*s - 1) / (doublereal) (*s - 2);
    ab = (doublereal) (*s) / (doublereal) (*s - 2);
    u = d_lg10(&aa) / d_lg10(&ab);
    d__1 = rr2 / rr1;
    *rr = rr1 * pow_dd(&d__1, &u);
    if (*s == z1) {
	goto L21;
    }
    goto L54;


/* ======================================================= */
/* RECOMBINAISON DIELECTRONIQUE */
/* ======================================================== */

L20:
    if (*s == z1) {
	goto L21;
    }
    arg = t15[iz - 1] * 1e5 / *te;
    if (arg > (float)150.) {
	arg = (float)150.;
    }
    ff = bdi[iz - 1] * (float).001 * exp(-arg);
    arg = t05[iz - 1] * 1e5 / *te;
    if (arg > (float)150.) {
	arg = (float)150.;
    }
    fact = exp(-arg) * (ff + 1);
    *rdiel = adi[iz - 1] * (float).001 * pow_dd(te, &c_b41) * fact;
    goto L22;

/* CALCUL DE NA AL PAR INTERPOLATION */

L54:
    y1 = t15[iz1 - 1] * (float)1e5 / *te;
    if (y1 > (float)150.) {
	y1 = (float)150.;
    }
    ff1 = bdi[iz1 - 1] * (float).001 * exp(-y1);
    y1 = t05[iz1 - 1] * (float)1e5 / *te;
    if (y1 > (float)150.) {
	y1 = (float)150.;
    }
    ff1 = exp(-y1) * (ff1 + 1);
    rdiel1 = adi[iz1 - 1] * (float).001 * pow_dd(te, &c_b41) * ff1;
    if (rdiel1 < 1e-70) {
	rdiel1 = 1e-70;
    }
    y2 = t15[iz2 - 1] * (float)1e5 / *te;
    if (y2 > (float)150.) {
	y2 = (float)150.;
    }
    ff2 = bdi[iz2 - 1] * (float).001 * exp(-y2);
    y2 = t05[iz2 - 1] * (float)1e5 / *te;
    if (y2 > (float)150.) {
	y2 = (float)150.;
    }
    ff2 = exp(-y2) * (ff2 + 1);
    rdiel2 = adi[iz2 - 1] * (float).001 * pow_dd(te, &c_b41) * ff2;
    if (rdiel2 < 1e-70) {
	rdiel2 = 1e-70;
    }
    if (*s == 2) {
	*rdiel = rdiel1 * rdiel1 / rdiel2;
    }
    if (*s == 2) {
	goto L22;
    }
    d__1 = rdiel2 / rdiel1;
    *rdiel = rdiel1 * pow_dd(&d__1, &u);
    goto L22;

/* RECOMBINAISON DES HELIUMOIDES DE YOUNGER */
/* ----------------------------------------- */

L21:
    za = (doublereal) (*z__ - 1);
    zb = (doublereal) (*z__ - 2);
    x = za * (float)3. / (float)4.;
    ax = sqrt(x) / ((x * (float).21 + (float)1. + x * (float).03 * x) * (
	    float)2.);
    d__ = za * (float)3. * za / (zb * zb * (pow_dd(&zb, &c_b45) * (float).015 
	    / (za * za) + (float)1.));
    xy = zb * zb + (float)13.4;
    xx = pow_dd(&za, &c_b46);
    b = zb * xx / (sqrt(xy) * (float)2.);
    chi = ktev / potli[*z__ - 1];
    y3 = d__ / chi;
    if (y3 > (float)150.) {
	y3 = (float)150.;
    }
    *rdiel = b * 3.2e-10 * ax * exp(-y3) / (pow_dd(&chi, &c_b47) * pow_dd(&zb,
	     &c_b45));
    goto L12;
/* -----------------------------------------------------------------------
 */
/* RECOMBINAISON DE CII,CIII,CIV;NII,NIII,NIV,NV;OII,OIII,OIV,OV,OVI */
/* MGII,ALII,ALIII,SIII,SIIII,SIIV */
/* A BASSE TEMPERATURE NUSSBAUMER ET STOREY */
/* -----------------------------------------------------------------------
 */

L22:
    if (*te > 6e4) {
	goto L23;
    }
    if (*s > kstor[*z__ - 1]) {
	goto L23;
    }
    ist = istor[*z__ - 1] + *s - 2;
    t4 = *te / 1e4;
    as = exp(-fstor[ist - 1] / t4);
    as /= pow_dd(&t4, &c_b47);
    as *= bstor[ist - 1] + t4 * cstor[ist - 1] + t4 * t4 * dstor[ist - 1] + 
	    astor[ist - 1] / t4;
    rstor = as * 1e-12;
    if (*z__ != 14 || tl > (float)4.7) {
	goto L12;
    }


/* CORRECTION DES FITS DE SHULL A BASSE TEMPERATURE */
/* POUR SI II,SI III */
/* -------------------------------------------------- */

    if (*s == 2 && tl <= (float)4.3) {
	*rdiel = pow_dd(te, &c_b51) * 4.35e-23;
    }
    if (*s == 3) {
	*rdiel = exp(-1.07e5 / *te) * .00816 / pow_dd(te, &c_b47);
    }


/* CORRECTION DES FITS DE SHULL A HAUTE TEMPERATURE */
/* POUR NEVII,NEVIII,SVI,SXIII,SXIV,CAXVIII */
/* -------------------------------------------------- */

L23:
    if (*z__ == 10) {
	goto L100;
    }
    if (*z__ == 16) {
	goto L101;
    }
    if (*z__ == 20) {
	goto L102;
    }
    goto L12;
L100:
    if (*s == 7 && tl >= (float)6.35) {
	*rdiel = 1.22e-6 / pow_dd(te, &c_b56);
    }
    if (*s == 8 && tl >= (float)6.35) {
	*rdiel = 1.52e-7 / pow_dd(te, &c_b57);
    }
    goto L12;
L101:
    if (*s == 6 && tl >= (float)6.5) {
	*rdiel = .0108 / pow_dd(te, &c_b58);
    }
    if (*s == 13 && tl >= (float)6.6) {
	*rdiel = 5.2e-6 / pow_dd(te, &c_b59);
    }
    if (*s == 14 && tl >= (float)6.7) {
	*rdiel = 8e-10 / pow_dd(te, &c_b60);
    }
    goto L12;
L102:
    if (*s == 18 && tl >= (float)6.8) {
	*rdiel = .00629 / pow_dd(te, &c_b61);
    }
    goto L12;
/*      IF (Z.EQ.26.AND.S.EQ.17.) RDIEL=.86*DEXP(-560./KTEV)/(TE**1.5) */
L12:
    *rdiel = rstor + *rdiel;
    return 0;
} /* recomb_ */



/* Subroutine */ int recofe_(z__, s, te, rr, rdiel)
integer *z__, *s;
doublereal *te, *rr, *rdiel;
{
    /* Initialized data */

    static doublereal ar[26] = { 1.42,10.2,33.2,78.,151.,262.,412.,605.,813.,
	    1090.,1330.,1640.,2e3,1460.,1680.,1910.,2240.,2590.,2960.,3160.,
	    3490.,3910.,4330.,4770.,5840.,0. };
    static doublereal eta[26] = { .891,.843,.746,.682,.699,.728,.759,.79,.81,
	    .829,.828,.834,.836,.597,.602,.601,.579,.567,.557,.534,.521,.523,
	    .531,.537,.546,0. };
    static doublereal beta[26] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    5.22,5.07,5.1,5.49,5.65,5.79,6.02,6.22,6.15,5.77,5.49,4.02,0. };

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double sqrt(), log(), pow_dd(), d_lg10();

    /* Local variables */
    static doublereal alam;
    static integer iz;
    static doublereal te4;
    extern doublereal alphadi_();

/* =======================================================================
 */
/* This subroutine computes the recombination rates */
/* (radiative and dielectronique) for iron only. */

/* S     is the ionicity of the recombining ion EX: s=1 for FeI */
/* Z     is the nuclear charge here Z=26 */
/* TE    is the temperature in Kelvin */
/* RR    is the radiative recombination rate in cm+3/s */
/* RDIEL IS the dielectronic recombination rate in cm+3/s */

/* Modifications: */
/* --------------- */

/*     IMPLEMENTED ON JUNE 20, 1994 INTO ARNMAIN.FOR */
/*      BY PETER BOCHSLER */

/*     Adated for SUN/UNIX  by Peter Wurz, Jannuary 22, 1998 */
/* =======================================================================
 */
/* -----------------------------------------------------------------------
 */
    *rr = (float)0.;
    iz = *s - 1;
/* ------------------------------ */
/* IONS HYDROGENOIDES ( SEATON) */
/* ------------------------------ */
    if (*s > *z__ || *z__ == 1) {
	alam = *z__ * (float)157890. * *z__ / *te;
	*rr = *z__ * 5.197e-14 * sqrt(alam) * (log(alam) * (float).5 + (float)
		.4288 + pow_dd(&alam, &c_b33) * (float).469);
	return 0;
    }

/* AUTRES IONS */
/* --------------- */

    te4 = *te / 1e4;
    d__1 = eta[iz - 1] + beta[iz - 1] * .01 * d_lg10(&te4);
    *rr = ar[iz - 1] * (float)1e-13 / pow_dd(&te4, &d__1);
/* RECOMBINAISON DIELECTRONIQUE */
/* ----------------------------- */
    *rdiel = alphadi_(z__, s, te);

    return 0;
} /* recofe_ */

doublereal alphadi_(n, j, t)
integer *n, *j;
doublereal *t;
{
    /* Initialized data */

    static doublereal a[100]	/* was [4][25] */ = { .43,0.,0.,0.,.256,.452,
	    0.,0.,.011,.0488,.0801,.529,.131,0.,.613,.0849,.129,9.2e-4,.912,
	    .192,.0185,.0953,.079,1.23,.016,.0717,.0906,.739,.00567,.0782,
	    .0318,1.263,.0336,.00253,1.92,.181,1.23,0.,0.,0.,.12,.12,.6,0.,
	    .19,.09,0.,0.,.26,.16,0.,0.,.24,.17,0.,0.,.225,.231,0.,0.,.1,.28,
	    0.,0.,.14,.26,0.,0.,.62,.24,0.,0.,.16,.036,0.,0.,.092,.041,0.,0.,
	    .08,.024,0.,0.,.038,.016,0.,0.,.015,.0047,0.,0.,.0023,.0027,0.,0.,
	    2.2e-4,1e-4,0.,0. };
    static doublereal e1[100]	/* was [4][25] */ = { 5300.,0.,0.,0.,4625.,
	    6e3,0.,0.,.1,36.2,306.,928.,73.2,0.,877.,316.,80.3,39.1,919.,392.,
	    13.2,66.6,297.,714.,23.7,85.1,329.,787.,16.2,96.,330.,729.,117.,
	    22.5,683.,341.,560.,0.,0.,0.,24.6,248.,560.,0.,39.4,198.,0.,0.,
	    36.3,193.,0.,0.,75.,205.,0.,0.,59.6,362.,0.,0.,22.2,144.,0.,0.,
	    21.6,136.,0.,0.,66.1,129.,0.,0.,66.7,123.,0.,0.,45.5,360.,0.,0.,
	    54.2,100.,0.,0.,37.3,67.4,0.,0.,28.6,52.1,0.,0.,16.7,31.4,0.,0.,
	    5.12,12.9,0.,0. };

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(), pow_dd();

    /* Local variables */
    static integer i__;
    static doublereal ad;

/* =======================================================================
 */
/*  returns value of dielectronic recombination rate coefficient. */
/*  for now, does only iron (n=26) */
/*  J is the ionicity : J=1 for Fe I, 2 for Fe II ... */
/*  T is in Kelvin */
/*  result is cm**3 s**-1 */
/*  data arrays contain coefficients for a sum of terms */
/*        T**-1.5 * A * EXP(-E1*11590./T) */
/*  Fe XXV - Karim&Bhalla : XXV - Chen : XXIV -  McLH & Romanik */
/*  XXIII-XXII - Badnell : XXI-XIX - Roszman */
/*  XVIII - Dasgupta&Whitney : XVII Smith etal scaled to Chen */
/*  XVI - II : Sarazin, Shull&Woods ? */

/* Modifications: */
/* --------------- */
/*  IMPLEMENTED INTO ARNMAIN.FOR BY PETER BOCHSLER ON JUNE 20, 1994 */

/*  Adapted for SUN/UNIX by Peter Wurz, January 22, 1998 */
/* .......................................................................
 */
/* -----------------------------------------------------------------------
 */
/*  data for Shull and van Steenberg for Fe XVI-II */
/*     data a/0.43,3*0., .256,.452,2*0., .011,.0488,.0801,.529, */
/*    1  .131,0.,.613,.0849,  .129,.00092,.912,.192, */
/*    2  .0185,.0953,.079,1.23, .016,.0717,.0906,.739, */
/*    3  .00567,.0782,.0318,1.263, */
/*    4  .0336,.00253,1.92,.181, 1.23,3*0., */
/*    5  .12,.12,2*0., .19,.09,2*0., .26,.16,2*0., .24,.17,2*0., */
/*    6  .20,.30,2*0., .10,.53,2*0., .14,.46,2*0., .15,.63,2*0., */
/*    7  .29,.067,2*0., .25,.025,2*0., .12,.043,2*0., .038,.016,2*0., */
/*    8  .015,.0047,2*0., .0084,.0027,2*0., .0016,.000736,2*0./ */
/*  e1 for Fe XIII looks odd */
/*     data e1/5300.,3*0., 4625.,6000.,2*0., 0.1,36.2,306.,928., */
/*    1  73.2,0.,877.,316.,  80.3,39.1,919.,392., */
/*    2  13.2,66.6,297.,714., 23.7,85.1,329.,787., */
/*    3  16.2,96.0,330.,729., */
/*    4  117.,22.5,683.,341., 560.,3*0., */
/*    5  24.6,248.,2*0.,39.4,198.,2*0.,36.3,193.,2*0.,75.0,205.,2*0., */
/*    6  24.5,155.,2*0.,22.2,144.,2*0.,21.6,136.,2*0.,22.6,136.,2*0., */
/*    7  66.7,123.,2*0.,64.7,105.,2*0.,54.2,100.,2*0.,37.3,67.4,2*0., */
/*    8  28.6,52.1,2*0.,16.7,31.4,2*0.,5.12,12.9,2*0./ */
/*  SvS scaled for Fe XIII- XVI, with Zhdanov inner shell added : */
/*  Hahn for Fe XII and Fe VII */
/*  SvS high T scaled to Hahn for Fe X,XI */
/*  Burgess formula for Fe IX */
/*  SvS scaled to Hahn for Fe VIII, Fe II-VI */
/* -----------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------
 */
    ad = (float)0.;
    for (i__ = 1; i__ <= 4; ++i__) {
/* L10: */
	ad += a[i__ + (*n - *j + 1 << 2) - 5] * exp(-e1[i__ + (*n - *j + 1 << 
		2) - 5] * (float)11590. / *t);
    }
    ret_val = ad * pow_dd(t, &c_b41);
    return ret_val;
} /* alphadi_ */

/* Subroutine */ int ionsub_(z__, aktev, auto__, dir, rion)
integer *z__;
doublereal *aktev, *auto__, *dir, *rion;
{
    /* Initialized data */

    static integer iz[15] = { 1,2,6,7,8,10,11,12,13,14,16,18,20,26,28 };

    /* Format strings */
    static char fmt_1001[] = "(1x,\002ARNAUD> mismatch in input DIR.DAT:\002\
/,3(i2,\002 ?=? \002,i5,5x),/,\002 ARNAUD> The program is stopped in subrout\
ine\002,\002 IONSUB \002)";
    static char fmt_1002[] = "(1x,t9,\002at line\002,i6)";
    static char fmt_1003[] = "(1x,\002ARNAUD> Mismatch in input EA.DAT: \002\
,2(i2,\002 ?=? \002,i2,5x)/,1x,t10,\002at line \002,i6,/,1x,\002ARNAUD> The \
program is stopped!\002)";

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    integer s_wsfe(), do_fio(), e_wsfe();
    double exp(), d_lg10(), log();

    /* Local variables */
    static integer iele;
    extern /* Subroutine */ int dir_data__();
    static integer elno;
    static doublereal pion;
    static integer ion_line__, linestar;
    static doublereal a, b, c__, d__, e, redac, relea[6], x;
    extern /* Subroutine */ int redan_();
    static integer elmin;
    extern doublereal f2_();
    extern /* Subroutine */ int ea_();
    extern doublereal fa_(), fb_(), fc_(), fd_();
    static doublereal sa, sd;
    static integer nj, ir;
    extern doublereal fu_();
    static integer kr, linend;
    static doublereal sealog;
    static integer zr;
    static doublereal dirlog;
    static integer ilines[15], nlines;
    static doublereal autlog, sea;
    static integer iel, nel;
    static doublereal rel[5];
    static integer ion;

    /* Fortran I/O blocks */
    static cilist io___109 = { 0, 6, 0, fmt_1001, 0 };
    static cilist io___110 = { 0, 6, 0, fmt_1002, 0 };
    static cilist io___119 = { 0, 6, 0, fmt_1003, 0 };


/* ***********************************************************************
 */
/*     THIS PROGRAM IS A COMPLETE REWRITING FOLLOWING INSTRUCTIONS FROM */
/*     M. ARNAUD ON JUNE 20, 1994 */

/*     MODIFICATIONS: */
/*     -------------- */
/*     Peter Wurz, 19/08/1996: Changed to D_FLOAT format */
/*     Peter Wurz,  4/09/1996: enabled shared use of input data */
/*     Peter Wurz,  9/11/1997: removed reading of data files */
/*     Peter Wurz  20/01/1998: Adapted for SUN/UNIX */
/* -----------------------------------------------------------------------
 */
    /* Parameter adjustments */
    --rion;
    --dir;
    --auto__;

    /* Function Body */
/* ---------------------------------------------------------------------- 
*/
    for (iel = 1; iel <= 15; ++iel) {
	if (iel == 1) {
	    ilines[iel - 1] = 1;
	}
	if (iel > 1 && iel <= 7) {
	    ilines[iel - 1] = iz[iel - 1] - 1 << 1;
	}
	if (iel > 7 && iel <= 12) {
	    ilines[iel - 1] = iz[iel - 1] << 1;
	}
	if (iel == 13) {
	    ilines[iel - 1] = 42;
	}
	if (iel == 14) {
	    ilines[iel - 1] = 60;
	}
	if (iel == 15) {
	    ilines[iel - 1] = 66;
	}
	if (iz[iel - 1] == *z__) {
	    elno = iel;
	    elmin = iel - 1;
	    goto L101;
	}
/* L100: */
    }
L101:
    linend = 0;
    i__1 = elno;
    for (iel = 1; iel <= i__1; ++iel) {
	linend = ilines[iel - 1] + linend;
/* L110: */
    }
    linestar = linend - ilines[elno - 1];
    nlines = ilines[elno - 1];
    if (linestar > 0) {
	dir_data__(&linestar, &zr, &ir, &kr, rel);
    }
    ion_line__ = 0;
    i__1 = elmin;
    for (iel = 1; iel <= i__1; ++iel) {
	ion_line__ += iz[iel - 1];
/* L210: */
    }
    if (ion_line__ > 0) {
	ea_(&ion_line__, &zr, &ir, relea);
    }
/* ---------------------------------------- */
/*     reset array of rates */
/* ---------------------------------------- */
    i__1 = *z__;
    for (ion = 1; ion <= i__1; ++ion) {
	dir[ion] = 0.;
	auto__[ion] = 0.;
	rion[ion] = 0.;

	nel = *z__ - ion + 1;
	sd = 0.;
	nj = 1;
	if (nel > 2 && nel <= 10) {
	    nj = 2;
	}
	if (nel > 10 && nel <= 12) {
	    nj = 3;
	}
	if (nel > 12 && nel <= 18) {
	    nj = 2;
	}
	if (nel > 18) {
	    nj = 3;
	}
	if (*z__ == 11 && ion == 1) {
	    nj = 2;
	}
	i__2 = nj;
	for (iele = 1; iele <= i__2; ++iele) {
	    i__3 = linestar + iele;
	    dir_data__(&i__3, &zr, &ir, &kr, rel);
/*         .......................................................
.........*/
/*          exclude mismatches in dir.dat */
/*         .......................................................
.........*/
	    if (zr != *z__ || ir != ion || kr != iele) {
		s_wsfe(&io___109);
		do_fio(&c__1, (char *)&zr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&ir, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&ion, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&kr, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&iele, (ftnlen)sizeof(integer));
		e_wsfe();
		s_wsfe(&io___110);
		i__3 = linestar + iele;
		do_fio(&c__1, (char *)&i__3, (ftnlen)sizeof(integer));
		e_wsfe();
		return 0;
/* 		CALL EXIT(-1) */
	    }
/*          write(6,1002) zr,z,ir,ion,kr,iele,rel */
/* 1002     format(1h ,6(i2,1x),5(0pf11.5)) */
	    a = rel[1];
	    b = rel[2];
	    c__ = rel[3];
	    d__ = rel[4];
	    pion = rel[0];
	    x = pion / *aktev;
	    sa = a * fa_(&x) + b * fb_(&x) + c__ * fu_(&x) + d__ * x * f2_(&x)
		    ;
/*          if (x.gt.150.d0) x=150.d0 */
	    x = min(150.,x);
	    sd += sa * exp(-x) / x;
/* L300: */
	}
	linestar += nj;
/*        if (sd .lt. REAL_LOW) sd=REAL_LOW */
	sd = max(sd,1e-38);
	dirlog = d_lg10(&sd) + d_lg10(&c_b85) - d_lg10(aktev) * 1.5;
/* 	 if (dirlog.lt.-150.d0) dir(ion) = 0.0d0 */
/*        if (dirlog.ge.-150.d0) dir(ion) = 10.0d0**dirlog */
	if (dirlog < -70.) {
	    dir[ion] = 0.;
	}
	if (dirlog >= -70.) {
	    dir[ion] = exp(dirlog * log(10.));
	}
/* ------------------------------------------------------------------
----- */
/*     excitation autoionisation */
/* ------------------------------------------------------------------
----- */
	i__2 = ion_line__ + ion;
	ea_(&i__2, &zr, &ir, relea);
/* 	WRITE(6,*) ION_LINE+ION,ZR,IR,RELEA */
/*     ............................... */
/*     exclude mismatch in ea.dat */
/*     ............................... */
	if (zr != *z__ || ir != ion) {
	    s_wsfe(&io___119);
	    do_fio(&c__1, (char *)&zr, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ir, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ion, (ftnlen)sizeof(integer));
	    i__2 = ion_line__ + ion;
	    do_fio(&c__1, (char *)&i__2, (ftnlen)sizeof(integer));
	    e_wsfe();
	    return 0;
/*             CALL EXIT(-1) */
	}

	auto__[ion] = 0.;
	a = relea[1];
	b = relea[2];
	c__ = relea[3];
	d__ = relea[4];
	e = relea[5];
	pion = relea[0];
	if (pion >= 1e-6) {
	    x = pion / *aktev;
	    sea = a + b * fa_(&x) + c__ * fc_(&x) + d__ * fd_(&x) + e * fu_(&
		    x);
	    if (x > 150.) {
		x = 150.;
	    }
	    sealog = log(sea) - x;
	    autlog = log(1e-16) + log(6.692e7) + sealog - log(*aktev) * .5;
	    auto__[ion] = exp(autlog);
	}
/*     ......................................... */
/*     processus dit 'reda' (La Gattuta et Hahn) */
/*     ......................................... */
	if (*z__ == 26 && ion == 16) {
	    redan_(aktev, &redac);
	    auto__[ion] += redac;
	} else {
	    redac = 0.;
	}
	rion[ion] = dir[ion] + auto__[ion];
/*     write(6,1011)ion,rion(ion),dir(ion),auto(ion) */
/* L1011: */
/* L400: */
    }
/*      close(unit=5,status='keep') */
/*      close(unit=4,status='keep') */
    return 0;
} /* ionsub_ */

/* ==================================== */
doublereal fu_(x)
doublereal *x;
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(), pow_dd(), exp();

    /* Local variables */
    static doublereal r__, q2, eps;

/* ==================================== */
/* ------------------------------------ */
    if (*x >= (float)10.) {
	goto L1;
    }
    if (*x <= (float).02) {
	goto L2;
    }
/* APPROXIMATION FROM M-S-(1978) */
    if (*x < (float)1.5) {
	eps = (float)-.5;
    }
    if (*x >= (float)1.5) {
	eps = (float).5;
    }
    r__ = (*x + (float)1.) / *x;
    q2 = (float)1. / ((*x + (float)1.) * (*x + (float)1.));
    d__1 = *x + (float).01;
    ret_val = log(r__) - (pow_dd(&d__1, &eps) * (float).03 + (float).36) * q2;
    return ret_val;
L1:
    ret_val = ((float)1. - (float)1. / *x + (float)2. / (*x * *x) - (float)6. 
	    / (*x * *x * *x)) / *x;
    return ret_val;
L2:
    ret_val = exp(*x) * (-log(*x) - (float).5772 + *x);
    return ret_val;
} /* fu_ */

/* ==================================== */
doublereal fa_(x)
doublereal *x;
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal fu_();

/* ==================================== */
/* ------------------------------------ */
    if (*x < 10.) {
	ret_val = (float)1. - *x * fu_(x);
    } else {
	ret_val = ((float)1. - (float)2. / *x + (float)6. / (*x * *x) - (
		float)24. / (*x * *x * *x) + (float)120. / (*x * *x * *x * *x)
		) / *x;
    }
    return ret_val;
} /* fa_ */

/* ==================================== */
doublereal fc_(x)
doublereal *x;
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal fa_();

/* ==================================== */
/* ------------------------------------ */
    if (*x < 10.) {
	ret_val = (float)1. - *x * fa_(x);
	return ret_val;
    } else {
	ret_val = (float)2. / *x - (float)6. / (*x * *x) + (float)24. / (*x * 
		*x * *x) - (float)120. / (*x * *x * *x * *x);
	return ret_val;
    }
    return ret_val;
} /* fc_ */

/* ==================================== */
doublereal fd_(x)
doublereal *x;
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal fu_();

/* ==================================== */
/* ------------------------------------ */
    if (*x <= 10.) {
	ret_val = (float)1. - *x * (float).5 * ((float)1. - *x + *x * *x * 
		fu_(x));
	return ret_val;
    } else {
	ret_val = (float)3. / *x - (float)12. / (*x * *x) + (float)60. / (*x *
		 *x * *x) - (float)360. / (*x * *x * *x * *x);
	return ret_val;
    }
    return ret_val;
} /* fd_ */

/* ==================================== */
doublereal fb_(x)
doublereal *x;
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal fu_();

/* ==================================== */
/* ------------------------------------ */
    if (*x < (float)1.) {
	ret_val = *x + (float)1. - *x * fu_(x) * (*x + (float)2.);
	return ret_val;
    } else {
	ret_val = *x * (float)2. * *x * *x * *x + *x * (float)60. * *x * *x + 
		*x * (float)540. * *x + *x * (float)1512. + (float)720.;
	ret_val /= *x * *x * *x * *x * *x + *x * (float)35. * *x * *x * *x + *
		x * (float)416. * *x * *x + *x * (float)2016. * *x + *x * (
		float)3708. + (float)1764.;
	ret_val *= fu_(x);
	return ret_val;
    }
    return ret_val;
} /* fb_ */

/* ============================================================ */
doublereal f2_(x)
doublereal *x;
{
    /* Initialized data */

    static doublereal ap[14] = { 216.5775917955525,20335.87105342909,
	    1091065.065646484,37113995.80079484,839632734.5237503,
	    12889181495.8338,134485688395.1851,940017194190.2539,
	    4257075535864.156,11743045765010.,17548675040595.69,
	    10806301481873.69,497762010031.9121,0. };
    static doublereal aq[14] = { 219.5775917955525,20983.60382881574,
	    1151650.523623183,40348832.60913706,949001856.5225945,
	    15344557192.30511,171816484158.5205,1324851363645.336,
	    6907059906460.437,23530911226128.37,49432218469424.25,
	    57760157441864.25,30225385876839.5,3364065905726.312 };

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal u, u2, u3, u4, ad, an;
    static integer ii;
    static doublereal ue;


/* Adapted for use at SUN/UNIX by Peter Wurz, January 23, 1998 */
/* ============================================================ */
/* ------------------------------------ */
    u = (float)1. / *x;
    if (*x < (float)10.) {
	u2 = u * u;
	u3 = u2 * u;
	u4 = u3 * u;
	ret_val = (u * (float).01345 - (float)5.725e-4 + u2 * (float).8691 + 
		u3 * (float).03404) / (u * (float)2.197 + (float)1. + u2 * (
		float).2454 + u3 * (float).002053);
    } else {
	an = 1.;
	ad = 1.;
	ue = 1.;
	for (ii = 1; ii <= 14; ++ii) {
	    ue *= u;
/* 	           AN=AN + AP(II)*(U**II ) */
/*  	           AD=AD + AQ(II)*(U**II ) */
	    an += ap[ii - 1] * ue;
	    ad += aq[ii - 1] * ue;
/* L200: */
	}
	ret_val = an * u * u / ad;
    }
    return ret_val;
} /* f2_ */

/****************************************************************************
****/
/*     subroutine redan */

/* MODIFICATIONS: */
/* --------------- */
/*     implemented on June 20, 1994 by P. Bochsler */
/*     Adapted for SUN/UNIX , January 22, 1998 by Peter Wurz */
/* ....................................................................... */
/* Subroutine */ int redan_(aktev, redac)
doublereal *aktev, *redac;
{
    /* Initialized data */

    static doublereal redas[12] = { .55,.6,2.7,1.5,.4,.1,.8,.7,1.15,.65,.65,
	    .2 };

    /* Builtin functions */
    double exp(), sqrt();

    /* Local variables */
    static integer k;
    static doublereal ed, fd, ef, ff, yd, sk, yf;

/* -----------------------------------------------------------------------
 */
    sk = 0.;
    for (k = 1; k <= 12; ++k) {
	ed = (doublereal) (k - 1) * 20. + 720.;
	ef = ed + 20.;
	yd = ed / *aktev;
	yf = ef / *aktev;
	fd = exp(-yd) * (yd + 1.);
	ff = exp(-yf) * (yf + 1.);
	sk += redas[k - 1] * 1e-19 * (fd - ff);
/* L2: */
    }
    *redac = sk * 6.692e7 * sqrt(*aktev);
    return 0;
} /* redan_ */

/* Subroutine */ int dir_data__(index, zr, ir, kr, rel)
integer *index, *zr, *ir, *kr;
doublereal *rel;
{
    /* Initialized data */

    static doublereal dir_data_1__[792]	/* was [8][99] */ = { 1.,1.,1.,13.6,
	    22.8,-12.,1.9,-22.6,2.,1.,1.,24.6,17.8,-11.,7.,-23.2,2.,2.,1.,
	    54.4,14.4,-5.6,1.9,-13.3,6.,1.,1.,11.3,6.,-16.,12.,-15.1,6.,1.,2.,
	    16.6,24.3,-7.8,2.5,-24.,6.,2.,1.,24.4,17.3,-9.,2.5,-13.6,6.,2.,2.,
	    30.9,23.7,-7.6,2.5,-21.7,6.,3.,1.,47.9,23.2,-7.4,2.5,-19.4,6.,3.,
	    2.,325.,20.,-5.6,4.1,-18.,6.,4.,1.,64.5,8.2,-2.7,1.4,-6.6,6.,4.,
	    2.,343.,20.,-5.6,4.1,-18.,6.,5.,1.,392.,20.4,-6.1,4.5,-18.,6.,6.,
	    1.,490.,12.2,-3.9,1.9,-10.3,7.,1.,1.,14.5,19.5,-30.5,15.,-29.,7.,
	    1.,2.,20.3,19.,-4.5,2.8,-20.2,7.,2.,1.,29.6,25.,-6.3,5.3,-25.7,7.,
	    2.,2.,36.7,18.5,-4.3,2.8,-18.,7.,3.,1.,47.4,16.,-7.5,2.3,-10.,7.,
	    3.,2.,55.8,18.1,-4.,2.8,-15.8,7.,4.,1.,77.5,17.6,-3.8,2.8,-13.6,
	    7.,4.,2.,471.,20.5,-5.8,4.1,-18.,7.,5.,1.,97.9,10.5,-3.3,1.4,-7.7,
	    7.,5.,2.,493.,20.5,-5.8,4.1,-18.,7.,6.,1.,552.,20.8,-6.3,4.4,
	    -18.2,7.,7.,1.,667.,12.3,-4.,1.9,-10.3,8.,1.,1.,13.6,3.5,-18.5,
	    15.6,-16.6,8.,1.,2.,28.5,18.2,-4.,2.8,-20.2,8.,2.,1.,35.1,26.,-8.,
	    8.4,-28.2,8.,2.,2.,42.6,17.8,-3.9,2.8,-18.1,8.,3.,1.,54.9,25.,-7.,
	    5.,-18.,8.,3.,2.,63.8,17.3,-3.5,2.9,-16.1,8.,4.,1.,77.4,15.,-5.,
	    2.2,-10.5,8.,4.,2.,87.6,16.8,-3.3,2.8,-14.1,8.,5.,1.,114.,16.4,
	    -3.,2.9,-12.,8.,5.,2.,644.,20.8,-6.,4.1,-18.,8.,6.,1.,138.,10.9,
	    -3.19,1.4,-9.21,8.,6.,2.,670.,20.8,-6.,4.1,-18.,8.,7.,1.,739.,
	    21.2,-6.5,4.3,-18.4,8.,8.,1.,871.,12.3,-4.,1.9,-10.3,10.,1.,1.,
	    21.6,40.,-42.,18.,-56.,10.,1.,2.,48.5,19.1,-4.9,2.8,-21.8,10.,2.,
	    1.,41.1,33.8,-20.4,15.5,-46.,10.,2.,2.,66.4,18.6,-4.7,2.8,-20.2,
	    10.,3.,1.,63.5,7.5,-17.5,25.,-19.7,10.,3.,2.,86.2,18.2,-4.4,2.8,
	    -18.4,10.,4.,1.,97.1,34.,-10.,7.5,-25.,10.,4.,2.,108.,17.8,-4.1,
	    2.8,-16.7,10.,5.,1.,126.,25.5,-8.5,4.5,-16.8,10.,5.,2.,139.,17.4,
	    -3.8,2.8,-14.9,10.,6.,1.,158.,14.5,-4.6,1.9,-8.5,10.,6.,2.,172.,
	    16.9,-3.4,2.8,-13.2,10.,7.,1.,207.,16.5,-3.1,2.8,-11.4,10.,7.,2.,
	    1073.,21.5,-6.4,4.1,-18.,10.,8.,1.,239.,10.1,-3.1,1.4,-7.1,10.,8.,
	    2.,1107.,21.5,-6.4,4.1,-18.,10.,9.,1.,1196.,21.9,-6.8,4.2,-18.7,
	    10.,10.,1.,1362.,12.5,-4.1,1.9,-10.4,11.,1.,1.,5.1,16.,-1.,.2,
	    -13.5,11.,1.,2.,34.,63.9,-27.,33.,-80.,11.,2.,1.,47.3,48.5,-33.5,
	    19.4,-65.9,11.,2.,2.,80.1,19.2,-5.3,2.8,-21.2,11.,3.,1.,71.7,50.1,
	    -20.2,14.8,-41.7,11.,3.,2.,102.,18.8,-5.,2.8,-19.6,11.,4.,1.,99.,
	    43.3,-16.3,10.7,-33.4,11.,4.,2.,126.,18.4,-4.7,2.8,-18.,11.,5.,1.,
	    138.,35.1,-12.4,7.2,-25.1,11.,5.,2.,151.,18.3,-4.3,2.8,-16.3,11.,
	    6.,1.,172.,25.5,-8.5,4.2,-16.8,11.,6.,2.,186.,17.6,-4.,2.8,-14.7,
	    11.,7.,1.,208.,14.5,-4.6,1.8,-8.5,11.,7.,2.,224.,17.2,-3.7,2.8,
	    -13.1,11.,8.,1.,264.,16.8,-3.4,2.8,-11.4,11.,8.,2.,1328.,21.7,
	    -6.5,4.1,-18.,11.,9.,1.,300.,10.,-3.,1.4,-6.9,11.,9.,2.,1366.,
	    21.7,-6.5,4.1,-18.,11.,10.,1.,1465.,22.2,-7.,4.2,-18.8,11.,11.,1.,
	    1649.,12.5,-4.1,1.9,-10.4,12.,1.,1.,7.6,18.,-1.,.6,-4.,12.,1.,2.,
	    54.,37.7,-30.,24.8,-62.,12.,1.,3.,92.2,17.6,-5.2,3.3,-19.,12.,2.,
	    1.,15.,9.,-3.6,.3,-5.4,12.,2.,2.,65.,37.7,-30.,24.8,-62.,12.,2.,
	    3.,104.5,17.6,-5.2,3.3,-19.,12.,3.,1.,80.1,55.5,-24.1,18.7,-65.,
	    12.,3.,2.,119.,19.3,-5.6,2.8,-20.5,12.,4.,1.,109.,50.1,-20.2,14.2,
	    -41.7,12.,4.,2.,144.,19.1,-5.3,2.8,-19.,12.,5.,1.,141.,43.3,-16.3,
	    10.3,-33.4,12.,5.,2.,172.,18.6,-4.9,2.8,-17.5,12.,6.,1.,187.,35.1,
	    -12.4,6.9,-25.1,12.,6.,2.,201.,18.4,-4.6,2.8,-16.,12.,7.,1.,225.,
	    25.5,-8.5,4.1,-16.8,12.,7.,2.,241.,18.,-4.3,2.8,-14.5,12.,8.,1.,
	    266.,14.5,-4.6,1.8,-8.5,12.,8.,2.,283.,17.5,-4.,2.8,-13.,12.,9.,
	    1.,328.,17.1,-3.6,2.7,-11.5,12.,9.,2.,1611.,22.,-6.7,4.1,-18.,12.,
	    10.,1.,367.,10.,-3.,1.4,-6.8,12.,10.,2.,1653.,22.,-6.7,4.1,-18. };
    static doublereal dir_data_2__[800]	/* was [8][100] */ = { 12.,11.,1.,
	    1762.,22.4,-7.1,4.1,-18.9,12.,12.,1.,1963.,12.6,-4.2,1.9,-10.4,
	    13.,1.,1.,6.,47.,-26.,.6,-39.,13.,1.,2.,10.6,55.1,-37.2,1.4,-41.,
	    13.,2.,1.,18.8,17.,-6.,1.,-8.,13.,2.,2.,90.,31.3,-22.7,21.,-44.1,
	    13.,2.,3.,131.,12.1,-3.5,3.3,-13.1,13.,3.,1.,28.4,6.3,-2.4,.5,
	    -4.1,13.,3.,2.,103.,31.3,-22.7,21.,-44.1,13.,3.,3.,145.6,12.1,
	    -3.5,3.3,-13.1,13.,4.,1.,120.,69.8,-23.7,18.,-69.8,13.,4.,2.,164.,
	    19.5,-5.9,2.8,-19.8,13.,5.,1.,154.,60.8,-20.2,13.7,-41.7,13.,5.,
	    2.,194.,19.2,-5.5,2.8,-18.4,13.,6.,1.,190.,49.5,-16.3,9.9,-33.4,
	    13.,6.,2.,225.,18.9,-5.2,2.8,-17.1,13.,7.,1.,241.,38.3,-12.4,6.7,
	    -25.1,13.,7.,2.,258.,18.5,-4.8,2.8,-15.7,13.,8.,1.,285.,27.,-8.5,
	    3.9,-16.8,13.,8.,2.,302.,18.2,-4.5,2.8,-14.3,13.,9.,1.,330.,14.,
	    -4.6,1.7,-8.5,13.,9.,2.,350.,17.9,-4.1,2.8,-13.,13.,10.,1.,399.,
	    17.4,-3.8,2.7,-11.6,13.,10.,2.,1921.,22.2,-6.8,4.1,-18.,13.,11.,
	    1.,442.,9.9,-3.,1.4,-6.7,13.,11.,2.,1967.,22.2,-6.8,4.1,-18.,13.,
	    12.,1.,2086.,22.7,-7.2,4.1,-19.,13.,13.,1.,2304.,12.6,-4.2,1.9,
	    -10.4,14.,1.,1.,8.1,74.5,-49.4,1.3,-54.6,14.,1.,2.,13.5,53.8,
	    -35.8,1.4,-40.7,14.,2.,1.,16.3,50.4,-33.4,.6,-36.9,14.,2.,2.,22.9,
	    55.1,-37.2,1.4,-41.,14.,3.,1.,33.5,19.8,-5.7,1.3,-11.9,14.,3.,2.,
	    133.,66.7,-24.8,18.7,-65.,14.,3.,3.,176.6,22.,-7.2,3.3,-20.9,14.,
	    4.,1.,45.1,9.,-3.,.6,-5.8,14.,4.,2.,148.,66.7,-24.8,18.7,-65.,14.,
	    4.,3.,193.5,22.,-7.2,3.3,-20.9,14.,5.,1.,167.,70.8,-23.4,17.4,
	    -64.2,14.,5.,2.,217.,19.6,-6.2,2.8,-19.,14.,6.,1.,205.,60.8,-20.2,
	    13.2,-41.7,14.,6.,2.,250.,19.3,-5.8,2.8,-17.8,14.,7.,1.,246.,49.5,
	    -16.3,9.6,-33.4,14.,7.,2.,285.,19.,-5.4,2.8,-16.6,14.,8.,1.,303.,
	    38.3,-12.4,6.4,-25.1,14.,8.,2.,321.,18.6,-5.1,2.8,-15.4,14.,9.,1.,
	    351.,27.,-8.5,3.8,-16.8,14.,9.,2.,371.,18.3,-4.7,2.8,-14.1,14.,
	    10.,1.,401.,14.,-4.6,1.6,-8.5,14.,10.,2.,423.,18.,-4.3,2.8,-12.9,
	    14.,11.,1.,476.,17.7,-4.,2.7,-11.7,14.,11.,2.,2259.,22.4,-6.9,4.1,
	    -18.,14.,12.,1.,523.,9.8,-2.9,1.4,-6.6,14.,12.,2.,2309.,22.4,-6.9,
	    4.1,-18.,14.,13.,1.,2438.,22.9,-7.3,4.,-19.1,14.,14.,1.,2673.,
	    12.7,-4.3,1.9,-10.4,16.,1.,1.,10.4,6.,-22.,20.,-20.,16.,1.,2.,
	    20.2,51.3,-33.2,1.4,-40.2,16.,2.,1.,23.4,98.7,-65.4,1.9,-72.3,16.,
	    2.,2.,30.7,52.5,-34.5,1.4,-40.5,16.,3.,1.,35.,74.5,-49.4,1.3,
	    -54.6,16.,3.,2.,43.8,53.8,-35.8,1.4,-40.7,16.,4.,1.,47.3,50.4,
	    -33.4,.6,-36.9,16.,4.,2.,57.6,55.1,-37.2,1.4,-41.,16.,5.,1.,72.7,
	    19.8,-5.7,1.6,-11.9,16.,5.,2.,239.,73.2,-27.,15.8,-61.1,16.,5.,3.,
	    288.2,23.1,-8.,3.3,-19.5,16.,6.,1.,88.1,9.,-2.8,.7,-5.4,16.,6.,2.,
	    257.,73.2,-27.,15.8,-61.1,16.,6.,3.,309.7,23.1,-8.,3.3,-19.5,16.,
	    7.,1.,281.,72.,-21.7,14.2,-55.9,16.,7.,2.,343.,19.6,-6.8,2.8,
	    -17.5,16.,8.,1.,328.,60.8,-20.2,10.9,-41.7,16.,8.,2.,384.,19.3,
	    -6.3,2.8,-16.6,16.,9.,1.,379.,49.5,-16.3,8.,-33.4,16.,9.,2.,426.,
	    19.1,-5.9,2.8,-15.6,16.,10.,1.,447.,38.3,-12.4,5.5,-25.1,16.,10.,
	    2.,469.,18.8,-5.5,2.8,-14.7,16.,11.,1.,505.,27.,-8.5,3.3,-16.8,
	    16.,11.,2.,528.,18.6,-5.1,2.8,-13.7,16.,12.,1.,564.,14.,-4.6,1.5,
	    -8.5,16.,12.,2.,589.,18.3,-4.7,2.8,-12.8,16.,13.,1.,652.,18.1,
	    -4.4,2.7,-11.8,16.,13.,2.,3017.,22.8,-7.1,4.1,-18.,16.,14.,1.,
	    707.,9.7,-2.8,1.4,-6.4,16.,14.,2.,3075.,22.8,-7.1,4.1,-18.,16.,
	    15.,1.,3224.,23.3,-7.6,4.,-19.3,16.,16.,1.,3493.,12.8,-4.3,1.9,
	    -10.5,18.,1.,1.,15.8,171.1,-78.,3.8,-169.,18.,1.,2.,29.2,48.7,
	    -30.5,1.4,-39.7,18.,2.,1.,27.6,147.,-97.4,3.2,-107.7,18.,2.,2.,
	    41.7,50.,-31.8,1.4,-40.,18.,3.,1.,40.9,122.8,-81.4,2.6,-90.,18.,
	    3.,2.,55.5,51.3,-33.2,1.4,-40.2,18.,4.,1.,59.7,98.7,-65.4,1.9,
	    -72.3,18.,4.,2.,70.4,52.5,-34.5,1.4,-40.5,18.,5.,1.,75.2,74.5,
	    -49.4,1.3,-54.6,18.,5.,2.,87.6,53.8,-35.8,1.4,-40.7,18.,6.,1.,
	    91.2,50.4,-33.4,.6,-36.9,18.,6.,2.,105.,55.1,-37.2,1.4,-41. };
    static doublereal dir_data_3__[800]	/* was [8][100] */ = { 18.,7.,1.,125.,
	    19.8,-5.7,1.9,-11.9,18.,7.,2.,373.,74.8,-27.,14.1,-58.6,18.,7.,3.,
	    427.,23.4,-8.3,3.3,-18.5,18.,8.,1.,143.,9.,-2.7,.8,-5.4,18.,8.,2.,
	    394.,74.8,-27.,14.1,-58.6,18.,8.,3.,453.1,23.4,-8.3,3.3,-18.5,18.,
	    9.,1.,423.,72.6,-19.9,11.9,-51.,18.,9.,2.,498.,19.6,-7.3,2.8,-16.,
	    18.,10.,1.,479.,60.8,-20.2,9.3,-41.7,18.,10.,2.,545.,19.4,-6.8,
	    2.8,-15.3,18.,11.,1.,539.,49.5,-16.3,6.9,-33.4,18.,11.,2.,594.,
	    19.2,-6.4,2.8,-14.6,18.,12.,1.,618.,38.3,-12.4,4.8,-25.1,18.,12.,
	    2.,644.,18.9,-5.9,2.8,-14.,18.,13.,1.,686.,27.,-8.5,3.,-16.8,18.,
	    13.,2.,713.,18.7,-5.4,2.8,-13.3,18.,14.,1.,755.,14.,-4.6,1.4,-8.5,
	    18.,14.,2.,784.,18.5,-5.,2.8,-12.6,18.,15.,1.,855.,18.4,-4.6,2.7,
	    -12.,18.,15.,2.,3885.,23.1,-7.3,4.1,-18.,18.,16.,1.,918.,9.6,-2.8,
	    1.4,-6.2,18.,16.,2.,3951.,23.1,-7.3,4.1,-18.,18.,17.,1.,4121.,
	    23.7,-7.8,3.9,-19.5,18.,18.,1.,4426.,12.8,-4.4,1.9,-10.5,20.,1.,
	    1.,6.1,2.5,-2.5,8.,-5.5,20.,1.,2.,28.,74.3,-24.2,7.,-63.,20.,1.,
	    3.,40.3,17.6,-3.8,1.9,-13.8,20.,2.,1.,11.9,7.9,-2.,.2,-6.,20.,2.,
	    2.,37.,74.3,-24.2,7.,-63.,20.,2.,3.,45.2,17.6,-3.8,1.9,-13.8,20.,
	    3.,1.,51.2,74.3,-24.2,7.,-63.,20.,3.,2.,70.1,17.6,-3.8,1.95,-13.8,
	    20.,4.,1.,67.3,55.8,-15.8,6.4,-44.5,20.,4.,2.,86.4,16.2,-3.2,1.77,
	    -11.6,20.,5.,1.,84.5,47.1,-14.5,4.75,-35.5,20.,5.,2.,104.,18.9,
	    -5.13,1.62,-13.2,20.,6.,1.,109.,40.9,-13.6,3.44,-30.1,20.,6.,2.,
	    123.,20.4,-6.33,2.13,-13.8,20.,7.,1.,128.,22.9,-7.4,2.84,-15.9,
	    20.,7.,2.,144.,21.9,-7.7,1.9,-14.9,20.,8.,1.,148.,11.1,-3.35,1.26,
	    -7.3,20.,8.,2.,165.,22.7,-8.65,1.89,-15.5,20.,9.,1.,189.,19.8,
	    -5.7,1.75,-11.9,20.,9.,2.,534.,76.1,-27.,12.8,-56.6,20.,9.,3.,
	    593.1,23.5,-8.4,3.3,-17.8,20.,10.,1.,211.,9.,-2.6,.9,-5.4,20.,10.,
	    2.,559.,76.1,-27.,12.8,-56.6,20.,10.,3.,623.7,23.5,-8.4,3.3,-17.8,
	    20.,11.,1.,592.,76.5,-24.5,10.3,-50.5,20.,11.,2.,680.,19.5,-7.8,
	    2.8,-14.5,20.,12.,1.,657.,60.8,-20.2,8.1,-41.7,20.,12.,2.,734.,
	    19.4,-7.3,2.8,-14.1,20.,13.,1.,727.,49.5,-16.3,6.1,-33.4,20.,13.,
	    2.,790.,19.2,-6.8,2.8,-13.7,20.,14.,1.,818.,38.3,-12.4,4.3,-25.1,
	    20.,14.,2.,847.,19.,-6.3,2.8,-13.2,20.,15.,1.,894.,27.,-8.5,2.7,
	    -16.8,20.,15.,2.,925.,18.9,-5.8,2.8,-12.8,20.,16.,1.,974.,14.,
	    -4.6,1.3,-8.5,20.,16.,2.,1006.,18.7,-5.3,2.8,-12.4,20.,17.,1.,
	    1087.,18.6,-4.6,2.7,-12.1,20.,17.,2.,4865.,23.4,-7.4,4.1,-18.,20.,
	    18.,1.,1157.,9.5,-2.7,1.4,-6.1,20.,18.,2.,4939.,23.4,-7.4,4.1,
	    -18.,20.,19.,1.,5129.,24.,-7.9,3.9,-19.6,20.,20.,1.,5470.,12.9,
	    -4.4,1.9,-10.5,26.,1.,1.,7.9,31.9,-15.,.32,-28.1,26.,1.,2.,9.,15.,
	    -16.7,7.,-12.7,26.,1.,3.,59.,115.,-72.4,9.57,-107.,26.,2.,1.,
	    16.18,17.4,-3.27,.16,-10.16,26.,2.,2.,24.83,30.12,-38.82,18.6,
	    -45.72,26.,2.,3.,83.37,115.,-72.4,9.57,-107.,26.,3.,1.,34.75,
	    84.77,-67.6,21.,-84.08,26.,3.,2.,93.28,87.7,-49.6,11.4,-84.8,26.,
	    3.,3.,131.9,25.9,-11.7,2.32,-23.9,26.,4.,1.,53.74,77.4,-43.9,19.6,
	    -81.9,26.,4.,2.,111.9,79.1,-30.,8.38,-74.6,26.,4.,3.,151.,16.7,
	    -3.44,2.32,-15.1,26.,5.,1.,75.15,48.1,-20.4,16.2,-48.4,26.,5.,2.,
	    132.7,66.8,-18.9,9.29,-60.5,26.,5.,3.,172.4,13.4,-.41,2.33,-10.9,
	    26.,6.,1.,98.69,36.9,-11.8,10.3,-31.5,26.,6.,2.,155.5,67.,-18.6,
	    9.43,-56.5,26.,6.,3.,195.8,12.7,-.086,2.42,-8.97,26.,7.,1.,124.2,
	    14.6,-4.36,5.98,-10.5,26.,7.,2.,180.,67.9,-20.6,9.82,-53.7,26.,7.,
	    3.,220.9,15.6,-2.29,2.3,-10.6,26.,8.,1.,151.7,14.3,-4.44,2.45,
	    -9.53,26.,8.,2.,213.,69.9,-23.7,9.5,-51.7,26.,8.,3.,249.,19.2,
	    -5.7,2.3,-12.7,26.,9.,1.,235.,69.9,-23.7,9.5,-51.7,26.,9.,2.,271.,
	    19.2,-5.7,2.3,-12.7,26.,10.,1.,262.,57.7,-18.6,7.8,-40.3,26.,10.,
	    2.,297.,21.,-7.1,2.3,-14.1,26.,11.,1.,290.,45.6,-13.9,6.2,-30.,
	    26.,11.,2.,324.,22.8,-8.4,2.3,-15.4,26.,12.,1.,331.,39.2,-9.7,4.4,
	    -20.8,26.,12.,2.,356.,24.6,-9.8,2.3,-16.8,26.,13.,1.,361.,21.3,
	    -5.9,3.,-12.6,26.,13.,2.,388.,26.4,-11.2,2.3,-18.1 };
    static doublereal dir_data_4__[736]	/* was [8][92] */ = { 26.,14.,1.,392.,
	    9.1,-2.6,1.4,-5.6,26.,14.,2.,421.,28.2,-12.5,2.3,-19.4,26.,15.,1.,
	    457.,19.8,-5.7,2.1,-11.9,26.,15.,2.,1185.,78.9,-27.,10.6,-52.8,
	    26.,15.,3.,1254.3,23.5,-7.8,3.3,-16.5,26.,16.,1.,490.,9.,-2.6,1.,
	    -5.4,26.,16.,2.,1223.,78.9,-27.,10.6,-52.8,26.,16.,3.,1298.6,23.5,
	    -7.8,3.3,-16.5,26.,17.,1.,1265.,82.2,-26.4,6.1,-49.8,26.,17.,2.,
	    1397.,19.2,-5.5,2.8,-12.3,26.,18.,1.,1358.,68.5,-22.,5.1,-41.5,
	    26.,18.,2.,1471.,19.2,-5.5,2.8,-12.3,26.,19.,1.,1456.,54.8,-17.6,
	    4.1,-33.2,26.,19.,2.,1548.,19.2,-5.5,2.8,-12.3,26.,20.,1.,1582.,
	    41.1,-13.2,3.1,-24.9,26.,20.,2.,1622.,19.2,-5.5,2.8,-12.3,26.,21.,
	    1.,1689.,27.4,-8.8,2.,-16.6,26.,21.,2.,1731.,19.2,-5.5,2.8,-12.3,
	    26.,22.,1.,1799.,13.7,-4.4,1.,-8.3,26.,22.,2.,1842.,19.2,-5.5,2.8,
	    -12.3,26.,23.,1.,1950.,19.2,-5.3,2.7,-12.3,26.,23.,2.,8482.,24.1,
	    -7.9,4.1,-18.,26.,24.,1.,2045.,9.3,-2.6,1.4,-5.8,26.,24.,2.,8580.,
	    24.1,-7.9,4.1,-18.,26.,25.,1.,8828.,24.8,-8.4,3.8,-20.,26.,26.,1.,
	    9278.,13.,-4.5,1.9,-10.6,28.,1.,1.,8.7,2.5,-.8,.2,-1.2,28.,1.,2.,
	    10.,12.6,-4.,.4,-6.1,28.,1.,3.,73.,69.9,-23.7,9.5,-51.7,28.,2.,1.,
	    18.2,32.2,-10.,1.,-15.4,28.,2.,2.,97.,69.9,-23.7,9.5,-51.7,28.,2.,
	    3.,142.,19.2,-5.7,2.3,-12.7,28.,3.,1.,35.2,44.4,-14.1,1.4,-21.5,
	    28.,3.,2.,122.,69.9,-23.7,9.5,-51.7,28.,3.,3.,166.,19.2,-5.7,2.3,
	    -12.7,28.,4.,1.,54.9,50.3,-16.,1.6,-24.3,28.,4.,2.,146.,69.9,
	    -23.7,9.5,-51.7,28.,4.,3.,190.,19.2,-5.7,2.3,-12.7,28.,5.,1.,75.5,
	    49.9,-15.9,1.6,-24.1,28.,5.,2.,171.,69.9,-23.7,9.5,-51.7,28.,5.,
	    3.,215.,19.2,-5.7,2.3,-12.7,28.,6.,1.,108.,50.8,-16.1,1.6,-24.6,
	    28.,6.,2.,196.,69.9,-23.7,9.5,-51.7,28.,6.,3.,239.,19.2,-5.7,2.3,
	    -12.7,28.,7.,1.,133.,43.2,-13.7,1.3,-20.9,28.,7.,2.,221.,69.9,
	    -23.7,9.5,-51.7,28.,7.,3.,264.,19.2,-5.7,2.3,-12.7,28.,8.,1.,162.,
	    34.5,-10.9,1.1,-16.7,28.,8.,2.,246.,69.9,-23.7,9.5,-51.7,28.,8.,
	    3.,288.,19.2,-5.7,2.3,-12.7,28.,9.,1.,193.,24.1,-7.7,.7,-11.7,28.,
	    9.,2.,271.,69.9,-23.7,9.5,-51.7,28.,9.,3.,313.,19.2,-5.7,2.3,
	    -12.7,28.,10.,1.,225.,12.5,-4.,.4,-6.,28.,10.,2.,296.,69.9,-23.7,
	    9.5,-51.7,28.,10.,3.,338.,19.2,-5.7,2.3,-12.7,28.,11.,1.,321.,
	    69.9,-23.7,9.5,-51.7,28.,11.,2.,363.,19.2,-5.7,2.3,-12.7,28.,12.,
	    1.,352.,57.7,-18.6,7.8,-40.3,28.,12.,2.,393.,21.,-7.1,2.3,-14.1,
	    28.,13.,1.,384.,45.6,-13.9,6.2,-30.,28.,13.,2.,423.,22.8,-8.4,2.3,
	    -15.4,28.,14.,1.,430.,33.4,-9.7,4.6,-20.8,28.,14.,2.,458.,24.6,
	    -9.8,2.3,-16.8,28.,15.,1.,464.,21.3,-5.9,3.,-12.6,28.,15.,2.,494.,
	    26.4,-11.2,2.3,-18.1,28.,16.,1.,499.,9.1,-2.6,1.4,-5.6,28.,16.,2.,
	    531.,28.2,-12.5,2.3,-19.4,28.,17.,1.,571.,19.8,-5.7,2.2,-11.9,28.,
	    17.,2.,1458.,79.6,-27.,10.1,-51.9,28.,17.,3.,1529.1,23.5,-7.8,3.3,
	    -16.2,28.,18.,1.,608.,9.,-2.6,1.,-5.4,28.,18.,2.,1500.,79.6,-27.,
	    10.1,-51.9,28.,18.,3.,1578.,23.5,-7.8,3.3,-16.2,28.,19.,1.,1546.4,
	    71.69,-23.19,10.71,-45.63,28.,19.,2.,1692.1,16.33,-5.04,3.52,
	    -11.47,28.,20.,1.,1655.5,61.24,-19.16,7.78,-38.09,28.,20.,2.,
	    1786.4,16.49,-5.11,3.44,-11.41,28.,21.,1.,1756.,49.29,-15.28,5.77,
	    -30.11,28.,21.,2.,1882.9,16.36,-4.97,3.35,-11.09,28.,22.,1.,
	    1882.5,37.12,-11.41,4.02,-22.3,28.,22.,2.,2179.8,16.08,-4.78,3.26,
	    -10.62,28.,23.,1.,2000.3,24.76,-7.54,2.5,-14.64,28.,23.,2.,2082.6,
	    15.74,-4.47,3.18,-10.13,28.,24.,1.,2131.,13.41,-3.76,1.16,-7.24,
	    28.,24.,2.,2185.6,15.52,-4.27,3.09,-9.74,28.,25.,1.,2290.9,15.46,
	    -4.18,3.01,-9.52,28.,25.,2.,9914.,24.3,-8.,4.1,-18.,28.,26.,1.,
	    2401.2,7.82,-2.13,1.48,-4.77,28.,26.,2.,10150.,23.37,-9.12,4.02,
	    -19.82,28.,27.,1.,10299.,23.27,-8.97,3.92,-19.55,28.,28.,1.,
	    10790.,13.,-4.5,1.9,-10.67 };

    static integer i__, remain, coarse;

/* =======================================================================
 */
/* This subroutine replaces the open and read statements in the */
/* subroutine IONSUB of the Arnaud program. */

/* Author: */
/* Peter Wurz,   6. Nov. 1997 Initial version */
/* Peter Wurz,  20. Jan. 1998 Adaptations for SUN/UNIX */
/* -----------------------------------------------------------------------
 */
/* Index of data set */
/* Atomic number */
/* Ionization state */

/* Coarse array selector */
/* Pointer in array */
/* Array size */
/* -----------------------------------------------------------------------
 */
    /* Parameter adjustments */
    --rel;

    /* Function Body */
/* -----------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------
 */
    coarse = *index / 100;
    remain = *index % 100;
/* 	WRITE(6,*) INDEX,COARSE,REMAIN */
    if (coarse == 0) {
	*zr = (integer) dir_data_1__[(remain << 3) - 8];
    }
    if (coarse == 0) {
	*ir = (integer) dir_data_1__[(remain << 3) - 7];
    }
    if (coarse == 0) {
	*kr = (integer) dir_data_1__[(remain << 3) - 6];
    }
    if (coarse == 1) {
	*zr = (integer) dir_data_2__[remain * 8];
    }
    if (coarse == 1) {
	*ir = (integer) dir_data_2__[(remain << 3) + 1];
    }
    if (coarse == 1) {
	*kr = (integer) dir_data_2__[(remain << 3) + 2];
    }
    if (coarse == 2) {
	*zr = (integer) dir_data_3__[remain * 8];
    }
    if (coarse == 2) {
	*ir = (integer) dir_data_3__[(remain << 3) + 1];
    }
    if (coarse == 2) {
	*kr = (integer) dir_data_3__[(remain << 3) + 2];
    }
    if (coarse == 3) {
	*zr = (integer) dir_data_4__[remain * 8];
    }
    if (coarse == 3) {
	*ir = (integer) dir_data_4__[(remain << 3) + 1];
    }
    if (coarse == 3) {
	*kr = (integer) dir_data_4__[(remain << 3) + 2];
    }
    for (i__ = 1; i__ <= 5; ++i__) {
	if (coarse == 0) {
	    rel[i__] = dir_data_1__[i__ + 3 + (remain << 3) - 9];
	}
	if (coarse == 1) {
	    rel[i__] = dir_data_2__[i__ + 3 + (remain << 3) - 1];
	}
	if (coarse == 2) {
	    rel[i__] = dir_data_3__[i__ + 3 + (remain << 3) - 1];
	}
	if (coarse == 3) {
	    rel[i__] = dir_data_4__[i__ + 3 + (remain << 3) - 1];
	}
/* L100: */
    }
/* -----------------------------------------------------------------------
 */
    return 0;
} /* dir_data__ */

/* Subroutine */ int ea_(index, zr, ir, relea)
integer *index, *zr, *ir;
doublereal *relea;
{
    /* Initialized data */

    static doublereal ea_data_1__[800]	/* was [8][100] */ = { 1.,1.,0.,0.,0.,
	    0.,0.,0.,2.,1.,0.,0.,0.,0.,0.,0.,2.,2.,0.,0.,0.,0.,0.,0.,6.,1.,0.,
	    0.,0.,0.,0.,0.,6.,2.,0.,0.,0.,0.,0.,0.,6.,3.,0.,0.,0.,0.,0.,0.,6.,
	    4.,297.6,.898,.0963,-.638,0.,1.18,6.,5.,0.,0.,0.,0.,0.,0.,6.,6.,
	    0.,0.,0.,0.,0.,0.,7.,1.,0.,0.,0.,0.,0.,0.,7.,2.,0.,0.,0.,0.,0.,0.,
	    7.,3.,0.,0.,0.,0.,0.,0.,7.,4.,0.,0.,0.,0.,0.,0.,7.,5.,418.5,.84,
	    .0901,-.597,0.,1.1,7.,6.,0.,0.,0.,0.,0.,0.,7.,7.,0.,0.,0.,0.,0.,
	    0.,8.,1.,0.,0.,0.,0.,0.,0.,8.,2.,0.,0.,0.,0.,0.,0.,8.,3.,0.,0.,0.,
	    0.,0.,0.,8.,4.,0.,0.,0.,0.,0.,0.,8.,5.,0.,0.,0.,0.,0.,0.,8.,6.,
	    559.8,.584,.0658,-.411,0.,.756,8.,7.,0.,0.,0.,0.,0.,0.,8.,8.,0.,
	    0.,0.,0.,0.,0.,10.,1.,0.,0.,0.,0.,0.,0.,10.,2.,0.,0.,0.,0.,0.,0.,
	    10.,3.,0.,0.,0.,0.,0.,0.,10.,4.,0.,0.,0.,0.,0.,0.,10.,5.,0.,0.,0.,
	    0.,0.,0.,10.,6.,0.,0.,0.,0.,0.,0.,10.,7.,0.,0.,0.,0.,0.,0.,10.,8.,
	    903.6,.361,.0396,-.256,0.,.472,10.,9.,0.,0.,0.,0.,0.,0.,10.,10.,
	    0.,0.,0.,0.,0.,0.,11.,1.,0.,0.,0.,0.,0.,0.,11.,2.,0.,0.,0.,0.,0.,
	    0.,11.,3.,0.,0.,0.,0.,0.,0.,11.,4.,0.,0.,0.,0.,0.,0.,11.,5.,0.,0.,
	    0.,0.,0.,0.,11.,6.,0.,0.,0.,0.,0.,0.,11.,7.,0.,0.,0.,0.,0.,0.,11.,
	    8.,0.,0.,0.,0.,0.,0.,11.,9.,1106.1,.289,.0313,-.205,0.,.379,11.,
	    10.,0.,0.,0.,0.,0.,0.,11.,11.,0.,0.,0.,0.,0.,0.,12.,1.,0.,0.,0.,
	    0.,0.,0.,12.,2.,52.,0.,14.6,0.,0.,0.,12.,3.,0.,0.,0.,0.,0.,0.,12.,
	    4.,0.,0.,0.,0.,0.,0.,12.,5.,0.,0.,0.,0.,0.,0.,12.,6.,0.,0.,0.,0.,
	    0.,0.,12.,7.,0.,0.,0.,0.,0.,0.,12.,8.,0.,0.,0.,0.,0.,0.,12.,9.,0.,
	    0.,0.,0.,0.,0.,12.,10.,1329.,.232,.0249,-.165,0.,.305,12.,11.,0.,
	    0.,0.,0.,0.,0.,12.,12.,0.,0.,0.,0.,0.,0.,13.,1.,0.,0.,0.,0.,0.,0.,
	    13.,2.,0.,0.,0.,0.,0.,0.,13.,3.,78.,0.,13.4,0.,0.,0.,13.,4.,0.,0.,
	    0.,0.,0.,0.,13.,5.,0.,0.,0.,0.,0.,0.,13.,6.,0.,0.,0.,0.,0.,0.,13.,
	    7.,0.,0.,0.,0.,0.,0.,13.,8.,0.,0.,0.,0.,0.,0.,13.,9.,0.,0.,0.,0.,
	    0.,0.,13.,10.,0.,0.,0.,0.,0.,0.,13.,11.,1572.3,.188,.02,-.134,0.,
	    .247,13.,12.,0.,0.,0.,0.,0.,0.,13.,13.,0.,0.,0.,0.,0.,0.,14.,1.,
	    0.,0.,0.,0.,0.,0.,14.,2.,0.,0.,0.,0.,0.,0.,14.,3.,0.,0.,0.,0.,0.,
	    0.,14.,4.,104.,0.,13.5,0.,0.,0.,14.,5.,0.,0.,0.,0.,0.,0.,14.,6.,
	    0.,0.,0.,0.,0.,0.,14.,7.,0.,0.,0.,0.,0.,0.,14.,8.,0.,0.,0.,0.,0.,
	    0.,14.,9.,0.,0.,0.,0.,0.,0.,14.,10.,0.,0.,0.,0.,0.,0.,14.,11.,0.,
	    0.,0.,0.,0.,0.,14.,12.,1836.,.151,.0161,-.107,0.,.199,14.,13.,0.,
	    0.,0.,0.,0.,0.,14.,14.,0.,0.,0.,0.,0.,0.,16.,1.,0.,0.,0.,0.,0.,0.,
	    16.,2.,0.,0.,0.,0.,0.,0.,16.,3.,0.,0.,0.,0.,0.,0.,16.,4.,0.,0.,0.,
	    0.,0.,0.,16.,5.,0.,0.,0.,0.,0.,0.,16.,6.,156.,0.,14.2,0.,0.,0.,
	    16.,7.,0.,0.,0.,0.,0.,0.,16.,8.,0.,0.,0.,0.,0.,0.,16.,9.,0.,0.,0.,
	    0.,0.,0.,16.,10.,0.,0.,0.,0.,0.,0.,16.,11.,0.,0.,0.,0.,0.,0.,16.,
	    12.,0.,0.,0.,0.,0.,0.,16.,13.,0.,0.,0.,0.,0.,0.,16.,14.,2424.6,
	    .0988,.0105,-.0704,0.,.13,16.,15.,0.,0.,0.,0.,0.,0.,16.,16.,0.,0.,
	    0.,0.,0.,0. };
    static doublereal ea_data_2__[736]	/* was [8][92] */ = { 18.,1.,0.,0.,0.,
	    0.,0.,0.,18.,2.,0.,0.,0.,0.,0.,0.,18.,3.,184.3,0.,0.,0.,12.3,0.,
	    18.,4.,189.,0.,0.,0.,12.3,0.,18.,5.,210.4,0.,0.,0.,12.3,0.,18.,6.,
	    243.5,0.,0.,0.,12.3,0.,18.,7.,243.,0.,0.,0.,12.3,0.,18.,8.,248.9,
	    0.,0.,0.,13.8,0.,18.,9.,0.,0.,0.,0.,0.,0.,18.,10.,0.,0.,0.,0.,0.,
	    0.,18.,11.,0.,0.,0.,0.,0.,0.,18.,12.,0.,0.,0.,0.,0.,0.,18.,13.,0.,
	    0.,0.,0.,0.,0.,18.,14.,0.,0.,0.,0.,0.,0.,18.,15.,0.,0.,0.,0.,0.,
	    0.,18.,16.,3094.8,.0658,.00699,-.0469,0.,.0869,18.,17.,0.,0.,0.,
	    0.,0.,0.,18.,18.,0.,0.,0.,0.,0.,0.,20.,1.,25.,15.,0.,0.,0.,16.8,
	    20.,2.,29.,28.4,0.,0.,0.,31.8,20.,3.,0.,0.,0.,0.,0.,0.,20.,4.,0.,
	    0.,0.,0.,0.,0.,20.,5.,287.8,0.,0.,0.,10.,0.,20.,6.,291.7,0.,0.,0.,
	    10.,0.,20.,7.,311.2,0.,0.,0.,10.,0.,20.,8.,340.1,0.,0.,0.,10.,0.,
	    20.,9.,341.1,0.,0.,0.,10.,0.,20.,10.,347.9,0.,0.,0.,8.42,0.,20.,
	    11.,0.,0.,0.,0.,0.,0.,20.,12.,0.,0.,0.,0.,0.,0.,20.,13.,0.,0.,0.,
	    0.,0.,0.,20.,14.,0.,0.,0.,0.,0.,0.,20.,15.,0.,0.,0.,0.,0.,0.,20.,
	    16.,0.,0.,0.,0.,0.,0.,20.,17.,0.,0.,0.,0.,0.,0.,20.,18.,3846.6,
	    .0446,.00473,-.0318,0.,.0588,20.,19.,0.,0.,0.,0.,0.,0.,20.,20.,0.,
	    0.,0.,0.,0.,0.,26.,1.,0.,0.,0.,0.,0.,0.,26.,2.,0.,0.,0.,0.,0.,0.,
	    26.,3.,57.28,.878,0.,-.0115,71.2,47.9,26.,4.,60.,3.02,67.5,-59.8,
	    46.,0.,26.,5.,81.,0.,.28,-16.2,35.5,0.,26.,6.,95.,0.,0.,-5.83,
	    12.3,8.85,26.,7.,125.,0.,0.,-48.1,42.5,16.3,26.,8.,160.,5.,43.,
	    -72.6,42.9,0.,26.,9.,650.,0.,0.,0.,1.87,0.,26.,10.,650.,0.,0.,0.,
	    1.96,0.,26.,11.,650.,0.,0.,0.,3.21,0.,26.,12.,650.,0.,0.,0.,3.89,
	    0.,26.,13.,670.,0.,0.,0.,4.1,0.,26.,14.,670.9,0.,0.,0.,5.92,0.,
	    26.,15.,700.,0.,0.,0.,4.81,0.,26.,16.,704.,0.,0.,0.,2.95,0.,26.,
	    17.,0.,0.,0.,0.,0.,0.,26.,18.,0.,0.,0.,0.,0.,0.,26.,19.,0.,0.,0.,
	    0.,0.,0.,26.,20.,0.,0.,0.,0.,0.,0.,26.,21.,0.,0.,0.,0.,0.,0.,26.,
	    22.,0.,0.,0.,0.,0.,0.,26.,23.,0.,0.,0.,0.,0.,0.,26.,24.,6591.7,
	    .0153,.00162,-.0109,0.,.0202,26.,25.,0.,0.,0.,0.,0.,0.,26.,26.,0.,
	    0.,0.,0.,0.,0.,28.,1.,0.,0.,0.,0.,0.,0.,28.,2.,0.,0.,0.,0.,0.,0.,
	    28.,3.,0.,0.,0.,0.,0.,0.,28.,4.,0.,0.,0.,0.,0.,0.,28.,5.,0.,0.,0.,
	    0.,0.,0.,28.,6.,0.,0.,0.,0.,0.,0.,28.,7.,0.,0.,0.,0.,0.,0.,28.,8.,
	    0.,0.,0.,0.,0.,0.,28.,9.,0.,0.,0.,0.,0.,0.,28.,10.,0.,0.,0.,0.,0.,
	    0.,28.,11.,0.,0.,0.,0.,0.,0.,28.,12.,0.,0.,0.,0.,0.,0.,28.,13.,
	    730.9,0.,0.,0.,5.1,0.,28.,14.,779.7,0.,0.,0.,5.1,0.,28.,15.,798.8,
	    0.,0.,0.,5.1,0.,28.,16.,792.4,0.,0.,0.,5.1,0.,28.,17.,833.4,0.,0.,
	    0.,5.1,0.,28.,18.,840.,0.,0.,0.,2.27,0.,28.,19.,0.,0.,0.,0.,0.,0.,
	    28.,20.,0.,0.,0.,0.,0.,0.,28.,21.,0.,0.,0.,0.,0.,0.,28.,22.,0.,0.,
	    0.,0.,0.,0.,28.,23.,0.,0.,0.,0.,0.,0.,28.,24.,0.,0.,0.,0.,0.,0.,
	    28.,25.,0.,0.,0.,0.,0.,0.,28.,26.,7669.9,.0111,.00118,-.00789,0.,
	    .0146,28.,27.,0.,0.,0.,0.,0.,0.,28.,28.,0.,0.,0.,0.,0.,0. };

    static integer i__, remain, coarse;

/* =======================================================================
 */
/* This subroutine replaces the open and read statements in the */
/* subroutine IONSUB of the Arnaud program. */

/* Author: */
/* Peter Wurz,  6. Nov. 1997 Initial version */
/* Peter Wurz, 20. Jan. 1998 Adaptations for SUN/UNIX */
/* Peter Wurz, 23. Jan. 1998 Remove subtle error in adea access */
/* -----------------------------------------------------------------------
 */
/* Atomic number */
/* Ionization state */
/* Array selector */
/* Array position */
/* Size of arrays */
/* -----------------------------------------------------------------------
 */
    /* Parameter adjustments */
    --relea;

    /* Function Body */
/* -----------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------
 */
    coarse = *index / 101;
    remain = *index % 101;
/* 	WRITE(6,*) INDEX,COARSE,REMAIN */
    if (coarse == 0) {
	*zr = (integer) ea_data_1__[(remain << 3) - 8];
    }
    if (coarse == 0) {
	*ir = (integer) ea_data_1__[(remain << 3) - 7];
    }
    if (coarse == 1) {
	*zr = (integer) ea_data_2__[remain * 8];
    }
    if (coarse == 1) {
	*ir = (integer) ea_data_2__[(remain << 3) + 1];
    }
    for (i__ = 1; i__ <= 6; ++i__) {
	if (coarse == 0) {
	    relea[i__] = ea_data_1__[i__ + 2 + (remain << 3) - 9];
	}
	if (coarse == 1) {
	    relea[i__] = ea_data_2__[i__ + 2 + (remain << 3) - 1];
	}
/* L100: */
    }
/* -----------------------------------------------------------------------
 */
    return 0;
} /* ea_ */

