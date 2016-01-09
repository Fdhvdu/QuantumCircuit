#include"../header/IQBit.h"
#include<ostream>
using namespace std;

namespace nQCircuit
{
	IQBit::~IQBit(){}

	ostream& operator<<(ostream &os,const IQBit &val)
	{
		return val.print(os);
	}

	ostream& Q_empty_bit::print(ostream &os) const
	{
		return os<<"¢q";
	}

	ostream& Q_not_bit::print(ostream &os) const
	{
		return os<<"¡ò";
	}

	ostream& Q_controlled_not_bit::print(ostream &os) const
	{
		return os<<"¡´";
	}

	ostream& Q_white_controlled_not_bit::print(ostream &os) const
	{
		return os<<"¡³";
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