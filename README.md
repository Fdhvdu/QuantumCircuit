# Contents
[Algorithm](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#algorithm)<br>
[Compiler](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#compiler)<br>
[How to compile](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#how-to-compile)<br>
[About compilation errors](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#about-compilation-errors)<br>
[Tutorial](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#tutorial)
# Algorithm
# Compiler
	g++ 7.2.1
	clang++ 5.0.1
(When you are using Visual Studio, you had better compile the source code in x64, because the memory usage is very high when the macro `USE_THREAD` is enable)
# How to compile
You have to download [my lib](https://github.com/Fdhvdu/lib) and [ThreadPool](https://github.com/Fdhvdu/ThreadPool)<br>.
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
Don't forget to compile `lib/src/CScopeGuard.cpp` and `ThreadPool/src/*`.
# Compilation errors?
See [How to compile](https://github.com/Fdhvdu/QuantumCircuit/blob/master/README.md#how-to-compile) or email me
# Tutorial
See [main.cpp](https://github.com/Fdhvdu/QuantumCircuit/blob/master/src/main.cpp), [QCFwd.cpp](https://github.com/Fdhvdu/QuantumCircuit/blob/master/header/QCFwd.hpp) and [CTsaiAlgorithm.cpp](https://github.com/Fdhvdu/QuantumCircuit/blob/master/header/CTsaiAlgorithm.hpp)<br>
if `USE_THREAD` is enable

	g++ -std=c++14 ../lib/src/CScopeGuard.cpp src/* ../ThreadPool/src/*
otherwise

	g++ -std=c++14 src/*