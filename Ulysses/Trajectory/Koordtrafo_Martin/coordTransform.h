#ifndef COORDTRANSFORM_H
#define COORDTRANSFORM_H

#include "engine/math/vectors.h"
#include "engine/hcTime.h"

Vec2D hcTFcelCoords(Vec2D pole, Vec2D long0, Vec2D coords);
	/*!< \brief transforms coords to new celestial coordinate system with pole given in coordinates of the old one			*/

void convDeg2HMS(const hcFloat &angle, hcFloat &h, hcFloat &m, hcFloat &s);
	/*!< \brief converts angle (in degrees) to hour-minute-second format																				*/

Vec2D equ2Eclip_s(const Vec2D &equCoords);
    /*!< \brief transforms equatorial to ecliptic coordinates                                                               */

Vec2D eclip2Equ_s(const Vec2D &eclipCoords);
    /*!< \brief transforms ecliptic coordinates to equatorial coordinates                                                  */

Vec2D HAE2Car_s(const Vec2D &eclipCoords);
    /*!< \brief transforms heliocentric aries ecliptic coordinates (spherical) to Carrington coordinates                                */

Vec2D hcTFcelECL2GAL(const Vec2D &coordsHAE);
	/*!< \brief transforms celestial ecliptic coordinates to celestial galactic coordinates																*/

Vec2D hcTFcelGAL2ECL(const Vec2D &coordsGAL);
	/*!< \brief transforms celestial galactic coordinates to celestial ecliptic coordinates																*/

Vec3D HAE2GEI_c(const Vec3D &posHAE);
	/*!< \brief transforms heliocentric aries ecliptic coordinates to geocentric equatorial inertial (cartesian) (TODO only rotation so far)			*/

Vec2D hcTFcelECL2EQU(const Vec2D &coordsECL);
	/*!< \brief transforms celestial ecliptic coordinates to celestial equatorial coordinates															*/

Vec2D hcTFcelEQU2ECL(const Vec2D &coordsEQU);
	/*!< \brief transforms celestial equatorial coordinates to celestial ecliptic coordinates															*/

Vec2D hcTFcelECL2HGC(const Vec2D &coordsECL, const hcDate &date);
	/*!< \brief transforms celestial ecliptic coordinates to heliographic coordinates																	*/

Vec2D hcTFcelHGC2ECL(const Vec2D &coordsHGC, const hcDate &date);
	/*!< \brief transforms celestial heliographic coordinates to ecliptic coordinates																	*/

Vec2D hcTFcelECL2HGI(const Vec2D &coordsECL);
	/*!< \brief transforms celestial ecliptic coordinates to heliographic inertial coordinates															*/

Vec3D GEI2HAE_c(const Vec3D &posGEI);
	/*!< \brief transforms geocentric earth equatorial coordinates to heliocentric aries ecliptic coordinates (cartesian) (TODO only rotation so far)	*/

Vec3D GEI2HGC_c(const Vec3D &posGEI, const hcDate &date);
	/*!< \brief transforms geocentric earth equatorial coordinates to heliographic coordinates (cartesian) (TODO only rotations so far)	*/

Vec3D HAE2HGC_c(const Vec3D &posHAE, const hcDate &date);
	/*!< \brief transforms heliocentric aries ecliptic coordinates to heliographic coordinates								*/

Vec3D HAE2HGC_c2(const Vec3D &posHAE, const hcDate &date);


/*
from Fränz,Harper - Heliospheric coordinate systems (2002):

Geocentric Earth Equatorial GEI_J2000 (Hapgood 1995).
This system is realized through the International Celestial
Reference Frame (ICRF), which is the base system for
star catalogues and reference values of planetary positions
(see the IERS webpage cited above).
XY -plane: Earth mean equator at J2000.0.
+X -axis: 4rst point of Aries, i.e. vector (Earth–Sun) of
vernal equinox at epoch J2000.0.
Angles: declination  and right ascension  right handed.

Heliocentric Aries Ecliptic HAE_J2000 (Fig. 1)
XY -plane: Earth mean ecliptic at J2000.0.
+X -axis: 4rst point of Aries, i.e. vector (Earth–Sun) of
vernal equinox at epoch J2000.0.
Angles: celestial latitude  and longitude  right handed.
Transform: T(GEIJ 2000; HAEJ 2000) = 0; X  = E(0; 0; 0)
and subtraction of solar position vector if necessary.

//*/

#endif // COORDTRANSFORM_H
