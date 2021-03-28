#include "biggest_int.hpp"
#include <algorithm>
#include <sstream>

namespace NBiggestInt {

TBiggestInt::TBiggestInt(const std::string & str) {
    this->Initialize(str);
}

TBiggestInt::TBiggestInt(const size_t & length, const long long & value) 
    : digits(length, value)
{}

void TBiggestInt::Initialize(const std::string & str) {
    long long startIdx = 0;
    while (startIdx < str.size() && str[startIdx] == '0') {
        ++startIdx;
    }
    if (startIdx == str.size()) {
        digits.push_back(0);
        return;
    }

    digits.clear();
    size_t digitsSize = (str.size() - startIdx) / RADIX;
    if ((str.size() - startIdx) % RADIX != 0) {
        ++digitsSize;
    }
    digits.resize(digitsSize);

    size_t digitsCount = 0;
    for (long long i = str.size() - 1; i >= startIdx; i -= RADIX) {
        long long currDigit = 0;
        long long digitStart = i - RADIX + 1;
        if (digitStart < 0 || digitStart <= startIdx) {
            digitStart = 0;
        }
        for (long long j = digitStart; j <= i; ++j) {
            currDigit = currDigit * 10 + str[j] - '0';
        }

        digits[digitsCount] = currDigit;
        ++digitsCount;
    }
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
    os << rhs.digits[rhs.Size()- 1];
    for (long long i = rhs.Size() - 2; i >= 0; --i) {
        os << std::setfill('0') << std::setw(TBiggestInt::RADIX) << rhs.digits[i]; 
    }
    return os;
}

std::string TBiggestInt::GetString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
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
        carry = sum / BASE;
        res.digits[i] = sum % BASE;
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
            diff += BASE;
        } else {
            carry = 0;
        }
        res.digits[i] = diff % BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator*(const TBiggestInt & rhs) const {
    TBiggestInt res(Size() + rhs.Size());
    for (size_t i = 0; i < Size(); ++i) {
        long long carry = 0;
        for (size_t j = 0; j < rhs.Size() || carry > 0; ++j) {
            long long current = res.digits[i + j] + carry;
            if (j < rhs.Size()) {
                current += digits[i] * rhs.digits[j];
            }
            res.digits[i + j] = current % BASE;
            carry = current / BASE;
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
        long long rightBound = BASE;
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

    TBiggestInt res("1");
    if (degree == 0) {
        return res;
    }

    TBiggestInt curr = *this;
    TBiggestInt currDegree = degree;
    while (currDegree > 0) {
        if (currDegree.digits.back() % 2 != 0) {
            res = res * curr;
        }

        curr = curr * curr;
        currDegree = currDegree / 2;
    }
    return res;
}

// Operators for long longs

TBiggestInt TBiggestInt::operator-(const long long & rhs) const {
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
    TBiggestInt res(Size());
    long long carry = 0;
    for (size_t i = 0; i < Size() || carry > 0; ++i) {
        long long currDigit = carry;
        if (i == Size()) {
            res.digits.push_back(0);
        } else {
            currDigit += digits[i] * rhs;
        }
        res.digits[i] = currDigit % BASE;
        carry = currDigit / BASE;
    }
    res.DeleteLeadingZeros();
    return res;
}

TBiggestInt TBiggestInt::operator/(const long long & rhs) const {
    TBiggestInt res(Size());
    long long carry = 0;
    for (size_t i = Size() - 1; i < Size(); --i) {
        long long currDigit = carry * BASE + digits[i];
        res.digits[i] = currDigit / rhs;
        carry = currDigit % rhs;
    }
    res.DeleteLeadingZeros();
    return res;
}

long long TBiggestInt::operator%(const long long & rhs) const {
    long long carry = 0;
    for (size_t i = Size() - 1; i < Size(); --i) {
        carry = ( carry * BASE + digits[i] ) % rhs;
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

bool TBiggestInt::operator==(const long long & rhs) const {
    if (Size() != 1) {
        return false;
    }
    return digits.back() == rhs;
}

bool TBiggestInt::operator> (const long long & rhs) const {
    if (Size() > 1) {
        return true;
    }
    return digits.back() > rhs;
}

} // namespace NBiggestInt