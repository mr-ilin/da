#include "biggest_int.hpp"

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);

    NBiggestInt::TBiggestInt num1, num2;
    char op;

    while(std::cin >> num1 >> num2 >> op) {
        try {
            if (op == '+') {
                std::cout << num1 + num2 << "\n";
            } else if (op == '-') {
                std::cout << num1 - num2 << "\n";
            } else if (op == '*') {
                std::cout << num1 * num2 << "\n";
            } else if (op == '/') {
                std::cout << num1 / num2 << "\n";
            } else if (op == '^') {
                std::cout << num1.Pow(num2) << "\n";
            } else if (op == '<') {
                std::cout << ( (num1 < num2) ? "true" : "false" ) << "\n";
            } else if (op == '>') {
                std::cout << ( (num1 > num2) ? "true" : "false" ) << "\n";
            } else if (op == '=') {
                std::cout << ( (num1 == num2) ? "true" : "false" ) << "\n";
            } else {
                std::cout << "Invalid operation" << "\n";
            }
        } catch (const std::logic_error & exp) {
            // std::cout << exp.what() << "\n";
            std::cout << "Error" << "\n";
        } 
        catch (const std::runtime_error & exp) {
            std::cout << exp.what() << "\n";
        }
    }
    return 0;
}