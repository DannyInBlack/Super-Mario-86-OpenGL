# CS352 Project (UNI) : OpenGL
This repo attempts at recreating Super Mario (1986) in OpenGL from scratch!

## Getting Started
This project was created for Ubuntu Linux and so some of the requirements and functionality might change on other operating systems.

### Libraries and Prerequisites
This project uses OpenGL libraries ([FreeGLUT specifically](https://freeglut.sourceforge.net/)) as well as a basic version of GNU GCC G++ for compiling the C++ file.

1. `sudo apt install g++` to install the default version of G++.
2. `sudo apt install freeglut3-dev` to install FreeGLUT.

This section will include more info on running on windows in the future.

### Build instructions

1. Clone the repository.
2. Go to `main.cpp`.
3. Build the file using the default g++ commands and link the GL libraries: <br />
   `g++ -O2 main.cpp -o main -lglut -lGL -lGLU`
(Make sure you have OpenGL libraries installed beforehand!) <br />

### Running the game
Just run the executable `main` that was created earlier!

![image](https://github.com/DannyInBlack/Project/assets/112534338/bfaf566e-0a8d-44e7-980c-d4202ae32c51)
