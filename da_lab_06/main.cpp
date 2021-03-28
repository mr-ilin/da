#include <iostream>
#include <vector>
#include "biggest_int.hpp"

int main() {
    std::ios_base::sync_with_stdio(false);

    NBiggestInt::TBiggestInt num1, num2;
    std::string op;

    while(std::cin >> num1 >> num2 >> op) {
        try {
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