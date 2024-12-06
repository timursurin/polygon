#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Сложность: O(L)
// сложность: O(1)
bool f(const string& str) {
    int x = 0; //O(1)
    for (char ch : str) { //O(L)
        if (ch == '(') {
            x++; //O(1)
        } else if (ch == ')') {
            x--; //O(1)
        }
        if (x < 0) {
            return false; //O(1)
        }
    }
    return x == 0; //O(1)
}

int main() {
    ifstream file("datalab3.txt"); //O(1)
    string str; //O(L)

    // Временная сложность: O(N * L)
    // Пространственная сложность: O(L)
    while (getline(file, str)) { //O(L)
        if (f(str)) { //O(L)
            cout << "закрыты" << endl; //O(1)
        } else {
            cout << "открыты" << endl; //O(1)
        }
    }

    file.close(); //O(1)
    return 0; //O(1)
}