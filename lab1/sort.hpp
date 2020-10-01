//
//  sort.hpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 24.09.2020.
//

#ifndef sort_hpp
#define sort_hpp

#include <stdio.h>

#include "date.hpp"
#include "vector.hpp"

namespace NSort {
    struct TKeyValue {
        NDate::TDate Key;
        unsigned long long Value;
    };
    
    const int keyLength = 8;
    const int digitLength = 4;
    
    void RadixSort(NVector::TVector<TKeyValue>& data, NDate::TDate& maxKey);
} // namespace NSort

#endif // sort_hpp
