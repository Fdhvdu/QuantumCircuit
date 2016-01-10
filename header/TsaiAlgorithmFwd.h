#ifndef TSAIALGORITHMFWD
#define TSAIALGORITHMFWD
#include"QCFwd.h"
#include<cstddef>

namespace nTsaiAlgorithm
{
	typedef std::vector<const vec_CQCircuit *> vec_const_vec_CQCircuit_ptr;
	typedef std::vector<vec_const_vec_CQCircuit_ptr> Split_t;

	void sort_by_size(vec_CQCircuit &);
	void erase_equal(vec_CQCircuit &);
	void erase_size_bigger_than_smallest_size_plus_1(vec_CQCircuit &);	//you have to use sort_by_size first
	void move_insert(vec_CQCircuit &,vec_CQCircuit &&);
}

#endif