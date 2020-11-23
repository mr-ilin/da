//
//  sort.cpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 24.09.2020.
//

#include "sort.hpp"

namespace NSort {
    void RadixSort(NVector::TVector<TKeyValue>& data, NDate::TDate& maxKey) {
        const int digitNum = keyLength / digitLength;
        const size_t size = data.Size();
        for (int digit = 0; digit < digitNum; ++digit) {
            const int max = maxKey.GetDigit(digit);
            
            NVector::TVector<int> count (max + 1, 0);
            NVector::TVector<TKeyValue> result (size);
            
            for (size_t i = 0; i < size; ++i) {
                ++count[data[i].key.GetDigit(digit)];
            }
            
            for (size_t i = 1; i <= max; ++i) {
                count[i] += count[i-1];
            }
            
            for (size_t i = data.Size() - 1; i < size; --i) { // Not a bug, reverse loop with unsigned! var
                result[count[data[i].key.GetDigit(digit)] - 1] = data[i];
                count[data[i].key.GetDigit(digit)]--;
            }
            
            data.Copy(result);
        }
    }
} // namespace NSort
