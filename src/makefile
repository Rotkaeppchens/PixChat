PROJECT := PixChat

TARGET 	:= $(PROJECT)

DEBUG 	:=
CACHE	:= ccache
FLAGS 	:= -Wall -std=c++0x $(shell fltk-config --use-images --cxxflags) $(shell gloox-config --cxxflags)
LIB 	:= $(shell fltk-config --use-images --ldflags) $(shell gloox-config --libs)
INC		:= $(shell fltk-config --use-images --includedir)

DIR 	:= ../env/bin
TMP		:= ../build
TMP_O 	:= $(TMP)/o
TMP_D 	:= $(TMP)/d
DFILE	:= $(TMP_D)/project.d

CC 		:= $(CACHE) g++ $(DEBUG) -c $(FLAGS)
LD 		:= $(CACHE) g++ $(DEBUG)
RM 		:= rm
CD 		:= cd
DGEN	:= g++ -MM -MG

DOXYCONF := doxy-conf

ifeq ($(OS),Windows_NT)
	OPTSUFFIX := .exe
else
	OPTSUFFIX :=
endif


# The project modules
MODULES := main config gnf includes interface log utility

SRC :=

# Including the mk files from the modules
include $(patsubst %, %/module.mk, $(MODULES))

# Include the dep file
-include $(DFILE)

# Determining the obj files
OBJ := $(patsubst %.cpp, $(TMP_O)/%.o, $(notdir $(filter %.cpp, $(SRC))))

help:
	@echo $(PROJECT) help.
	@echo	build 		Build the project.
	@echo 	clean 		Clean the build environment.
	@echo 	doxygen		Create The auto documentation.
	@echo	help		Display this help.

clean:
	@echo Cleaning TMP and BIN Files
	@$(RM) -f $(DIR)/$(TARGET)$(OPTSUFFIX)
	@$(RM) -f $(TMP_O)/*.o
	@$(RM) -f $(DFILE)

build: $(OBJ)
	@echo Linking...
	@$(LD) -o $(DIR)/$(TARGET)$(OPTSUFFIX) $(TMP_O)/*.o $(LIB)
	@echo Finished

doxygen:
	@echo Generating documentation ... && doxygen $(DOXYCONF)

$(DFILE): $(SRC)
	@echo Removing old dependency file...
	@$(RM) -f $(DFILE)
	@echo Generating dependency file $(DFILE) ...
	@$(DGEN) $(filter %.cpp, $(SRC)) | sed -e "s@\(.*.o:\)@$(TMP_O)/\1@" >> $(DFILE)

%.o:
	@echo Building $@  ...
#~ 	@echo Targets $^ ...
	@$(CC) -o $@ $(filter %.cpp, $^)
