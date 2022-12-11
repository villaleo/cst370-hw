/*
 * Title: main_hw4_1.cpp
 * Abstract: Displays the adjacency list given an unirected graph.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 02/25/2022
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    size_t n_vertices, n_edges;
    std::cin >> n_vertices >> n_edges;

    std::vector<std::vector<int>> adjacency_list(n_vertices);

    int source, destination;
    for (int i = 0; i < n_edges; i++) {
        std::cin >> source >> destination;
        adjacency_list[source].push_back(destination);
    }

    for (size_t i = 0; i < n_vertices; i++) {
        std::cout << i;
        if (!adjacency_list[i].empty()) {
            std::cout << "->";
            std::sort(adjacency_list[i].begin(), adjacency_list[i].end());

            for (int j = 0; j < adjacency_list[i].size(); j++) {
                std::cout << adjacency_list[i][j];
                if (j == adjacency_list[i].size() - 1) continue;
                std::cout << "->";
            }
        }
        std::cout << '\n';
    }
    return 0;
}
