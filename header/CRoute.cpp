#include"CRoute.h"
#include<iterator>
#include"../../lib/header/math/math.h"
#include"path_algorithm.h"

namespace nTsaiAlgorithm
{
	template<class Iter>
	CRoute::CRoute(const std::size_t bit,Iter begin,Iter end)
	{
		if(1<std::distance(begin,end))
		{
			const std::size_t route_count{route(nMath::diff_bit_count(*begin,*std::prev(end)))};
			for(std::size_t i{0};i!=route_count;++i)
				vec_.emplace_back(path_algorithm(begin,end,bit,i));
		}
	}
}