#################################################
#                                               #
# file:      Makefile                           # 
# author:    Lars Berger                        #
#            <berger@physik.uni-kiel.de>        #
#                                               #
# version:   1.02                               #
#                                               #
# rev. date: 21.11.2005                         #
#                                               #
# Makefile for these projects:                  #
#   - ion_pos.pro                               #
#   - ion_pos.cc                                #
#                                               #
#                                               #
#                                               #
# last modified 07.12.04			#
#						#
#################################################

# updates at CAU Kiel
# $Id: Makefile,v 1.13 2005/05/23 $

CC = gcc
CXX = g++

export LOCAL = ./src

default: 
	cd ./libetph; make
	cd ../
	cd $(LOCAL); make  	
	-ln -s $(LOCAL)/ion_pos 
	-ln -s $(LOCAL)/analyse_testdata 
	-ln -s $(LOCAL)/analyse_data
	-ln -s $(LOCAL)/testdatagen

.SUFFIXES: .cpp .o

clean: 
	cd $(LOCAL); make clean
	rm -f ion_pos
	rm -f analyse_data


