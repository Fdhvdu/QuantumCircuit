#include"../header/CTsaiAlgorithm.h"
#include<algorithm>	//min_element, rotate, sort, transform
#include<chrono>	//for random
#include<cstddef>	//size_t
#include<functional>	//equal_to, hash
#include<iterator>	//make_move_iterator
#include<random>	//mt19937, uniform_int_distribution
#include<stdexcept>	//logic_error
#include<utility>	//move, pair
#include<vector>
#include"../../lib/header/algorithm/algorithm.h"	//for_each, unique_without_sort
#include"../../lib/header/math/math.h"	//Cantor_pairing_function
#include"../../lib/header/thread/CThread_unordered_map.h"
#include"../../lib/header/tool/Boolean.h"
#include"../header/TsaiAlgorithmFwd.h"
#include"../header/CData.h"	//step4_algorithm
#include"../header/CPath.h"
#include"../header/path_algorithm.h"	//path_algorithm
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
	size_t next_permutation_count(const Cycle_t &);
	inline size_t next_permutation_count(const Split_with_index &split)
	{
		return nMath::factorial(split.size());
	}
	size_t route(size_t size);	//when your bit is higher than 4, you have to modify this
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
		nAlgorithm::for_each<size_t>(0,gate.size(),[&](const auto i){
			gate[i].first=i;	//for next_permutation in step3_permutate_cycle
		});
		nAlgorithm::for_each<size_t>(0,gate.size(),[&,bit](const auto i){
			find_path_impl(cycle[i],gate[i].second,bit);
		});
		return gate;
	}

	Split_with_index find_path_random(mt19937 &mt,const Cycle_t &cycle,const size_t bit)
	{
		Split_with_index gate(cycle.size());	//not {}
		nAlgorithm::for_each<size_t>(0,gate.size(),[&](const auto i){
			gate[i].first=i;	//for next_permutation in step3_permutate_cycle
		});
		nAlgorithm::for_each<size_t>(0,gate.size(),[&,bit](const auto i){
			find_path_impl_random(mt,cycle[i],gate[i].second,bit);
		});
		return gate;
	}

	void find_path_impl(const Cycle_t::value_type &cycle,vec_const_vec_CQCircuit_ptr &vec,const size_t bit)
	{
		static nThread::CThread_unordered_map<PoolKey_t,vec_CQCircuit> pool;
		for(size_t i{cycle.size()-1};i;--i)
		{
			const PoolKey_t key{cycle[i],cycle[i-1]};
			pool.try_emplace_func(key,[&,bit,i]{
				const CPath<Func_t::value_type> path{cycle[i],cycle[i-1]};
				const auto routeCount{route(path.diff_bit_count())};
				vec_CQCircuit temp{path.size()*routeCount,vec_CQCircuit::value_type{bit}};
				nAlgorithm::for_each<size_t>(0,path.size(),[&,bit,routeCount](const auto j){
					nAlgorithm::for_each<size_t>(0,routeCount,[&,bit,routeCount,j](const auto k){
						temp[j*routeCount+k]=path_algorithm(path[j].begin(),path[j].end(),bit,k);
					});
				});
				return temp;
			});
			vec.emplace_back(&pool.at(key));
		}
	}

	void find_path_impl_random(mt19937 &mt,const Cycle_t::value_type &cycle,vec_const_vec_CQCircuit_ptr &vec,const size_t bit)
	{
		for(size_t i{cycle.size()-1};i;--i)
		{
			const CPath<Func_t::value_type> path{cycle[i],cycle[i-1]};
			const auto choice{uniform_int_distribution<size_t>{0,path.size()*route(path.diff_bit_count())-1}(mt)};
			vec.emplace_back(new vec_CQCircuit{1,path_algorithm(path[choice/path.size()].begin(),path[choice/path.size()].end(),bit,choice%path.size())});
		}
	}

	Split_t make_split(Split_with_index &vec)
	{
		Split_t split;
		split.reserve(vec.size());
		transform(make_move_iterator(vec.begin()),make_move_iterator(vec.end()),back_inserter(split),[](pair<size_t,vec_const_vec_CQCircuit_ptr> &&val){return val.second;});
		return split;
	}

	void make_split_with_index(Split_with_index &vec,Split_t &split)
	{
		nAlgorithm::for_each<size_t>(0,vec.size(),[&](const auto i){
			vec[i].second=move(split[i]);
		});
	}

	bool next_permutation(Cycle_t &cycle)
	{
		for(auto &val:cycle)
			if(2<val.size())
			{
				rotate(val.begin(),next(val.begin()),val.end());
				if(min_element(val.begin(),val.end())!=val.begin())
					return true;
			}
		return false;
	}

	size_t next_permutation_count(const Cycle_t &cycle)
	{
		size_t count{1};
		for(auto &val:cycle)
			if(2<val.size())
				count*=val.size();
		return count;
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

	Cycle_t step1_create_cycle(const Func_t &func)
	{
		Cycle_t cycle;
		vector<nTool::Boolean> ready(func.size());	//not {}
		nAlgorithm::for_each<size_t>(0,ready.size(),[&](const auto i){
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
		}while(next_permutation(split_with_index.begin(),split_with_index.end(),[](const pair<size_t,vec_const_vec_CQCircuit_ptr> &lhs,const pair<size_t,vec_const_vec_CQCircuit_ptr> &rhs){return lhs.first<rhs.first;}));
		erase_equal(result);
		sort_by_size(result);
		if(result.size())
			erase_size_bigger_than_smallest_size_plus_1(result);
		return result;
	}

	vec_CQCircuit step3_permutate_cycle_random(mt19937 &mt,Split_with_index &split_with_index)
	{
		for(auto choice{uniform_int_distribution<size_t>{0,next_permutation_count(split_with_index)-1}(mt)};choice--;)
			next_permutation(split_with_index.begin(),split_with_index.end(),[](const pair<size_t,vec_const_vec_CQCircuit_ptr> &lhs,const pair<size_t,vec_const_vec_CQCircuit_ptr> &rhs){return lhs.first<rhs.first;});
		return step4_algorithm(make_split(split_with_index));
	}
}

namespace nTsaiAlgorithm
{
	void sort_by_size(vec_CQCircuit &val)
	{
		sort(val.begin(),val.end(),[](const CQCircuit &lhs,const CQCircuit &rhs){return lhs.size()<rhs.size();});
	}
	
	void erase_equal(vec_CQCircuit &val)
	{
		val.erase(nAlgorithm::unique_without_sort(val.begin(),val.end()),val.end());
	}

	void erase_size_bigger_than_smallest_size_plus_1(vec_CQCircuit &val)
	{
		const auto size{val.front().size()+1};
		val.erase(find_if(val.begin(),val.end(),[=](const CQCircuit &circuit){return size<circuit.size();}),val.end());
	}
	
	void move_insert(vec_CQCircuit &result,vec_CQCircuit &&rVal)
	{
		result.insert(result.end(),make_move_iterator(rVal.begin()),make_move_iterator(rVal.end()));
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