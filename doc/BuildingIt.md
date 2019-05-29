# Istruzioni di build complete

Prima di tutto ti serve [cmake](https://cmake.org) (assicurati di inserirlo nel
`PATH` dall'installer), poi ti serve un compilatore per la tua piattaforma.

Dopo aver ottenuto il software necessario, basta dare i seguenti comandi da shell:

```
mkdir build
cd build
cmake ..
cmake --build .
```

Questo funziona in maniera _generale_, per i comandi specifici per sistema basta
continuare a leggere.

## Per Windows

Puoi usare [MSVC da Visual Studio](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=BuildTools&rel=16),
[MinGW](http://www.mingw.org/) o [MinGW di STL](https://nuwen.net/mingw.html).
Se non vuoi usare nessuno di questi, rimane [WSL](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux)
usando poi le istruzioni di per Linux.

### Per Visual Studio (Build Tools for VS o l'intero IDE)

Assicurati di installare Windows SDK, Microsoft Visual C++ Compiler (le edizioni
2017 e 2019 funzionano bene) e MSBuild da Visual Studio Installer.

Poi, invoca `cmake ..` nella cartella `build`; trovera' automaticamente MSVC e
generera' una soluzione per  Visual Studio.
Se non ti interessa modificare il progetto in Visual Studio, invoca
`cmake --build .` nella cartella `build` per compilare il progetto.


### Per qualsiasi MinGW

Invoca `cmake -G "MinGW Makefiles" ..` nella cartella `build` e compila il
programma con `mingw-make` (o con `cmake --build .`).

## Per Linux

Ti serve un compilatore come GCC or Clang. La tua distro probabilmente avra'
preinstallati GCC e glibc.

Invoca `cmake ..` nella cartella `build`, poi usa `make` o `cmake --build .`.

## Per OSX

Ti serve un compilatore come GCC (da brew), upstream Clang (da brew) o
AppleClang (installato con XCode).

### Con `make` e GCC/Clang/AppleClang

Invoca `cmake .. -G "Makefile"` nella cartella `build`, poi usa `make` o
`cmake --build .`.

### Con un progetto di XCode

Invoca `cmake .. -G "XCode Project"` nella cartella `build`, poi compila da
XCode o usa `cmake --build .`.
