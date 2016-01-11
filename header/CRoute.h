#ifndef CROUTE
#define CROUTE
#include<cstddef>
#include<vector>
#include"CQCircuit.h"

namespace nTsaiAlgorithm
{
	class CRoute
	{
	public:
		typedef nQCircuit::CQCircuit value_type;
	private:
		std::vector<value_type> vec_;
	public:
		template<class Iter>
		CRoute(std::size_t,Iter,Iter);
		typename std::vector<value_type>::iterator begin() noexcept
		{
			return vec_.begin();
		}
		typename std::vector<value_type>::const_iterator begin() const noexcept
		{
			return vec_.begin();
		}
		typename std::vector<value_type>::iterator end() noexcept
		{
			return vec_.end();
		}
		typename std::vector<value_type>::const_iterator end() const noexcept
		{
			return vec_.end();
		}
		inline std::size_t size() const noexcept
		{
			return vec_.size();
		}
		inline nQCircuit::CQCircuit& operator[](const std::size_t subscript)
		{
			return vec_[subscript];
		}
		inline const nQCircuit::CQCircuit& operator[](const std::size_t subscript) const
		{
			return vec_[subscript];
		}
	};
}

#include"CRoute.cpp"

#endif