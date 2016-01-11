#ifndef PATH_AND_ROUTE
#define PATH_AND_ROUTE
#include<vector>

namespace nHypercube
{
	template<class T>
	std::vector<std::vector<T>> create_path(T,T);
	//create_path(0,7)={{0,1,3,7},{0,1,5,7},{0,2,3,7},{0,2,6,7},{0,4,5,7},{0,4,6,7}}
	//create_path(0,7)={{7,3,1,0},{7,3,2,0},{7,5,1,0},{7,5,4,0},{7,6,2,0},{7,6,4,0}}
}

#include"path_and_route.cpp"

#endif