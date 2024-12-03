#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int f(const std::vector<std::pair<int, int>>& items, int weight_limit) {
    int n = items.size();
    int max_value = 0;
    for (int i = 0; i < std::pow(2, n); ++i) {
        int total_weight = 0;
        int total_value = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                total_weight += items[j].first;
                total_value += items[j].second;
            }
        }

        if (total_weight <= weight_limit) {

            max_value = std::max(max_value, total_value);
        }
    }
    return max_value;
}

int main() {
    std::vector<std::pair<int, int>> items = {
            {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10},
            {1, 2}, {3, 6}, {4, 7}, {2, 4}, {5, 9}, {6, 10}, {7, 11}, {8, 12}, {9, 13},
            {2, 5}, {3, 8}, {4, 10}, {5, 12}, {6, 14}, {7, 15}, {8, 16}, {9, 17}
    };

    int weight_limit = 100;
    int max_value = f(items, weight_limit);

    std::cout << "Максимальная стоимость: " << max_value << std::endl;

    return 0;
}