#include <iostream>
#include<cassert>
#include <cstring>

/*
 * Требование для всех вариантов Задачи 4
 *  Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
 *  Решение должно поддерживать передачу функции сравнения снаружи.
 *  Куча должна быть динамической.
 *
 * Задача 4.1 Слияние массивов.
 * Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
 * Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
 * Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива.
 * Каждый массив упорядочен по возрастанию.
 * Формат выходных данных: Итоговый отсортированный массив.
 */

//  time complexity O(N * logK)
//  space complexity O(K)

template<class T>
class Buffer {
public:
    Buffer();

    explicit Buffer(int initSize);

    ~Buffer();

    Buffer &operator=(const Buffer &data);

    void Insert(const T &data);

    T *allocate(int initSize);

    T *buffer;
    int size;
private:
    T *renew();

    int bufferSize;
};

template<class T>
Buffer<T>::Buffer() {
    buffer = nullptr;
    bufferSize = 0;
    size = 0;
}

template<class T>
Buffer<T>::Buffer(int initSize) {
    buffer = new T[initSize];
    bufferSize = initSize;
    size = 0;
}

template<class T>
Buffer<T>::~Buffer() {
    if (bufferSize > 0)
        delete[] buffer;

    bufferSize = size = 0;
}


template<class T>
Buffer<T> &Buffer<T>::operator=(const Buffer &data) {
    if (data.buffer != this->buffer) {
        if (bufferSize > 0) {
            T *tmp = buffer;
            buffer = nullptr;
            delete[] tmp;
        }
        buffer = data.buffer;
        bufferSize = data.bufferSize;
        size = data.size;
        data = nullptr;
    } else {
        this->bufferSize = data.bufferSize;
        this->size = data.size;
    }

    return *this;
}

template<class T>
void Buffer<T>::Insert(const T &data) {
    if (bufferSize <= size)
        renew();

    buffer[size] = data;
    ++size;
}


template<class T>
T *Buffer<T>::renew() {
    T *transBuffer = new T[2 * bufferSize];

    if (std::is_trivially_copyable<T>::value) {
        memcpy(transBuffer, buffer, bufferSize * sizeof(T));
    } else //  if not trivially copyable
        for (int i = 0; i < bufferSize; ++i)
            transBuffer[i] = buffer[i];

    if (bufferSize > 0) {
        T *tmpBuffer = buffer;
        delete[] tmpBuffer;
    }
    buffer = transBuffer;
    bufferSize *= 2;

    return buffer;
}

template<class T>
T *Buffer<T>::allocate(const int initSize) {
    if (buffer != nullptr) {
        T *tmpBuffer = buffer;
        buffer = nullptr;
        delete[] tmpBuffer;
    }
    buffer = new T[initSize];
    bufferSize = initSize;

    return buffer;
}

template<class T>
class CompareLess {
public:
    bool operator()(const T &l, const T &r) { return l < r; }
};

template<class T, class Compare = CompareLess<T> >
class Heap {
public:
    Heap(Compare _cmp = CompareLess<T>()) : cmp(_cmp) {};

    Heap(T *arr, int size, Compare _cmp = CompareLess<T>());

    ~Heap() = default;

    Heap &operator=(const Heap &data);

    T ExtractMax();

    const T &PeekMax() const;

    void Insert(const T &el);

    int Size() const;

private:
    void siftDown(int index);

    void siftUp(int index);

    void buildHeap();

    Buffer<T> dynArr;
    Compare cmp;
};

template<class T, class Compare>
Heap<T, Compare>::Heap(T *arr, int _size, Compare _cmp) : cmp(_cmp) {
    dynArr.allocate(_size);
    if (std::is_trivially_copyable<T>::value) {
        memcpy(dynArr.buffer, arr, _size * sizeof(T));
    } else //  if not trivially copyable
        for (int i = 0; i < _size; ++i)
            dynArr.buffer[i] = arr[i];

    dynArr.size = _size;

    buildHeap();
}

template<class T, class Compare>
Heap<T, Compare> &Heap<T, Compare>::operator=(const Heap &data) {
    this->dynArr = data.dynArr;
    return *this;
}

template<class T, class Compare>
T Heap<T, Compare>::ExtractMax() {
    assert(dynArr.size);
    T result = dynArr.buffer[0];

    dynArr.buffer[0] = dynArr.buffer[dynArr.size - 1];
    --dynArr.size;

    if (dynArr.size) {
        siftDown(0);
    }

    return result;
}

template<class T, class Compare>
const T &Heap<T, Compare>::PeekMax() const {
    assert(dynArr.size);
    return dynArr.buffer[0];
}

template<class T, class Compare>
void Heap<T, Compare>::Insert(const T &el) {

    dynArr.Insert(el);
    siftUp(dynArr.size - 1);
}

template<class T, class Compare>
void Heap<T, Compare>::siftDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < dynArr.size && cmp(dynArr.buffer[left], dynArr.buffer[largest]))
        largest = left;
    if (right < dynArr.size && cmp(dynArr.buffer[right], dynArr.buffer[largest]))
        largest = right;

    while (largest != index) {
        std::swap(dynArr.buffer[index], dynArr.buffer[largest]);
        index = largest;

        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < dynArr.size && cmp(dynArr.buffer[left], dynArr.buffer[largest]))
            largest = left;
        if (right < dynArr.size && cmp(dynArr.buffer[right], dynArr.buffer[largest]))
            largest = right;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!cmp(dynArr.buffer[index], dynArr.buffer[parent]))
            return;
        std::swap(dynArr.buffer[index], dynArr.buffer[parent]);
        index = parent;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::buildHeap() {
    for (int i = dynArr.size / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}

template<class T, class Compare>
int Heap<T, Compare>::Size() const {
    return dynArr.size;
}

struct Element {
    int Value;
    int ValueIndex;
    int ArrayIndex;
};

class ElementCmp {
public:
    bool operator()(const Element &a, const Element &b) { return a.Value < b.Value; };
};

int main() {
    int amtOfArrays = 0;
    std::cin >> amtOfArrays;
    assert(amtOfArrays > 0);
    Buffer<int> arr(1);
    Buffer<int> arrSplitPoints(1);
    int arrSize = 0;
    arrSplitPoints.Insert(arrSize);

    for (int i = 0; i < amtOfArrays; ++i) {
        std::cin >> arrSize;
        assert(arrSize > 0);
        arrSplitPoints.Insert(arrSplitPoints.buffer[i] + arrSize);

        int inputVar;
        for (int j = 0; j < arrSize; ++j) {
            std::cin >> inputVar;
            arr.Insert(inputVar);
        }
    }

    Element *elements = new Element[amtOfArrays];
    for (int i = 0; i < amtOfArrays; ++i) {
        elements[i].Value = arr.buffer[arrSplitPoints.buffer[i]];
        elements[i].ArrayIndex = i;
        elements[i].ValueIndex = arrSplitPoints.buffer[i];
    }

    Heap<Element, ElementCmp> h(&elements[0], amtOfArrays, ElementCmp());

    int tempEl = -1;
    while (h.Size() > 1) {
        std::cout << h.PeekMax().Value << " ";
        tempEl = h.ExtractMax().ArrayIndex;

        if (++elements[tempEl].ValueIndex < arrSplitPoints.buffer[tempEl + 1]) {
            elements[tempEl].Value = arr.buffer[(elements[tempEl].ValueIndex)];
            h.Insert(elements[tempEl]);
        }
    }

    tempEl = h.ExtractMax().ArrayIndex;
    for (int i = elements[tempEl].ValueIndex; i < arrSplitPoints.buffer[tempEl + 1]; ++i)
        std::cout << arr.buffer[i] << " ";

    delete[] elements;
}