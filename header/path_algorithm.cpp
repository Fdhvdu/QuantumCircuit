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
			if(i)
			{
				temp.attach(createGate(size,begin[0],begin[1]));
				temp.attach(createGate(size,begin[1],begin[2]));
				temp.attach(createGate(size,begin[0],begin[1]));
			}
			else
			{
				temp.attach(createGate(size,begin[1],begin[2]));
				temp.attach(createGate(size,begin[0],begin[1]));
				temp.attach(createGate(size,begin[1],begin[2]));
			}
			break;
		case 4:
			switch(i)
			{
			case 0:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a d c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d a c
				temp.attach(createGate(size,begin[0],begin[1]));	//d b a c
				temp.attach(createGate(size,begin[2],begin[3]));	//d b c a
				break;
			case 1:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a d c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d a c
				temp.attach(createGate(size,begin[2],begin[3]));	//b d c a
				temp.attach(createGate(size,begin[0],begin[1]));	//d b c a
				break;
			case 2:
				temp.attach(createGate(size,begin[2],begin[3]));	//a b d c
				temp.attach(createGate(size,begin[0],begin[1]));	//b a d c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d a c
				temp.attach(createGate(size,begin[0],begin[1]));	//d b a c
				temp.attach(createGate(size,begin[2],begin[3]));	//d b c a
				break;
			case 3:
				temp.attach(createGate(size,begin[2],begin[3]));	//a b d c
				temp.attach(createGate(size,begin[0],begin[1]));	//b a d c
				temp.attach(createGate(size,begin[1],begin[2]));	//b d a c
				temp.attach(createGate(size,begin[2],begin[3]));	//b d c a
				temp.attach(createGate(size,begin[0],begin[1]));	//d b c a
				break;
			case 4:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c d a
				temp.attach(createGate(size,begin[1],begin[2]));	//b d c a
				temp.attach(createGate(size,begin[0],begin[1]));	//d b c a
				break;
			case 5:
				temp.attach(createGate(size,begin[2],begin[3]));	//a b d c
				temp.attach(createGate(size,begin[1],begin[2]));	//a d b c
				temp.attach(createGate(size,begin[0],begin[1]));	//d a b c
				temp.attach(createGate(size,begin[1],begin[2]));	//d b a c
				temp.attach(createGate(size,begin[2],begin[3]));	//d b c a
				break;
			}
			break;
		case 5:
			switch(i)
			{
			case 0:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//a e b c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e a b c d
				temp.attach(createGate(size,begin[1],begin[2]));	//e b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 1:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e c d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 2:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e c d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 3:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//a b e c d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 4:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 5:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 6:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 7:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 8:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 9:
				temp.attach(createGate(size,begin[3],begin[4]));	//a b c e d
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b c e d a
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 10:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 11:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 12:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b a e c d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e a c d
				temp.attach(createGate(size,begin[2],begin[3]));	//b e c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 13:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 14:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 15:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b a c e d
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b c e d a
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 16:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c a d
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//e b c d a
				break;
			case 17:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 18:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a d e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c a e d
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e a d
				temp.attach(createGate(size,begin[3],begin[4]));	//b c e d a
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			case 19:
				temp.attach(createGate(size,begin[0],begin[1]));	//b a c d e
				temp.attach(createGate(size,begin[1],begin[2]));	//b c a d e
				temp.attach(createGate(size,begin[2],begin[3]));	//b c d a e
				temp.attach(createGate(size,begin[3],begin[4]));	//b c d e a
				temp.attach(createGate(size,begin[2],begin[3]));	//b c e d a
				temp.attach(createGate(size,begin[1],begin[2]));	//b e c d a
				temp.attach(createGate(size,begin[0],begin[1]));	//e b c d a
				break;
			}
			break;
		}
		return temp;
	}
}