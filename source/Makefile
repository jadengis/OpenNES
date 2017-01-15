###############################################################################
# OsNES osnes/source/Makefile
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

SUBSYSTEMS := $(sort $(dir $(wildcard */ )))

###############################################################################
# Targets
###############################################################################
.PHONY: all $(SUBSYSTEMS)

all: $(SUBSYSTEMS)
	
$(SUBSYSTEMS):
	$(MAKE) -C $@

clean: 
	$(foreach subsystem, $(SUBSYSTEMS), $(MAKE) -C $(subsystem) clean;)
