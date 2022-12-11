/*
 * Title: main_hw7_2.cpp
 * Abstract: Conducts the BFS traversal of a graph and displays city names in the
 *           range of hop(s) from a starting city.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 03/25/2022
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

constexpr int INF = std::numeric_limits<int>::max();
std::vector<std::vector<int>> graph;
std::map<std::string, int> nodeIDs;
std::map<int, std::string> nodeNames;

auto bfs(int src) -> std::map<std::string, int>;

int main() {
    // Read number of cities.
    int nodes; std::cin >> nodes;
    // Initialize graph.
    graph.resize(nodes, std::vector<int>(nodes, INF));

    for (int i = 0; i < nodes; i++) {
        std::string city; std::cin >> city;
        // Populate the mappings.
        nodeIDs.emplace(city, i);
        nodeNames.emplace(i, city);
    }

    // Read number of graph.
    int edges; std::cin >> edges;
    for (int i = 0; i < edges; i++) {
        std::string source, destination; std::cin >> source >> destination;
        // Place a 1 on the graph from source to destination.
        graph.at(nodeIDs[source]).at(nodeIDs[destination]) = 1;
    }

    // Read the starting city.
    std::string startingCity; std::cin >> startingCity;
    // Read number of hops.
    int hops; std::cin >> hops;

    // Call the bread-first search algorithm.
    auto paths = bfs(nodeIDs[startingCity]);
    for (const auto &[key, value] : paths) {
        if (value <= hops) {
            printf("%s:%d\n", key.c_str(), value);
        }
    }

    return 0;
}

auto bfs(int src) -> std::map<std::string, int> {
    // Initialize the result and track the visited nodes and their distances.
    std::map<std::string, int> result;
    std::queue<int> visited;
    std::vector<int> distances(graph.size(), INF);

    visited.push(src);
    distances[src] = 0;
    result.emplace(nodeNames[src], 0);

    while (!visited.empty()) {
        // Get the next node to visit.
        int node = visited.front();
        visited.pop();

        // Visit all the neighbors of the node.
        for (int i = 0; i < graph.size(); i++) {
            if (graph[node][i] == INF) continue;
            if (distances[i] == INF) {
                distances[i] = distances[node] + 1;
                result.emplace(nodeNames[i], distances[i]);
                visited.push(i);
            }
        }
    }

    return result;
}
