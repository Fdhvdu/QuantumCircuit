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
	//1. call algorithm
	//2. create circuit"s" of the func_
	virtual void create()=0;
	//1. get the circuit"s"
	//2. every nQCircuit::CQCircuit is an unique circuit
	//3. to show the content of nQCircuit::CQCircuit, see nQCircuit::print or nQCircuit::print_t 
	virtual const vec_CQCircuit& get() const noexcept=0;
	//1.
	//the func.size() must be 2^(the X-bit circuit you want to create)
	//for example, if you are going to create a 3-bit circuit, the func.size() must be 8
	//for example, if you are going to create a 4-bit circuit, the func.size() must be 16
	//2. the value inside the func must be unique
	//3. the range of value inside the func must be [0,func.size())
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

std::size_t calc_func_num(const Func_t &) noexcept;
Func_t get_circuit_func(const nQCircuit::CQCircuit &);
Func_t get_func_after_circuit(Func_t,const nQCircuit::CQCircuit &);
Func_t get_func_after_gate(Func_t,const nQCircuit::CQGate &);
Func_t get_gate_func(const nQCircuit::CQGate &);
Func_t reverse_func(const Func_t &);

#endif
