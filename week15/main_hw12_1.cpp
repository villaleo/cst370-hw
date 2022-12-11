/*
 * Title: main_hw12_1.cpp
 * Abstract: Conduct the greedy algorithm to collect the maximum amount of
 * 			 coins given an N * M matrix.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 05/13/2022
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <deque>

template <class T>
using Vec = std::vector<T>;

using DequeOfPairs = std::deque<std::pair<int, int>>;

void backtrack(Vec<Vec<int>> const& matrix, DequeOfPairs& path);

int main() {
	int rows, columns;
	std::cin >> rows >> columns;
	
	// Read in the board
	Vec<Vec<int>> matrix(rows + 1, Vec<int>(columns + 1));
	for (int i{0}; i < matrix.size(); ++i) {
		for (int j{0}; j < matrix.at(i).size(); ++j) {
			if (i == 0 || j == 0) {
				// Create the top-left border of zeroes
				matrix.at(i).at(j) = 0;
				continue;
			}
			std::cin >> matrix.at(i).at(j);
		}
	}
	
	// Calculate the running sum for each cell
	for (int i{1}; i < rows + 1; ++i) {
		for (int j{1}; j < columns + 1; ++j) {
			int largest{std::max(matrix.at(i).at(j - 1), matrix.at(i - 1).at(j))};
			matrix.at(i).at(j) += largest;
		}
		
	}
	
	// Backtrack and collect the coins
	DequeOfPairs path;
	backtrack(matrix, path);
	
	// Display the output path
	printf("Max coins:%d\nPath:", matrix.at(rows).at(columns));
	int count{0};
	for (const auto &[i, j] : path) {
		printf("(%d,%d)", i, j);
		if (count >= path.size() - 1) {
			std::cout << '\n';
			break;
		}
		count++;
		std::cout << "->";
	}
	return 0;
}

void backtrack(Vec<Vec<int>> const& matrix, DequeOfPairs& path) {
	int row{static_cast<int>(matrix.size()) - 1};
	int column{static_cast<int>(matrix.at(0).size()) - 1};
	
	// Backtrack depending on value for top and left cell
	path.emplace_front(row, column);
	while (row != 1 && column != 1) {
		if (matrix.at(row).at(column - 1) >= matrix.at(row - 1).at(column)) {
			column--;
		} else {
			row--;
		}
		path.emplace_front(row, column);
	}
	
	// If we're on an edge but not at (1, 1), move until we reach (1, 1)
	if (column == 1 && row != 1) {
		while (row != 1) {
			path.emplace_front(--row, column);
		}
	}
	if (row == 1 && column != 1) {
		while (column != 1) {
			path.emplace_front(row, --column);
		}
	}
}