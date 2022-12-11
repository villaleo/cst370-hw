/*
 * Title: main_hw11_1.cpp
 * Abstract: Simulate linear probing using a hash table.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 05/06/2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <tuple>

enum State {
	Empty,
	Active,
	Deleted
};

constexpr int maxTableSize = 200;
std::vector<int> primes;

struct Dictionary {
	static constexpr double loadFactorLimit = 1.0 / 2;
	
	int tableSize;
	std::vector<std::pair<int, State>> table;
	int keyCount;
	double loadFactor;
	
	mutable std::vector<std::string> logs;
	
	explicit Dictionary(int size) {
		tableSize = size;
		table.resize(tableSize);
		keyCount = 0;
		loadFactor = 0;
	}
	
	inline int hash(int key) const {
		return key % tableSize;
	}
	
	void insert(int key);
	
	void rehash();
	
	void print() const;
	
	void getStatus(int entry) const;
	
	void search(int key);
	
	void remove(int key);
};

bool isPrime(int n);

int main() {
	for (int i = 2; i <= maxTableSize; i++) {
		if (isPrime(i)) {
			primes.push_back(i);
		}
	}
	
	int tableSize{};
	int queries{};
	std::cin >> tableSize >> queries;
	Dictionary dict(tableSize);
	
	std::string command;
	int argument;
	for (int i = 0; i < queries; i++) {
		std::cin >> command;
		if (command == "insert") {
			std::cin >> argument;
			dict.insert(argument);
		}
		else if (command == "delete") {
			std::cin >> argument;
			dict.remove(argument);
		}
		else if (command == "search") {
			std::cin >> argument;
			dict.search(argument);
		}
		else if (command == "displayStatus") {
			std::cin >> argument;
			dict.getStatus(argument);
		}
		else if (command == "tableSize") {
			dict.logs.emplace_back(std::to_string(dict.tableSize));
		}
	}
	
	for (auto const& entry : dict.logs) {
		std::cout << entry << '\n';
	}

	return 0;
}

void Dictionary::insert(int key) {
	keyCount++;
	loadFactor = static_cast<double>(keyCount) / tableSize;
	if (loadFactor > loadFactorLimit) {
		rehash();
	}
	
	int position = hash(key);
	auto& [thisKey, thisState] = table.at(position);
	
	if (thisState == State::Active) {
		int i = position + 1;
		auto& [currentKey, currentState] = table.at(i % tableSize);
		
		while (true) {
			std::tie(currentKey, currentState) = table.at(i % tableSize);
			if (currentState != State::Active) {
				break;
			}
			i++;
		}
		
		currentKey = key;
		currentState = State::Active;
	}
	else {
		thisKey = key;
		thisState = State::Active;
	}
}

void Dictionary::rehash() {
	auto ptr = std::upper_bound(
		primes.begin(), primes.end(), tableSize * 2
	);
	int newTableSize = tableSize * 2;
	if (!isPrime(newTableSize)) {
		newTableSize = *ptr;
	}
	
	std::vector<std::pair<int, State>> temp(newTableSize);
	auto newHash = [&](int key) -> int { return key % newTableSize; };
	
	for (auto const& [key, state] : table) {
		if (state == State::Empty) {
			continue;
		}
		
		int newPosition = newHash(key);
		auto& [thisKey, thisState] = temp.at(newPosition);
		thisKey = key;
		thisState = state;
	}
	
	table = temp;
	tableSize = static_cast<int>(table.size());
}

void Dictionary::print() const {
	int index = 0;
	for (auto& [key, state] : table) {
		std::cout << index++ << ": " << key << ", ";
		
		if (state == State::Active) {
			std::cout << "Active\n";
		} else if (state == State::Empty) {
			std::cout << "Empty\n";
		} else {
			std::cout << "Deleted\n";
		}
	}
}

void Dictionary::getStatus(int entry) const {
	auto const& [key, state] = table.at(entry);
	std::stringstream response;
	
	switch (state) {
		case State::Empty:
			logs.emplace_back("Empty");
			return;
		case State::Active:
			response << key << " Active";
			logs.emplace_back(response.str());
			return;
		case State::Deleted:
			response << key << " Deleted";
			logs.emplace_back(response.str());
	}
}

void Dictionary::search(int key) {
	int position = hash(key);
	auto const& [thisKey, thisState] = table.at(position);
	std::stringstream response;
	
	if (thisKey == key && thisState == State::Active) {
		response << key << " Found";
		logs.emplace_back(response.str());
		return;
	}
	
	if (thisState == State::Deleted) {
		int count = 0;
		int i = position + 1;
		auto& [currentKey, currentState] = table.at(i % tableSize);
		
		while (true) {
			if (count >= tableSize) {
				break;
			}
			
			std::tie(currentKey, currentState) = table.at(i % tableSize);
			if (thisKey == key && thisState == State::Active) {
				response << key << " Found";
				logs.emplace_back(response.str());
				return;
			}
			
			i++;
			count++;
		}
	}
	
	response << key << " Not found";
	logs.emplace_back(response.str());
}

void Dictionary::remove(int key) {
	int position = hash(key);
	auto& [thisKey, thisState] = table.at(position);
	
	if (thisKey == key && thisState == State::Active) {
		thisState = State::Deleted;
		keyCount--;
		return;
	}
	
	if (thisState == State::Deleted) {
		int count = 0;
		int i = position + 1;
		auto& [currentKey, currentState] = table.at(i % tableSize);
		
		while (true) {
			if (count >= tableSize) {
				break;
			}
			
			std::tie(currentKey, currentState) = table.at(i % tableSize);
			if (thisKey == key && thisState == State::Active) {
				thisState = State::Empty;
				return;
			}
			
			i++;
			count++;
		}
	}
	keyCount--;
}

bool isPrime(int n) {
	// source: https://www.geeksforgeeks.org/print-all-prime-numbers-less-than-or-equal-to-n/
	if (n <= 1) {
		return false;
	}
	
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	
	return true;
}
