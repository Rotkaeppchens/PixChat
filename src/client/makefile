PROJECT = PixChat

TARGET 	= $(PROJECT)
DEBUG 	=
FLAGS 	= -Wall -std=c++0x $(shell fltk-config --use-images --cxxflags) $(shell gloox-config --cxxflags)
LIB 	= $(shell fltk-config --use-images --ldflags) $(shell gloox-config --libs)
INC		= $(shell fltk-config --use-images --includedir)
DIR 	= ../../env/client/bin
TMP 	= ../../build
CC 		= $(OPTCACHE) g++ $(DEBUG) -c $(FLAGS)
LD 		= $(OPTCACHE) g++ $(DEBUG)
RM 		= rm
CD 		= cd
MAKE 	= make --no-print-directory
DOXYCONF = doxy-conf

ifeq ($(OS),Windows_NT)
	OPTCACHE =
else
	OPTCACHE = ccache
endif

.EXPORT_ALL_VARIABLES:
.PHONY: all main client_main config utility log interface gnf

print:
	@echo "############################## Building $(TARGET) ##############################"
clean:
	@echo Cleaning TMP and BIN Files && $(RM) $(DIR)/$(TARGET)
	@$(RM) $(TMP)/*.o
build: all link
build_extra: all link doxygen
arecmake:
	@echo Make $(MAKETARGET) from root && cd $(MAKEDIR) && $(MAKE) $(MAKETARGET)
link: print
	@echo Linking... && $(LD) -o $(DIR)/$(TARGET) $(TMP)/*.o $(LIB) && echo FINISHED
all: main client_main config log utility interface gnf

main: main.cpp
	@echo Building main ... && $(CC) main.cpp -o $(TMP)/main.o

client_main: client_main.cpp
	@echo Building client_main ... && $(CC) client_main.cpp -o $(TMP)/client_main.o

config: print
	@echo ROOTBUILD $@ && $(CD) $@ && $(MAKE)

utility: print
	@echo ROOTBUILD $@ && $(CD) $@ && $(MAKE)

log: print
	@echo ROOTBUILD $@ && $(CD) $@ && $(MAKE)

interface: print
	@echo ROOTBUILD $@ && $(CD) $@ && $(MAKE) all

gnf: print
	@echo ROOTBUILD $@ && $(CD) $@ && $(MAKE)

doxygen:
	@echo Generating documentation ... && doxygen $(DOXYCONF)

%:
	@if test -e $@.cpp; then \
	echo Building $@ ... && $(CC) $@.cpp -o $(TMP)/$@.o; \
	else if test -d $@; then echo ROOTBUILD $@ && cd $@ && $(MAKE); fi \
	fi
