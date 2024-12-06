#include <iostream>
#include <set>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    vector<int> arr;
    ifstream file("datalab2.txt");

    if (!file) {
        cerr << "не удалось открыть файл" << endl;
        return 1;
    }
    int num;
    while (file >> num) {
        arr.push_back(num);
    }
    file.close();
    set<int> s;
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
