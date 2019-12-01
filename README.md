# What is it
It is a simple implementation of [GO](https://en.wikipedia.org/wiki/Go_(game)) game written in **C++** using **[SFML](https://github.com/SFML/SFML)** library for drawing.
Players can play 1vs1 on one PC or you can play versus AI (WIP).
The AI uses [Monte Carlo Tree Search](http://wikipedia.org/wiki/Monte-Carlo_Tree_Search) to evaluate moves.

# Cloning and building the project

## Cloning directory
To clone a project run this command
```bash
git clone --recurse-submodules https://github.com/LoGosX/PO_Go
```
this command will download source for this project and for third party libraries.

## Building 
To build a project run following commands from project directory (directory that was created by ```git clone``` command):
```bash
chmod +x compile.bash
./compile.bash
```

To build a project again run 
```bash
./compile.bash
``` 

## Running
To run the project :
```bash
chmod +x run.bash
./run.bash
```
or
```bash
./compile.bash --run
```
if you want to compile project before running


# Dependencies:
To build this project, ```cmake``` program needs to be installed.
## Linux dependencies
These packages required to make SFML work on Linux.
+ freetype
+ x11
+ xrandr
+ udev
+ opengl
+ flac
+ ogg
+ vorbis
+ vorbisenc
+ vorbisfile
+ openal
+ pthread

You can use following commands to install those on Ubuntu:
```bash
sudo apt-get install -y libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev libxcb-image0-dev libjpeg-dev libflac-dev
```