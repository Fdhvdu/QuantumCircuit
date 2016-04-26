#include"../header/CTsaiAlgorithm.hpp"
#include<algorithm>	//min_element, rotate, sort, transform
#include<chrono>	//for random
#include<cstddef>	//size_t
#include<functional>	//equal_to, hash
#include<numeric>	//accumulate
#include<iterator>	//back_inserter, begin, end, make_move_iterator
#include<random>	//mt19937, uniform_int_distribution
#include<utility>	//move, pair
#include<vector>
#include"../../lib/header/algorithm/algorithm.hpp"	//for_each_val, unique_without_sort
#include"../../lib/header/algorithm/exchange_endpoint_by_swapping.hpp"
#include"../../lib/header/math/math.hpp"	//Cantor_pairing_function, factorial, log_2
#include"../../lib/header/thread/CLock_unordered_map.hpp"
#include"../../lib/header/tool/Boolean.hpp"
#include"../../lib/header/tool/CInsert_iterator.hpp"
#include"../header/TsaiAlgorithmFwd.hpp"
#include"../header/CData.hpp"	//step4_algorithm
#include"../header/CQCircuit.hpp"
#include"../header/path.hpp"
#include"../header/synthesis.hpp"
using namespace nQCircuit;
using namespace nTsaiAlgorithm;
using namespace std;

namespace
{
	typedef vector<vector<Func_t::value_type>> Cycle_t;
	typedef pair<Func_t::value_type,Func_t::value_type> PoolKey_t;
	typedef vector<pair<size_t,vec_const_vec_CQCircuit_ptr>> Split_with_index;
	//index is for next_permutation in step3_permutate_cycle and step3_permutate_cycle_random

	Split_with_index find_path(const Cycle_t &,size_t);
	Split_with_index find_path_random(mt19937 &,const Cycle_t &,size_t);
	void find_path_impl(const Cycle_t::value_type &,vec_const_vec_CQCircuit_ptr &,size_t);
	void find_path_impl_random(mt19937 &,const Cycle_t::value_type &,vec_const_vec_CQCircuit_ptr &,size_t);
	Split_t make_split(Split_with_index &);
	void make_split_with_index(Split_with_index &,Split_t &);
	bool next_permutation(Cycle_t &);
	inline size_t next_permutation_count(const Cycle_t &cycle)
	{
		return accumulate(begin(cycle),end(cycle),static_cast<size_t>(1),[](const auto init,const vector<Func_t::value_type> &vec){
			if(2<vec.size())
				return init*vec.size();
			return init;
		});
	}
	inline size_t next_permutation_count(const Split_with_index &split)
	{
		return nMath::factorial(split.size());
	}
	Cycle_t step1_create_cycle(const Func_t &);
	vec_CQCircuit step2_rotate_cycle(Cycle_t &,size_t);
	vec_CQCircuit step2_rotate_cycle_random(mt19937 &,Cycle_t &,size_t);
	vec_CQCircuit step3_permutate_cycle(Split_with_index &);
	vec_CQCircuit step3_permutate_cycle_random(mt19937 &,Split_with_index &);
}

namespace std
{
	template<>
	struct equal_to<PoolKey_t>
	{
		inline bool operator()(const PoolKey_t &lhs,const PoolKey_t &rhs) const
		{
			return (lhs.first==rhs.first&&lhs.second==rhs.second)
				||(lhs.first==rhs.second&&lhs.second==rhs.first);
		}
	};

	template<>
	struct hash<PoolKey_t>
	{
		inline size_t operator()(const PoolKey_t &val) const
		{
			return val.first<val.second?
				nMath::Cantor_pairing_function(val.first,val.second):
				nMath::Cantor_pairing_function(val.second,val.first);
		}
	};
}

namespace
{
	Split_with_index find_path(const Cycle_t &cycle,const size_t bit)
	{
		Split_with_index gate(cycle.size());	//not {}
		nAlgorithm::for_each_val<size_t>(0,gate.size(),[&](const auto i){
			gate[i].first=i;	//for next_permutation in step3_permutate_cycle
		});
		nAlgorithm::for_each_val<size_t>(0,gate.size(),[&,bit](const auto i){
			find_path_impl(cycle[i],gate[i].second,bit);
		});
		return gate;
	}

	Split_with_index find_path_random(mt19937 &mt,const Cycle_t &cycle,const size_t bit)
	{
		Split_with_index gate(cycle.size());	//not {}
		nAlgorithm::for_each_val<size_t>(0,gate.size(),[&](const auto i){
			gate[i].first=i;	//for next_permutation in step3_permutate_cycle
		});
		nAlgorithm::for_each_val<size_t>(0,gate.size(),[&,bit](const auto i){
			find_path_impl_random(mt,cycle[i],gate[i].second,bit);
		});
		return gate;
	}

	void find_path_impl(const Cycle_t::value_type &cycle,vec_const_vec_CQCircuit_ptr &vec,const size_t bit)
	{
		static nThread::CLock_unordered_map<PoolKey_t,vec_CQCircuit> pool;
		for(size_t i{cycle.size()-1};i;--i)
		{
			const PoolKey_t key{cycle[i],cycle[i-1]};
			pool.try_emplace_gen(key,[&,bit,i]{
				const vector<vector<Cycle_t::value_type::value_type>> path{nHypercube::create_path(cycle[i],cycle[i-1])};
				vec_CQCircuit temp;
				for(const vector<Cycle_t::value_type::value_type> &val:path)
					for(vector<CQGate> &val2:nAlgorithm::exchange_endpoint_by_swapping(begin(val),end(val),[bit](const auto lhs,const auto rhs){return nQCircuit::create_QGate(bit,lhs,rhs);}))
						//notice, vector<CQGate> &&val2 is not valid here
					{
						temp.emplace_back(bit);
						temp.back().reserve(val2.size());
						move(begin(val2),end(val2),make_CQGate_inserter(temp.back()));
					}
				return temp;
			});
			vec.emplace_back(&pool.at(key));
		}
	}

	void find_path_impl_random(mt19937 &mt,const Cycle_t::value_type &cycle,vec_const_vec_CQCircuit_ptr &vec,const size_t bit)
	{
		uniform_int_distribution<size_t> dist;
		for(size_t i{cycle.size()-1};i;--i)
		{
			const vector<vector<Cycle_t::value_type::value_type>> path{nHypercube::create_path(cycle[i],cycle[i-1])};
			dist.param(uniform_int_distribution<size_t>::param_type(0,path.size()-1));
			const auto choice_path{dist(mt)};
			vector<vector<CQGate>> route{nAlgorithm::exchange_endpoint_by_swapping(begin(path[choice_path]),end(path[choice_path]),[bit](const auto lhs,const auto rhs){return nQCircuit::create_QGate(bit,lhs,rhs);})};
			dist.param(uniform_int_distribution<size_t>::param_type(0,route.size()-1));
			const auto choice_route{dist(mt)};
			vec_CQCircuit *p{new vec_CQCircuit{1,CQCircuit{bit}}};
			move(begin(route[choice_route]),end(route[choice_route]),make_CQGate_inserter(p->back()));
			vec.emplace_back(p);
		}
	}

	Split_t make_split(Split_with_index &vec)
	{
		Split_t split;
		split.reserve(vec.size());
		transform(make_move_iterator(begin(vec)),make_move_iterator(end(vec)),back_inserter(split),[](pair<size_t,vec_const_vec_CQCircuit_ptr> &&val){return val.second;});
		return split;
	}

	void make_split_with_index(Split_with_index &vec,Split_t &split)
	{
		nAlgorithm::for_each_val<size_t>(0,vec.size(),[&](const auto i){
			vec[i].second=move(split[i]);
		});
	}

	bool next_permutation(Cycle_t &cycle)
	{
		for(auto &val:cycle)
			if(2<val.size())
			{
				rotate(begin(val),next(begin(val)),end(val));
				if(min_element(begin(val),end(val))!=begin(val))
					return true;
			}
		return false;
	}

	Cycle_t step1_create_cycle(const Func_t &func)
	{
		Cycle_t cycle;
		vector<nTool::Boolean> ready(func.size());	//not {}
		nAlgorithm::for_each_val<size_t>(0,ready.size(),[&](const auto i){
			if(i!=func[i]&&!ready[i])	//i!=func[i], implicit conversion
			{
				cycle.emplace_back();	//push a empty object
				for(auto j{i};!ready[j];ready[j]=true,j=func[j])
					cycle.back().emplace_back(static_cast<Cycle_t::value_type::value_type>(j));
			}
		});
		return cycle;
	}
	
	vec_CQCircuit step2_rotate_cycle(Cycle_t &cycle,const size_t bit)
	{
		vec_CQCircuit result;
		do
		{
			auto temp{find_path(cycle,bit)};
			move_insert(result,step3_permutate_cycle(temp));
		}while(next_permutation(cycle));
		erase_equal(result);
		sort_by_size(result);
		if(result.size())
			erase_size_bigger_than_smallest_size_plus_1(result);
		return result;
	}

	vec_CQCircuit step2_rotate_cycle_random(mt19937 &mt,Cycle_t &cycle,const size_t bit)
	{
		for(auto choice{uniform_int_distribution<size_t>{0,next_permutation_count(cycle)-1}(mt)};choice--;)
			next_permutation(cycle);
		Split_with_index split{find_path_random(mt,cycle,bit)};
		const auto temp{step3_permutate_cycle(split)};
		for(const pair<size_t,vec_const_vec_CQCircuit_ptr> &val:split)
			for(const vec_CQCircuit *val2:val.second)
				delete val2;
		return temp;
	}

	vec_CQCircuit step3_permutate_cycle(Split_with_index &split_with_index)
	{
		vec_CQCircuit result;
		do
		{
			auto split{make_split(split_with_index)};
			move_insert(result,step4_algorithm(split));
			make_split_with_index(split_with_index,split);
		}while(next_permutation(begin(split_with_index),end(split_with_index),[](const pair<size_t,vec_const_vec_CQCircuit_ptr> &lhs,const pair<size_t,vec_const_vec_CQCircuit_ptr> &rhs){return lhs.first<rhs.first;}));
		erase_equal(result);
		sort_by_size(result);
		if(result.size())
			erase_size_bigger_than_smallest_size_plus_1(result);
		return result;
	}

	vec_CQCircuit step3_permutate_cycle_random(mt19937 &mt,Split_with_index &split_with_index)
	{
		for(auto choice{uniform_int_distribution<size_t>{0,next_permutation_count(split_with_index)-1}(mt)};choice--;)
			next_permutation(begin(split_with_index),end(split_with_index),[](const pair<size_t,vec_const_vec_CQCircuit_ptr> &lhs,const pair<size_t,vec_const_vec_CQCircuit_ptr> &rhs){return lhs.first<rhs.first;});
		return step4_algorithm(make_split(split_with_index));
	}
}

namespace nTsaiAlgorithm
{
	void sort_by_size(vec_CQCircuit &val)
	{
		sort(begin(val),end(val),[](const CQCircuit &lhs,const CQCircuit &rhs){return lhs.size()<rhs.size();});
	}
	
	void erase_equal(vec_CQCircuit &val)
	{
		val.erase(nAlgorithm::unique_without_sort(begin(val),end(val)),end(val));
	}

	void erase_size_bigger_than_smallest_size_plus_1(vec_CQCircuit &val)
	{
		const auto size{val.front().size()+1};
		val.erase(find_if(begin(val),end(val),[=](const CQCircuit &circuit){return size<circuit.size();}),end(val));
	}
	
	void move_insert(vec_CQCircuit &result,vec_CQCircuit &&rVal)
	{
		result.insert(end(result),make_move_iterator(begin(rVal)),make_move_iterator(end(rVal)));
	}

	void CTsaiAlgorithm::create()
	{
		Cycle_t cycle{step1_create_cycle(getFunc())};
		if(cycle.size())
			result_=step2_rotate_cycle(cycle,nMath::log_2(getFunc().size()));	//find_path_impl will use the second argument
	}

	void CRandom_TsaiAlgorithm::create()
	{
		Cycle_t cycle{step1_create_cycle(getFunc())};
		mt19937 mt{static_cast<mt19937::result_type>(chrono::high_resolution_clock::now().time_since_epoch().count())};
		if(cycle.size())
		{
			result_=step2_rotate_cycle_random(mt,cycle,nMath::log_2(getFunc().size()));	//find_path_impl will use the second argument
			erase_equal(result_);
			sort_by_size(result_);
			if(result_.size())
				erase_size_bigger_than_smallest_size_plus_1(result_);
		}
	}
}