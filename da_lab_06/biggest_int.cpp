#include "biggest_int.hpp"

// #include <algorithm>

namespace NBiggestInt {

TBiggestInt::TBiggestInt(const std::string & str) {
    this->Initialize(str);
}

TBiggestInt::TBiggestInt(const size_t & length, const int & value) 
    : digits(length, value)
{}

void TBiggestInt::Initialize(const std::string & str) {
    digits.clear();
    digits.resize(str.size() / TBiggestInt::RADIX);
    for (size_t i = str.size() - 1; i < str.size(); --i) {
        digits[i] = static_cast<decltype(digits)::value_type>(str[i] - '0');
    }
    std::reverse(std::begin(digits), std::end(digits));
    DeleteLeadingZeros();
}

size_t TBiggestInt::Size() const {
    return digits.size();
}

TBiggestInt& TBiggestInt::operator=(const TBiggestInt & rhs) {
    digits.resize(rhs.Size());
    for (size_t i = 0; i < Size(); ++i) {
        digits[i] = rhs.digits[i];
    }
    return *this;
}

void TBiggestInt::DeleteLeadingZeros() {
    while (Size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

// Streams operators

std::istream& operator>>(std::istream & is, TBiggestInt & rhs) {
    std::string str;
    is >> str;
    rhs.Initialize(str);
    return is;
}

std::ostream& operator<<(std::ostream & os, const TBiggestInt & rhs) {
    if (rhs.digits.empty()) {
        os << "0";
        return os;
    }

    for (size_t i = rhs.Size() - 1; i < rhs.Size(); --i) {
        os << rhs.digits[i];
    }
    return os;
}

// Operators for TBiggestInt
TBiggestInt TBiggestInt::operator+(const TBiggestInt & rhs) const {
    size_t resSize = std::max(rhs.Size(), Size());
    TBiggestInt res(resSize);
    long long carry = 0;

    for (size_t i = 0; i < resSize; ++i) {
        long long sum = carry;
        if (i < rhs.Size()) {
            sum += rhs.digits[i];
        }
        if (i < Size()) {
            sum += digits[i];
        }
        carry = sum / TBiggestInt::BASE;
        res.digits[i] = sum % TBiggestInt::BASE;
    }
    if (carry != 0) {
        res.digits.push_back(carry);
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator-(const TBiggestInt & rhs) const {
    if (*this < rhs) {
        throw std::logic_error("Error: trying to subtract bigger number from smaller");
    }

    size_t resSize = std::max(rhs.Size(), Size());
    long long carry = 0;
    TBiggestInt res(resSize);

    for (size_t i = 0; i < resSize; ++i) {
        long long diff = digits[i] - carry;
        if (i < rhs.Size()) {
            diff -= rhs.digits[i];
        }

        if (diff < 0) {
            carry = 1;
            diff += TBiggestInt::BASE;
        } else {
            carry = 0;
        }
        res.digits[i] = diff % TBiggestInt::BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator*(const TBiggestInt & rhs) const {
    TBiggestInt res(Size() + rhs.Size());
    for (size_t i = 0; i < Size(); ++i)
    {
        long long carry = 0;
        for (size_t j = 0; j < rhs.Size() || carry > 0; ++j)
        {
            int current = res.digits[i + j] + carry;
            if (j < rhs.Size()) {
                current += digits[i] * rhs.digits[j];
            }
            res.digits[i + j] = current % TBiggestInt::BASE;
            carry = current / TBiggestInt::BASE;
        }
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator/(const TBiggestInt & rhs) const {
    if (rhs == 0) {
        throw std::logic_error("Error: Trying to divide by zer0");
    }

    TBiggestInt res;
    TBiggestInt curr;
    for (size_t i = Size() - 1; i < Size(); --i) {
        curr.digits.insert(std::begin(curr.digits), digits[i]);
        curr.DeleteLeadingZeros();

        long long currResDigit = 0;
        long long leftBound = 0;
        long long rightBound = TBiggestInt::BASE;
        while (leftBound <= rightBound) {
            long long middle = (leftBound + rightBound) / 2;
            TBiggestInt tmp = rhs * middle;
            if (tmp <= curr) {
                currResDigit = middle;
                leftBound = middle + 1;
            }
            else {
                rightBound = middle - 1;
            }   
        }

        res.digits.insert(std::begin(res.digits), currResDigit);
        curr = curr - rhs * currResDigit;
    }

    res.DeleteLeadingZeros();
    return res;

}

TBiggestInt TBiggestInt::Pow(const TBiggestInt & degree) const {
    if (*this == 0 && degree == 0) {
        throw std::logic_error("Error: 0^0 is uncertain");
    }

    if (degree == 0) {
        return TBiggestInt("1");
    }

    TBiggestInt res;
    if (degree % 2 == 0) {
        res = this->Pow(degree / 2);
        return res * res;
    }

    res = this->Pow(degree - 1);
    return (*this) * res;
}

// Operators for long longs

bool isValidShortNumber(const long long & rhs, const int base) {
    return rhs < base;
}

TBiggestInt TBiggestInt::operator-(const long long & rhs) const {
    if (!isValidShortNumber(rhs, BASE)) {
        throw std::runtime_error("Error: invalid short number " + std::to_string(rhs) + " in operator-");
    }

    if (Size() == 1 && digits[0] < rhs) {
        throw std::logic_error("Error: trying to subtract bigger number from smaller");
    }

    TBiggestInt res = *this;
    int idx = 0;
    res.digits[0] -= rhs;
    while (res.digits[idx] < 0) {
        --res.digits[idx + 1];
        res.digits[idx++] += BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator*(const long long & rhs) const {
    if (!isValidShortNumber(rhs, BASE)) {
        throw std::runtime_error("Error: invalid short number " + std::to_string(rhs) + " in operator*");
    }

    TBiggestInt res(Size());
    long long carry = 0;
    for (size_t i = 0; i < Size() || carry > 0; ++i) {
        long long currDigit = carry;
        if (i == Size()) {
            res.digits.push_back(0);
        } else {
            currDigit += digits[i] * rhs;
        }
        res.digits[i] = currDigit % TBiggestInt::BASE;
        carry = currDigit / TBiggestInt::BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator/(const long long & rhs) const {
    if (!isValidShortNumber(rhs, BASE)) {
        throw std::runtime_error("Error: invalid short number " + std::to_string(rhs) + " in operator/");
    }

    TBiggestInt res(Size());
    long long carry = 0;
    for (size_t i = Size() - 1; i < Size(); --i) {
        long long currDigit = carry * TBiggestInt::BASE + digits[i];
        res.digits[i] = currDigit / rhs;
        carry = currDigit % rhs;
    }
    res.DeleteLeadingZeros();
    return res;
}

long long TBiggestInt::operator%(const long long & rhs) const {
    if (!isValidShortNumber(rhs, BASE)) {
        throw std::runtime_error("Error: invalid short number " + std::to_string(rhs) + " in operator%");
    }

    long long carry = 0;
    for (size_t i = Size() - 1; i < Size(); --i) {
        carry = ( carry * TBiggestInt::BASE + digits[i] ) % rhs;
    }
    return carry;
}

// Comparasion operators

bool TBiggestInt::operator< (const TBiggestInt & rhs) const {
    if (Size() != rhs.Size()) {
        return Size() < rhs.Size();
    }

    for (size_t i = Size() - 1; i < Size(); --i) { 
        if (digits[i] != rhs.digits[i]) {
            return digits[i] < rhs.digits[i];
        }
    }

    return false; 
}

bool TBiggestInt::operator<= (const TBiggestInt & rhs) const {
    return !(*this > rhs);
}

bool TBiggestInt::operator> (const TBiggestInt & rhs) const {
    if (Size() != rhs.Size()) {
        return Size() > rhs.Size();
    }

    for (size_t i = Size() - 1; i < Size(); --i) { 
        if (digits[i] != rhs.digits[i]) {
            return digits[i] > rhs.digits[i];
        }
    }

    return false; 
}

bool TBiggestInt::operator==(const long long & rhs) const {
    if (Size() != 1) {
        return false;
    }
    return digits.back() == rhs;
}

bool TBiggestInt::operator==(const TBiggestInt & rhs) const {
    if (Size() != rhs.Size()) {
        return false;
    }

    for (size_t i = Size() - 1; i < Size(); --i) { 
        if (digits[i] != rhs.digits[i]) {
            return false;
        }
    }

    return true;
}

} // namespace NBiggestInt