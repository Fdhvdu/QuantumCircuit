#include"../header/QCFwd.hpp"
#include<algorithm>	//count_if
#include<numeric>	//iota
#include<utility>	//move
#include"../../lib/header/algorithm/algorithm.hpp"
#include"../../lib/header/math/math.hpp"
#include"../../lib/header/tool/Boolean.hpp"
#include"../header/CQCircuit.hpp"
#include"../header/IQBit.hpp"
using namespace std;

namespace
{
	void operate(const nQCircuit::CQGate &gate,Func_t::value_type &input)
	{
		//input=3
		//bit=011
		//input=5
		//bit=101
		//input=6
		//bit=110
		vector<nTool::Boolean> bit(gate.gate_size());
		nMath::reverse_bit(input,bit.rbegin(),bit.rend());
		if(nAlgorithm::all_of_val<size_t>(0,gate.gate_size(),[&](const size_t subscript){return gate[subscript]->is_valid(gate,bit,subscript);}))
			nAlgorithm::for_each_val<size_t>(0,gate.gate_size(),[&](const auto i){
				bit[i]=gate[i]->operate(bit[i]);
			});
		input=bit[0];
		//make bit to number
		for_each(next(bit.begin()),bit.end(),[&](const auto &val){
			input<<=1;
			input|=static_cast<Func_t::value_type>(val);
		});
	}
}

ICircuitAlgorithm::~ICircuitAlgorithm(){}

size_t calc_func_num(const Func_t &func) noexcept
{
	//{0,1}=0
	//{1,0}=1
	//{0,1,2,3}=0
	//{0,1,3,2}=1
	//{3,2,1,0}=23
	//{0,1,2,3,4,5,6,7}=0
	//{0,1,2,3,4,5,7,6}=1
	//{7,6,5,4,3,2,1,0}=40319
	size_t num{0};
	nAlgorithm::for_each_val<size_t>(0,func.size(),[&](const auto i){
		num+=count_if(next(begin(func),i+1),end(func),[&,i](const auto val){return val<func[i];})*nMath::factorial(func.size()-i-1);
	});
	return num;
}

Func_t get_circuit_func(const nQCircuit::CQCircuit &circuit)
{
	Func_t temp(nMath::power_of_2(circuit.gate_size()));	//not {}
	iota(temp.begin(),temp.end(),0);
	return get_func_after_circuit(move(temp),circuit);
}

Func_t get_func_after_circuit(const Func_t &func,const nQCircuit::CQCircuit &circuit)
{
	auto temp{func};
	return get_func_after_circuit(move(temp),circuit);
}

Func_t get_func_after_circuit(Func_t &&rVal,const nQCircuit::CQCircuit &circuit)
{
	nAlgorithm::for_each_val<size_t>(0,circuit.size(),[&](const auto i){
		rVal=get_func_after_gate(move(rVal),circuit[i]);
	});
	return rVal;
}

Func_t get_func_after_gate(const Func_t &func,const nQCircuit::CQGate &gate)
{
	auto temp{func};
	return get_func_after_gate(move(temp),gate);
}

Func_t get_func_after_gate(Func_t &&rVal,const nQCircuit::CQGate &gate)
{
	for(auto &val:rVal)
		operate(gate,val);
	return rVal;
}

Func_t get_gate_func(const nQCircuit::CQGate &gate)
{
	Func_t temp(nMath::power_of_2(gate.gate_size()));	//not {}
	iota(temp.begin(),temp.end(),0);
	return get_func_after_gate(move(temp),gate);
}

Func_t reverse_func(const Func_t &func)
{
	Func_t temp{func};
	for(const auto val:func)
		temp[func[val]]=val;
	return temp;
}