###############################################################################
# OpenNES OpenNES/tests/Makefile
#
# This Makefile will build all the OsNES subsystems (CPU, PPU, Memory etc.)
###############################################################################

ifndef TOP
	TOP := ..
endif
# For including common make utility commands
include $(TOP)/Makefile.util

###############################################################################
# Flags and Definitions
###############################################################################

.KEEP_STATE:
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
SUBSYSTEMS := $(sort $(dir $(wildcard */ )))

###############################################################################
# Targets
###############################################################################
.PHONY: all $(SUBSYSTEMS)

all: $(SOURCES) $(SUBSYSTEMS)
	
%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

$(SUBSYSTEMS):
	$(MAKE) -C $@

clean: 
	$(foreach subsystem, $(SUBSYSTEMS), $(MAKE) -C $(subsystem) clean;)
	$(RM) *.o *.d
