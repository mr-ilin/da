//
//  vector.cpp
//  Lab1_xcode
//
//  Created by Илья Ильин on 21.09.2020.
//

#include <stdlib.h>

namespace NVector {
    template<class T>
    class TVector{
    public:
        TVector();
        TVector(size_t size);
        TVector(size_t size, const T & initial);
        TVector(const TVector<T> & vector);
        ~TVector();
        
        T* Begin();
        T* End();
        
        size_t Capacity() const;
        size_t Size() const;
        bool Empty() const;
        
        void PushBack(const T & value);
        T PopBack();
        T & operator[](size_t idx);
        T operator[](size_t idx) const;
        bool operator<(const T& rhs) const;
        void Copy(TVector<T> & vector);

    private:
        size_t capacity_;
        size_t size_;
        T *buffer_;
    };
    
    // TVector
    template<class T>
    TVector<T>::TVector() :
        capacity_(0),
        size_(0),
        buffer_(nullptr)
    {}
    
    template<class T>
    T* TVector<T>::Begin() {
        return buffer_;
    }
    
    template<class T>
    T* TVector<T>::End() {
        if(buffer_) {
            return buffer_ + size_;
        }
        return nullptr;
    }
    
    template<class T>
    TVector<T>::TVector(size_t size) :
        TVector()
    {
        if (size < 0) {
            throw "Error: size of vector cannot be less then zero";
        }
        buffer_ = new T[size];
        size_ = size;
        capacity_ = size;
    }

    template<class T>
    TVector<T>::TVector(size_t size, const T & initial) :
        TVector()
    {
        if (size < 0) {
            throw "Error: size of vector cannot be less then zero";
        }
        
        capacity_ = size;
        size_ = size;
        buffer_ = new T[size];
        
        for (size_t i = 0; i < size; ++i) {
            buffer_[i] = initial;
        }
    }
    template<class T>
    TVector<T>::TVector(const TVector<T> & vector)
        : capacity_(vector.Capacity()),
        size_(vector.Size()),
        buffer_(new T[vector.Size()])
    {
        for (size_t i = 0; i < vector.Size(); ++i) {
            buffer_[i] = vector[i];
        }
    }
    
    template<class T>
    TVector<T>::~TVector() {
        delete [] buffer_;
        
        capacity_ = 0;
        size_ = 0;
        buffer_ = nullptr;
    }
    
    template<class T>
    size_t TVector<T>::Capacity() const {
        return capacity_;
    }
    template<class T>
    size_t TVector<T>::Size() const {
        return size_;
    }
    template<class T>
    bool TVector<T>::Empty() const {
        return (size_ == 0);
    }
    
    template<class T>
    void TVector<T>::PushBack(const T & value) {
        if (size_ < capacity_) {
            buffer_[size_] = value;
            ++size_;
            return;
        }
        
        const size_t capacityMultiplier = 2;
        size_t newCapacity = 1;
        if (capacity_ != 0) {
            newCapacity = capacity_ * capacityMultiplier;
        }
        
        T* newBuffer = new T[newCapacity];
        if (buffer_) {
            for (int i = 0; i < size_; ++i) {
                newBuffer[i] = buffer_[i];
            }
            delete[] buffer_;
        }
        
        buffer_ = newBuffer;
        capacity_ = newCapacity;
        ++size_;
        buffer_[size_ - 1] = value;
    }
    
    template<class T>
    T TVector<T>::PopBack() {
        if (size_ == 1) {
            T to_return = buffer_[0];
            delete[] buffer_;
            buffer_ = nullptr;
            capacity_ = 0;
            size_ = 0;
            return to_return;
        } else if (size_ > 1) {
            T to_return = buffer_[size_ - 1];
            const size_t capacityMultiplier = 2;
            --size_;
            if (size_ * 2 < capacity_) {
                capacity_ /= capacityMultiplier;
                T* newBuffer = new T[capacity_];
                for (int i = 0; i < size_; ++i) {
                    newBuffer[i] = buffer_[i];
                }
                delete[] buffer_;
                buffer_ = newBuffer;
            }
            return to_return;
        }
    }
    
    template<class T>
    T & TVector<T>::operator[](size_t idx) {
        if (idx > size_ || idx < 0 ) {
            throw "Error: index out of bounds";
        }
        return buffer_[idx];
    }
    
    template<class T>
    T TVector<T>::operator[](size_t idx) const{
        if (idx > size_ || idx < 0 ) {
            throw "Error: index out of bounds";
        }
        return buffer_[idx];
    }
    
    template<class T>
    void TVector<T>::Copy(TVector<T> & vector) {
        if (size_ != vector.Size()) {
            delete[] buffer_;
            size_ = vector.Size();
            buffer_ = new T[size_];
        }
        capacity_ = vector.Capacity();
        if (buffer_) {
            for (size_t i = 0; i < size_; ++i) {
                buffer_[i] = vector[i];
            }
        }
    }
} // namespace NVector
