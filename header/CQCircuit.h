#ifndef CQCIRCUIT
#define CQCIRCUIT
#include<cstddef>
#include<memory>
#include"../../lib/header/tool/CPimpl.h"

namespace nQCircuit
{
	struct IQBit;

	class CQGate
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		explicit CQGate(std::size_t);
		CQGate(const CQGate &);
		CQGate(CQGate &&) noexcept;
		std::size_t gate_size() const noexcept;
		CQGate& operator=(const CQGate &);
		CQGate& operator=(CQGate &&);	//check_size in CCQCircuit.cpp make it not noexcept
		std::unique_ptr<const IQBit>& operator[](std::size_t);
		const std::unique_ptr<const IQBit>& operator[](std::size_t) const;
		~CQGate();
	};

	bool operator!=(const CQGate &,const CQGate &) noexcept;

	inline bool operator==(const CQGate &lhs,const CQGate &rhs) noexcept
	{
		return !(lhs!=rhs);
	}

	class CQCircuit
	{
		struct Impl;
		nTool::CPimpl<Impl> impl_;
	public:
		explicit CQCircuit(std::size_t gateSize);
		CQCircuit(const CQCircuit &);
		CQCircuit(CQCircuit &&) noexcept;
		void attach(const CQCircuit &);
		void attach(CQCircuit &&);
		void attach(const CQGate &);
		void attach(CQGate &&);
		void erase(std::size_t);
		std::size_t gate_size() const noexcept;
		std::size_t size() const noexcept;
		CQCircuit& operator=(const CQCircuit &);
		CQCircuit& operator=(CQCircuit &&);	//check_size in CCQCircuit.cpp make it not noexcept
		CQGate& operator[](std::size_t);
		const CQGate& operator[](std::size_t) const;
		~CQCircuit();
	};

	bool operator!=(const CQCircuit &,const CQCircuit &) noexcept;

	inline bool operator==(const CQCircuit &lhs,const CQCircuit &rhs) noexcept
	{
		return !(lhs!=rhs);
	}

	std::unique_ptr<const IQBit> copy_QBit(const std::unique_ptr<const IQBit> &);
	
	std::unique_ptr<const IQBit> make_Q_empty_bit();
	
	std::unique_ptr<const IQBit> make_Q_not_bit();
	
	std::unique_ptr<const IQBit> make_Q_controlled_not_bit();

	std::unique_ptr<const IQBit> make_Q_white_controlled_not_bit();
}

#endif