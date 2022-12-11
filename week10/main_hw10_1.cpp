/*
 * Title: main_hw10_1.cpp
 * Abstract: Conducts the topological ordering algorithm on a given DAG.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 04/22/2022
 */

#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

std::unordered_map<uint32_t, std::unique_ptr<std::set<uint32_t>>> graph {};

int main() {
	uint32_t numberOfNodes {}, numberOfEdges {};
	std::cin >> numberOfNodes >> numberOfEdges;
	
	// Initialize the graph edges to nullptr
	for (uint32_t node = 0; node < numberOfNodes; node++) {
		graph.emplace(node, nullptr);
	}
	
	// Read in the edges
	std::vector<uint32_t> inDegreeList(numberOfNodes, 0);
	for (uint32_t i = 0; i < numberOfEdges; i++) {
		uint32_t from {}, to {};
		std::cin >> from >> to;
		
		// Initialize inDegreeList
		inDegreeList.at(to)++;
		auto& array = graph.at(from);
		if (array == nullptr) {
			array = std::make_unique<std::set<uint32_t>>();
		}
		
		array->insert(to);
	}
	
	// Display the inDegreeList
	for (uint32_t i = 0; i < inDegreeList.size(); i++) {
		std::cout << "In-degree[" << i << "]:" << inDegreeList.at(i) << '\n';
	}
	
	// Place all the zeroes from the inDegreeList into the queue
	std::queue<uint32_t> output;
	for (uint32_t i = 0; i < inDegreeList.size(); i++) {
		if (inDegreeList.at(i) == 0 ) {
			output.push(i);
		}
	}
	
	// Khan's Algorithm
	std::vector<uint32_t> results;
	while (!output.empty()) {
		// Poll the front
		uint32_t const current = output.front();
		output.pop();
		// Push the current node to the results
		results.push_back(current);
		
		if (graph.at(current) != nullptr) {
			// Decrease the count of each neighbor of the current node
			for (uint32_t i : *graph.at(current)) {
				inDegreeList.at(i)--;
				// Check for 0's and enqueue
				if (inDegreeList.at(i) == 0) {
					output.push(i);
				}
			}
		}
	}
	
	// Display the topological order
	std::cout << "Order:";
	for (uint32_t node = 0; node < results.size(); node++) {
		std::cout << results.at(node) << (node == results.size() - 1? "\n" : "->");
	}
	
	return 0;
}
