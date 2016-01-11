#include"CPath.h"
#include"../../lib/header/algorithm/algorithm.h"
#include"../../lib/header/math/math.h"

namespace nTsaiAlgorithm
{
	template<class T>
	void CPath<T>::create_(const std::size_t rowBegin,const std::size_t rowEnd,const std::size_t column,const T val)
	{
		if(column==vec_.front().size()-1)
			return;
		nAlgorithm::for_each(rowBegin,rowEnd,[&,column,val](const auto i){vec_[i][column]=val;});
		const auto range{(rowEnd-rowBegin)/(diff_bit_count()-column)};
		T path{vec_.front().back()^val},mask{1};
		for(auto i{rowBegin};i!=rowEnd;i+=range,mask<<=1)
		{
			while(!(path&mask))
				mask<<=1;
			create_(i,i+range,column+1,val^mask);
		}
	}

	template<class T>
	CPath<T>::CPath(const T begin,const T end)
		:diff_bit_count_{nMath::diff_bit_count(begin,end)}
	{
		vec_.assign(nMath::factorial(diff_bit_count()),value_type(diff_bit_count()+1));
		for(auto &val:vec_)
			val.back()=end;
		create_(0,size(),0,begin);
	}
}