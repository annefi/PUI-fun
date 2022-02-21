import spiceypy as spice

#spice.furnsh("./cassMetaK.txt")
spice.furnsh("./naif0009.tls")
#spice.furnsh("./cas00084.tsc")
#spice.furnsh("./cpck05Mar2004.tpc")
#spice.furnsh("./020514_SE_SAT105.bsp")
spice.furnsh("./981005_PLTEPH-DE405S.bsp")
#spice.furnsh("./030201AP_SK_SM546_T45.bsp")
#spice.furnsh("./04135_04171pc_psiv2.bc")
#spice.furnsh("./cas_v37.tf")
#spice.furnsh("./cas_iss_v09.ti")
spice.furnsh("./ulysses_1990_2009_2050.bsp")

utc = ['Jun 20, 2004', 'Dec 1, 2005']

# get et values one and two, we could vectorize str2et
etOne = spice.str2et(utc[0])
etTwo = spice.str2et(utc[1])

positions, lightTimes = spice.spkpos('Ulysses', etOne, 'J2000', 'NONE', 'SATURN BARYCENTER')

spice.kclear()