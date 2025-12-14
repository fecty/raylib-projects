
# raylib-projects

Different Projects made using raylib graphics library in C++ language.

## Overview
A collection of small example projects and experiments built with raylib. Each example lives under `src/` and includes a Makefile to build the demo.

## Projects
- Collision Detection — simple collision demo. See [src/collision-detection/main.cpp](src/collision-detection/main.cpp) and [src/collision-detection/README.md](src/collision-detection/README.md).
- Triangle Example — triangle drawing and basic input handling. See [src/triangle-example/main.cpp](src/triangle-example/main.cpp), [src/triangle-example/triangle.cpp](src/triangle-example/triangle.cpp) and [src/triangle-example/README.md](src/triangle-example/README.md).
- Template — a starter project template for new examples. See [src/template/main.cpp](src/template/main.cpp) and [src/template/README.md](src/template/README.md).

## Structure
- Headers for linking are available in [include/](include/) (e.g. [include/raylib.h](include/raylib.h)).
- Example sources and makefiles are under [src/](src/).
- Any libraries are in [lib/](lib/).

## Prerequisites
- Install raylib (system package or build from source) so headers and libraries are available to the Makefiles.

## Build & Run
Build an example by changing into the example directory and running make:

```sh
cd src/<project-name>
make
# then run the produced binary, e.g.:
./collision-detection