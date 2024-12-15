#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int countOperationsToEmpty(vector<int>& nums) { // O(1)
    int operations = 0;  // 4 байта
    while (!nums.empty()) { // O(n), память: O(1)
        int minElement = *min_element(nums.begin(), nums.end());  // 4 байта
        if (nums[0] == minElement) { // O(n)
            nums.erase(nums.begin());  // O(n)
        } else {
            nums.push_back(nums[0]);
            nums.erase(nums.begin());  // O(n)
        }
        operations++;
    }
    return operations;
}

int main() { // O(n)
    vector<int> nums = {3, 4, -1};  // 4 * n байт
    // Время: O(n²), Память: O(n)
    cout << countOperationsToEmpty(nums) << endl;
    return 0;
}