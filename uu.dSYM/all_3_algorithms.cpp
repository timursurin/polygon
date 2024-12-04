#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "counting_sort.h"
#include "coctail_sort.h"
#include "quick_sort.h"
using namespace std;

int main(){
    vector<int> arr;
    ifstream file("aaa.txt")
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int number;
        while (ss >> number) {
            arr.push_back(number);
        }
    }
    file.close();
    vector<int> sorted_arr;
    
    // Counting Sort
    // countingSort(arr, sorted_arr);

    // Quick Sort
    // quicksort(arr, 0, arr.size() - 1);
    // sorted_arr = arr;

    // Cocktail Sort
    // CoctailSort(arr);
    // sorted_arr = arr;

    for (int x : sorted_arr) {
        cout << x << " ";
    }
    return 0;
}
