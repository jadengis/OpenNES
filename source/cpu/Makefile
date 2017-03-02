###############################################################################
# OsNES osnes/source/Makefile
#
# This Makefile will be used to build all C++ files in the source directory.
###############################################################################

ifndef TOP
	TOP := ../..
endif
# For including common make utility commands
include $(TOP)/Makefile.util

###############################################################################
# Flags and Definitions
###############################################################################

LIB = libcpu.a

CFLAGS  := $(CFLAGS)
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

all: $(LIB)

$(LIB) : $(OBJECTS)
	$(AR) rsv $(LIB) $(OBJECTS)

%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o *.d *.a *.gcno *.gcda
