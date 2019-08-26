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
	cd $(LOCAL); make  	
	-ln -s $(LOCAL)/analysis 

.SUFFIXES: .cpp .o

clean: 
	cd $(LOCAL); make clean
	rm -f analysis



