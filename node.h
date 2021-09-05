#pragma once

#include "comparison.h"
#include "date.h"
#include <memory>

class Node {
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const std::string& event) const;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, const Date& date)
	  : cmp_(cmp)
	  , date_(date){}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const Comparison cmp_;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, const std::string& event)
	  : cmp_(cmp)
	  , event_(event){}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const Comparison cmp_;
	const std::string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation lo, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
	  : lo_(lo)
	  , left_(left)
	  , right_(right){}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	LogicalOperation lo_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> right_;
};

template <typename COMP>
bool comparison(const COMP& compared, const COMP& result, const Comparison cmp) {
	switch (cmp)
	{
		case Comparison::Less : return compared < result;
			break;
		case Comparison::LessOrEqual : return compared <= result;
			break;
		case Comparison::Greater : return compared > result;
			break;
		case Comparison::GreaterOrEqual : return compared >= result;
			break;
		case Comparison::Equal : return compared == result;
			break;
		case Comparison::NotEqual : return compared != result;
			break;
		default: return false;
	}
}
