PLATFORM=auto
PUBLISH=


OUTPUT=shoot
BIN=bin
SRC=src
OBJ=obj


INCLUDE=
LIBRARY=-lSDL2

CONSTANTS=
GLOBAL_HEADERS=include.h math.hpp


CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wno-unused -O2
LXXFLAGS=-std=c++11 -O2


#-----------------------------------------------------------#

ifndef PUBLISH
CONSTANTS+=BUILD_DEBUG
CXXFLAGS+=-g
else
LXXFLAGS+=-s
endif

SOURCES=$(wildcard $(SRC)/*.cpp)
OBJECTS=$(SOURCES:$(SRC)/%.cpp=$(OBJ)/%.o)
OBJECTS_DEL=$(OBJECTS)

DEST=bad_platform
EXEC=$(BIN)/$(OUTPUT)

ifndef PLATFORM
	DEST=usage
endif

ifeq "$(PLATFORM)" "auto"
	UNAME=$(shell uname -s)
	ifeq "$(OS)" "Windows_NT"
		PLATFORM=windows
	endif
	ifeq "$(UNAME)" "MINGW32_NT-6.1"
		PLATFORM=mingw
	endif
	ifeq "$(UNAME)" "Linux"
		PLATFORM=linux
	endif
	ifeq "$(UNAME)" "Darwin"
		PLATFORM=osx
	endif
endif

# windows with or without msys/mingw
ifeq "$(OS)" "Windows_NT"
	OUTPUT:=$(OUTPUT).exe

	LIBRARY:=-lopengl32 -lSDL2main $(LIBRARY)
	ifdef PUBLISH
		LXXFLAGS+=-mwindows
	endif
endif


ifeq "$(PLATFORM)" "windows"
	DEL=del /F/Q
	OBJECTS_DEL=$(SOURCES:$(SRC)/%.cpp=$(OBJ)\\%.o)
	
	DEST=$(EXEC)
endif

ifeq "$(PLATFORM)" "mingw"
	DEL=rm -f
	
	# msys stuff
	ifndef HACKY_64
		LIBRARY:=-L/lib -lmingw32 $(LIBRARY)
	endif
	INCLUDE+=-I/include
	
	DEST=$(EXEC)
endif


ifeq "$(PLATFORM)" "linux"
	# use -f to ignore missing files
	DEL=rm -f
	
	DEST=$(EXEC)

	LIBRARY+=-lGL
endif

ifeq "$(PLATFORM)" "osx"
	# ???
endif


ifdef HACKY_64
	CXX=g++-64
	LIBRARY+=-L/lib/64
endif


CXXFLAGS+=$(INCLUDE) $(CONSTANTS:%=-D%)
LXXFLAGS+=$(LIBRARY)


all: $(OBJ) $(BIN) $(DEST)

usage:
	@echo Use 'make PLATFORM=...' to set the platform
	@echo Available platforms:
	@echo     windows
	@echo     mingw
	@echo     linux

bad_platform:
	@echo Invalid platform '$(PLATFORM)'
	
$(EXEC): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(LXXFLAGS) -o $@

$(OBJ)/%.o: $(GLOBAL_HEADERS:%=$(SRC)/%)
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

clean:
	$(DEL) $(OBJECTS_DEL) $(OUTPUT)

$(OBJ):
	mkdir $@
$(BIN):
	mkdir $@
#


	
rebuild: clean all
go: all
	cd $(BIN) && ./$(OUTPUT)
