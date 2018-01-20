# GibEngine
-----------------------

A 3D game engine, and associated world editor. Builds available for Windows, Ubuntu Linux.

![GibEditor Screenshot](https://i.imgur.com/2rxN2Ti.jpg)

| Windows | Linux | Codacy Grade |
| :------ | :---- | :----------- |
| [![Build status](https://ci.appveyor.com/api/projects/status/yb3s8d92ii3035u0?svg=true)](https://ci.appveyor.com/project/MattRyder/gibengine) | [![Build Status](https://travis-ci.org/MattRyder/GibEngine.svg?branch=master)](https://travis-ci.org/MattRyder/GibEngine) | [![Codacy Badge](https://api.codacy.com/project/badge/Grade/c0b8f78f53384371b5f8293b2e6129f1)](https://www.codacy.com/app/MattRyder/GibEngine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=MattRyder/GibEngine&amp;utm_campaign=Badge_Grade)|

# Requirements
 * cmake > 3.1
 * C++11 compatible compiler
 * OpenGL 4.0 or OpenGL ES 3.0 compatible GPU

# Build Instructions

## GNU/Linux
``` bash
git clone https://github.com/MattRyder/GibEngine.git
mkdir build
cd build
cmake ..
make
```

## Windows, MSVC
``` bash
git clone https://github.com/MattRyder/GibEngine.git
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" ..
# Open GibEngine.sln within the `build` directory
```