#include"path_algorithm.h"
#include<iterator>	//distance
#include"CQCircuit.h"

namespace nTsaiAlgorithm
{
	template<class RanIter>
	nQCircuit::CQCircuit path_algorithm(RanIter begin,RanIter end,const std::size_t size,const std::size_t i)
	{
		nQCircuit::CQCircuit temp{size};
		switch(std::distance(begin,end))
		{
		case 1:	//no, you don't need to attach anything
			break;
		case 2:
			temp.attach(createGate(size,begin[0],begin[1]));
			break;
		case 3:
			temp.reserve(3);
			switch(i)
			{
			case 0:
				temp.attach(createGate(size,begin[0],begin[1]));
				temp.attach(createGate(size,begin[1],begin[2]));
				temp.attach(createGate(size,begin[0],begin[1]));
				break;
			case 1:
				temp.attach(createGate(size,begin[1],begin[2]));
				temp.attach(createGate(size,begin[0],begin[1]));
				temp.attach(createGate(size,begin[1],begin[2]));
				break;
			}
			break;
		case 4:
			temp.reserve(5);
			switch(i)
			{
			case 0:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c d_a
				temp.attach(createGate(size,begin[1],begin[2]));	//b d_c a
				temp.attach(createGate(size,begin[0],begin[1]));	//d_b c a
				break;
			case 1:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a d_c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d_a c
				temp.attach(createGate(size,begin[0],begin[1]));	//d_b a c
				temp.attach(createGate(size,begin[2],begin[3]));	//d b c_a
				break;
			case 2:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a d_c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d_a c
				temp.attach(createGate(size,begin[2],begin[3]));	//b d c_a
				temp.attach(createGate(size,begin[0],begin[1]));	//d_b c a
				break;
			case 3:
				temp.attach(createGate(size,begin[2],begin[3]));	//a b d_c
				temp.attach(createGate(size,begin[1],begin[2]));	//a d_b c
				temp.attach(createGate(size,begin[0],begin[1]));	//d_a b c
				temp.attach(createGate(size,begin[1],begin[2]));	//d b_a c
				temp.attach(createGate(size,begin[2],begin[3]));	//d b c_a
				break;
			case 4:
				temp.attach(createGate(size,begin[2],begin[3]));	//a b d_c
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a d c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d_a c
				temp.attach(createGate(size,begin[2],begin[3]));	//b d c_a
				temp.attach(createGate(size,begin[0],begin[1]));	//d_b c a
				break;
			case 5:
				temp.attach(createGate(size,begin[2],begin[3]));	//a b d_c
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a d c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d_a c
				temp.attach(createGate(size,begin[0],begin[1]));	//d_b a c
				temp.attach(createGate(size,begin[2],begin[3]));	//d b c_a
				break;
			}
			break;
		case 5:
			temp.reserve(7);
			switch(i)
			{
			case 0:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a d e
				temp.attach(createGate(size,begin[2],begin[3]));	//b c d_a e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c d e_a
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_d a
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 1:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c a e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 2:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c a e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d_a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 3:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c a e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b c e d_a
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 4:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 5:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e_d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 6:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e_d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d_a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 7:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e_d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b c e d_a
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 8:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c_a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 9:
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d_a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 10:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//a e_b c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_a b c d
				temp.attach(createGate(size,begin[1],begin[2]));	//e b_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 11:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e_c d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d_a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 12:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e_c d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c_a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 13:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e_c d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 14:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b c e d_a
				temp.attach(createGate(size,begin[2],begin[3]));	//b e_c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 15:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d_a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 16:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c_a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 17:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e_c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_a c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c_a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			case 18:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d_a
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c d a
				break;
			case 19:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e_d
				temp.attach(createGate(size,begin[0],begin[1]));	//b_a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c_a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e_a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e_c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e_b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d_a
				break;
			}
			break;
		}
		return temp;
	}
}