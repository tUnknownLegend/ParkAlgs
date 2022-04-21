#include <iostream>
#include<cassert>
#include <cstring>

//  time complexity O(N * logK)
//  space complexity O(K)

template<class T>
class Buffer {
public:
    Buffer();

    explicit Buffer(int initSize);

    ~Buffer();

    //Buffer &operator=(const Buffer &data);

    void Insert(const T &data);

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

/*
template<class T>
Buffer<T> &Buffer<T>::operator=(const Buffer &data) {
    if (bufferSize > 0) {
        T *tmp = buffer;
        buffer = nullptr;
        delete[] tmp;
    }
    buffer = data.buffer;
    bufferSize = data.bufferSize;
    size = data.size;

    return *this;
}
*/
template<class T>
void Buffer<T>::Insert(const T &data) {
    if (bufferSize <= size)
        renew();

    buffer[size] = data;
    ++size;
}


template<class T>
T *Buffer<T>::renew() {
    T *transBuffer = new int[2 * bufferSize];

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
class CompareLess {
public:
    bool operator()(const T &l, const T &r) { return l < r; }
};

template<class T, class Compare = CompareLess<T> >
class Heap {
public:
    Heap(Compare cmp = CompareLess<T>());

    Heap(T *arr, int size, Compare cmp = CompareLess<T>());

    ~Heap();

    T ExtractMax();

    const T &PeekMax() const;

    void Insert(const T &el);

    int Size() const;

private:
    void siftDown(int index);

    void siftUp(int index);

    void buildHeap();

    T *renew();

    T *buffer;
    int size;
    int bufferSize;
    Compare cmp;
};

template<class T, class Compare>
Heap<T, Compare>::Heap(Compare _cmp) {
    buffer = nullptr;
    size = 0;
    bufferSize = 0;
    cmp = _cmp;
}

template<class T, class Compare>
Heap<T, Compare>::Heap(T *arr, int _size, Compare _cmp) {
    bufferSize = size = _size;
    //buffer = new T[bufferSize];
    //size = _size;
    cmp = _cmp;

    //buffer = arr;

    buffer = new T[bufferSize];

    if (std::is_trivially_copyable<T>::value) {
        memcpy(buffer, arr, bufferSize * sizeof(T));
    } else //  if not trivially copyable
        for (int i = 0; i < bufferSize; ++i)
            buffer[i] = arr[i];

    buildHeap();
}

template<class T, class Compare>
Heap<T, Compare>::~Heap() {
    if (bufferSize > 0)
        delete[] buffer;

    bufferSize = size = 0;
}

template<class T, class Compare>
T Heap<T, Compare>::ExtractMax() {
    assert(size);

    T result = buffer[0];

    buffer[0] = buffer[size - 1];
    --size;

    if (size) {
        siftDown(0);
    }

    return result;
}

template<class T, class Compare>
const T &Heap<T, Compare>::PeekMax() const {
    assert(size);
    return buffer[0];
}

template<class T, class Compare>
T *Heap<T, Compare>::renew() {
    T *transBuffer = new T[2 * bufferSize];

    if (std::is_trivially_copyable<T>::value) {
        memcpy(transBuffer, buffer, bufferSize * sizeof(T));
    } else //  if not trivially copyable
        for (int i = 0; i < bufferSize; ++i)
            transBuffer[i] = buffer[i];

    T *tmpBuffer = buffer;
    buffer = transBuffer;
    delete[] tmpBuffer;
    bufferSize *= 2;

    return buffer;
}

template<class T, class Compare>
void Heap<T, Compare>::Insert(const T &el) {
    if (bufferSize <= size)
        renew();

    buffer[size] = el;
    siftUp(size);
    ++size;
}

template<class T, class Compare>
void Heap<T, Compare>::siftDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < size && cmp(buffer[left], buffer[largest]))
        largest = left;
    if (right < size && cmp(buffer[right], buffer[largest]))
        largest = right;

    while (largest != index) {
        std::swap(buffer[index], buffer[largest]);
        index = largest;

        left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < size && cmp(buffer[left], buffer[largest]))
            largest = left;
        if (right < size && cmp(buffer[right], buffer[largest]))
            largest = right;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::siftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (!cmp(buffer[index], buffer[parent]))
            return;
        std::swap(buffer[index], buffer[parent]);
        index = parent;
    }
}

template<class T, class Compare>
void Heap<T, Compare>::buildHeap() {
    for (int i = size / 2 - 1; i >= 0; --i) {
        siftDown(i);
    }
}

template<class T, class Compare>
int Heap<T, Compare>::Size() const {
    return size;
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


