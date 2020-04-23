# ttTrace

This repository contains a Windows-only app that will display strings sent to it by using the `ttTRACE` macro (or `ttlib::wintrace` function) found in the `ttLib/include/ttdebug.h` header file. Besides displaying strings from any program that uses the **ttLib** macro or function, this will also display strings sent by the **KeyHelp** and **HTML Help** ActiveX controls.

## Cloning

To clone this repository, use:

```
git clone --recurse-submodules https://github.com/KeyWorksRW/ttTrace
```

If you already cloned the repository without using the --recurse command, then enter:

```
	git submodule init
	git submodule update
```

## Building

At an absolute minimum, you will need to have the following in your PATH:

- [Ninja.exe](https://github.com/ninja-build/ninja)

- Either of the following compilers:
  - [CLANG](https://clang.llvm.org/) (version 7 or higher)
  - MSVC

Before building, you will need to start one of the Visual Studio command shells, preferably one that builds 64-bit targets. From within that shell, you can use the following commands to build the library:

	cd src
	nmake

By default, this will build a 64-bit release version of the `ttLib.lib` library followed by a 64-bit version of `ttTrace.exe`.

If you have MINGW installed and both MINGW and the **clang-cl** compiler are in your PATH, you can use the following commands to build:

	cd src
	mingw32-make

## Contributing

If you wish to contribute to the project, please refer to the [Contributing](CONTRIBUTING.md) documentation.
