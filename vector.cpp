#include <iostream>
#include <iterator>

template <typename T>
class Vector {
    public:
        class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
            public:
                Iterator() : _iter{nullptr} {}
                Iterator(T* rhs) : _iter{rhs} {}
                Iterator(const Iterator& rhs) : _iter{rhs._iter} {}
            public:
                Iterator& operator=(T* rhs) { _iter = rhs; return *this; }
                Iterator& operator=(const Iterator& rhs) { _iter = rhs._iter; return *this; }
                Iterator& operator+=(const std::size_t& rhs) { _iter += rhs; return *this; }
                Iterator& operator-=(const std::size_t& rhs) { _iter -= rhs; return *this; }
                Iterator operator+(const Iterator& rhs) { return Iterator(_iter + rhs._iter); }
                Iterator operator-(const Iterator& rhs) { return Iterator(_iter - rhs._iter); }
                Iterator operator+(const std::size_t& rhs) { return Iterator(_iter + rhs); }
                Iterator operator-(const std::size_t& rhs) { return Iterator(_iter - rhs); }
                friend Iterator operator+(const std::size_t& lhs, const Iterator& rhs) { return lhs + rhs._iter; }
                friend Iterator operator-(const std::size_t& lhs, const Iterator& rhs) { return lhs - rhs._iter; }
                Iterator& operator++() { ++_iter; return *this; }
                Iterator& operator--() { --_iter; return *this; }
                Iterator operator++(int) { Iterator tmp(*this); ++_iter; return tmp; }
                Iterator operator--(int) { Iterator tmp(*this); --_iter; return tmp; }
                T& operator*() { return *_iter; } // dereference
                T* operator->() { return _iter; }
                T& operator[](std::size_t index) { return _iter[index]; }
                bool operator==(const Iterator& rhs) const { return _iter == rhs._iter; }
                bool operator!=(const Iterator& rhs) const { return _iter != rhs._iter; }
                bool operator>(const Iterator& rhs) const { return _iter > rhs._iter; }
                bool operator<(const Iterator& rhs) const { return _iter < rhs._iter; }
                bool operator>=(const Iterator& rhs) const { return _iter >= rhs._iter; }
                bool operator<=(const Iterator& rhs) const { return _iter <= rhs._iter; }
            private:
                T* _iter;
        };
    public:
        ~Vector() { delete[] _arr; }
        Vector();
        Vector(std::size_t cap);
        Vector(std::initializer_list<T>& list);
        Vector(const Vector<T>& oth);
        Vector(Vector<T>&& oth);
        template <typename E>
        Vector(const Vector<E>& oth);
    public:
        Vector<T>& operator=(const Vector<T>& rhs);
        Vector<T>& operator=(Vector<T>&& rhs);
        template<typename E>
        Vector<T>& operator=(const Vector<E>& rhs);
        T& operator[](std::size_t index) { return _arr[index]; }
    public:
        void push_back(T value);
        void pop_back();
        void insert(T value, std::size_t index);
        void insert(std::initializer_list<T>& value, std::size_t index);
        void erase(std::size_t index);
        bool empty();
        void reserve(std::size_t cap);
        std::size_t size() const { return _size; }
        std::size_t capacity() const { return _capacity; }
        Iterator begin() const { return _begin; }
        Iterator end() const { return _end; }
    private:
        void copy();
    private:
        Iterator _begin;
        Iterator _end;
        std::size_t _size;
        std::size_t _capacity;
        T* _arr;
};


// SPECIALIZATION
template <>
class Vector<bool> {
    public:
        class Iterator : public std::iterator<std::random_access_iterator_tag, bool> {
            public:
                Iterator() : _iter{nullptr} {}
                Iterator(bool* rhs) : _iter{rhs} {}
                Iterator(const Iterator& rhs) : _iter{rhs._iter} {}
            public:
                Iterator& operator=(bool* rhs) { _iter = rhs; return *this; }
                Iterator& operator=(const Iterator& rhs) { _iter = rhs._iter; return *this; }
                Iterator& operator+=(const std::size_t& rhs) { _iter += rhs; return *this; }
                Iterator& operator-=(const std::size_t& rhs) { _iter -= rhs; return *this; }
                Iterator& operator++() { ++_iter; return *this; }
                Iterator& operator--() { --_iter; return *this; }
                Iterator operator++(int) { Iterator tmp(*this); ++_iter; return *this; }
                Iterator operator--(int) { Iterator tmp(*this); --_iter; return *this; }
                bool& operator*() { return *_iter; } // dereference
                bool* operator->() { return _iter; }
                bool& operator[](std::size_t index) { return _iter[index]; }
                bool operator==(const Iterator& rhs) const { return _iter == rhs._iter; }
                bool operator!=(const Iterator& rhs) const { return _iter != rhs._iter; }
                bool operator>(const Iterator& rhs) const { return _iter > rhs._iter; }
                bool operator<(const Iterator& rhs) const { return _iter < rhs._iter; }
                bool operator>=(const Iterator& rhs) const { return _iter >= rhs._iter; }
                bool operator<=(const Iterator& rhs) const { return _iter <= rhs._iter; }
            private:
                bool* _iter;
        };
    public:
        ~Vector() { delete[] _arr; }
        Vector();
        Vector(std::size_t cap);
        Vector(const Vector<bool>& oth);
        Vector(Vector<bool>&& oth);
    public:
        Vector<bool>& operator=(const Vector<bool>& rhs);
        Vector<bool>& operator=(Vector<bool>&& rhs);
        bool operator[](std::size_t index) { return ((*_arr >> (index - 1)) & 1); }
    public:
        void push_back(bool value);
        void pop_back();
        void insert(bool value, std::size_t index);
        void erase(std::size_t index);
        bool empty() { return _capacity == 0; }
        void reserve(std::size_t cap);
        std::size_t size() const { return _size; }
        std::size_t capacity() const { return _capacity; }
        Iterator begin() const { return _begin; }
        Iterator end() const { return _end; }
    private:
        void copy();
    private:
        Iterator _begin;
        Iterator _end;
        std::size_t _size;
        std::size_t _capacity;
        unsigned long* _arr;
};

// CONSTRUCTORS FOR BOOL
Vector<bool>::Vector() : _size{}, _capacity{}, _arr{}, _begin{}, _end{} {}

Vector<bool>::Vector(std::size_t cap) : _size{cap} {
    while(cap) {
        ++_capacity;
        cap /= sizeof(long) * std::size_t(8);
    }
    _arr = new unsigned long[_capacity] {};
}

Vector<bool>::Vector(const Vector<bool>& oth) {
    _size = oth._size;
    _capacity = oth._capacity;
    _arr = new unsigned long[_capacity];
    for(std::size_t i = 0; i < _capacity; ++i) {
        _arr[i] = oth._arr[i];
    }
}

Vector<bool>::Vector(Vector<bool>&& oth) : _size{oth._size}, _capacity{oth._capacity} {
    _arr = oth._arr;
    oth._arr = nullptr;
}

// FUNCTIONS FOR BOOL
void Vector<bool>::push_back(bool value) {
    if(_capacity == std::size_t(0)) {
        _capacity = 1;
        _arr = new unsigned long[_capacity]{};
    }    
    if((sizeof(long) * std::size_t(8) * _capacity) == _size) {
        ++_capacity;
        copy();
    }
    if(value) {
        _arr[0] = _arr[0] | (std::size_t(1) << (_size - std::size_t(1)));
    } else {
        _arr[0] = _arr[0] & ~(std::size_t(1) << (_size - std::size_t(1)));
    }
    ++_size;
}

void Vector<bool>::pop_back() {
    if(_capacity > (--_size / sizeof(long) * std::size_t(8)) && _capacity > std::size_t(1)) {
        --_capacity;
        copy();
    }
    _arr[0] = _arr[0] & ~(std::size_t(1) << (_size - std::size_t(1)));
}

void Vector<bool>::insert(bool value, std::size_t index) {
    unsigned long* tmp = new unsigned long[_capacity];
    if(index >= _size || index < std::size_t(0)) {
        return;
    }
    ++_size;
    if(_capacity <= (_size / (sizeof(long) * std::size_t(8))) && _capacity > std::size_t(1)) {
        ++_capacity;
        copy();
    }
    for(std::size_t i = 0; i < index; ++i) {
        if(((*_arr >> (i)) & 1)) {
            tmp[0] = tmp[0] | (std::size_t(1) << (i));
        } else {
            tmp[0] = tmp[0] & ~(std::size_t(1) << (i));
        }
    }
    tmp[0] = value ? tmp[0] | (std::size_t(1) << (index)) : tmp[0] & ~(std::size_t(1) << (index));
    for(std::size_t i = index; i < _size; ++i) {
        if(((*_arr >> (i)) & std::size_t(1))) {
            tmp[0] = tmp[0] | (std::size_t(1) << (i + std::size_t(1)));
        } else {
            tmp[0] = tmp[0] & ~(std::size_t(1) << (i + std::size_t(1)));
        }
    }
    delete[] _arr;
    _arr = tmp;
    tmp = nullptr;
}

void Vector<bool>::erase(std::size_t index) {
    if(index >= _size || index < 0) {
        return;
    }
    --_size;
    if(_capacity > (_size / (sizeof(long) * std::size_t(8))) && _capacity > std::size_t(1)) {
        --_capacity;
        copy();
    }
    unsigned long* tmp = new unsigned long[_capacity];
    for(std::size_t i = 0; i < index; ++i) {
        if((*_arr >> (i)) & std::size_t(1)) {
            tmp[0] = tmp[0] | (std::size_t(1) << (i));
        } else {
            tmp[0] = tmp[0] & ~(std::size_t(1) << (i));
        }
    }
    for(std::size_t i = index + 1; i < _size; ++i) {
        if((*_arr >> (i)) & std::size_t(1)) {
            tmp[0] = tmp[0] | (std::size_t(1) << (i - std::size_t(1)));
        } else {
            tmp[0] = tmp[0] & ~(std::size_t(1) << (i - std::size_t(1)));
        }
    }
    delete[] _arr;
    _arr = tmp;
    tmp = nullptr;
}

void Vector<bool>::reserve(std::size_t cap) {
    _size = cap;
    if(cap < std::size_t(8) * sizeof(long)) {
        _capacity = std::size_t(1);
    }
    while(cap > std::size_t(8) * sizeof(long)) {
        ++_capacity;
        cap /= std::size_t(8);
    }
    copy();
}

// PRIVATE FUNCTIONS FOR BOOL
void Vector<bool>::copy() {
    if(_arr == nullptr) {
        _arr = new unsigned long[_capacity];
    } else {
        unsigned long* tmp = new unsigned long[_capacity] {0};
        for(std::size_t i = 0; i < _capacity; ++i) {
            tmp[i] = _arr[i];
        }
        delete[] _arr;
        _arr = tmp;
        tmp = nullptr;
    }
}

// CONSTRUCTORS
template <typename T>
Vector<T>::Vector() : _size{}, _capacity{}, _arr{}, _begin{}, _end{} {}

template <typename T>
Vector<T>::Vector(std::size_t cap) : _size{cap}, _capacity{cap} {
    _arr = new T[_capacity] {};
    _begin = _arr;
    _end = _arr + _size;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T>& list) {
    _size = _capacity = list.size();
    _arr = new T[_capacity];
    _begin = _arr;
    _end = _arr + _size;
    auto j = list.begin();
    for(int i = 0; i < _size; ++i, ++j) {
        _arr[i] = *j;
    }
}

template<typename T>
Vector<T>::Vector(const Vector<T>& oth) : _size{oth._size}, _capacity{oth._capacity} {
    _arr = new T[_capacity];
    for(std::size_t i = 0; i < _size; ++i) {
        _arr[i] = oth._arr[i];
    }
    _begin = _arr;
    _end = _arr + (_size - std::size_t(1));
}

template<typename T>
Vector<T>::Vector(Vector<T>&& oth) : _size{oth._size}, _capacity{oth._capacity}  {
    _arr = oth._arr;
    oth._arr = nullptr;
    _begin = _arr;
    _end = _arr + (_size - std::size_t(1));
}

template<typename T>
template <typename E>
Vector<T>::Vector(const Vector<E>& oth) {
    _size = oth.size();
    _capacity = oth.capacity();
    _arr = new T[_capacity];
    for(std::size_t i = 0; i < _size; ++i) {
        _arr[i] = oth[i];
    }
    _begin = _arr;
    _end = _arr + (_size - std::size_t(1));
}

// OPERATORS
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
    _size = rhs._size;
    _capacity = rhs._capacity;
    delete[] _arr;
    _arr = new T[_capacity];
    for(std::size_t i = 0; i < _size; ++i) {
        _arr[i] = rhs._arr[i];
    }
    _begin = _arr;
    _end = _arr + (_size - std::size_t(1));
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhs) {
    _size = rhs._size;
    _capacity = rhs._capacity;
    delete[] _arr;
    _arr = rhs._arr;
    rhs._arr = nullptr;
    _begin = _arr;
    _end = _arr + (_size - std::size_t(1));
}

template<typename T>
template<typename E>
Vector<T>& Vector<T>::operator=(const Vector<E>& rhs) {
    _size = rhs._size;
    _capacity = rhs._capacity;
    delete[] _arr;
    _arr = new T[_capacity];
    for(std::size_t i = 0; i < _size; ++i) {
        _arr[i] = rhs[i];
    }
    _begin = _arr;
    _end = _arr + (_size - std::size_t(1));
}

// FUNCTIONS
template<typename T>
void Vector<T>::push_back(T value) {
    if(_capacity == std::size_t(0)) {
        _capacity = std::size_t(2);
        _arr = new T[_capacity];
        _begin = _arr;
        _end = _arr + std::size_t(1);
    }
    if(_size == _capacity) {
        _capacity *= std::size_t(2);
        copy();
    }
    _arr[_size] = value;
    _end += 1;
    ++_size;
}

template<typename T>
void Vector<T>::pop_back() {
    if((_capacity / std::size_t(2)) == _size) {
        _capacity /= std::size_t(2);
        copy();
    }
    --_size;
    _arr[_size] = {};
}

template<typename T>
void Vector<T>::insert(T value, std::size_t index) {
    if(index < std::size_t(0) || index > _size) {
        return;
    }
    if(_capacity == _size) {
        _capacity *= std::size_t(2);
        copy();
    }
    for(std::size_t i = _size - std::size_t(1); i > index; --i) {
        T tmp = _arr[i];
        _arr[i] = _arr[i - 1];
        _arr[i - 1] = tmp;
    }
    _arr[index] = value;
    _end += 1;
    ++_size;
}

template<typename T>
void Vector<T>::insert(std::initializer_list<T>& value, std::size_t index)  {
    if(index < std::size_t(0) || index > _size) {
        return;
    }
    _size += value.size();
    if(_capacity <= _size) {
        _capacity = _size;
        copy();
    }
    int j = value.size();
    while(j) {
        for(std::size_t i = _size - std::size_t(1); i > index; --i) {
            T tmp = _arr[i];
            _arr[i] = _arr[i - 1];
            _arr[i - 1] = tmp;
        }
        --j;
    }
    auto z = value.begin();
    for(int i = index; z < value.end(); ++i, ++z) {
        _arr[i] = *z;
    }
}

template<typename T>
void Vector<T>::erase(std::size_t index) {
    if(index > _size || index < std::size_t(0)) {
        return;
    }
    if((_capacity / std::size_t(2)) == _size) {
        _capacity /= std::size_t(2);
        copy();
    }
    T* tmp = new T[_capacity];
    for(std::size_t i = 0; i < index; ++i) {
        tmp[i] = _arr[i];
    }
    for(std::size_t i = index + std::size_t(1); i < _size; ++i) {
        tmp[i - 1] = _arr[i];
    }
    delete[] _arr;
    _arr = tmp;
    tmp = nullptr;
    --_size;
    _begin = _arr;
    _end = _arr + _size;
}

template<typename T>
void Vector<T>::reserve(std::size_t cap) {
    _size = _capacity = cap;
    copy();
}

template<typename T>
bool Vector<T>::empty() {
    return _size != std::size_t(0);
}

// PRIVATE FUNCTION
template<typename T>
void Vector<T>::copy() {
    T* tmp = new T[_capacity] {0};
    for(std::size_t i = 0; i < _size; ++i) {
        tmp[i] = _arr[i];
    }
    delete[] _arr;
    _arr = tmp;
    _begin = _arr;
    _end = _arr + _size;
    tmp = nullptr;
}
