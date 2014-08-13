PLATFORM=auto

OUTPUT=shoot
SRC=src
OBJ=obj

INCLUDE=-I.
LIBRARY=-lm
CONSTANTS=BUILD_DEBUG

CXX=g++
CXXFLAGS=-std=c++11 -g -Wall -Wno-unused -O3
LFLAGS=-std=c++11 -O3


#-----------------------------------------------------------#

CXXFLAGS+=$(INCLUDE) $(CONSTANTS:%=-D%)
LFLAGS+=$(LIBRARY)

SOURCES=$(wildcard $(SRC)/*.cpp)
OBJECTS=$(SOURCES:$(SRC)/%.cpp=$(OBJ)/%.o)
OBJECTS_DEL=$(OBJECTS)

DEST=bad_platform

ifndef PLATFORM
	DEST=usage
endif

ifeq "$(PLATFORM)" "auto"
	# got from http://stackoverflow.com/questions/714100/os-detecting-makefile
	ifeq "$(OS)" "Windows_NT"
		PLATFORM=windows
	else
		UNAME=$(shell uname -s)
		ifeq "$(UNAME)" "Linux"
			PLATFORM=linux
		endif
		ifeq "$(UNAME)" "Darwin"
			PLATFORM=osx
		endif
	endif
endif

ifeq "$(PLATFORM)" "windows"
	OUTPUT:=$(OUTPUT).exe
	DEL=del /F/Q
	OBJECTS_DEL=$(SOURCES:$(SRC)/%.cpp=$(OBJ)\\%.o)
	
	# mingw stuff
	LFLAGS+=
	
	DEST=$(OUTPUT)
endif

ifeq "$(PLATFORM)" "linux"
	# use -f to ignore missing files
	DEL=rm -f
	
	DEST=$(OUTPUT)
endif

ifeq "$(PLATFORM)" "osx"
	# ???
endif


all: $(DEST)

usage:
	@echo Use 'make PLATFORM=...' to set the platform
	@echo Available platforms:
	@echo     windows
	@echo     linux

bad_platform:
	@echo Invalid platform '$(PLATFORM)'
	
$(OUTPUT): $(OBJECTS)
	$(CXX) $(LFLAGS) -o $(OUTPUT) $(OBJECTS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(DEL) $(OBJECTS_DEL) $(OUTPUT)

rebuild: clean all