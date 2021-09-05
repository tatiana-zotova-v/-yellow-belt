#include "date.h"
#include <iomanip>
#include <string>

using namespace std;

int Date::GetYear() const {
	return Year;
}

int Date::GetMonth() const {
	return Month;
}

int Date::GetDay() const {
	return Day;
}

ostream& operator<<(ostream& os, const Date& date){
	os << setfill('0');
	os << setw(4) << date.GetYear() << '-' <<
		  setw(2) << date.GetMonth() << '-' <<
		  setw(2) << date.GetDay();
	return os;
}

bool operator<(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() != rhs.GetYear()){
		return lhs.GetYear() < rhs.GetYear();
	} else if (lhs.GetMonth() != rhs.GetMonth()){
		return lhs.GetMonth() < rhs.GetMonth();
	} else {
		return lhs.GetDay() < rhs.GetDay();
	}
}

bool operator>(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() != rhs.GetYear()){
		return lhs.GetYear() > rhs.GetYear();
	} else if (lhs.GetMonth() != rhs.GetMonth()){
		return lhs.GetMonth() > rhs.GetMonth();
	} else {
		return lhs.GetDay() > rhs.GetDay();
	}
}

bool operator==(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() == rhs.GetYear() &&
		lhs.GetMonth() == rhs.GetMonth() &&
		lhs.GetDay() == rhs.GetDay()){
		return true;
	} else {
		return false;
	}
}

bool operator!=(const Date& lhs, const Date& rhs){
	if (lhs.GetYear() != rhs.GetYear() ||
		lhs.GetMonth() != rhs.GetMonth() ||
		lhs.GetDay() != rhs.GetDay()){
		return true;
	} else {
		return false;
	}
}

bool operator>=(const Date& lhs, const Date& rhs){
	if (lhs == rhs || lhs > rhs){
		return true;
	} else {
		return false;
	}
}

bool operator<=(const Date& lhs, const Date& rhs){
	if (lhs == rhs || lhs < rhs){
		return true;
	} else {
		return false;
	}

}

Date ParseDate(istream& is) {
	string year, month, day;
	getline(is, year, '-');
	getline(is, month, '-');
	is >> day;
	return {stoi(year), stoi(month), stoi(day)};
}
