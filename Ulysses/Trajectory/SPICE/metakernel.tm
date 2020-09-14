KPL/MK

   This is the meta-kernel used in the solution of the "Time
   Conversion" task in the Remote Sensing Hands On Lesson.

   The names and contents of the kernels referenced by this
   meta-kernel are as follows:

   File name                   Contents
   --------------------------  -----------------------------
   latest_leapseconds.tls       Leapseconds LSK
   de438.bsp			Ephemeris solar system bodies SPK
   pck00010.tpc			Sizes and Constants of solar system bodies PCK

   020514_SE_SAT105.bsp		Ephemeris Saturnian Satellites SPK
   030201AP_SK_SM546_T45.bsp	Ephemeris Cassini Spacecraft SPK
   cas00137.tsc                	Cassini Spacecraft Clock SCLK




   \begindata
   KERNELS_TO_LOAD = ('Ulysses/Trajectory/SPICE/data/latest_leapseconds.tls',
			'Ulysses/Trajectory/SPICE/data/de438.bsp',
			'Ulysses/Trajectory/SPICE/data/pck00010.tpc')

			
   \begintext

