#################################################
#                                               #
# file:      Makefile                           # 
# author:    Lars Berger                        #
#            <berger@physik.uni-kiel.de>        #
#                                               #
# version:   1.00                               #
#                                               #
# rev. date: 06.02.2006                         #
#                                               #
# Makefile for these projects:                  #
# 	- ion_pos                               #
#                                               #
#                                               #
# last modified 06.02.06			#
#						#
#################################################

# updates at CAU Kiel
# $Id: Makefile,v 1.13 2005/05/23 $

CC = g++
CXX = g++
export INCLUDE = ../include
VPATH = .:../include

CFLAGS = -I$(INCLUDE) -L$(INCLUDE) -Wall -O3
CPPFLAGS = $(CFLAGS)
DEPS = heavyside.o ion.o twodgauss4sig.o fitting.o normfit.o boxrates.o sort.o read_data.o read_et_mat.o read_header.o copy_header.o filter_data.o databinning.o datagen.o ../libetph/src/libetph.a check_data_file.o
#LDFLAGS=

default: ion_pos analyse_data testdatagen errordatagen error_analyse_data analyse_testdata

ion_pos: ion_pos.o $(DEPS)

analyse_data: analyse_data.o $(DEPS)

analyse_testdata: analyse_testdata.o $(DEPS)

testdatagen: testdatagen.o $(DEPS)

errordatagen: errordatagen.o $(DEPS)

error_analyse_data: error_analyse_data.o $(DEPS)

%.o : %.cc %.h



show: 
	echo INCLUDE = $(INCLUDE)
	echo CFLAGS = $(CFLAGS)
	echo VPATH = $(VPATH)
clean: 
	rm -f *.o
	rm -f ion_pos
	rm -f analyse_data
	rm -f testdatagen
	rm -f errordatagen
	rm -f error_analyse_data

