#pragma once
#include <iostream>

class Date {
public:
	Date(int year, int month, int day)
	  : Year(year)
	  , Month(month)
	  , Day(day){
	}
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
private:
	const int Year, Month, Day;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);


Date ParseDate(std::istream& is);
