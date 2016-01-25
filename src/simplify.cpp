#include"../header/simplify.hpp"
#include"../../lib/header/algorithm/algorithm.hpp"
#include"../header/CQCircuit.hpp"
#include"../header/IQBit.hpp"
using namespace nQCircuit;
using namespace std;

namespace
{
	bool disjoint(const CQGate &lhs,const CQGate &rhs)
	{
		bool both{false};
		return nAlgorithm::find_if_val<size_t>(0,lhs.gate_size(),[&](const auto i){
			return lhs[i]->info()==QBit::NOT&&rhs[i]->info()==QBit::NOT
				||(lhs[i]->info()==QBit::CONTROLLED_NOT&&rhs[i]->info()==QBit::WHITE_CONTROLLED_NOT||lhs[i]->info()==QBit::WHITE_CONTROLLED_NOT&&rhs[i]->info()==QBit::CONTROLLED_NOT)
				||((lhs[i]->info()==QBit::NOT&&rhs[i]->info()==QBit::EMPTY||lhs[i]->info()==QBit::EMPTY&&rhs[i]->info()==QBit::NOT)&&!(both=!both));
		})!=lhs.gate_size();
	}

	inline size_t diff_pos(const CQGate &lhs,const CQGate &rhs)
	{
		return nAlgorithm::find_if_val<size_t>(0,lhs.gate_size(),[&](const size_t subscript){return *lhs[subscript]!=*rhs[subscript];});
	}

	inline bool is_1_diff(const CQGate &lhs,const CQGate &rhs)
	{
		return nAlgorithm::count_if_val<size_t>(0,lhs.gate_size(),[&](const size_t subscript){return *lhs[subscript]!=*rhs[subscript];})==1;
	}
}

namespace nQCircuit
{
	bool ABA_B(CQCircuit &val)
	{
		if(val.size())
			for(size_t i{0};i!=val.size()-1;++i)
				for(size_t j{i+1};j!=val.size();++j)
					if(val[i]==val[j])
					{
						if(nAlgorithm::all_of_val(i+1,j,[&,i](const size_t subscript){return disjoint(val[i],val[subscript]);}))
						{
							val.erase(j);
							val.erase(i);
							return true;
						}
						break;
					}
		return false;
	}

	bool diff_1_bit(CQCircuit &val)
	{
		if(val.size())
			for(size_t i{0};i!=val.size()-1;++i)
				for(size_t j{i+1};j!=val.size();++j)
					if(is_1_diff(val[i],val[j]))
					{
						const auto pos{diff_pos(val[i],val[j])};
						val[i][pos]=make_Q_empty_bit();
						val[j][pos]=make_Q_empty_bit();
						return true;
					}
		return false;
	}

	bool simplify_all(CQCircuit &val)
	{
		return ABA_B(val)||diff_1_bit(val);
	}
}