//requirements: x64 and C++14
#define USE_THREAD 1
#include<fstream>
#include<memory>	//make_unique
#if USE_THREAD
#include<mutex>
#include<thread>	//thread::hardware_concurrency()
#endif
#include<utility>	//declval
#include<type_traits>	//remove_reference
#include<vector>
#include"../../lib/header/tool/CChrono_timer.hpp"
#include"../../lib/header/tool/show.hpp"
#if USE_THREAD
#include"../../ThreadPool/header/CThreadPool.hpp"
#endif
#include"../header/CQCircuit.hpp"
#include"../header/QCFwd.hpp"
#include"../header/CTsaiAlgorithm.hpp"

namespace
{
	std::vector<std::remove_reference<decltype(std::declval<ICircuitAlgorithm>().get())>::type::size_type> accu;
	std::ofstream ofs{"output.txt"};
#if USE_THREAD
	std::mutex accu_mut;
	std::mutex ofs_mut;
#endif
	void call_and_output(const Func_t &func)
	{
		using namespace std;
		unique_ptr<ICircuitAlgorithm> algorithm{make_unique<nTsaiAlgorithm::CTsaiAlgorithm>()};
		algorithm->setFunc(func);
		algorithm->create();
		auto size{algorithm->get().size()};
		if(size)
			size=algorithm->get().front().size();
		{
#if USE_THREAD
			lock_guard<mutex> lock{ofs_mut};
#endif
			nTool::show(func.begin(),func.end(),ofs);
			ofs<<"gate : "<<size<<endl<<endl;
		}
#if USE_THREAD
		lock_guard<mutex> lock{accu_mut};
#endif
		if(accu.size()<=size)
			accu.resize(size+1);
		++accu[size];
	}
}

int main()
{
	using namespace std;
	nTool::CChrono_timer timer;
	{
	#if USE_THREAD
		nThread::CThreadPool tp{max<unsigned>(4,thread::hardware_concurrency())};
	#endif
		Func_t func{0,1,2,3,4,5,6,7};
		timer.start();
		do
	#if USE_THREAD
			tp.add_and_detach(call_and_output,func);	//copy func, not reference
	#else
			call_and_output(func);
	#endif
		while(next_permutation(func.begin(),func.end()));
	}
	timer.stop();
	ofs<<timer.duration_minutes()<<"\tminutes"<<endl
		<<timer.duration_seconds()%60<<"\tseconds"<<endl
		<<timer.duration_milliseconds()%1000<<"\tmilliseconds"<<endl;
	nTool::show(accu.begin(),accu.end(),ofs);
	system("PAUSE");
}