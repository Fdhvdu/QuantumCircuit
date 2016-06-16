#include"../header/QCOstream.hpp"
#include<ostream>
#include<memory>
#include"../header/CQCircuit.hpp"
#include"../header/IQBit.hpp"
using namespace std;

namespace
{
	inline void print_space(ostream &os)
	{
		os<<"\u3000";
	}

	inline void print_column(ostream &os)
	{
		os<<"\u2502";
	}

	void print_IQBit_or_space(ostream &os,const unique_ptr<const nQCircuit::IQBit> &qbit)
	{
		if(qbit)
			os<<*qbit;
		else
			print_space(os);
	}

	inline void print_row(ostream &os)
	{
		os<<"\u2500";
	}
}

namespace nQCircuit
{
	void print(ostream &os,const CQGate &gate)
	{
		print_IQBit_or_space(os,gate[0]);
		for(size_t i{1};i!=gate.gate_size();++i)
		{
			print_row(os);
			print_IQBit_or_space(os,gate[i]);
		}
		os<<endl;
	}

	void print(ostream &os,const CQCircuit &circuit)
	{
		if(circuit.size())
		{
			print(os,circuit[0]);
			for(size_t i{1};i!=circuit.size();++i)
			{
				print_column(os);
				for(size_t j{1};j!=circuit.gate_size();++j)
				{
					print_space(os);
					print_column(os);
				}
				os<<endl;
				print(os,circuit[i]);
			}
		}
	}

	void print_t(ostream &os,const CQGate &gate)
	{
		print_IQBit_or_space(os,gate[0]);
		for(size_t i{1};i!=gate.gate_size();++i)
		{
			os<<endl;
			print_column(os);
			os<<endl;
			print_IQBit_or_space(os,gate[i]);
		}
		os<<endl;
	}

	void print_t(ostream &os,const CQCircuit &circuit)
	{
		auto print_circuit_row{[&](ostream &os,const size_t i){
			print_IQBit_or_space(os,circuit[0][i]);
			for(size_t j{1};j!=circuit.size();++j)
			{
				print_row(os);
				print_IQBit_or_space(os,circuit[j][i]);
			}
			os<<endl;
		}};
		if(circuit.size())
		{
			print_circuit_row(os,0);
			for(size_t i{1};i!=circuit.gate_size();++i)
			{
				print_column(os);
				for(size_t j{1};j!=circuit.size();++j)
				{
					print_space(os);
					print_column(os);
				}
				os<<endl;
				print_circuit_row(os,i);
			}
		}
	}
}