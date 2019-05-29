# Complete build instructions

First of all you need [cmake](https://cmake.org) (be sure to add it to the
`PATH`), then you need a compiler for your platform.

Once you have all of that, you can just do the following:

```
mkdir build
cd build
cmake ..
cmake --build .
```

## For Windows

You can use either [MSVC from Visual Studio](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools&rel=16),
[MinGW](http://www.mingw.org/) or [STL's MinGW](https://nuwen.net/mingw.html).
If none of these options are available, you can use [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux)
with the Linux instructions.

### For Visual Studio (Build Tools for VS or the actual IDE)

Please be sure to install the Windows SDK, Microsoft Visual C++ Compiler (the
2017 or the 2019 edition work fine) and MSBuild from the Visual Studio Installer.

Then, just invoke `cmake ..` in the `build` directory; it will automatically
find MSVC and generate a Visual Studio solution for the project.
If you don't care about modifying the project in Visual Studio, just run
`cmake --build .` in the `build` directory to compile the project.


### For any MinGW

Just invoke `cmake -G "MinGW Makefiles" ..` in the `build` directory and build
the program with `mingw-make` (or with `cmake --build .`).

## For Linux

You need a compiler like GCC or Clang. Your distro will probably ship with GCC
and glibc.

Just invoke `cmake ..` in the `build` directory, then use either `make` or
`cmake --build .`.

## For OSX

You need a compiler like GCC (from brew), upstream Clang (from brew) or
AppleClang (installed with XCode).

### With make and GCC/Clang/AppleClang

Just invoke `cmake .. -G "Makefile"` in the `build` directory, then use either
`make` or `cmake --build .`.

### With an XCode project

Just invoke `cmake .. -G "XCode Project"` in the `build` directory, then either
build it from XCode or run `cmake --build .`.
