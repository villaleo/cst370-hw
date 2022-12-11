/*
 * Title: main_hw5_2.cpp
 * Abstract: Finds the least expensive path given a graph.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/28/2022
 */

#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>
#include <utility>

std::vector<std::vector<int>>
permutate(std::vector<int> list);

std::pair<int, std::vector<std::string>>
shortest_path(const std::vector<std::vector<int>> &graph, const std::vector<std::string> &nodes);

constexpr int INF = std::numeric_limits<int>::max();

int main() {
    int num_nodes, num_edges;
    std::cin >> num_nodes;

    std::vector<std::string> node_names(num_nodes);
    for (auto &node : node_names) std::cin >> node;
    
    std::cin >> num_edges;
    std::vector<std::vector<int>> adj_list(num_nodes, std::vector<int>(num_nodes, INF));

    for (int i = 0; i < num_edges; i++) {
        std::string node_1, node_2;
        int weight;
        std::cin >> node_1 >> node_2 >> weight;

        int index_1 = std::find(node_names.begin(), node_names.end(), node_1) - node_names.begin();
        int index_2 = std::find(node_names.begin(), node_names.end(), node_2) - node_names.begin();

        adj_list[index_1][index_2] = weight;
    }

    for (int i = 0; i < num_nodes; i++) adj_list[i][i] = 0;

    const auto &[cost, path] = shortest_path(adj_list, node_names);
    std::cout << "Path:";
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i != path.size() - 1)
            std::cout << "->";
    }
    std::cout << "\nCost:" << cost << '\n';

    return 0;
}

std::vector<std::vector<int>>
permutate(std::vector<int> list) {
    std::vector<std::vector<int>> out;

    std::sort(list.begin(), list.end());
    do {
        if (list[0] != 0)
            continue;
        
        out.push_back(list);
    } while (std::next_permutation(list.begin(), list.end()));

    return out;
}

std::pair<int, std::vector<std::string>>
shortest_path(const std::vector<std::vector<int>> &graph, const std::vector<std::string> &nodes) {
    std::vector<int> accumulator(nodes.size(), 0);
    for (int i = 0; i < accumulator.size(); i++)
        accumulator[i] = i;
    
    auto permutations = permutate(accumulator);

    std::map<int, std::vector<int>> paths;
    for (auto &permutation: permutations) {
        int cost = 0;
        bool validPath = true;
        for (int i = 0; i < permutation.size() - 1; i++) {
            if (graph[permutation[i]][permutation[i + 1]] == INF) {
                validPath = false;
                break;
            }
            cost += graph[permutation[i]][permutation[i + 1]];
        }

        if (cost < 0) validPath = false;
        
        if (validPath) {
            if (graph[permutation[permutation.size() - 1]][permutation[0]] == INF)
                continue;

            cost += graph[permutation[permutation.size() - 1]][permutation[0]];
            permutation.push_back(permutation[0]);
            paths.emplace(cost, permutation);
        }
    }

    if (paths.empty()) return { -1, {} };

    const auto &[min_cost, min_path] = *paths.begin();
    std::vector<std::string> min_path_names;
    for (const auto &node : min_path)
        min_path_names.push_back(nodes[node]);

    return { min_cost, min_path_names };
}
