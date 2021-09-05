#pragma once

#include "node.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

class Database {
public:
	void Add(const Date& date, const std::string& event);

	void Print(std::ostream& os) const;

	template <class Func>
	std::vector<std::pair<Date, std::string>> FindIf(Func predicate) const {
		std::vector<std::pair<Date, std::string>> result;
		for (auto current_pair : database_) {
			auto begin = current_pair.second.begin();
			auto end = current_pair.second.end();
			for (auto it = begin; it < end; it++) {
				const Date& current_date = current_pair.first;
				it = find_if(it, end, [predicate, current_date] (const std::string& event){return predicate(current_date, event);});
				if (it != end) {
					result.push_back(std::make_pair(current_pair.first, *it));
				}
			}
		}
		return result;
	}

	template <class Func>
	int RemoveIf(Func predicate){
		int cnt = 0;
		std::vector<Date> to_delete;
		for (std::pair<const Date, std::vector<std::string>>& current_pair : database_) {
			auto begin = current_pair.second.begin();
			auto end = current_pair.second.end();
			const Date current_date = current_pair.first;

			auto newEnd = stable_partition(begin, end, [predicate, current_date](const std::string& event)
													   {return !predicate(current_date, event);});
			for(auto del = newEnd; del < end; del++){
				database[current_date].erase(*del);
			}
			current_pair.second.erase(newEnd, end);
			cnt += (end - newEnd);
			if(current_pair.second.empty()) {
				to_delete.push_back(current_pair.first);
			}
		}
		for (const auto& i : to_delete) {
			database_.erase(i);
			database.erase(i);
		}
		return cnt;
	}

	std::pair<Date, std::string> Last(const Date date) const;
private:
	std::map<Date, std::set<std::string>> database;
	std::map<Date, std::vector<std::string>> database_;
};

std::ostream& operator<< (std::ostream& os, std::pair<Date, std::string> pair);

std::ostream& operator<< (std::ostream& os, std::pair<Date, std::vector<std::string>> pair);

template <typename T>
std::ostream& operator<< (std::ostream& os, std::vector<T> events) {
	for (const auto t : events) {
		os << t << std::endl;
	}
	return os;
}
