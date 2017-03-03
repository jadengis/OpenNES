###############################################################################
# OpenNES tests/memory/Makefile
#
# This Makefile will be used to build all C++ files in the source/memory dir
###############################################################################

ifndef TOP
	TOP := ../..
endif
# For including common make utility commands
include $(TOP)/Makefile.util

###############################################################################
# Flags and Definitions
###############################################################################

LIB = 

CFLAGS  := $(CFLAGS) -I $(TOP)/source/cpu
LDFLAGS := 

###############################################################################
# Source
###############################################################################
.KEEP_STATE:
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

###############################################################################
# Targets
###############################################################################

all: $(OBJECTS)

%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	$(RM) $(TORM)
