###############################################################################
# OsNES osnes/Makefile
#
# This Makefile will build all the OsNES source and test executables
###############################################################################

ifndef TOP
	TOP := .
endif
# For including common make utility commands
include $(TOP)/Makefile.util

###############################################################################
# Flags and Definitions
###############################################################################

SOURCES := source/

###############################################################################
# Targets
###############################################################################
.PHONY: all $(SOURCES)

all: $(SOURCES)
	
$(SOURCES):
	$(MAKE) -C $@

clean: 
	$(foreach source, $(SOURCES), $(MAKE) -C $(source) clean;)

ctags:
	$(CTAGS) -R -f ./tags .
