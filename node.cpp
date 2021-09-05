#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const{
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	return comparison(date, date_, cmp_);
}

bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const {
	if (event == "~")
		return false;
	return comparison(event, event_, cmp_);
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
	switch(lo_){
	case LogicalOperation::And :
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
		break;
	case LogicalOperation::Or :
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
		break;
	default :
		throw std::invalid_argument("chto legit u tebya v lo_ boje ne ponimayu");
		return false;
	}
}

