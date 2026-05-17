ifeq ($(OS),Windows_NT)
	.DEFAULT_GOAL := windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		.DEFAULT_GOAL := linux
	endif
	ifeq ($(UNAME_S),Darwin)
		.DEFAULT_GOAL := mac
	endif
endif

all: directories common linux windows

.PHONY: directories clean common linux windows

# What you are supposed to call
clean:
	@echo "Cleaning old binaries"
	@rm bin -rf

ifeq ($(OS),Windows_NT)
linux: 
	@echo "Unfortunately you can't compile for linux from windows"

windows: common bin/main.exe bin/SDL2.dll bin/SDL2_image.dll
else
linux: common bin/main
	
windows: common bin/main.exe bin/SDL2.dll bin/SDL2_image.dll bin/libstdc++-6.dll bin/libgcc_s_seh-1.dll
endif

#Common
common: directories

directories:
	@mkdir -p bin/

#Linux
bin/main: src/AarniEngine/* main.cpp
	@echo "Compiling game for Linux"
	g++ -I src -o bin/main main.cpp -lSDL2main -lSDL2 -lSDL2_image

#Windows
bin/main.exe: src/AarniEngine/* main.cpp
	@echo "Compiling game for Windows"
	x86_64-w64-mingw32-g++ -I src -ISDL2/include/ -LSDL2/lib/ -o bin/main.exe main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

bin/SDL2.dll: SDL2/bin/SDL2.dll
	cp SDL2/bin/SDL2.dll bin/SDL2.dll

bin/SDL2_image.dll: SDL2/bin/SDL2_image.dll
	cp SDL2/bin/SDL2_image.dll bin/SDL2_image.dll

bin/libstdc++-6.dll: /usr/lib/gcc/x86_64-w64-mingw32/13-win32/libstdc++-6.dll
	cp /usr/lib/gcc/x86_64-w64-mingw32/13-win32/libstdc++-6.dll ./bin/

bin/libgcc_s_seh-1.dll: /usr/lib/gcc/x86_64-w64-mingw32/13-win32/libgcc_s_seh-1.dll
	cp /usr/lib/gcc/x86_64-w64-mingw32/13-win32/libgcc_s_seh-1.dll ./bin/
