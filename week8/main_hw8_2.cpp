/*
 * Title: main_hw8_2.cpp
 * Abstract: Collects the maximum number of apples in boxes.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 04/08/2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <cmath>

std::vector<uint32_t> boxes;

bool contiguous(std::string const& s);

std::string toBinary(uint32_t n);

std::string pad(uint32_t amount);

uint32_t countApplesFromPositionArray(std::string const& s);

int main() {
	uint32_t n; std::cin >> n;
	boxes.resize(n);
	for (uint32_t& box : boxes) std::cin >> box;
	
	std::vector<std::string> binaryPositions;
	for (uint32_t i = 0; i < pow(2, boxes.size()); i++) {
		std::string binary = toBinary(i);
		std::string paddedBinary = pad(boxes.size() - binary.size()) + binary;
		if (not contiguous(paddedBinary)) {
			binaryPositions.push_back(paddedBinary);
		}
	}
	
	uint32_t appleAmount = countApplesFromPositionArray(binaryPositions.front());
	std::string positionString = binaryPositions.front();
	for (auto it = ++binaryPositions.begin(); it != binaryPositions.end(); it++) {
		uint32_t amount = countApplesFromPositionArray(*it);
		if (amount > appleAmount) {
			appleAmount = amount;
			positionString = *it;
		}
	}

	std::cout << "Boxes:";
	for (uint32_t i = 0; i < boxes.size(); i++) {
		if (positionString[i] == '1') {
			std::cout << i;
			if (i != boxes.size() - 1) {
				std::cout << ' ';
			}
		}
	}
	std::cout << "\nMax Apples:" << appleAmount << '\n';
	return 0;
}

bool contiguous(std::string const& s) {
	for (uint32_t i = 0; i < s.size() - 1; i++) {
		if (s[i] == '1' and s[i + 1] == '1') {
			return true;
		}
	}
	return false;
}

std::string toBinary(uint32_t n) {
	if (n == 0) return "0";
	
	std::deque<char> bits;
	n = abs(static_cast<int>(n));
	while (n > 0) {
		bits.push_front((n % 2 == 1) ? '1' : '0');
		n /= 2;
	}
	
	return {bits.begin(), bits.end() };
}

std::string pad(uint32_t amount) {
	std::string padding;
	for (uint32_t i = 0; i < amount; i++) padding += '0';
	return padding;
}

uint32_t countApplesFromPositionArray(std::string const& s) {
	uint32_t count = 0;
	for (uint32_t i = 0; i < s.size(); i++) {
		if (s[i] == '1') count += boxes[i];
	}
	return count;
}
