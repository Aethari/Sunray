# The C compiler to be used (i.e. gcc)
CC=gcc
CC_WIN=x86_64-w64-mingw32-gcc

# Anytime a path variable is declared here, it should always have a / at the end

# The windows path to Lua's source - lua >= 5.2 is required, 5.4.7 recommended
LUA_WINPATH=C:/Lua/source/

# The linux path to Lua's source - lua >= 5.2 is required, 5.4.6 recommended
LUA_LNXPATH=/usr/include/lua5.4/

# Build flags for linux
LNX_CFLAGS=-I src -I$(LUA_LNXPATH) -L$(LUA_LNXPATH) -llua5.4 -Wall

# Build flags for windows
WIN_CFLAGS=-I src -Wall -D_WIN32

# Create a debug build targeted to linux
build-lnx:
	@make clean
	@mkdir build
	@$(CC) ./*.c ./src/*.c $(LNX_CFLAGS) -o ./build/main

# Create a debug build targeted to linux (using build-lnx), then runs it
test-lnx:
	@make build-lnx
	@./build/main

# Create a debug build targeted to windows
build-win:
	@make clean
	@mkdir build
	@$(CC_WIN) ./*.c ./src/*.c $(WIN_CFLAGS) -o ./build/main.exe

# Create a debug build targeted to windows (using build-win), then runs it
test-win:
	@make build-win
	@./build/main.exe

# Removes the build directory
clean:
	@rm -fr build

