/*
 * Title: main_hw8_1.cpp
 * Abstract: Given a list of integers, partitions the list such that the left half of the list
 * 		     contains all the negatives and the right half contains all the positives. Uses two
 * 		     different methods: the two-pointer method and the single-pointer method.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 04/08/2022
 */

#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Partitions the list to have negatives on the left and positives on the right
 * using the two-pointer method.
 */
void twoPointers(std::vector<int32_t> numbers);

/**
 * Partitions the list to have negatives on the left and positives on the right
 * using the single-pointer method.
 */
void onePointer(std::vector<int32_t> numbers);

int main() {
	int32_t amount; std::cin >> amount;
	std::vector<int32_t> numbers(amount);
	
	for (int32_t& item: numbers) std::cin >> item;
	twoPointers(numbers);
	onePointer(numbers);
	
	return 0;
}

void onePointer(std::vector<int32_t> numbers) {
	int32_t pointer = 0;
	for (uint32_t i = 0; i < numbers.size(); i++) {
		if (numbers[i] < 0) {
			std::swap(numbers[i], numbers[pointer++]);
		}
	}
	
	for (uint32_t i = 0; i < numbers.size(); ++i) {
		if (i == numbers.size() - 1) {
			std::cout << numbers[i];
		} else {
			std::cout << numbers[i] << " ";
		}
	}
	std::cout << '\n';
}

void twoPointers(std::vector<int32_t> numbers) {
	uint32_t
		left = 0,
		right = static_cast<int>((numbers.size() - 1));
	auto valid = <:&:>() { return left < right; };
	
	while (valid()) {
		while (numbers[left] < 0 && valid()) left++;
		while (numbers[right] >= 0 && valid()) right--;
		
		if (valid()) {
			std::swap(numbers[left++], numbers[right--]);
		}
	}
	
	for (uint32_t i = 0; i < numbers.size(); ++i) {
		if (i == numbers.size() - 1) {
			std::cout << numbers[i];
		} else {
			std::cout << numbers[i] << " ";
		}
	}
	std::cout << '\n';
}
