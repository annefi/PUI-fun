#include "engine/math/coordTransform.h"
#include "engine/negotiator.h"
#include "engine/hcTime.h"

/*!	the old system is defined by a pole at (0.0, PI/2.0) and origin at (0.0, 0.0)
 *  the new system is defined by the parameters \param pole and \param origin
 *
 *  all coordinates are given in (longitude, latitude)-format, where
 *  longitude in [0, 2PI) and
 *  latitude  in [-PI/2,PI/2]
 *
 *  the algorithm was copied from
 *  John A. Smith - Some Fortran Subprograms used in Astronomy (1969)
 *
 */
Vec2D hcTFcelCoords(Vec2D pole, Vec2D origin, Vec2D coords)
{
	hcFloat alpha	= (coords[0] < PI ? coords[0] : coords[0] - 2*PI);
	hcFloat delta	= coords[1];
	hcFloat alphaO	= (origin[0] < PI ? origin[0] : origin[0] - 2*PI);
	hcFloat deltaO	= origin[1];
	hcFloat alphaP	= (pole[0]   < PI ? pole[0]   : pole[0]   - 2*PI);
	hcFloat deltaP	= pole[1];

	hcFloat sbo		= sin(deltaO);
	hcFloat cbo		= cos(deltaO);
	hcFloat sbp		= sin(deltaP);
	hcFloat cbp		= cos(deltaP);
	hcFloat sb1		= sin(delta);
	hcFloat cb1		= cos(delta);

	hcFloat sb2		= sbp * sb1 + cbp * cb1 * cos(alphaP-alpha);
	hcFloat b2		= asin(sb2);
	hcFloat cb2		= cos(b2);
	hcFloat saa		= sin(alphaP-alpha) * cb1 / cb2;
	hcFloat caa		= (sb1-sb2*sbp) / (cb2 * cbp);
	hcFloat cbb		= sbo/cbp;
	hcFloat sbb		= sin(alphaP-alphaO) * cbo;

	hcFloat ta202	= (1.0-caa*cbb-saa*sbb) / (saa*cbb-caa*sbb);
	hcFloat a2		= 2.0*atan(ta202);
	a2				+= a2 < 0.0 ? 2*PI : 0.0;

	Vec2D retval((double)a2, (double)b2);
	return retval;
}

/*! see https://physics.stackexchange.com/questions/88663/converting-between-galactic-and-ecliptic-coordinates
 *
 * 	\param pole 	celestial coordinates (right ascension/longitude in [0,2PI), declination in [-PI/2, PI/2]) of the new pole in the old coordinate system
 * 	\param long0	celestial coordinates of the new reference longitude in the old coordinate system
 * 	\param coords	celestial coordinates of the point to be transformed
 *
 */
/*
Vec2D transformCelCoords(Vec2D pole, Vec2D origin, Vec2D coords)
{
	Vec2D retval;
	hcFloat alpha	= coords[0];
	hcFloat delta	= coords[1];
	hcFloat alphaO	= origin[0];
	hcFloat deltaO	= origin[1];
	hcFloat alphaP	= pole[0];
	hcFloat deltaP	= pole[1];
	hcFloat apMao	= alphaP-alphaO;
	hcFloat aMap	= alpha-alphaP;

	bool sign = fabs(aMap) < PI/2.0 || fabs(aMap) > 3.0/2.0 * PI;
	aMap	+= sign ? PI : 0.0;
	delta	*= sign ? -1 : 1;

	hcFloat angle	= acos(sin(deltaO)*cos(deltaP)-cos(deltaO)*sin(deltaP)*cos(apMao));

	hcFloat b		= (sign ? -1 : 1) * asin(sin(deltaP)*sin(delta)+cos(deltaP)*cos(delta)*cos(aMap));
	hcFloat at		= atan2(cos(delta)*sin(aMap), cos(deltaP)*sin(delta)-sin(deltaP)*cos(delta)*cos(aMap));

	hcFloat l		= angle - at;
	hcFloat l2		= angle - asin(cos(delta)*sin(aMap) / cos(b));

	l	+= l < 0.0 ? 2*PI : 0.0;

	//printf("a:\t\t%E\nab:\t\t%E\nag:\t\t%E\n90-deltaG:\t%E\n90-delta:\t%E\n90-b:\t\t%E\na-aG:\t\t%E\nag-ab:\t\t%E\ndeltaG:\t\t%E\ndeltaB:\t\t%E\ndelta:\t\t%E\nangle:\t\t%E\natan:\t\t%E (%u)\nl2:\t\t%E\nl:\t\t%E\nb:\t\t%E\n\n", alpha, alphaO, alphaP, 90-deltaP*rad2deg, 90-delta*rad2deg,90-b*rad2deg, aMap, apMao, deltaP, deltaO, delta, angle, at, sign ? 1 : 0,l2, l, b);

	retval(0)	= l;
	retval(1)	= b;

	return retval;
}//*/


void convDeg2HMS(const hcFloat &angle, hcFloat &h, hcFloat &m, hcFloat &s)
{
	h	= trunc(angle * 24 / 360);
	m	= trunc((angle * 24 / 360 - h) * 60);
	s	= ((angle * 24 / 360 - h) * 60 - m) * 60;
}

/*! see http://en.wikipedia.org/wiki/Celestial_coordinate_system#Converting_coordinates
 *
 *  equCoords[0]    = right ascension       = alpha  	in [0		, 2*PI  )
 *  equCoords[1]    = declination           = delta  	in [-PI/2.0	, PI/2.0]
 *
 *  retval[0]       = ecliptic longitude    = lambda 	in [0      	, 2*PI  )
 *  retval[1]       = ecliptic latitude     = beta   	in [-PI/2.0	, PI/2.0]
 *
 */
Vec2D equ2Eclip_s(const Vec2D &equCoords){

    Vec2D retval;

    double epsilon  = 23.4 * deg2rad; 	// obliquity of the ecliptic
    double alpha    = equCoords[0];
    double delta    = equCoords[1];
    retval(0)       = atan2(sin(alpha) * cos(epsilon) + tan(delta) * sin(epsilon), cos(alpha));
    retval(1)       = asin( sin(delta) * cos(epsilon) - cos(delta) * sin(epsilon) * sin(alpha));

    retval(0)		+= retval[0] < 0.0 ? 2*PI : 0.0;

    return retval;
}

/*! see http://en.wikipedia.org/wiki/Celestial_coordinate_system#Converting_coordinates
 *
 *  eclipCoords[0]  = ecliptic longitude    = lambda	in [0		, 2*PI )
 *  eclipCoords[1]  = ecliptic latitude     = beta		in [-PI/2.0	, PI/2.0]
 *
 *  retval[0]       = right ascension       = alpha		in [0		, 2*PI )
 *  retval[1]       = declination           = delta		in [-PI/2.0	, PI/2.0]
 *
 */
Vec2D eclip2Equ_s(const Vec2D &eclipCoords){

    Vec2D retval;

    double epsilon  = 23.4 * deg2rad; 	// obliquity of the ecliptic
    double lambda   = eclipCoords[0];
    double beta     = eclipCoords[1];

    retval(0)       = atan2(sin(lambda) * cos(epsilon) - tan(beta) * sin(epsilon), cos(lambda));
    retval(1)       = asin( sin(beta)   * cos(epsilon) + cos(beta) * sin(epsilon) * sin(lambda));

    retval(0)		+= retval[0] < 0.0 ? 2*PI : 0.0;

    return retval;
}

/*! transforms coordinates from celestial ecliptic to celestial galactic (both in J2000.0)
 *  coordinate system origin is in the sun
 *
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelECL2GAL(const Vec2D &coordsHAE)
{
	Vec2D pole(192.85*deg2rad, 27.13*deg2rad);
	Vec2D origin(266.4*deg2rad, -28.94*deg2rad);
	Vec2D retval = hcTFcelCoords(pole, origin, coordsHAE);
	return retval;
}

/*! transforms coordinates from celestial galactic to celestial ecliptic (both in J2000.0)
 *  coordinate system origin is in the sun
 *
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelGAL2ECL(const Vec2D &coordsGAL)
{
	Vec2D pole 		= hcTFcelECL2GAL(Vec2D(0.0, PI/2.0));
	Vec2D origin	= hcTFcelECL2GAL(Vec2D(0.0, 0.0));
	Vec2D retval	= hcTFcelCoords(pole, origin, coordsGAL);
	return retval;
}

/*!	\param coordsECL 	ecliptic coordinates
 * 	\param date			date to be transformed at
 * 	\param retval		heliographic coordinates
 *
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelECL2HGC(const Vec2D &coordsECL, const hcDate &date)
{
	Vec2D coordsEQU = hcTFcelECL2EQU(coordsECL);
	Vec2D pole(286.13*deg2rad, 63.87*deg2rad);
	Vec2D origin(PI/2.0 + 286.13*deg2rad - 2*PI, 0.0);		// ascending node of solar equator on celestial equator
															// according to Fränz, Harper, HGC longitude is measured from the ascending node on the ECLIPTIC westwards
	long jd;
	double jdFrac;
	date.getJulianDate(jd, jdFrac);
	hcFloat d0 	= jd - 2451545 + jdFrac;
	hcFloat w0	= cyclicPhi((84.1 + 14.1844*d0)*deg2rad);

	Vec2D retval	= hcTFcelCoords(pole, origin, coordsEQU);
	retval(0)		-= w0;
	retval(0)		+= retval[0] < 0.0 ? 2*PI : 0.0;

	return retval;
}

/*!	\param coordsHGC 	heliographic coordinates
 * 	\param date			date to be transformed at
 * 	\param retval		ecliptic coordinates
 *
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelHGC2ECL(const Vec2D &coordsHGC, const hcDate &date)
{
	Vec2D pole_ECL	= hcTFcelECL2HGC(Vec2D(0.0, PI/2.0), date);
	Vec2D origin_ECL= hcTFcelECL2HGC(Vec2D(0.0, 0.0), date);

	Vec2D retval = hcTFcelCoords(pole_ECL, origin_ECL, coordsHGC);

	return retval;
}

/*!	Heliographic Inertial Coordinate System (HGI)
 *	The HGI coordinates are Sun-centered and inertially fixed with respect to an X-axis directed along the intersection line of
 *	the ecliptic and solar equatorial planes, and defines zero of the longitude, HGI_LONG. The solar equator plane is inclined
 *	at 7.25 degrees from the ecliptic. This direction was towards ecliptic longitude of 74.367 deg on 1 January 1900 at 12:00 UT;
 *	because of the precession of the Earth's equator, this longitude increases by 1.4 deg/century.
 *	The Z-axis is directed perpendicular to and northward of the solar equator, and the Y-axis completes the right-handed set.
 *	The longitude, HGI_LONG increase from zero in the X-direction towards Y-direction.The latitude HG_LAT increases to +90 deg
 *	towards the north pole, and to -90 deg towards south pole.These Lat/Long are designated as HLAT & HILON in output
 *	(from https://omniweb.gsfc.nasa.gov/coho/helios/plan_des.html)
 *
 * 	\param coordsECL 	ecliptic coordinates
 * 	\param retval		heliographic inertial coordinates
 *
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelECL2HGI(const Vec2D &coordsECL)
{
	Vec2D poleEQU(286.13*deg2rad, 63.87*deg2rad);
	Vec2D poleECL = hcTFcelEQU2ECL(poleEQU);
	//Vec2D poleECL2((75.76-90+360)*deg2rad, (90-7.25)*deg2rad);
	//printf("p1: %E / %E\np2: %E / %E\n\n", poleECL[0], poleECL[1], poleECL2[0], poleECL2[1]);
	Vec2D origin(75.76*deg2rad, 0.0);		// ascending node of solar equator on ecliptic

	Vec2D retval	= hcTFcelCoords(poleECL, origin, coordsECL);

	return retval;
}

/*!
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelECL2EQU(const Vec2D &coordsECL)
{
	Vec2D pole(1.0/2.0*PI, PI/2.0 - 23.4*deg2rad);
	Vec2D origin(0.0, 0.0);
	Vec2D retval = hcTFcelCoords(pole, origin, coordsECL);
	return retval;
}

/*!
 *  input/output coordinates are stored in (longitude, latitude)-format with
 *  longitude in [0. 2PI) and
 *  latitude in [-PI/2, PI/2]
 */
Vec2D hcTFcelEQU2ECL(const Vec2D &coordsEQU)
{
	Vec2D pole 		= hcTFcelECL2EQU(Vec2D(0.0, PI/2.0));	// pole of ecliptic system in equatorial coordinates
	Vec2D origin	= hcTFcelECL2EQU(Vec2D(0.0, 0.0));		// origin direction of ecliptic system in equatorial coordinates
	Vec2D retval	= hcTFcelCoords(pole, origin, coordsEQU);
	return retval;
}

Vec3D HAE2GEI_c(const Vec3D &posHAE)
{
	Vec3D retval;
	Matrix3x3 rotMat;
	rotMat.loadRotationX(-23.4 * deg2rad);
	retval = rotMat * posHAE;				// TODO: shift of coordinate system origin
	return retval;
}


Vec3D GEI2HAE_c(const Vec3D &posGEI)
{
	Vec3D retval;
	Matrix3x3 rotMat;
	rotMat.loadRotationX(23.4 * deg2rad);
	retval = rotMat * posGEI;				// TODO: shift of coordinate system origin
	return retval;
}

Vec3D GEI2HGC_c(const Vec3D &posGEI, const hcDate &date)
{
	Matrix3x3 rotMat;
	long jd;
	double jdFrac;
	date.getJulianDate(jd, jdFrac);
	double d0 		= jd - 2451545 + jdFrac;		// days since epoch noon January 1, 2000 = Julian Day 2451545.0 (J2000.0)
	double delta	= 63.87  * deg2rad;
	double alpha	= 286.13 * deg2rad;
	double w0		= cyclicPhi((84.1 + 14.1844 *d0) * deg2rad);
	rotMat.loadEulerTransform(alpha + PI/2.0, PI/2.0 - delta, w0);

	Vec3D retval 	= rotMat * posGEI;			// TODO: shift of coordinate system
	return retval;
}

Vec3D HAE2HGC_c2(const Vec3D &posHAE, const hcDate &date)
{
	Vec3D retval 	= HAE2GEI_c(posHAE);
	retval			= GEI2HGC_c(retval, date);
	return retval;
}

/*!
 * 		see Fränz,Harper - Heliospheric coordinate systems (2002)
 *
 * 		transforms
 */
Vec3D HAE2HGC_c(const Vec3D &posHAE, const hcDate &date)
{
	long jd;
	double jdFrac;
	Matrix3x3 rotMat;

	date.getJulianDate(jd, jdFrac);
	double d0 	= jd - 2451545 + jdFrac;		// days since epoch noon January 1, 2000 = Julian Day 2451545.0 (J2000.0)
	double T0 	= d0/36525.0;					// Julian centuries since epoch
	double inc	= 7.25 * deg2rad;				// inclination of the solar equator
	double omega= (75.76 + 1.397*T0)*deg2rad;	// longitude of ascending node
	double w0	= (d0 + 2415020.0 - 2398220.0)/25.38 * 2 * PI;	// prime meridian angle
																// noon on January 1, 1854 		= Julian Day 2398220.0
																// noon on December 31, 1899 	= Julian Day 2415020.0 (Doublin JD)
	rotMat.loadEulerTransform(omega, inc, w0);

	return rotMat * posHAE;

}
