#-----------------------------------------------------------------------------
# SPICE demonstration
#-----------------------------------------------------------------------------
MAKEFILE      = Makefile
####### Compiler, tools and options

DEFINES       	=  -D_DEBUG
DEFINES			+= -DhcFloat=float		# floating point precision to be used

CC            	= gcc
CXX           	= g++
CFLAGS        	= -pipe -g -fPIE $(DEFINES)
CXXFLAGS      	= -pipe -g -std=c++0x -fPIE -O0 $(DEFINES)  -Wall
INCPATH       	= -I. -I/usr/include 
LINK          	= g++
LFLAGS        	= -O0	
LIBS			= -L/usr/lib64/ -L/usr/local/lib/
LIBS			+= -l:cspice.a -lm										# NAIF spice library
DEL_FILE      	= rm -f

####### Output directory

DST_DIR   = ./bin/

####### Files

OBJECTS       = main.o 		

OBJECTS_IN_DIR = $(addprefix $(DST_DIR), $(OBJECTS))

TARGET        = spice

first: all

####### Build rules

all: $(TARGET)

$(TARGET):  $(OBJECTS_IN_DIR) $(CUDAOBJ_IN_DIR)
	$(LINK) $(LFLAGS) -o $(DST_DIR)$(TARGET) $(OBJECTS_IN_DIR) $(CUDAOBJ_IN_DIR) $(LIBS)

clean:
	-$(DEL_FILE) $(OBJECTS_IN_DIR) $(CUDAOBJ_IN_DIR) $(DST_DIR)cudalink.o	
	-$(DEL_FILE) *~ core *.core
	-$(DEL_FILE) $(DST_DIR)$(TARGET)

####### Compile

$(DST_DIR)main.o: ./main.cpp 
	$(CXX) $(CXXFLAGS) $(INCPATH) -c -o $(DST_DIR)main.o ./main.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
