# SneakyEngine

Fun gaming/visualisation engine to maintain (and improve) my C++ and mathematics knowledge.

# Build
This project uses cmake, so make sure you installed this (at the time of writing cmake version 3.23.1 is used).
You can check your cmake version with:
```
cmake --version
```

Also, make sure you have SDL2 installed on your system. Assuming you use a Linux (Debian based) system, install it using the following command (as root):
```
apt update && apt install libsdl2-dev
```

Now clone this repo to your system, generate the build files and build the project.
```
git clone https://github.com/jochemste/sneakyengine.git
cd sneakyengine
mkdir build && cd build
cmake ..
make
```

This should result in the executable being created in ```<repo>/bin/```, called *sneakyengine*

# Goal of the project
The goal of this project is to make something fun and learn stuff while doing it. The intend is to eventually make a library out of it to be used for other projects (possibly even with Python3 bindings, who knows). It is also used to learn more about things like GoogleTest, Valgrind, SDL2 and mroe. Creating a amateur gaming engine is simply a good way to learn a bit of everything.

# Testing
To run the unit tests manually, make sure you cloned this project with its submodules included. To clone the repository including the submodules, run:

```
git clone --recurse-submodules https://github.com/jochemste/sneakyengine.git
```

Or if you have already cloned the repository, use the following to update/clone the submodules:

```
git submodule update --init
```

After this, [build](#build) the executables. This will result in binary executables being placed in _bin/_. The test executable can be identified by the _\_tst_ postfix (e.g. _sneakyengine\_tst_).

Use the following command to automatically update submodules when pulling from the repo:

```
git submodule foreach git pull
```

[Valgrind](https://valgrind.org/) is also used to test for memory leaks, which is especially useful when performing the unit tests, since it is easier to spot the origin of a memory leak there. To do this, use the following command:

```
valgrind --tool=memcheck --leak-check=yes bin/sneakyengine_tst
```
# Documentation

[Doxygen](https://www.doxygen.nl/index.html) is used to generate the documentation.
