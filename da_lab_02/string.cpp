#include "string.hpp"

// Конструкторы
TString::TString()
    : buffer(nullptr),
    size(0),
    capacity(0)
{}

TString::TString(const char* str) {
    size = std::strlen(str);
    capacity = size + 1;
    buffer = new char[capacity]{'\0'};
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = str[i];
    }
}

TString::TString(const TString& str) {
    size = str.size;
    capacity = str.capacity;
    buffer = new char[capacity]{'\0'};
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = str[i];
    }
}

TString::TString(TString&& str) noexcept
    : buffer(str.buffer),
    size(str.size),
    capacity(str.capacity)
{
    str.buffer = nullptr;
    str.size = 0;
    str.capacity = 0;
}

TString::TString(char* & str, size_t s, size_t cap)
    : buffer(str),
    size(s),
    capacity(cap)
{
    str = nullptr;
}

// Деструктор
TString::~TString() {
    if (buffer) {
        delete[] buffer;
    }
    size = 0;
    capacity = 0;
}

char* TString::begin() {
    return buffer;
}
const char* TString::begin() const{
    return buffer;
}

char* TString::end() {
    if (buffer) {
        return buffer + size;
    }
    return nullptr;
}
const char* TString::end() const{
    if (buffer) {
        return buffer + size;
    }
    return nullptr;
}

// Обмен
void TString::Swap(TString& str) {
    std::swap(size, str.size);
    std::swap(capacity, str.capacity);
    std::swap(buffer, str.buffer);
}

// Метод получения размера
size_t TString::Size() const {
    return size;
}

const char* TString::Buffer() const {
    return this->buffer;
}

// Приведение к верхнему регистру
void TString::ToUpperCase() {
    for(size_t i = 0; i < this->size; ++i) {
        this->buffer[i] = std::toupper(this->buffer[i]);
    }
}

// Перегрузки стандартных операторов
char& TString::operator[](size_t idx) {
    return buffer[idx];
}
const char& TString::operator[](size_t idx) const {
    return buffer[idx];
}

// Оператор присваивания
TString& TString::operator=(const TString& rhs) {
    if (this->buffer) {
        delete[] buffer;
    }
    this->buffer = new char[rhs.capacity]{'\0'};
    std::copy(rhs.buffer, rhs.buffer + rhs.capacity, this->buffer);
    this->capacity = rhs.capacity;
    this->size = rhs.size;
    return *this;
}

TString& TString::operator=(TString&& rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }
    
    delete[] buffer;
    buffer = rhs.buffer;
    size = rhs.size;
    capacity = rhs.capacity;
    
    rhs.buffer = nullptr;
    rhs.size = 0;
    rhs.capacity = 0;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TString& lhs) {
    if (lhs.buffer) {
        os << lhs.buffer;
    }
    return os;
}
std::istream& operator>>(std::istream& is, TString& lhs) {
    if (!lhs.buffer) {
        lhs.buffer = new char[257]{'\0'};
        lhs.capacity = 257;
    }

    is >> lhs.buffer;
    size_t size = 0;
    while(lhs.buffer[size] != '\0') {
        ++size;
    }
    lhs.size = size;
    return is;
}

bool operator<(const TString& lhs, const TString& rhs) {
    size_t minSize = std::min(lhs.Size(), rhs.Size());
    for (size_t i = 0; i < minSize; ++i) {
        if (lhs[i] != rhs[i]) {
            return (lhs[i] < rhs[i]);
        }
    }
    return (lhs.Size() < rhs.Size());
}

bool operator>(const TString& lhs, const TString& rhs) {
    return (rhs < lhs);
}

bool operator==(const TString& lhs, const TString& rhs) {
    if (lhs.Size() != rhs.Size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.Size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const TString& lhs, const TString& rhs) {
    return !(lhs == rhs);
}
