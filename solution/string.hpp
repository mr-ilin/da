#pragma once

#include <iostream>
#include <cstring>

class TString {
private:
    char* buffer;
    size_t size;
    size_t capacity;

public:
    TString();
    TString(const char* str);
    TString(const TString& str);
    TString(char* & str, size_t s, size_t cap);
    TString(TString&& str) noexcept;
    ~TString();

    char* begin();
    char* end();
    const char* begin() const;
    const char* end() const;

    void Swap(TString& str);
    size_t Size() const;
    const char* Buffer() const;

    void ToUpperCase();

    char& operator[](size_t idx);
    const char& operator[](size_t idx) const;
    TString& operator=(TString const& another);
    TString& operator=(TString&& another) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const TString& lhs);
	friend std::istream& operator>>(std::istream& is, TString& lhs);
};

bool operator<(const TString& lhs, const TString& rhs);
bool operator>(const TString& lhs, const TString& rhs);
bool operator==(const TString& lhs, const TString& rhs);
bool operator!=(const TString& lhs, const TString& rhs);
