# Omni-FEM

The development repository for the Omni-FEM simulator

The simulator is still under construction

Please see wiki for more inforation

# Requirements

Must have wxWidgets v3.1.0 installed
Must have support for openGL V2.1
For font rendering in the canvas, we are using the freetype library. The current version that the program uses in FreeType2.7
The font that the program uses is called DejaVuSansMono. 

# Notes

A helpful tool, the project was built using the Code Lite IDE. It can be downloaded here: http://downloads.codelite.org/
For building the project, run the command:

sudo apt-get install freeglut3-dev
sudo apt-get install libglew-dev

This will get the OpenGL libraries. Double check compiler settings to make sure that -lglut, -lGL, and -lGLU are placed in their approiate places (This does matter).

To install wxwidgets, follow these instructions:
http://codelite.org/LiteEditor/WxWidgets31Binaries#toc2

The current version of Omni-FEM is running wxwidgets v3.1.0

The icons that are used by the UI are the default kde4 icons that are suppose to be located in the folder /usr/share/icons

In order to install the freetype 2.7, run these commands in terminal (these are for ubuntu. Another otion is to build the source)

sudo add-apt-repository ppa:no1wantdthisname/ppa
sudo apt update && sudo apt install libfreetype6

The include files are located in /usr/include/freetype2 and the library file is located in /usr/lib/x86_64-linux-gnu/libfreetype.a

In order to install and run the fonts, you have to first install the microsoft core fonts:

sudo apt-get install ttf-mscorefonts-installer
sudo fc-cache -f -v
sudo apt-get install ubuntu-restricted-extras

An easy way to install boost on ubuntu is to run the following command:
sudo apt-get install libboost-all-dev


In order for dealii to run, you must copy the library files from the deal ii install location to /usr/lib. Must be root.

Same thing goes for paraview libraries.
=======
There are a few things that need to happen in order to compile dealii directly from an IDE without the need for cmake file

1) In the compiler settings, you need to make sure that the include paths are to your installation for dealII.Both for the sources and what is bundled.
Ex.
/home/phillip/dealii851/include
and
/home/phillip/dealii851/include/deal.II/bundled

2) IN the linker settings, have the linker library search path point to the dealii installation director with the lib folder. And, place in the library name in the Libraries option
Ex
Path -> /home/phillip/dealii851/lib
Library -> libdeal_II

3) In order to actually run a program (steps 1 and 2 will allow you to compile the application), you need to copy the library libdeal_II.so.8.5.1 from the lib folder in the installation directory of DealII to the /usr/lib folder
