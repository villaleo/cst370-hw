/*
 * Title: main_hw12_2.cpp
 * Abstract: Conducts Floyd's algorithm on a given adjacency matrix.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 05/13/2022
 */

#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
using Vec = std::vector<T>;

constexpr int infinity{std::numeric_limits<int>::max()};

int main() {
	int numberVertices;
	std::cin >> numberVertices;
	Vec<Vec<int>> graph(numberVertices, Vec<int>(numberVertices));
	
	auto const& at = [&](int x, int y) -> int {
		return graph.at(x).at(y);
	};
	
	// Read in the graph as a matrix
	for (int i{0}; i < numberVertices; ++i) {
		for (int j{0}; j < numberVertices; ++j) {
			int& current{graph.at(i).at(j)};
			std::cin >> current;
			if (current == -1) {
				current = infinity;
			}
		}
	}
	
	// Floyd's algorithm
	for (int k{0}; k < numberVertices; ++k) {
		for (int i{0}; i < numberVertices; ++i) {
			for (int j{0}; j < numberVertices; ++j) {
				int& current = graph.at(i).at(j);
				bool notInfinity{at(k, j) != infinity && at(i, k) != infinity};
				if (at(i, j) > (at(i, k) + at(k, j)) && notInfinity) {
					current = at(i, k) + at(k, j);
				}
			}
		}
	}
	
	// Display the output
	for (int i{0}; i < numberVertices; ++i) {
		for (int j{0}; j < numberVertices; ++j) {
			std::cout << (at(i, j) == infinity ? -1 : at(i, j));
			if (j != numberVertices - 1) {
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}
	
	return 0;
}
