#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

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
    std::ifstream file("datalab4.txt");
    std::vector<std::pair<int, int>> items;
    int weight, value;
    while (file >> weight >> value) {
        items.push_back({weight, value});
    }
    int weight_limit = 100;
    int max_value = f(items, weight_limit);
    std::cout << "Максимальная стоимость: " << max_value << std::endl;
    return 0;
}