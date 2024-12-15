#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) { // 4 * n байт
        sort(satisfaction.rbegin(), satisfaction.rend()); // ~8 * log2(n) байт.
        int maxSatisfaction = 0; // 4 байта
        int currentSum = 0;      // 4 байта
        int totalSum = 0;        // 4 байта
        for (int i = 0; i < satisfaction.size(); ++i) { // O(n)
            currentSum += satisfaction[i];
            if (currentSum < 0) break;
            totalSum += currentSum;
        }
        return totalSum;
    }
};

int main() {
    vector<int> satisfaction = {-1, -8, 0, 2, 3, 8, -15}; // (4 * n) + 16 (служ данные) = 44 байта.
    Solution solution;
    int result = solution.maxSatisfaction(satisfaction); // 4 * n байт.
    cout << result << endl;
    return 0;
}