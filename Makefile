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
TESTS   := tests/
ALL_SOURCES = $(shell find . -name '*.cpp')
###############################################################################
# Targets
###############################################################################
.PHONY: all $(SOURCES)

all: $(SOURCES)
	
$(SOURCES):
	$(MAKE) -C $@

clean: 
	$(foreach source, $(SOURCES), $(MAKE) -C $(source) clean;)
	$(RM) -f *.o *.gcno *.gcda *.gcov

test:
	$(foreach test, $(TESTS), $(MAKE) -C $(test);)

ctags:
	$(CTAGS) -R -f ./tags .
