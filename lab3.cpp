//
// Created by Тимур Сурин on 03.12.2024.
//
#include <iostream>
#include <string>
bool f(const std::string& str) {
    int x = 0;
    for (char ch : str) {
        if (ch == '(') {
            x++;
        } else if (ch == ')') {
            x--;
        }
        if (x < 0) {
            return false;
        }
    }
    return x == 0;
}

int main() {
    std::string str = "a(b)(((a)b)";
    if (f(str)) {
        std::cout << "закрыты\n";
    } else {
        std::cout << "открыты\n";
    }
    return 0;
}