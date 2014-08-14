PLATFORM=auto

OUTPUT=shoot
SRC=src
OBJ=obj

INCLUDE=
LIBRARY=-lSDL2

CONSTANTS=

CXX=g++
CXXFLAGS=-std=c++11 -g -Wall -Wno-unused -O3
LXXFLAGS=-std=c++11 -O3


#-----------------------------------------------------------#

SOURCES=$(wildcard $(SRC)/*.cpp)
OBJECTS=$(SOURCES:$(SRC)/%.cpp=$(OBJ)/%.o)
OBJECTS_DEL=$(OBJECTS)

DEST=bad_platform

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

	LIBRARY:=-lSDL2main -lopengl32 $(LIBRARY)
	LXXFLAGS+=-mwindows
endif


ifeq "$(PLATFORM)" "windows"
	DEL=del /F/Q
	OBJECTS_DEL=$(SOURCES:$(SRC)/%.cpp=$(OBJ)\\%.o)
	
	DEST=$(OUTPUT)
endif

ifeq "$(PLATFORM)" "mingw"
	DEL=rm -f
	
	# msys stuff
	LIBRARY:=-L/lib -lmingw32 $(LIBRARY)
	INCLUDE+=-I/include
	
	DEST=$(OUTPUT)
endif


ifeq "$(PLATFORM)" "linux"
	# use -f to ignore missing files
	DEL=rm -f
	
	DEST=$(OUTPUT)

	LIBRARY+=-lGL
endif

ifeq "$(PLATFORM)" "osx"
	# ???
endif


CXXFLAGS+=$(INCLUDE) $(CONSTANTS:%=-D%)
LXXFLAGS+=$(LIBRARY)


all: $(OBJ) $(DEST)

usage:
	@echo Use 'make PLATFORM=...' to set the platform
	@echo Available platforms:
	@echo     windows
	@echo     mingw
	@echo     linux

bad_platform:
	@echo Invalid platform '$(PLATFORM)'
	
$(OUTPUT): $(OBJECTS) Makefile
	$(CXX) $(OBJECTS) $(LXXFLAGS) -o $(OUTPUT)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

clean:
	$(DEL) $(OBJECTS_DEL) $(OUTPUT)

$(OBJ):
	mkdir $(OBJ)
#


	
rebuild: clean all
go: all
	./$(OUTPUT)
