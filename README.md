# Blaster #

This is a Uni project using c++, SDL, SDL_ttf

## Story ##
In a galaxy far far away, aliens have invaded Rumple, they come in waves and try to get to the ground**Blaster**.

## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line

```bash
$ g++ -c src/*.cpp
$ g++ -o starship *.o -lSDL2 -lSDL2_image
```

You will also need SDL_ttf.h, credit to http://elinux.org/Didj_and_Explorer_SDL_ttf for the information

It is fairly simple to install SDL_ttf, it requires freetype to be installed as well, so we will do both from their own folder in the packages directory, so browse to your kernel sources, go to the packages folder and make 2 new folders:

mkdir SDL_ttf freetype


copy the following into a a text editor and save it into the freetype folder as install.sh

#!/bin/bash
export CFLAGS='-I${ROOTFS_PATH}/usr/include -I${ROOTFS_PATH}/usr/include/SDL'
export LD_FLAGS='-L${ROOTFS_PATH}/usr/lib'
export CC=arm-linux-uclibcgnueabi-gcc
export CXX=arm-linux-uclibcgnueabi-g++ 
if [ "$CLEAN" == "1" ]; then
rm -rf ./SDL_ttf-2.0.10
rm ./SDL_ttf-2.0.10.tar.gz
wget http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.10.tar.gz
tar -xf SDL_ttf-2.0.10.tar.gz
fi
cd ./SDL_ttf-2.0.10
./configure --prefix=${ROOTFS_PATH}/usr --build=`uname -m` --host=arm-linux --enable-shared --libdir=${ROOTFS_PATH}/usr/lib --includedir=${ROOTFS_PATH}/usr/include --without-x --disable-opengl --with-sdl-prefix=${ROOTFS_PATH}/usr/
make -j3
make -j3 install


Now do the same for SDL_ttf and save it into the SDL_ttf folder as install.sh

#!/bin/bash
export CFLAGS='-I${ROOTFS_PATH}/usr/include -I${ROOTFS_PATH}/usr/include/SDL'
export LD_FLAGS='-L${ROOTFS_PATH}/usr/lib'
export CC=arm-linux-uclibcgnueabi-gcc
export CXX=arm-linux-uclibcgnueabi-g++ 
if [ "$CLEAN" == "1" ]; then
rm -rf ./SDL_ttf-2.0.10
rm ./SDL_ttf-2.0.10.tar.gz
wget http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.10.tar.gz
tar -xf SDL_ttf-2.0.10.tar.gz
fi
cd ./SDL_ttf-2.0.10
./configure --prefix=${ROOTFS_PATH}/usr --build=`uname -m` --host=arm-linux --enable-shared --libdir=${ROOTFS_PATH}/usr/lib --includedir=${ROOTFS_PATH}/usr/include --without-x --disable-opengl --with-sdl-prefix=${ROOTFS_PATH}/usr/
make -j3
make -j3 install

As long as you have your environment variables set you should now be able to start compiling/installing the freetype lib which is needed by SDL_ttf.

go into the freetype directory and type:

CLEAN=1 ./install.sh

Once its done you should have the freetype headers in your ROOTFS_PATH/usr/include and the libs in ROOTFS_PATH/usr/lib, if they are there you are now ready to compile SDL_ttf.


Same procedure here, go into the SDL_ttf directory and type:

CLEAN=1 ./install.sh


that should put your headers and libs into their appropriate places in ROOTFS_PATH/usr/include and /lib

if you ever want to build either lib again, you can omit the CLEAN=1 from the ./install.sh command, unless of course you want to build from scratch.

to use the libs add the following to your .c file:

#include "SDL/SDL_ttf.h"

and to compile use something like this:

arm-linux-uclibcgnueabi-gcc -o testttf testttf.c -I${ROOTFS_PATH}/usr/include/ -L${ROOTFS_PATH}/usr/lib -lSDL -lSDL_ttf -lfreetype -lpthread



which will produce an executable file called "starship" in the
top-level directory.  To execute this file do the following

`$ ./starship`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Issues ##
The font is causing issues and needs a small fix, renderer is almost working as well

## Credits ##
The sprites in this game come directly from 
[SpriteLib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html) and are used
under the terms of the [CPL 1.0](http://opensource.org/licenses/cpl1.0.php).


The event system is based on [Libsigc++](http://libsigc.sourceforge.net/)
and is used under the [LGPL](http://www.gnu.org/copyleft/lgpl.html).
