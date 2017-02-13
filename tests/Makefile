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
EXECUTABLE = test.out
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
SUBSYSTEMS := $(sort $(dir $(wildcard */ )))

TESTS = $(foreach dir, $(SUBSYSTEMS),$(wildcard $(dir)*.o))

###############################################################################
# Targets
###############################################################################
.PHONY: all $(SUBSYSTEMS)

all: $(EXECUTABLE)
	$(CXX) $(LFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(TESTS) 

$(EXECUTABLE): $(OBJECTS) $(SUBSYSTEMS)
	
%.o : %.cpp
	$(CXX) $(CFLAGS) $< -o $@

$(SUBSYSTEMS):
	$(MAKE) -C $@

clean: 
	$(foreach subsystem, $(SUBSYSTEMS), $(MAKE) -C $(subsystem) clean;)
	$(RM) *.o *.d *.gcov *.gcno *.gcda
