# matrix-simple

Schönherz Mátrix super module

## Prerequisites
**FMOD** matrixsource dependency, check matrixsource\fmod\README.txt for details

Qt **5.12**(LTS) or above is recommended

**C++ 17** compatible compiler

Build tools for Qt(platform dependent):

- **MSVC**(Desktop development with C++)/MinGW on **Windows**
- **build-essential** on **Unix/Linux**

## How to manage submodules

Use the example bellow to add more submodules

```bash
git submodule add -b master [URL to Git repo]
```

Use the command bellow to update all submodules

```bash
git submodule update --remote
```

## How to build

Use Qt Creator **without shadow build**

Using command line simply run

```bash
qmake
make
```