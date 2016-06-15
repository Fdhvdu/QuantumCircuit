#include"../header/IQBit.hpp"
#include<ostream>
using namespace std;

namespace nQCircuit
{
	IQBit::~IQBit()=default;

	ostream& operator<<(ostream &os,const IQBit &val)
	{
		return val.print(os);
	}

	ostream& Q_empty_bit::print(ostream &os) const
	{
		return os<<"\u253c";
	}

	ostream& Q_not_bit::print(ostream &os) const
	{
		return os<<"\u2295";
	}

	ostream& Q_controlled_not_bit::print(ostream &os) const
	{
		return os<<"\u25cf";
	}

	ostream& Q_white_controlled_not_bit::print(ostream &os) const
	{
		return os<<"\u25cb";
	}

	//this is an example to help you understand how to use IQBit correctly
	//bool Q_or_bit::is_valid(const CQGate &gate,const std::vector<Boolean> &bit,size_t subscript) const
	//{
	//	for(size_t i{0};i!=gate.gate_size();++i)
	//		if(gate[i]->info()==QBIT::OR&&bit[i])
	//			return true;
	//	return false;
	//}
}