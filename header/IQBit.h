#ifndef IQBIT
#define IQBIT
#include<iosfwd>
#include<vector>
#include"../../lib/header/tool/Boolean.h"
#include"QBit.h"

namespace nQCircuit
{
	class CQGate;

	struct IQBit
	{
		virtual QBit info() const noexcept=0;
		virtual bool is_valid(const CQGate &,const std::vector<nTool::Boolean> &,size_t) const=0;
		virtual bool operate(bool input) const
		{
			return input;
		}
		virtual std::ostream& print(std::ostream &) const=0;
		virtual ~IQBit();
	};

	inline bool operator!=(const IQBit &lhs,const IQBit &rhs) noexcept
	{
		return lhs.info()!=rhs.info();
	}

	inline bool operator==(const IQBit &lhs,const IQBit &rhs) noexcept
	{
		return lhs.info()==rhs.info();
	}

	std::ostream& operator<<(std::ostream &,const IQBit &);

	struct Q_empty_bit:public IQBit
	{
		QBit info() const noexcept override
		{
			return QBit::EMPTY;
		}
		bool is_valid(const CQGate &,const std::vector<nTool::Boolean> &,size_t) const override
		{
			return true;
		}
		std::ostream& print(std::ostream &) const override;
	};

	struct Q_not_bit:public IQBit
	{
		QBit info() const noexcept override
		{
			return QBit::NOT;
		}
		bool is_valid(const CQGate &,const std::vector<nTool::Boolean> &,size_t) const override
		{
			return true;
		}
		bool operate(bool input) const override
		{
			return !input;
		}
		std::ostream& print(std::ostream &) const override;
	};

	struct Q_controlled_not_bit:public IQBit
	{
		QBit info() const noexcept override
		{
			return QBit::CONTROLLED_NOT;
		}
		bool is_valid(const CQGate &,const std::vector<nTool::Boolean> &bit,size_t subscript) const override
		{
			return bit[subscript];
		}
		std::ostream& print(std::ostream &) const override;
	};

	struct Q_white_controlled_not_bit:public IQBit
	{
		QBit info() const noexcept override
		{
			return QBit::WHITE_CONTROLLED_NOT;
		}
		bool is_valid(const CQGate &,const std::vector<nTool::Boolean> &bit,size_t subscript) const override
		{
			return !bit[subscript];
		}
		std::ostream& print(std::ostream &) const override;
	};

	//this is an example to help you understand how to use IQBit correctly
	//check IQBit.cpp for more detail
	//struct Q_or_bit:public IQBit
	//{
	//	QBit info() const noexcept override
	//	{
	//		return QBit::OR;
	//	}
	//	bool is_valid(const CQGate &,const std::vector<nTool::Boolean> &,size_t) const override;
	//	std::ostream& print(std::ostream &) const override;
	//};
}

#endif