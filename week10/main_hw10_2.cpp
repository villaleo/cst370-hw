/*
 * Title: main_hw10_2.cpp
 * Abstract: Display the alphabetical order of an alien language given
 * 			 an ordered collection of "words".
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 04/22/2022
 */

#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>

int main() {
	uint32_t numberOfWords{};
	std::cin >> numberOfWords;
	
	// Read each word
	std::vector<std::string> words(numberOfWords);
	for (std::string& word : words) {
		std::cin >> word;
	}
	
	// Find all the unique characters from the words (the nodes)
	std::unordered_set<char> nodes;
	for (std::string const& word : words) {
		for (char const& c : word) {
			nodes.insert(c);
		}
	}
	
	// Initialize the graph edges to nullptr
	std::unordered_map<char, std::unique_ptr<std::set<char>>> graph{};
	for (char const& c : nodes) {
		graph.emplace(c, nullptr);
	}
	
	// Grab the edges from the graph using the words
	for (uint32_t i = 0; i < numberOfWords - 1; i++) {
		std::string wordA{words.at(i)};
		for (uint32_t j = i + 1; j < numberOfWords; j++) {
			std::string wordB{words.at(j)};
			// Find the first mismatch of wordA and wordB
			uint32_t charIndex{0};
			while (charIndex < wordA.size() && charIndex < wordB.size()) {
				if (wordA.at(charIndex) != wordB.at(charIndex)) {
					// Add edge to graph
					auto& array = graph.at(wordA.at(charIndex));
					if (array == nullptr) {
						array = std::make_unique<std::set<char>>();
					}
					array->insert(wordB.at(charIndex));
					break;
				}
				charIndex++;
			}
		}
	}
	
	// Initialize inDegreeList
	std::unordered_map<char, uint32_t> inDegreeList{};
	for (const auto &item : graph) {
		inDegreeList.emplace(item.first, 0);
	}
	for (auto const& [node, edges] : graph) {
		if (edges == nullptr) {
			continue;
		}
		for (char c : *edges) {
			inDegreeList.at(c)++;
		}
	}
	
	// Place all the zeroes from the inDegreeList into the queue
	std::queue<char> output;
	for (auto const& [node, occurrence] : inDegreeList) {
		if (occurrence == 0) {
			output.push(node);
		}
	}
	
	// Khan's Algorithm
	std::vector<char> results;
	while (!output.empty()) {
		// Poll the front
		char const current = output.front();
		output.pop();
		// Push the current node to the results
		results.push_back(current);
		
		if (graph.at(current) != nullptr) {
			// Decrease the count of each neighbor of the current node
			for (char c : *graph.at(current)) {
				inDegreeList.at(c)--;
				// Check for 0's and enqueue
				if (inDegreeList.at(c) == 0) {
					output.push(c);
				}
			}
		}
	}
	
	// Display the topological order
	for (uint32_t i = 0; i < results.size(); i++) {
		std::cout << results.at(i) << (i != results.size() - 1 ? "->" : "\n");
	}
	
	return 0;
}
