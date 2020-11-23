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
        void Copy(TVector<T> & vector);

    private:
        size_t bufferSize;
        size_t bufferUsed;
        T *buffer;
    };
    
    // TVector
    template<class T>
    TVector<T>::TVector() :
        bufferSize(0),
        bufferUsed(0),
        buffer(nullptr)
    {}
    
    template<class T>
    T* TVector<T>::Begin() {
        return buffer;
    }
    
    template<class T>
    T* TVector<T>::End() {
        if(buffer) {
            return buffer + bufferUsed;
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
        buffer = new T[size];
        bufferUsed = size;
        bufferSize = size;
    }

    template<class T>
    TVector<T>::TVector(size_t size, const T & initial) :
        TVector()
    {
        if (size < 0) {
            throw "Error: size of vector cannot be less then zero";
        }
        
        bufferSize = size;
        bufferUsed = size;
        buffer = new T[size];
        
        for (size_t i = 0; i < size; ++i) {
            buffer[i] = initial;
        }
    }
    template<class T>
    TVector<T>::TVector(const TVector<T> & vector)
        : bufferSize(vector.Capacity()),
        bufferUsed(vector.Size()),
        buffer(new T[vector.Size()])
    {
        for (size_t i = 0; i < vector.Size(); ++i) {
            buffer[i] = vector[i];
        }
    }
    
    template<class T>
    TVector<T>::~TVector() {
        delete [] buffer;
        
        bufferSize = 0;
        bufferUsed = 0;
        buffer = nullptr;
    }
    
    template<class T>
    size_t TVector<T>::Capacity() const {
        return bufferSize;
    }
    template<class T>
    size_t TVector<T>::Size() const {
        return bufferUsed;
    }
    template<class T>
    bool TVector<T>::Empty() const {
        return (bufferUsed == 0);
    }
    
    template<class T>
    void TVector<T>::PushBack(const T & value) {
        if (bufferUsed < bufferSize) {
            buffer[bufferUsed] = value;
            ++bufferUsed;
            return;
        }
        
        const size_t capacityMultiplier = 2;
        size_t newCapacity = 1;
        if (bufferSize != 0) {
            newCapacity = bufferSize * capacityMultiplier;
        }
        
        T* newBuffer = new T[newCapacity];
        if (buffer) {
            for (int i = 0; i < bufferUsed; ++i) {
                newBuffer[i] = buffer[i];
            }
            delete[] buffer;
        }
        
        buffer = newBuffer;
        bufferSize = newCapacity;
        ++bufferUsed;
        buffer[bufferUsed - 1] = value;
    }
    
    template<class T>
    T TVector<T>::PopBack() {
        if (bufferUsed == 1) {
            T to_return = buffer[0];
            delete[] buffer;
            buffer = nullptr;
            bufferSize = 0;
            bufferUsed = 0;
            return to_return;
        } else if (bufferUsed > 1) {
            T to_return = buffer[bufferUsed - 1];
            const size_t capacityMultiplier = 2;
            --bufferUsed;
            if (bufferUsed * 2 < bufferSize) {
                bufferSize /= capacityMultiplier;
                T* newBuffer = new T[bufferSize];
                for (int i = 0; i < bufferUsed; ++i) {
                    newBuffer[i] = buffer[i];
                }
                delete[] buffer;
                buffer = newBuffer;
            }
            return to_return;
        }
    }
    
    template<class T>
    T & TVector<T>::operator[](size_t idx) {
        if (idx > bufferUsed || idx < 0 ) {
            throw "Error: index out of bounds";
        }
        return buffer[idx];
    }
    
    template<class T>
    T TVector<T>::operator[](size_t idx) const{
        if (idx > bufferUsed || idx < 0 ) {
            throw "Error: index out of bounds";
        }
        return buffer[idx];
    }
    
    template<class T>
    void TVector<T>::Copy(TVector<T> & vector) {
        if (bufferUsed != vector.Size()) {
            delete[] buffer;
            bufferUsed = vector.Size();
            buffer = new T[bufferUsed];
        }
        bufferSize = vector.Capacity();
        if (buffer) {
            for (size_t i = 0; i < bufferUsed; ++i) {
                buffer[i] = vector[i];
            }
        }
    }
} // namespace NVector
