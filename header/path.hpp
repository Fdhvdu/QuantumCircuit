#ifndef PATH
#define PATH
#include<algorithm>	//for_each
#include<cstddef>	//size_t
#include<functional>	//function
#include<vector>
#include"../../lib/header/math/math.hpp"

namespace nHypercube
{
	template<class T>
	std::vector<std::vector<T>> create_path(const T begin,const T end)
	{
		using namespace std;
		function<void(size_t,vector<vector<T>> &,size_t,size_t,size_t,T)> create_path_{[&,end](const size_t diff_bit_count,vector<vector<T>> &vec,const size_t row_begin,const size_t row_end,const size_t column,const T val){
			if(column!=diff_bit_count)
			{
				for_each(vec.begin()+row_begin,vec.begin()+row_end,[=](vector<T> &vec){vec[column]=val;});
				const auto range{(row_end-row_begin)/(diff_bit_count-column)};
				const T path{end^val};
				T mask{1};
				for(auto i{row_begin};i!=row_end;i+=range,mask<<=1)
				{
					while(!(path&mask))
						mask<<=1;
					create_path_(diff_bit_count,vec,i,i+range,column+1,val^mask);
				}
			}
		}};
		const auto diff_bit_count{nMath::diff_bit_count(begin,end)};
		vector<vector<T>> vec{nMath::factorial(diff_bit_count),vector<T>(diff_bit_count+1)};
		for(auto &val:vec)
			val.back()=end;
		create_path_(diff_bit_count,vec,0,vec.size(),0,begin);
		return vec;
	}
	//create_path(0,7)={{0,1,3,7},{0,1,5,7},{0,2,3,7},{0,2,6,7},{0,4,5,7},{0,4,6,7}}
	//create_path(0,7)={{7,3,1,0},{7,3,2,0},{7,5,1,0},{7,5,4,0},{7,6,2,0},{7,6,4,0}}
}

#endif