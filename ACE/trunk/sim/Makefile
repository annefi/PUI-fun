#################################################
#                                               #
# file:      Makefile                           # 
# author:    roland schaerer                    #
#            <roland.schaerer@phim.unibe.ch>    #
#                                               #
# version:   1.02                               #
#                                               #
# rev. date: 4.4.1999                           #
#                                               #
# Makefile for these projects:                  #
#   - getdata                                   #
#   - speed                                     #
#   - convert                                   #
#   - testfit                                   #
#                                               #
# last modified 07.12.04			#
#						#
#################################################

# updates at CAU Kiel
# $Id: Makefile,v 1.13 2005/01/28 15:29:58 steigies Exp $

CC = gcc
CXX = g++
CFLAGS = -g
CPPFLAGS = $(CFLAGS)

default: 
	cd ./src; make
	ln -s ./src/swicstest

clean: 
	cd ./src; make clean
	rm -f *.o
	rm -f swicstest
	rm -f *~


