#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Сложность: O(L), где L — длина строки `str`
// сложность: O(1), так как используется только одна дополнительная переменная х
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
    if (!file) {
        cerr << "Не удалось открыть файл" << endl;
        return 1; // Завершение программы — O(1)
    }

    string str; //O(L)

    // Временная сложность: O(N * L), где N — количество строк, L — средняя длина строки
    // Пространственная сложность: O(L), так как в памяти хранится только одна строка за раз
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