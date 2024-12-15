#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.rbegin(), satisfaction.rend());
        int maxSatisfaction = 0;
        int currentSum = 0;
        int totalSum = 0;
        for (int i = 0; i < satisfaction.size(); ++i) {
            currentSum += satisfaction[i];
            if (currentSum < 0) break;
            totalSum += currentSum;
        }

        return totalSum;
    }
};

int main() {
    vector<int> satisfaction = {-1, -8, 0, 2, 3, 8, -15};
    Solution solution;
    int result = solution.maxSatisfaction(satisfaction);
    cout << result << endl;
    return 0;
}