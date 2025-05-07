# Makefile for building, testing, and installing Sunray.
# See README.md for more information about the project.
# See LICENSE.txt for license info

# == START USER MODIFICATIONS ======================================
# You may change any of the settings below to suit your environment.
# Please do not try to push custom changes that differ from the 
# default to the repository.

# The compiler to use. For cross-platform development/testing,
# different variables for Unix and Windows are used.
CC = gcc
CC_WIN = x86_64-w64-mingw32-gcc

# == END USER MODIFICATIONS ========================================
# Anything beyond this point is not very user-friendly and should 
# not be touched by a normal user, unless you want to add support
# for additional platforms.

# Hide "Entered directory" and "Exited directory" messages
MAKEFLAGS += --no-print-directory

# All of the C files that need to be compiled
SRCS = main.c \
	   src/*.c \
	   src/util/*.c \
	   src/assets/*.c \
	   src/pages/*.c

# -- Detect OS ------------------------------------------------
UNAME_S = $(shell uname -s)

# Windows
ifeq ($(OS), Windows_NT)
$(info Guessing Windows_NT)

CC = $(CC_WIN)

all: build-win
build: build-win
test: test-win
clean: clean-win

# Unix
else
$(info Guessing Unix)

all: build-nix
build: build-nix
test: test-nix
install: install-nix
clean: clean-nix

endif

# -- Includes/linking -----------------------------------------
INCLUDE = -Isrc -Ilib/SDL/include -Ilib/SDL_ttf/include -Ilib/lua/src
LINK = -Llib
CFLAGS = -lSDL3 -lSDL3_ttf -llua54 -lm -Wall

# == Unix targets =============================================
build-nix:
	make clean

	mkdir -p build

	cp lib/libSDL3.so.0.2.12 build/libSDL3.so.0.2.12
	ln -s build/libSDL3.so.0.2.12 build/libSDL3.so.0
	ln -s build/libSDL3.so.0.2.12 build/libSDL3.so

	cp lib/libSDL3_ttf.so.0.3.0 build/libSDL3_ttf.so.0.3.0
	ln -s build/libSDL3_ttf.so.0.3.0 build/libSDL3_ttf.so.0
	ln -s build/libSDL3_ttf.so.0.3.0 build/libSDL3_ttf.so

	cp -R src/scripts build/scripts

	cp LICENSE.txt build/LICENSE.txt

	@echo
	@echo Compiling project:
	$(CC) $(SRCS) $(INCLUDE) $(LINK) $(CFLAGS) -o build/sunray

test-nix:
	make

	@echo
	@echo Running project:
	./build/sunray

install-nix:
	make
	cp /build/sunray /usr/bin/sunray

clean-nix:
	@mkdir -p build
	rm -fr build

# == Windows targets ==========================================
build-win:
	make clean

	@echo mkdir build
	@cmd /C "if not exist build mkdir build"

	@echo copy /Y "lib/SDL3.dll" "build/SDL3.dll"
	@cmd /C "copy /Y "lib\\SDL3.dll" "build\\SDL3.dll" > nul"

	@echo copy /Y "lib/SDL3_ttf.dll" "build/SDL3_ttf.dll"
	@cmd /C "copy /Y "lib\\SDL3_ttf.dll" "build\\SDL3_ttf.dll" > nul"

	@echo copy /Y "lib/lua54.dll" "build/lua54.dll"
	@cmd /C "copy /Y "lib\\lua54.dll" "build\\lua54.dll" > nul"

	@echo xcopy src/scripts build/scripts
	@cmd /C "xcopy src\\scripts build\\scripts /E /I /H /Y > nul"

	@echo copy /Y "LICENSE.txt" "build/LICENSE.txt"
	@cmd /C "copy /Y "LICENSE.txt" "build\\LICENSE.txt" > nul"

	@echo
	@echo Compiling project:
	$(CC) $(SRCS) $(INCLUDE) $(LINK) $(CFLAGS) -o build/sunray.exe

test-win:
	make

	@echo
	@echo Running project:
	./build/sunray.exe

clean-win:
	@cmd /C "if not exist "build" mkdir build"

	@echo rmdir /s /q build
	@cmd /C "rmdir /s /q build"
