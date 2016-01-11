#ifndef PATH_ALGORITHM
#define PATH_ALGORITHM
#include<cstddef>

namespace nQCircuit
{
	class CQGate;
	class CQCircuit;
}

namespace nTsaiAlgorithm
{
	nQCircuit::CQGate createGate(size_t,size_t,size_t);

	template<class RanIter>
	nQCircuit::CQCircuit path_algorithm(RanIter,RanIter,size_t,size_t);	//when your bit is higher than 4, you have to modify this

	std::size_t route(std::size_t);	//when your bit is higher than 4, you have to modify this
}

#include"path_algorithm.cpp"

#endif