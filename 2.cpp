//
// Created by Тимур Сурин on 06.12.2024.
//
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    vector<int> arr; //4 байта каждый элемент
    // накладные расходы +- 24 байта
    ifstream file("datalab2.txt"); // 8 байт.

    if (!file) {
        cerr << "не удалось открыть файл" << endl;
        return 1;
    }
    int num; // 4 байта.
    while (file >> num) {
        arr.push_back(num);
        // 4 байта
    }
    file.close();
    set<int> s; // каждый элемент 4 байта
    for (int r : arr) {
        s.insert(r);
    }
    cout << "Уникальные элементы: " << endl;
    for (const int& elem : s) {
        cout << elem << ' ';
    }
    cout << endl;
    return 0;
}