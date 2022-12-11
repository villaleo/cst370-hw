/*
 * Title: main_hw6_1.cpp
 * Abstract: Given a collection of numbers, uses short representation for consecutive numbers.
 * ID: 6403
 * Name: Leonardo Villalobos
 * Date: 03/11/2022
 */

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <cmath>
#include <deque>
#include <limits>

using namespace std;

constexpr int INF = std::numeric_limits<int>::max();

int main() {
    int num_inputs;
    cin >> num_inputs;

    deque<int> inputs(num_inputs, 0);
    for (int &num: inputs) {
        cin >> num;
    }

    sort(inputs.begin(), inputs.end());

    size_t prev = -1;
    pair<int, int> range(INF, INF);
    deque<pair<int, int>> out;

    for (size_t i = 0; i < num_inputs; i++) {
        auto &[x, y] = range;

        if (i == 0) {
            prev++;
            x = inputs[i];
            continue;    
        }

        if (abs(inputs[i] - inputs[prev]) != 1) {
            if (x != INF && y != INF) {
                out.emplace_back(x, y);
            } else {
                out.emplace_back(x, INF);
            }
            x = inputs[i];
            y = INF;
            prev++;
        }
        else {
            y = inputs[i];
            prev++;
        }
    }

    if (range.first != INF && range.second != INF) {
        out.push_back(range);
    } else {
        out.emplace_back(range.first, INF);
    }

    for (size_t i = 0; i < out.size(); i++) {
        auto &[x, y] = out[i];

        if (y == INF) {
            cout << x;
        } else {
            cout << x << '-' << y;
        }

        if (i != out.size() - 1) cout << ' ';
    }
    cout << '\n';
    return 0;
}
