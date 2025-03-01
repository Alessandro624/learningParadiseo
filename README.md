# Guida alla compilazione di ParadisEO
Questa guida fornisce istruzioni dettagliate su come compilare la libreria Paradiseo 3.0.0 con supporto per MPI, Gnuplot e il modulo MO (Metaheuristic Optimization).

## 1. Requisiti
Assicurarsi di avere installati i seguenti pacchetti prima di procedere con la compilazione:

- **CMake**
- **GCC**
- **MPI** (OpenMPI) se si desidera abilitare il supporto MPI
- **Gnuplot** (se si vuole abilitare il supporto per la visualizzazione grafica)
- **Git** (per clonare il repository, se necessario)

### Installazione dei pacchetti richiesti (Ubuntu/Debian)

```sh
sudo apt update
sudo apt install -y cmake make g++ libeigen3-dev libopenmpi-dev doxygen graphviz libgnuplot-iostream-dev git
```

## 2. Installazione Paradiseo
Se non si dispone già del codice sorgente di Paradiseo, scaricare la release 3.0.0 su [ParadisEO](https://github.com/nojhan/paradiseo/releases/tag/v3.0.0)
Inserire la cartella paradiseo-3.0.0 nella cartella lib

## 3. Risoluzione problemi MPI e MO
Se si volesse abilitare il supporto MPI, scaricare la cartella [mpi](https://github.com/Alessandro624/paradiseo/tree/master/eo/src/mpi) e sostituirla all'interno della libreria in ./lib/paradiseo-3.0.0/eo/src

Scaricare il file [eoInit.h](https://github.com/Alessandro624/paradiseo/blob/master/eo/src/eoInit.h) e sostituirlo all'interno della libreria in ./lib/paradiseo-3.0.0/eo/src per la compilazione delle lezioni presenti in moTutorial

## 4. Compilazione base
Per una compilazione standard senza moduli opzionali:
```sh
mkdir build && cd build
cmake ..
make -j
```

## 5. Compilazione con MPI
Se si desidera attivare il supporto MPI, bisogna abilitare l'opzione MPI:
```sh
mkdir build-mpi && cd build-mpi
cmake .. -DMPI=ON
make -j
```

## 6. Compilazione con Supporto Gnuplot
Se si vuole abilitare il supporto per Gnuplot, usare il flag ENABLE_GNUPLOT:
```sh
mkdir build-gnuplot && cd build-gnuplot
cmake .. -DENABLE_GNUPLOT=ON
make -j
```

## 7. Pulizia dei file di compilazione
Se si desidera rimuovere i file di compilazione per ricompilare da zero:
```sh
rm -rf build*
```
