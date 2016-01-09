#include"CPath.h"
#include<algorithm>
#include"../../lib/header/math/math.h"

namespace nTsaiAlgorithm
{
	template<class T>
	void CPath<T>::create_(const std::size_t rowBegin,const std::size_t rowEnd,const std::size_t column,const T val)
	{
		if(column==vec_.front().size()-1)
			return ;
		std::for_each(vec_.begin()+rowBegin,vec_.begin()+rowEnd,[=](value_type &vec){vec[column]=val;});
		const auto range{nMath::factorial(nMath::diff_bit_count(val,vec_.front().back())-1)};
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
	{
		const auto temp{nMath::diff_bit_count(begin,end)};
		vec_.assign(nMath::factorial(temp),value_type(temp+1));
		for(auto &val:vec_)
			val.back()=end;
		create_(0,vec_.size(),0,begin);
	}
}