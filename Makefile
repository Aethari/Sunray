# Hide "Entered directory" and "Exited directory" messages
MAKEFLAGS += --no-print-directory

# The C compiler to be used (i.e. gcc)
CC=gcc
CC_WIN=x86_64-w64-mingw32-gcc

SRCS = main.c \
	   src/*.c \
	   src/util/*.c \
	   src/assets/*.c

# Anytime a path variable is declared here, it should always have a / at the end

# The linux path to a parent include directory - for this project, contains
# a "lua5.4" folder with Lua 5.4 headers, and an "SDL3" folder with SDL headers.
# The parent directory should also include a library file (.so, .a, etc.) for
# each header folder.
LNX_INCLUDEPATH=/usr/include/

# Build flags for linux
LNX_CFLAGS=-I src -I$(LNX_INCLUDEPATH) -L$(LNX_INCLUDEPATH) -llua5.4 -lSDL3 -lm -Wall

# The windows path to a parent include directory - for this project, contains
# a "lua5.4" folder with Lua 5.4 headers, and an "SDL3" folder with SDL headers
# The parent directory should also include a library file (.dll, .a) for each
# header folder.
WIN_INCLUDEPATH=C:/Include/

# Build flags for windows - missing lua at the moment
WIN_CFLAGS=-I src -I$(WIN_INCLUDEPATH) -L$(WIN_INCLUDEPATH) -l:lua5.4.a -lSDL3 -lm -Wall

# Create a debug build targeted to linux
build-lnx:
	@make clean
	@mkdir build
	@cp -R ./src/scripts ./build/
	@$(CC) $(SRCS) $(LNX_CFLAGS) -o ./build/sunray

# Create a debug build targeted to linux (using build-lnx), then runs it
test-lnx:
	@make build-lnx
	@./build/sunray

# Create a debug build targeted to windows
build-win:
	@make clean
	@mkdir build
	@cp -R ./src/scripts ./build/
	@cp ./include/SDL3.dll ./build/SDL3.dll
	@$(CC_WIN) $(SRCS) $(WIN_CFLAGS) -o ./build/sunray.exe

# Create a debug build targeted to windows (using build-win), then runs it
test-win:
	@make build-win
	@./build/sunray.exe

# Removes the build directory
clean:
	@rm -fr build

