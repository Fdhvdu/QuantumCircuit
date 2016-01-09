#include"../header/CData.h"
#include<algorithm>	//for_each, max
#include<condition_variable>
#include<iterator>	//back_inserter, distance, make_move_iterator, move_iterator, prev
#include<memory>	//make_shared, shared_ptr
#include<mutex>
#include<numeric>	//accumulate
#include<string>
#include<utility>	//move
#include<vector>
#include"../../lib/header/algorithm/algorithm.h"
#include"../../lib/header/math/math.h"
#include"../../lib/header/thread/CThread_unordered_map.h"
#include"../header/CQCircuit.h"
#include"../header/IQBit.h"
#include"../header/simplify.h"
using namespace nQCircuit;
using namespace nTsaiAlgorithm;
using namespace std;

namespace
{
	class CData
	{
	public:
		typedef string key_t;	//when your bit is higher than 7, you have to use another type
	private:
		typedef string hash_t;	//when your bit is higher than 7, you have to use another type
		nThread::CThread_unordered_map<hash_t,bool> complete_;
		condition_variable cv_;
		vec_CQCircuit data_;
		const key_t key_;
		mutex mut_;
		static vec_CQCircuit combine_(const CData &lhs,const CData &rhs)
		{
			return combine_Des_t_vec_(lhs.read(),rhs.read());
		}
		static vec_CQCircuit combine_Des_t_vec_(const vec_CQCircuit &,const vec_CQCircuit &);
		static hash_t get_hash_(const key_t &lhs,const key_t &rhs)	//must not as same as combine_key
		{
			return lhs+' '+rhs;
		}
	public:
		explicit CData(const vec_CQCircuit &);
		CData(const key_t &,const CData &,const CData &);
		void insert(const CData &,const CData &);
		inline const key_t& key() const noexcept
		{
			return key_;
		}
		const vec_CQCircuit& read() const noexcept
		{
			return data_;
		}
	};

	typedef shared_ptr<CData> Data_t;

	void combine(const Data_t &,const Data_t &,size_t,Data_t &);
	inline CData::key_t combine_key(const CData::key_t &lhs,const CData::key_t &rhs)	//must not as same as CData::get_hash_
	{
		return lhs+rhs;
	}
	CData::key_t get_key(const CQCircuit &);
	inline size_t get_split_size(const Split_t &vec)
	{
		return accumulate(vec.begin(),vec.end(),static_cast<size_t>(0),[](const size_t init,const pair<size_t,vec_const_vec_CQCircuit_ptr> &val){return init+val.second.size();});
	}
	vec_CQCircuit step5_dynamic(const Split_t &);
	const vec_CQCircuit& step5_get_split_elem(const Split_t &,size_t);

	vec_CQCircuit CData::combine_Des_t_vec_(const vec_CQCircuit &lhs,const vec_CQCircuit &rhs)
	{
		vec_CQCircuit temp;
		temp.reserve(max<size_t>(1,lhs.size())*max<size_t>(1,rhs.size()));
		nAlgorithm::multiply(lhs.begin(),lhs.end(),rhs.begin(),rhs.end(),back_inserter(temp),[](const CQCircuit &lhs,const CQCircuit &rhs){
			auto temp{lhs};
			temp.attach(rhs);
			while(nQCircuit::ABA_B(temp))
				;
			return temp;
		});
		erase_equal(temp);
		sort_by_size(temp);
		if(temp.size())
			erase_size_bigger_than_smallest_size_plus_1(temp);
		return temp;
	}

	CData::CData(const vec_CQCircuit &vec)
		:data_{vec},key_{get_key(vec.front())}{}

	CData::CData(const key_t &key,const CData &lhs,const CData &rhs)
		:data_{combine_(lhs,rhs)},key_{key}
	{
		complete_.emplace(get_hash_(lhs.key(),rhs.key()),true);
	}

	void CData::insert(const CData &lhs,const CData &rhs)
	{
		unique_lock<mutex> lock{mut_,defer_lock};
		const auto key{get_hash_(lhs.key(),rhs.key())};
		if(complete_.try_emplace_func(key,[&]{lock.lock();return false;}))
		{
			move_insert(data_,combine_(lhs,rhs));
			erase_equal(data_);
			sort_by_size(data_);
			if(data_.size())
				erase_size_bigger_than_smallest_size_plus_1(data_);
			complete_.at(key)=true;
			cv_.notify_all();
		}
		else
			if(!complete_.at(key))
			{
				lock.lock();
				cv_.wait(lock,[&]{return complete_.at(key);});
			}
	}
	
	void combine(const Data_t &lhs,const Data_t &rhs,const size_t level,Data_t &des)
	{
		static nThread::CThread_unordered_map<size_t,nThread::CThread_unordered_map<CData::key_t,Data_t>> pool;
		const auto key{combine_key(lhs->key(),rhs->key())};	//it means combination, not func
															//use func as key is cheating
		if(!pool[level].try_emplace_func(key,[&]{return make_shared<Data_t::element_type>(key,*lhs,*rhs);}))
			pool.at(level).at(key)->insert(*lhs,*rhs);
		if(!des)
			des=pool.at(level).at(key);
	}

	CData::key_t get_key(const CQCircuit &circuit)
	{
		Func_t temp{get_circuit_func(circuit)};
		return {make_move_iterator(temp.begin()),make_move_iterator(temp.end())};
	}

	vec_CQCircuit step5_dynamic(const Split_t &path)
	{
		const auto pathSize{get_split_size(path)};
		vector<vector<Data_t>> vec(pathSize);
		nAlgorithm::for_each<size_t>(0,vec.size(),[&,pathSize](const auto i){
			vec[i].resize(pathSize-i);
		});
		nAlgorithm::for_each<size_t>(0,vec.front().size(),[&](const auto i){
			vec.front()[i]=make_shared<Data_t::element_type>(step5_get_split_elem(path,i));
		});
		nAlgorithm::for_each<size_t>(1,vec.size(),[&](const auto i){
			nAlgorithm::for_each<size_t>(0,vec[i].size(),[&,i](const auto j){
				nAlgorithm::for_each<size_t>(0,i,[&,i,j](const auto k){
					combine(vec[k][j],vec[i-k-1][j+k+1],i,vec[i][j]);
				});
			});
		});
		return vec.back().front()->read();
	}

	const vec_CQCircuit& step5_get_split_elem(const Split_t &vec,const size_t subscript)
	{
		size_t i{0},j{0};
		for(;vec[i].second.size()+j<=subscript;j+=vec[i].second.size(),++i)
			;
		return *vec[i].second[subscript-j];
	}
}

namespace nTsaiAlgorithm
{
	vec_CQCircuit step4_algorithm(const Split_t &path)
	{
		if(1==get_split_size(path))
			return step5_get_split_elem(path,0);
		return step5_dynamic(path);
	}
}