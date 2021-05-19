#include <iostream>
#include <fstream>
#include <random>

int main(){
    std::random_device random_device; // Источник энтропии.
    std::mt19937 generator(random_device()); // Генератор случайных чисел.
    std::uniform_int_distribution<> itemDist(0, 1);
    
    std::ofstream fout;
    fout.open("Test.txt", std::ios_base::out | std::ios_base::trunc);
    
    unsigned long long i_, j_;
    
    std::cin >> i_ >> j_;
    
    for (unsigned long long i = 0; i < i_; ++i){
        for (unsigned long long j = 0; j < j_; ++j){
            int item = itemDist(generator);
            fout << item;
        }
        fout << "\n";
    }
    fout.close();
    return 0;
}
