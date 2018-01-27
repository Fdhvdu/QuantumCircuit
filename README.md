# Contents
[Algorithm](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#algorithm)<br>
[Compiler](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#compiler)<br>
[How to compile](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#how-to-compile)<br>
[About compilation errors](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#about-compilation-errors)<br>
[Tutorial](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#tutorial)
# Algorithm
# Compiler
VC++ 14.2<br>
or any compiler which supports C++14<br>
(you had better compile the source code in x64, because the memory usage is very high when the macro `USE_THREAD` is enable)
# How to compile
You have to download [my lib](https://github.com/Fdhvdu/lib) and [ThreadPool](https://github.com/Fdhvdu/ThreadPool)<br>
The directory should look like

	├── lib
	│   ├── header
	│   ├── LICENSE
	│   ├── README.md
	│   ├── src
	│   └── tutorial
	├── QuantumCircuit
	│   ├── header
	│   ├── LICENSE
	│   ├── README.md
	│   └── src
	└── ThreadPool
	    ├── comparison
	    ├── header
	    ├── LICENSE
	    ├── README.md
	    ├── src
	    └── tutorial
Don't forget to compile ThreadPool/src/* and lib/src/CScopeGuard.cpp.
# About compilation errors
Q: My compiler doesn't support C++14<br>
A: Get a newer compiler version, such as GCC 5.3.0 or VC++ 14.2 (inside Visual Studio Community 2015 Update 2)<br><br>
Q: Other problems<br>
A: See [How to compile](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#how-to-compile) or email me
# Tutorial
See [main.cpp](https://github.com/Fdhvdu/QuantumCircuit/blob/master/src/main.cpp), [QCFwd.cpp](https://github.com/Fdhvdu/QuantumCircuit/blob/master/header/QCFwd.hpp) and [CTsaiAlgorithm.cpp](https://github.com/Fdhvdu/QuantumCircuit/blob/master/header/CTsaiAlgorithm.hpp)<br>
g++ -std=c++14 src/* ../lib/src/CScopeGuard.cpp ../ThreadPool/src/*