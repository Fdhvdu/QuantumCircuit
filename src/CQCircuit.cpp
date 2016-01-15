#include"../header/CQCircuit.h"
#include<iterator>	//make_move_iterator
#include<stdexcept>	//logic_error, invalid_argument
#include<utility>	//move
#include<vector>
#include"../../lib/header/algorithm/algorithm.h"
#include"../../lib/header/tool/CInsert_iterator.h"
#include"../header/IQBit.h"
using namespace std;

namespace
{
	void check_size(const size_t lhs,const size_t rhs)
	{
		if(lhs!=rhs)
			throw invalid_argument{"Different size of circuit or gate"};
	}
}

namespace nQCircuit
{
	bool operator!=(const CQGate &lhs,const CQGate &rhs) noexcept
	{
		if(lhs.gate_size()!=rhs.gate_size())
			return true;
		return nAlgorithm::any_of_val<size_t>(0,lhs.gate_size(),[&](const auto val){return *lhs[val]!=*rhs[val];});
	}

	struct CQGate::Impl
	{
		const size_t gateSize;
		vector<unique_ptr<const IQBit>> gate;
		Impl(size_t);
		Impl(const Impl &);
		Impl(size_t,vector<unique_ptr<const IQBit>> &&);
		Impl& operator=(const Impl &);
	};

	CQGate::Impl::Impl(const size_t gateSize_)
		:gateSize{gateSize_},gate(gateSize_){}

	CQGate::Impl::Impl(const Impl &val)
		:gateSize{val.gateSize},gate(val.gateSize)
	{
		*this=val;
	}

	CQGate::Impl::Impl(const size_t gateSize_,vector<unique_ptr<const IQBit>> &&rVal)
		:gateSize{gateSize_},gate{move(rVal)}{}

	CQGate::Impl& CQGate::Impl::operator=(const Impl &impl)
	{
		nAlgorithm::for_each_val<size_t>(0,gateSize,[&](const auto val){
			gate[val]=copy_QBit(impl.gate[val]);
		});
		return *this;
	}

	CQGate::CQGate(const size_t size)
		:impl_{size}{}

	CQGate::CQGate(const CQGate &val)
		:impl_{val.impl_}{}

	CQGate::CQGate(CQGate &&val) noexcept
		:impl_{val.gate_size(),move(val.impl_.get().gate)}{}

	size_t CQGate::gate_size() const noexcept
	{
		return impl_.get().gateSize;
	}
	
	CQGate& CQGate::operator=(const CQGate &val)
	{
		check_size(gate_size(),val.gate_size());
		impl_.get()=val.impl_.get();
		return *this;
	}

	CQGate& CQGate::operator=(CQGate &&rVal)
	{
		check_size(gate_size(),rVal.gate_size());
		impl_.get().gate=move(rVal.impl_.get().gate);
		return *this;
	}

	unique_ptr<const IQBit>& CQGate::operator[](const size_t subscript)
	{
		return impl_.get().gate[subscript];
	}

	const unique_ptr<const IQBit>& CQGate::operator[](const size_t subscript) const
	{
		return impl_.get().gate[subscript];
	}

	CQGate::~CQGate(){}

	bool operator!=(const CQCircuit &lhs,const CQCircuit &rhs) noexcept
	{
		if(lhs.gate_size()!=rhs.gate_size()||lhs.size()!=rhs.size())
			return true;
		return nAlgorithm::any_of_val<size_t>(0,lhs.size(),[&](const auto val){return lhs[val]!=rhs[val];});
	}

	struct CQCircuit::Impl
	{
		const size_t gateSize;
		vector<CQGate> circuit;
		Impl(size_t);
		Impl(size_t,vector<CQGate> &&);
		inline void attach(const vector<CQGate> &val)
		{
			circuit.insert(circuit.end(),val.begin(),val.end());
		}
		inline void attach(vector<CQGate> &&rVal)
		{
			circuit.insert(circuit.end(),make_move_iterator(rVal.begin()),make_move_iterator(rVal.end()));
		}
		inline void erase(const size_t subscript)
		{
			circuit.erase(circuit.begin()+subscript);
		}
	};

	CQCircuit::Impl::Impl(const size_t gateSize_)
		:gateSize{gateSize_}{}

	CQCircuit::Impl::Impl(const size_t gateSize_,vector<CQGate> &&rVal)
		:gateSize{gateSize_},circuit{move(rVal)}{}

	CQCircuit::CQCircuit(const size_t gateSize)
		:impl_{gateSize}{}

	CQCircuit::CQCircuit(const CQCircuit &val)
		:impl_{val.impl_}{}

	CQCircuit::CQCircuit(CQCircuit &&val) noexcept
		:impl_{val.gate_size(),move(val.impl_.get().circuit)}{}

	void CQCircuit::attach(const CQCircuit &val)
	{
		check_size(gate_size(),val.gate_size());
		impl_.get().attach(val.impl_.get().circuit);
	}

	void CQCircuit::attach(CQCircuit &&rVal)
	{
		check_size(gate_size(),rVal.gate_size());
		impl_.get().attach(move(rVal.impl_.get().circuit));
	}

	void CQCircuit::attach(const CQGate &val)
	{
		check_size(gate_size(),val.gate_size());
		impl_.get().circuit.emplace_back(val);
	}

	void CQCircuit::attach(CQGate &&rVal)
	{
		check_size(gate_size(),rVal.gate_size());
		impl_.get().circuit.emplace_back(move(rVal));
	}

	void CQCircuit::erase(const size_t subscript)
	{
		impl_.get().erase(subscript);
	}

	size_t CQCircuit::gate_size() const noexcept
	{
		return impl_.get().gateSize;
	}

	void CQCircuit::reserve(const size_t new_cap)
	{
		impl_.get().circuit.reserve(new_cap);
	}

	void CQCircuit::shrink_to_fit()
	{
		impl_.get().circuit.shrink_to_fit();
	}

	size_t CQCircuit::size() const noexcept
	{
		return impl_.get().circuit.size();
	}

	CQCircuit& CQCircuit::operator=(const CQCircuit &val)
	{
		check_size(gate_size(),val.gate_size());
		impl_.get().circuit=val.impl_.get().circuit;
		return *this;
	}

	CQCircuit& CQCircuit::operator=(CQCircuit &&rVal)
	{
		check_size(gate_size(),rVal.gate_size());
		impl_.get().circuit=move(rVal.impl_.get().circuit);
		return *this;
	}

	CQGate& CQCircuit::operator[](const size_t subscript)
	{
		return impl_.get().circuit[subscript];
	}

	const CQGate& CQCircuit::operator[](const size_t subscript) const
	{
		return impl_.get().circuit[subscript];
	}

	CQCircuit::~CQCircuit(){}

	nTool::CInsert_iterator<CQGate,CQCircuit,void(CQCircuit::*)(const CQGate &),void(CQCircuit::*)(CQGate &&)> make_CQGate_inserter(CQCircuit &circuit)
	{
		return nTool::inserter<CQGate>(circuit,static_cast<void(CQCircuit::*)(const CQGate &)>(&CQCircuit::attach),static_cast<void(CQCircuit::*)(CQGate &&)>(&CQCircuit::attach));
	}

	nTool::CInsert_iterator<CQCircuit,CQCircuit,void(CQCircuit::*)(const CQCircuit &),void(CQCircuit::*)(CQCircuit &&)> make_CQCircuit_inserter(CQCircuit &circuit)
	{
		return nTool::inserter<CQCircuit>(circuit,static_cast<void(CQCircuit::*)(const CQCircuit &)>(&CQCircuit::attach),static_cast<void(CQCircuit::*)(CQCircuit &&)>(&CQCircuit::attach));
	}

	unique_ptr<const IQBit> copy_QBit(const unique_ptr<const IQBit> &bit)
	{
		if(!bit)
			return unique_ptr<const IQBit>();
		switch(bit->info())
		{
		case QBit::CONTROLLED_NOT:
			return make_Q_controlled_not_bit();
		case QBit::EMPTY:
			return make_Q_empty_bit();
		case QBit::NOT:
			return make_Q_not_bit();
		case QBit::WHITE_CONTROLLED_NOT:
			return make_Q_white_controlled_not_bit();
		}
		throw logic_error{"You didn't add correct QBit, check QBit.h for more detail"};
	}

	unique_ptr<const IQBit> make_Q_empty_bit()
	{
		return make_unique<const Q_empty_bit>();
	}

	unique_ptr<const IQBit> make_Q_not_bit()
	{
		return make_unique<const Q_not_bit>();
	}

	unique_ptr<const IQBit> make_Q_controlled_not_bit()
	{
		return make_unique<const Q_controlled_not_bit>();
	}

	unique_ptr<const IQBit> make_Q_white_controlled_not_bit()
	{
		return make_unique<const Q_white_controlled_not_bit>();
	}
}