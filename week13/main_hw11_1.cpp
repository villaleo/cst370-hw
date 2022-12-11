/*
 * Title: main_hw11_1.cpp
 * Abstract: Conduct the Radix sort algorithm on a list of numbers.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 05/06/2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <array>

std::string getLsd(std::string const&, int);

std::string pad(std::string const&, int);

int main() {
	// amount of numbers to read
	int amount;
	std::cin >> amount;
	// numbers to read in
	std::vector<std::string> list(amount);
	for (auto& str: list) {
		std::cin >> str;
	}
	
	// buckets is array with vectors of strings
	std::array<std::vector<std::string>, 10> buckets;
	
	// stoppingPoint = The longest string in the list
	int stoppingPoint = static_cast<int>(list.at(0).size());
	for (int i = 1; i < amount; i++) {
		int current = static_cast<int>(list.at(i).size());
		if (current > stoppingPoint) {
			stoppingPoint = current;
		}
	}
	
	for (int i = 0; i < stoppingPoint; i++) {
		// put each number into the buckets
		for (auto const& str: list) {
			auto current = str;
			
			if (current.size() < stoppingPoint) {
				current = pad(current, stoppingPoint);
			}
			
			int lsd = std::stoi(getLsd(current, i));
			buckets.at(lsd).push_back(current);
		}
		
		// collect each number from the buckets and reassign list
		int listIndex = 0;
		for (auto const& sublist: buckets) {
			if (sublist.empty()) {
				continue;
			}
			for (auto const& str: sublist) {
				list.at(listIndex++) = str;
			}
		}
		
		// clear the buckets
		for (auto& bucket: buckets) {
			bucket.clear();
		}
		
		// print the list
		for (int j = 0; j < list.size(); j++) {
			std::cout << std::stoi(list[j]);
			if (j != list.size() - 1) {
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
	
	return 0;
}

std::string getLsd(std::string const& number, int offset) {
	if (number.empty() || offset < 0) {
		return {};
	}
	if (offset >= number.size()) {
		return { number.at(0) };
	}
	
	int i = 0;
	auto ptr = number.rbegin();
	
	while (ptr != number.rend() && i < offset) {
		ptr++;
		i++;
	}
	
	return { *ptr };
}

std::string pad(std::string const& number, int target) {
	if (target <= 0) {
		return number;
	}
	
	std::deque<char> characters;
	for (char const& c: number) {
		characters.push_back(c);
	}
	
	while (characters.size() != target) {
		characters.push_front('0');
	}
	
	return { characters.begin(), characters.end() };
}
