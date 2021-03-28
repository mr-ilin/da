#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

namespace NBiggestInt {

class TBiggestInt {
    public:
        static const int BASE = 1e6; 
        static const int RADIX = 6;

        TBiggestInt() = default;
        TBiggestInt(const std::string & str);
        TBiggestInt(const size_t & length, const long long & value = 0);
        void Initialize(const std::string & str);
        std::string GetString() const;

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
        bool operator> (const long long   & rhs) const;

        friend std::istream& operator>>(std::istream &is, TBiggestInt & rhs);
        friend std::ostream& operator<<(std::ostream &os, const TBiggestInt & rhs);
    private:
        std::vector<long long> digits;

        void DeleteLeadingZeros();
};

} // namespace NBiggestInt
