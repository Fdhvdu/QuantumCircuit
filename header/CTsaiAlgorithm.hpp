#ifndef CTSAIALGORITHM
#define CTSAIALGORITHM
#include"QCFwd.hpp"

namespace nTsaiAlgorithm
{
	class CTsaiAlgorithm:public ICircuitAlgorithm
	{
		vec_CQCircuit result_;
	public:
		CTsaiAlgorithm()=default;
		CTsaiAlgorithm(const CTsaiAlgorithm &)=delete;
		void create() override;
		const vec_CQCircuit& get() const noexcept override
		{
			return result_;
		}
		CTsaiAlgorithm& operator=(const CTsaiAlgorithm &)=delete;
	};

	//1. it uses uniform_int_distribution and mt19937 to randomly create circuit
	//2. the result of this algorithm is not accurate, but runs very fast
	class CRandom_TsaiAlgorithm:public ICircuitAlgorithm
	{
		vec_CQCircuit result_;
	public:
		CRandom_TsaiAlgorithm()=default;
		CRandom_TsaiAlgorithm(const CRandom_TsaiAlgorithm &)=delete;
		void create() override;
		const vec_CQCircuit& get() const noexcept override
		{
			return result_;
		}
		CRandom_TsaiAlgorithm& operator=(const CRandom_TsaiAlgorithm &)=delete;
	};
}

#endif
