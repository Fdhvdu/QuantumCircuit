#include"../header/path_algorithm.h"
#include<bitset>
#include"../../lib/header/algorithm/algorithm.h"
#include"../header/IQBit.h"
using namespace nQCircuit;
using namespace std;

namespace nTsaiAlgorithm
{
	CQGate createGate(const size_t size,const size_t lhs,const size_t rhs)
	{
		CQGate temp{size};
		bitset<sizeof(size_t)*8> gate{lhs^rhs},bitLhs{lhs};
		nAlgorithm::for_each<size_t>(0,size,[&,size](const auto i){
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