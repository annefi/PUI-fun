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

CFLAGS = -I$(INCLUDE) -L$(INCLUDE) -Wall
CPPFLAGS = $(CFLAGS)
DEPS = heavyside.o ion.o twodgauss4sig.o twodgaussschief.o twodgauss.o fitting.o poidev.o gammln.o ran_2.o 

default: analysis

analysis: analysis.o $(DEPS)
#	$(CXX) -o $@ analysis.cc $(CFLAGS) 

%.o : %.cc %.h



show: 
	echo INCLUDE = $(INCLUDE)
	echo CFLAGS = $(CFLAGS)
	echo VPATH = $(VPATH)
clean: 
	rm -f *.o
	rm -f analysis


