#include "string.hpp"

// Конструкторы
TString::TString() : 
    buffer(nullptr),
    size(0),
    capacity(0)
{}

TString::TString(const char* str) {
    size = std::strlen(str);
    capacity = size + 1;
    buffer = new char[capacity];
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = str[i];
    }
    buffer[size] = '\0';
}

TString::TString(const TString& str) {
    size = str.size;
    capacity = str.capacity;
    buffer = new char[capacity];
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = str[i];
    }
    buffer[size] = '\0';
}

TString::TString(TString&& str) noexcept:
    buffer(std::move(str.buffer)),
    size(std::move(str.size)),
    capacity(std::move(str.capacity))
{}

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

// Перемещение
void TString::Move(char* str) noexcept {
    delete[] buffer;
    buffer = str;
    size = std::strlen(str);
    capacity = size + 1;
    str = nullptr;
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

std::ostream& operator<<(std::ostream& os, const TString& lhs) {
    if (lhs.buffer) {
        os << lhs.buffer;
    }
    return os;
}
std::istream& operator>>(std::istream& is, TString& lhs) {
    if (lhs.buffer) {
        delete[] lhs.buffer;
    }

    lhs.buffer = new char[256]{'\0'};
    lhs.capacity = 256;

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
