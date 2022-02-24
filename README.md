# SneakyEngine

Fun gaming/visualisation engine to keep (and improve) my C++ and mathematics knowledge.

# Build
This project uses cmake, so make sure you installed this (at the time of writing cmake version 3.19.6 is used).
You can check your cmake version with:
```
cmake --version
```

Also, make sure you have SDL2 installed on your system. Assuming you use a Linux (Debian based) system, install it using the following command:
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
The goal of this project is to make something fun and learn stuff while doing it. The intend is to eventually make a library out of it to be used for other projects (possibly even with Python3 bindings, who knows).
