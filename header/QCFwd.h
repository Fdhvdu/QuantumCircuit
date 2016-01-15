#ifndef QCFWD
#define QCFWD
#include<cstddef>
#include<vector>

namespace nQCircuit
{
	class CQGate;
	class CQCircuit;
}

typedef std::vector<unsigned> Func_t;
typedef std::vector<nQCircuit::CQCircuit> vec_CQCircuit;

class ICircuitAlgorithm
{
	Func_t func_;
public:
	virtual void create()=0;
	virtual const vec_CQCircuit& get() const noexcept=0;
	inline void setFunc(const Func_t &func)
	{
		func_=func;
	}
	inline const Func_t& getFunc() const noexcept
	{
		return func_;
	}
	virtual ~ICircuitAlgorithm();
};

std::size_t calc_func_num(const Func_t &);
Func_t get_circuit_func(const nQCircuit::CQCircuit &);
Func_t get_func_after_circuit(const Func_t &,const nQCircuit::CQCircuit &);
Func_t get_func_after_circuit(Func_t &&,const nQCircuit::CQCircuit &);
Func_t get_func_after_gate(const Func_t &,const nQCircuit::CQGate &);
Func_t get_func_after_gate(Func_t &&,const nQCircuit::CQGate &);
Func_t get_gate_func(const nQCircuit::CQGate &);

#endif