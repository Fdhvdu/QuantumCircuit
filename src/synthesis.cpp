#include"../header/synthesis.h"
#include<bitset>
#include"../../lib/header/algorithm/algorithm.h"
#include"../header/CQCircuit.h"
#include"../header/IQBit.h"
using namespace nQCircuit;
using namespace std;

namespace nQCircuit
{
	CQGate create_QGate(const size_t size,const Func_t::value_type lhs,const Func_t::value_type rhs)
	{
		CQGate temp{size};
		const bitset<sizeof(Func_t::value_type)*8> gate{lhs^rhs},bitLhs{lhs};
		nAlgorithm::for_each_val<size_t>(0,size,[&,size](const auto i){
			if(gate[size-i-1])
				temp[i]=make_Q_not_bit();
			else
				if(bitLhs[size-i-1])
					temp[i]=make_Q_controlled_not_bit();
				else
					temp[i]=make_Q_white_controlled_not_bit();
		});
		return temp;
	}
}