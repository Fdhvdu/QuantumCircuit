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
		std::vector<value_type> vec_;
		void create_(std::size_t,std::size_t,std::size_t,T);
	public:
		CPath(T,T);
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