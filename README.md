[![🇮🇹 Italiano](https://img.shields.io/badge/lang-%F0%9F%87%AE%F0%9F%87%B9%20Italiano-green)](README.it.md)
[![🇬🇧 English](https://img.shields.io/badge/lang-%F0%9F%87%AC%F0%9F%87%A7%20English-blue)](README.md)

---

# ParadisEO Compilation Guide
This guide provides detailed instructions on how to compile the Paradiseo 3.0.0 library with support for MPI, Gnuplot, and the MO (Metaheuristic Optimization) module.

## 1. Requirements
Make sure you have the following packages installed before proceeding with the compilation:

- **CMake**
- **GCC**
- **MPI** (OpenMPI) if you want to enable MPI support
- **Gnuplot** (if you want to enable graphical visualization support)
- **Git** (to clone the repository, if needed)

### Install required packages (Ubuntu/Debian)

```sh
sudo apt update
sudo apt install -y cmake make g++ libeigen3-dev libopenmpi-dev doxygen graphviz libgnuplot-iostream-dev git
```

## 2. Installing Paradiseo
If you don't already have the Paradiseo source code, download release 3.0.0 from [ParadisEO](https://github.com/nojhan/paradiseo/releases/tag/v3.0.0)
Place the paradiseo-3.0.0 folder inside the lib directory.

## 3. Troubleshooting MPI and MO
If you want to enable MPI support, download the [mpi](https://github.com/Alessandro624/paradiseo/tree/master/eo/src/mpi) folder and replace it inside the library at ./lib/paradiseo-3.0.0/eo/src

Download the file [eoInit.h](https://github.com/Alessandro624/paradiseo/blob/master/eo/src/eoInit.h) and replace it inside the library at ./lib/paradiseo-3.0.0/eo/src to compile the lessons in moTutorial

## 4. Basic Compilation
For a standard compilation without optional modules:
```sh
mkdir build && cd build
cmake ..
make -j
```

## 5. Compilation with MPI
If you want to enable MPI support, you need to enable the MPI option:
```sh
mkdir build-mpi && cd build-mpi
cmake .. -DMPI=ON
make -j
```

## 6. Compilation with Gnuplot Support
If you want to enable Gnuplot support, use the ENABLE_GNUPLOT flag:
```sh
mkdir build-gnuplot && cd build-gnuplot
cmake .. -DENABLE_GNUPLOT=ON
make -j
```

## 7. Cleaning Compilation Files
If you want to remove compilation files to start over:
```sh
rm -rf build*
```
