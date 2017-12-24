# A sub makefile

OBJDIR     = ../../../build
MAKEDIR    = gnf
MAKETARGET = $@
MAKE       = make --no-print-directory

.EXPORT_ALL_VARIABLES:
.PHONY: all

all: gnf friend_roster

%:
ifeq (0,${MAKELEVEL})
	@cd .. && $(MAKE) arecmake
else
	@if test -e $@.cpp; then \
	echo Building $@ ... && $(CC) $@.cpp -o $(OBJDIR)/$@.o; \
	else echo CALL ROOT FOR $@ && cd .. && $(MAKE) $@; \
	fi
endif
