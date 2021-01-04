# matrix-simple

Schönherz Mátrix super module

## Prerequisites
**FMOD** matrixsource dependency, check matrixsource\fmod\README.txt for details

Qt **5.12**(LTS) or above is recommended

**C++ 17** compatible compiler

Build tools for Qt(platform dependent):

- **MSVC**(Desktop development with C++)/MinGW on **Windows**
- **build-essential** on **Unix/Linux**

## How to build

Using Qt creator open CMakeLists.txt in the project root folder then build matrix-simple project

Using command line in the project root folder

```bash
cmake -DCMAKE_BUILD_TYPE=Release -B build && cmake --build build
```

## How to manage submodules

Use the example bellow to add more submodules

```bash
git submodule add -b master [URL to Git repo]
```

Use the command bellow to update all submodules

```bash
git submodule update --remote
```