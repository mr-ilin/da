#pragma once

#include <iostream>
#include <vector>

namespace NBiggestInt {

class TBiggestInt {
    public:
        static const int BASE = 10; // Основание системы счисления
        static const int RADIX = 1; // Длина разряда

        TBiggestInt() = default;
        TBiggestInt(const std::string & str);
        TBiggestInt(const size_t & length, const int & value = 0);
        void Initialize(const std::string & str);

        size_t Size() const;
        TBiggestInt Pow(const TBiggestInt & degree) const;

        TBiggestInt & operator=(const TBiggestInt & rhs);

        TBiggestInt operator+(const TBiggestInt & rhs) const;
        TBiggestInt operator-(const TBiggestInt & rhs) const;
        TBiggestInt operator*(const TBiggestInt & rhs) const;
        TBiggestInt operator/(const TBiggestInt & rhs) const;

        TBiggestInt operator-(const long long & rhs) const;
        TBiggestInt operator*(const long long & rhs) const;
        TBiggestInt operator/(const long long & rhs) const;
        long long   operator%(const long long & rhs) const;

        bool operator< (const TBiggestInt & rhs) const;
        bool operator<=(const TBiggestInt & rhs) const;
        bool operator> (const TBiggestInt & rhs) const;
        bool operator==(const TBiggestInt & rhs) const;
        bool operator==(const long long   & rhs) const;

        friend std::istream& operator>>(std::istream &is, TBiggestInt & rhs);
        friend std::ostream& operator<<(std::ostream &os, const TBiggestInt & rhs);
    private:
        std::vector<int> digits;

        void DeleteLeadingZeros();
};

} // namespace NBiggestInt
