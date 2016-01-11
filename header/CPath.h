#ifndef CPATH
#define CPATH
#include<cstddef>
#include<vector>

namespace nTsaiAlgorithm
{
	template<class T>
	class CPath
	{
	public:
		typedef std::vector<T> value_type;
	private:
		const std::size_t diff_bit_count_;
		std::vector<value_type> vec_;
		void create_(std::size_t,std::size_t,std::size_t,T);
	public:
		CPath(T,T);
		//0,7
		//vec_={
		//	{0,1,3,7},
		//	{0,1,5,7},
		//	{0,2,3,7},
		//	{0,2,6,7},
		//	{0,4,5,7},
		//	{0,4,6,7}
		//}
		//7,0
		//vec_={
		//	{7,3,1,0},
		//	{7,3,2,0},
		//	{7,5,1,0},
		//	{7,5,4,0},
		//	{7,6,2,0},
		//	{7,6,4,0}
		//}
		inline std::size_t diff_bit_count() const noexcept
		{
			return diff_bit_count_;
		}
		inline std::size_t size() const noexcept
		{
			return vec_.size();
		}
		inline const value_type& operator[](const std::size_t subscript) const
		{
			return vec_[subscript];
		}
	};
}

#include"CPath.cpp"

#endif