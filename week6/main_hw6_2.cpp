/*
 * Title: main_hw6_1.cpp
 * Abstract: A program that implements the Depth-First Search algorithm
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 03/11/2022
 */

#include <iostream>
#include <deque>
#include <limits>
using namespace std;

constexpr int INF = std::numeric_limits<int>::max();

namespace impl {
int current = 0;
deque<int> visited;
deque<deque<int>> graph;

auto dfs(int node) -> void;
inline auto unvisited(int node) { return visited[node] == 0; }
} // namespace impl

auto dfs(deque<deque<int>> &graph, int start) -> void;

int main() {
    int num_nodes, num_edges;
    cin >> num_nodes >> num_edges;

    impl::graph.resize(num_nodes);
    for (auto &entry: impl::graph) entry.resize(num_nodes, INF);

    for (int i = 0; i < num_edges; i++) {
        int index_1, index_2;
        cin >> index_1 >> index_2;

        impl::graph[index_1][index_2] = 1;
    }

    impl::visited.resize(num_nodes);
    for (int &num: impl::visited) num = 0;

    dfs(impl::graph, 0);

    for (int i = 0; i < num_nodes; i++) {
        cout << "Mark[" << i << "]:" << impl::visited[i] << '\n';
    }
    return 0;
}

void dfs(deque<deque<int>> &graph, int start) {
    for (int i = 0; i < graph[start].size(); i++) {
        if (impl::unvisited(i)) {
            impl::dfs(i);
        }
    }
}

void impl::dfs(int node) {
    impl::current += 1;
    impl::visited[node] = impl::current;

    for (int i = 0; i < impl::visited.size(); i++) {
        if (impl::graph[node][i] == 1 && impl::unvisited(i)) {
            impl::dfs(i);
        }
    }
}
