#include <iostream>
#include <vector>
#include "biggest_int.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    std::string str1, str2;
    std::string op;

    while(std::cin >> str1 >> str2 >> op) {
        try {
            NBiggestInt::TBiggestInt num1(str1);
            NBiggestInt::TBiggestInt num2(str2);
            if (op == "+") {
                std::cout << num1 + num2 << "\n";
            } else if (op == "-") {
                std::cout << num1 - num2 << "\n";
            } else if (op == "*") {
                std::cout << num1 * num2 << "\n";
            } else if (op == "/") {
                std::cout << num1 / num2 << "\n";
            } else if (op == "^") {
                std::cout << num1.Pow(num2) << "\n";
            } else if (op == "<") {
                std::cout << ( (num1 < num2) ? "true" : "false" ) << "\n";
            } else if (op == ">") {
                std::cout << ( (num1 > num2) ? "true" : "false" ) << "\n";
            } else if (op == "=") {
                std::cout << ( (num1 == num2) ? "true" : "false" ) << "\n";
            } else {
                std::cout << "Invalid operation" << "\n";
            }
        } catch (const std::exception & exp) {
            std::cout << "Error" << "\n";
        } 
    }
    return 0;
}