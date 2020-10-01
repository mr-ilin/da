//
//  benchmark.cpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 21.09.2020.
//

#include <iostream>
#include <chrono>
#include <vector>

#include "sort.hpp"

bool operator<(const NSort::TKeyValue& lhs, const NSort::TKeyValue& rhs) {
    if (lhs.Key.GetYear() != rhs.Key.GetYear()) {
        return lhs.Key.GetYear() < rhs.Key.GetYear();
    }
    if (lhs.Key.GetMonth() < rhs.Key.GetMonth()) {
        return lhs.Key.GetMonth() < rhs.Key.GetMonth();
    }
    return rhs.Key.GetDay() < rhs.Key.GetDay();
}

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    NSort::TKeyValue elem;
    NDate::TDate maxKey;
    NVector::TVector<NSort::TKeyValue> elems;
    NVector::TVector<NSort::TKeyValue> elemsStl;
    
    while(std::cin >> elem.Key >> elem.Value) {
        maxKey.SetDay(std::max(maxKey.GetDay(), elem.Key.GetDay()));
        maxKey.SetMonth(std::max(maxKey.GetMonth(), elem.Key.GetMonth()));
        maxKey.SetYear(std::max(maxKey.GetYear(), elem.Key.GetYear()));
        elems.PushBack(elem);
        elemsStl.PushBack(elem);
    }

    auto start = std::chrono::high_resolution_clock::now();
    NSort::RadixSort(elems, maxKey);
    auto end = std::chrono::high_resolution_clock::now();
    double radixSortTime = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    std::stable_sort(elemsStl.Begin(), elemsStl.End(), operator<);
    end = std::chrono::high_resolution_clock::now();
    double stlStableSortTime = std::chrono::duration<double>(end - start).count();

    std::cout << "Radix Sort Time: " << radixSortTime << std::endl;
    std::cout << "STL Stable Sort Time: " << stlStableSortTime << std::endl;

    /*for(size_t i = 0; i < elems.Size(); ++i) {
        std::cout << elems[i].Key << '\t' << elems[i].Value << '\n';
    }*/
    
    return 0;
}
