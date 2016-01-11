#include"../header/path_algorithm.h"
#include<bitset>
#include<stdexcept>	//logic_error
#include"../../lib/header/algorithm/algorithm.h"
#include"../header/IQBit.h"
using namespace nQCircuit;
using namespace std;

namespace nTsaiAlgorithm
{
	CQGate createGate(const size_t size,const size_t lhs,const size_t rhs)
	{
		CQGate temp{size};
		const bitset<sizeof(size_t)*8> gate{lhs^rhs},bitLhs{lhs};
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

	size_t route(const size_t bit)
	{
		switch(bit)
		{
		case 1:			return 1;	//1 bit has 1 routes to exchange
		case 2:			return 2;	//2 bit has 2 routes to exchange
		case 3:			return 6;	//3 bit has 6 routes to exchange
		case 4:			return 20;	//4 bit has 20 routes to exchange
		default:		throw logic_error{"Cannot find route"};
		}
	}
}