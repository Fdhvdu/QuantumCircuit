#ifndef SYNTHESIS
#define SYNTHESIS
#include"QCFwd.hpp"

namespace nQCircuit
{
	class CQGate;

	CQGate create_QGate(std::size_t,Func_t::value_type,Func_t::value_type);
}

#endif