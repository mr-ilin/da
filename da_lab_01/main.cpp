//
//  main.cpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 21.09.2020.
//

#include <iostream>
#include <chrono>

#include "sort.hpp"


int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    
    NSort::TKeyValue elem;
    NDate::TDate maxKey;
    NVector::TVector<NSort::TKeyValue> elems;
    
    while(std::cin >> elem.key >> elem.value) {
        maxKey.SetDay(std::max(maxKey.GetDay(), elem.key.GetDay()));
        maxKey.SetMonth(std::max(maxKey.GetMonth(), elem.key.GetMonth()));
        maxKey.SetYear(std::max(maxKey.GetYear(), elem.key.GetYear()));
        elems.PushBack(elem);
    }
    
    NSort::RadixSort(elems, maxKey);
    
    for(size_t i = 0; i < elems.Size(); ++i) {
        std::cout << elems[i].key << '\t' << elems[i].value << '\n';
    }
    
    return 0;
}
