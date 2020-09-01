#include "SpiceUsr.h"
#include <string>
#include <iostream>

using namespace std;

#define WORD_SIZE  48

// see if the SPICE state machine encountered an error
bool checkError()
{
	if(failed_c())
	{
		SpiceChar msg[1841];
		getmsg_c ("long", 1841, msg);
		cerr << "Spice Error Message:\n" << msg << "\n";
		reset_c();
		return true;
	}

	return false;
}

// well.... quite obvious what happens here
bool loadKernel(string filename)
{
	furnsh_c(filename.data());

	if(checkError())	return false;
						return true;
}

/*!	@param	date		time of observation
 * 	@param	observer	SPICE identifier of observation point
 * 	@param	target		SPICE identifier of target body to be observed
 * 	@param	frame		SPICE identifier of coordinate reference frame (e.g., "ECLIPJ2000")
 * 	@param 	pos_x		first return coordinate
 * 	@param 	pos_y		second return coordinate
 * 	@param 	pos_z		third return coordinate
 *
 *	for the strings to be used as observer/target, see https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
 *	for the strings to be used as reference frames, see https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html and the kernel of the coodrinate frames (heliospheric.tf)
 */
void getPos(const string &date, const string &observer, const string &target, const string &frame, SpiceDouble &pos_x, SpiceDouble &pos_y, SpiceDouble &pos_z)
{
	SpiceChar ref[15];
	SpiceChar corr[15];
	snprintf(ref,  15, "%s", frame.data());
	snprintf(corr, 15, "%s", "NONE");
	SpiceDouble et, lt;
	SpiceChar utc[WORD_SIZE];
	SpiceChar targ[WORD_SIZE];
	SpiceChar obs[WORD_SIZE];
	SpiceDouble pos[3];

	snprintf(utc, 	WORD_SIZE, "%s", date.data());
	snprintf(targ, 	WORD_SIZE, "%s", target.data());
	snprintf(obs, 	WORD_SIZE, "%s", observer.data());
	str2et_c(utc, &et);

	spkpos_c(targ, et, ref, corr, obs, pos, &lt);

	if(checkError())
	{
		cerr 	<< __FILE__ << ":" << __LINE__ << " Spice could not acquire position of " << target << " with respect to "
				<< observer << " in frame " << frame << ".\n";
		return;
	}

	// SPICE returns coordinates in kilometers
	pos_x	= pos[0] * 1000;
	pos_y	= pos[1] * 1000;
	pos_z	= pos[2] * 1000;
}

/*!	@param	pos_x		first input coordinate
 * 	@param	pos_y		second input coordinate
 * 	@param	pos_z		third input coordinate
 * 	@param	date		date of observation (as appropriatly formatted string)
 * 	@param	from		SPICE identifier of origin frame (e.g. "ECLIPJ2000")
 * 	@param	to			SPICE identifier of destination frame (e.g. "ECLIPDATE")
 * 	@param	retpos_x	first output coordinate
 * 	@param	retpos_y	second output coordinate
 * 	@param	retpos_z	third output coordinate
 *
 * 	state vector is defined by position (elements 0-2) and velocity (elements 3-5) of observated object
 *
 * 	WARNING: this only transforms positions, not velocities
 */
void transformFrame(SpiceDouble pos_x, SpiceDouble pos_y, SpiceDouble pos_z, const string &date, const string &from, const string &to, SpiceDouble &retpos_x, SpiceDouble &retpos_y, SpiceDouble &retpos_z)
{
	SpiceDouble instate[6], outstate[6];
	SpiceDouble xform[6][6];
	SpiceChar utc[WORD_SIZE];
	SpiceDouble et;

	instate[0] 	= pos_x;
	instate[1] 	= pos_y;
	instate[2] 	= pos_z;
	instate[3] 	= 0.0;		// enter velocities here
	instate[4] 	= 0.0;
	instate[5] 	= 0.0;

	outstate[0] = 0.0;		// initialize return values
	outstate[1] = 0.0;
	outstate[2] = 0.0;
	outstate[3] = 0.0;
	outstate[4] = 0.0;
	outstate[5] = 0.0;

	snprintf(utc, WORD_SIZE, "%s", date.data());
	str2et_c(utc, &et);

	sxform_c(from.data(), to.data(), et, xform);	// the magic happens here, get transformation matrix

	if(checkError())
	{
		cerr << __FILE__ << ":" << __LINE__ << " Spice could not trasform from frame " << from << " to " << to << "\n";
		return;
	}

	// apply transformation matrix to input data
	for(uint i=0; i<6; ++i)
		for(uint j=0; j<6; ++j)
			outstate[i] += xform[i][j] * instate[j];

	// return results (at least the position)
	retpos_x	= outstate[0];
	retpos_y	= outstate[1];
	retpos_z	= outstate[2];
}

// demonstration of how to extract coordinates of a body in different reference frames and how to transform one frame into the other
int main()
{
	// setup SPICE
	SpiceChar action[10];
	snprintf(action, 7, "%s", "RETURN");
	erract_c ("SET", 7, action);

	loadKernel("../data/latest_leapseconds.tls");		// well.... leapseconds
	loadKernel("../data/de430.bsp");					// orbital data for solar system bodies
	loadKernel("../data/pck00010.tpc");					// orientation and shapes of solar system bodies
	loadKernel("../data/heliospheric.tf");				// Heliospheric Coordinate Frames

	// Now let's get some coordinates for Ulysses
	loadKernel("../data/ulysses_1990_2009_2050.bsp");	// load kernel so Spice knows our target
	string date = "1990-12-24T12:12:12";				// time in Spice format
	SpiceDouble pos_HAE[3];								// array for storing the requested position in Heliocentric Aries Ecliptic coordinates (J2000)
	SpiceDouble pos_HGC[3];								// array for storing the requested position in Heliographic coordinates
	SpiceDouble pos_HGC2HAE[3];							// array for transforming Heliographic to Heliocentric coordinates
	SpiceDouble pos_HAE2HGC[3];							// array for transforming Heliocentric to Heliographic coordinates

	// this is how you extract positions of bodies from the Ulysses-kernel
	getPos(date, "SUN", "ULYSSES", "ECLIPJ2000", 	pos_HAE[0], pos_HAE[1], pos_HAE[2]);
	getPos(date, "SUN", "ULYSSES", "IAU_SUN", 		pos_HGC[0], pos_HGC[1], pos_HGC[2]);

	// this is how you transform coordinate frames
	transformFrame(pos_HAE[0], pos_HAE[1], pos_HAE[2], date, "ECLIPJ2000", "IAU_SUN", 	pos_HAE2HGC[0], pos_HAE2HGC[1], pos_HAE2HGC[2]);
	transformFrame(pos_HGC[0], pos_HGC[1], pos_HGC[2], date, "IAU_SUN",    "ECLIPJ2000",pos_HGC2HAE[0], pos_HGC2HAE[1], pos_HGC2HAE[2]);

	cout << "Heliocentric Aries Ecliptic coordinates (J2000) of Ulysses at " << date << ":\n";
	cout << "------------------------------------------------------------------------------------------\n";
	cout << "extracted from kernel: " << pos_HAE[0] 	<< "/" << pos_HAE[1] 		<< "/" 	<< pos_HAE[2] 		<< "\n";
	cout << "converted from HGC:    " << pos_HGC2HAE[0] << "/" << pos_HGC2HAE[1] 	<< "/"  << pos_HGC2HAE[2] 	<< "\n\n";
	cout << "Heliographic coordinates of Ulysses at " << date << ":\n";
	cout << "------------------------------------------------------------------------------------------\n";
	cout << "extracted from kernel: " << pos_HGC[0] 	<< "/" << pos_HGC[1] 		<< "/" 	<< pos_HGC[2] 		<< "\n";
	cout << "converted from HAE:    " << pos_HAE2HGC[0] << "/" << pos_HAE2HGC[1] 	<< "/"  << pos_HAE2HGC[2] 	<< "\n";
}
