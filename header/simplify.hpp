#ifndef SIMPLIFY
#define SIMPLIFY

namespace nQCircuit
{
	class CQCircuit;

	bool ABA_B(CQCircuit &);
	bool diff_1_bit(CQCircuit &);
	bool simplify_all(CQCircuit &);
}

#endif