###############################################################################
# OsNES osnes/source/Makefile
#
# This Makefile will be used to build all C++ files in the source directory.
###############################################################################

ifndef TOP
	TOP := ..
endif
# For including common make utility commands
# include $(TOP)/Makefile.util

###############################################################################
# Flags and Definitions
###############################################################################

INCLUDE = ../include
LIB =

AR  		= /usr/bin/ar
RM  		= /bin/rm -f
CC  		= /usr/bin/clang
CXX 		= /usr/bin/clang++

CFLAGS  = -std=c++14 -I $(INCLUDE) -c
LDFLAGS = 

###############################################################################
# Source
###############################################################################
.KEEP_STATE:
SOURCES = mem.cpp mos_6502.cpp
OBJECTS = $(SOURCES:.cpp=.o)

###############################################################################
# Targets
###############################################################################

all: $(OBJECTS)

%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *.d
