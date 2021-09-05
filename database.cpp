#include "database.h"

#include <stdexcept>
using namespace std;

void Database::Add(const Date& date, const string& event) {
	if(event != "") {
		auto res = database[date].insert(event);
		if (res.second == true) {
			database_[date].push_back(event);
		}
	}
}

void Database::Print(std::ostream& os) const {
	for (const auto i : database_) {
		os << i;
	}
}

pair<Date, string> Database::Last(const Date date) const {
	if (database_.empty())
		throw invalid_argument("");
	auto it = database_.upper_bound(date);
	if (it == database_.begin()) {
		throw invalid_argument("");
	} else {
		return make_pair(prev(it)->first, prev(it)->second.back());
	}
}

ostream& operator<< (ostream& os, pair<Date, string> pair) {
	os << pair.first << " " << pair.second;
	return os;
}

std::ostream& operator<< (std::ostream& os, std::pair<Date, std::vector<std::string>> events){
	for (const auto event : events.second) {
		os << events.first << " " << event << endl;
	}
	return os;
}
