#ifndef QCOSTREAM
#define QCOSTREAM
#include<iosfwd>

namespace nQCircuit
{
	class CQGate;
	class CQCircuit;

	void print(std::ostream &,const nQCircuit::CQGate &);
	void print(std::ostream &,const nQCircuit::CQCircuit &);
	void print_t(std::ostream &,const nQCircuit::CQGate &);
	void print_t(std::ostream &,const nQCircuit::CQCircuit &);
}

#endif