
PROGRAM = test1

objects=ELOSS.o CFOIL.o CFOILZ.o ERF.o FWHM.o GAMMLN.o GAMMP.o GAMMQ.o \
        GFC.o GEOFACP.o GSER.o HESTOP.o HISTOP.o PLOR.o PSTOP.o PWID.o \
        SCATWID.o SCOEF.o  STOP.o SWEFF.o \
        geom.o swxeff.o sweffsrim.o deadlayer.o dedxdl.o elosscf.o dedxcf.o\
	integrall.o integralg.o winkel.o betrag.o evektor.o skalarprodukt.o \
	kreuzprodukt.o schnittpunkt.o signum.o drehung.o integration.o \
	dedxmacor.o vap.o ftos.o elname.o\
	phd.o dutycycle.o dutycycleth.o integrationconv.o integrallconv.o\
	integrationconv2.o integrallconv2.o geomforfit.o error.o paramerror.o\
	dedxgold.o noise.o ran1.o ran2.o ran3.o rotation.o geometriescan.o\
	geombeta.o geomaspang.o dedxncf.o

#SWICSEF1.o SWICSEF2.o SWICSEFF.o SWICSEFF_ANG.o SWICSEFF_CAL.o SWICSEFF_NEW.o STEST.o SEK_ELE.o ELECTRONS.o EFFIC.o EFFTABLE.o FOILLOSS.o PHPRED.o STOPPING.o 
# TESIG.o TESTPWID.o TRANS.o TRYCFOIL.o TRYELOSS.o TRYFWHM.o TRYPLOR.o TRYPROBSE.o TRYSCATW.o #TRYSTOP.o
#Hier muessen alle anderen Subroutinen eingefuegt werden, z.B. FOILLOSS.o, etc.

FC=g77
FFLAGS	= -O -g -fPIC
#FFLAGS	= -g -fPIC

$(PROGRAM): $(PROGRAM).o libswics.a
	g77 -o test1 $^ -lm -lc

libswics.a: $(objects)
	ar cr $@ $^
	ranlib $@

clean: 
	rm -f *.o $(PROGRAM) libswics.a $(PLUGIN).so

######### gnuplot plugin ########

GPTHOME = $(HOME)/src

PLUGIN = swxeff_gpt

plugin: $(PLUGIN).so

HOSTTYPE := $(shell uname -m)
HOSTEXT-x86_64=-amd64
GNUPLOTSRC = $(GPTHOME)/gnuplot-4.0.0-ext$(HOSTEXT-$(HOSTTYPE))

CC = gcc -g -O2 -Wall -DHAVE__BOOL
CFLAGS = -rdynamic -fPIC -I$(GNUPLOTSRC)/src -I$(GNUPLOTSRC)/plugin

FLIBS = -lg2c 



%.so: %.o libswics.a /usr/lib/libg2c.so
	$(LD) -v -shared -o $@ $^ \
              -L$(GNUPLOTSRC)/plugin -lgnuplot_plugin 
