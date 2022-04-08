/*
 * Задача 3
 *
 * Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
 * Формат входных данных.
 * В первой строке количество команд n. n ≤ 1000000.
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 2 - pop front
 * a = 3 - push back
 *
 * Команды добавления элемента 3 заданы с неотрицательным параметром b.
 * Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 *
 * Формат выходных данных.
 * Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
 *
 * Задача 3.1. Реализовать очередь с динамическим зацикленным буфером.
 * Требования: Очередь должна быть реализована в виде класса.
 */

// time complexity o()
// space complexity o()

#include<cassert>
#include<iostream>
#include<sstream>
#include <cstring>

#define ARRAY_INIT_SIZE 1

template<class T>
class Queue {
public:
    Queue() = default;

    Queue(const Queue &) = delete;

    ~Queue();

    Queue &operator=(const Queue &) = delete;

    void PushBack(const T &value);

    T PopFront();

    int Size() const { return sizeUsed; }

    bool IsEmpty() const { return sizeUsed == 0; }

private:
    T *Array = nullptr;
    T *head = nullptr;
    T *tail = nullptr;
    size_t sizeOfArray = 0;  //  size of allocated Array
    size_t sizeUsed = 0;  //  amount of elements storing data

    T *renew();

    T *alloc();
};

template<class T>
T *Queue<T>::renew() {
    T *array = new int[sizeOfArray * 2];
    if (std::is_trivially_copyable<T>::value) {
        if (head <= tail)
            memcpy(array, Array, sizeOfArray * sizeof(T));
        else {  //  if tail is on the left side of the array
            //  copy elements in range (head, sizeOfArray)
            memcpy(array, head, (Array + sizeOfArray - head) * sizeof(T));
            // copy elements in range (Array[0], tail)
            memcpy(array + (Array + sizeOfArray - head), Array, (tail - Array) * sizeof(T));
        }
    } else  //  if not trivially copyable
        for (int i = 0; i < sizeOfArray; ++i)
            array[i] = Array[i];

    T *tmpArray = Array;
    Array = array;
    head = Array;
    tail = Array + sizeOfArray - 1;
    delete[] tmpArray;
    sizeOfArray *= 2;

    return Array;
}


template<class T>
T *Queue<T>::alloc() {
    Array = new int[ARRAY_INIT_SIZE];
    head = Array;
    tail = Array;
    sizeOfArray = ARRAY_INIT_SIZE;

    return Array;
}

template<class T>
Queue<T>::~Queue() {
    delete[] Array;
    sizeOfArray = sizeUsed = 0;
}

template<class T>
void Queue<T>::PushBack(const T &value) {
    if (Array == nullptr)
        alloc();
    else if (sizeOfArray <= sizeUsed)
        renew();

    // if (sizeOfArray > sizeUsed)
    if (IsEmpty()) {
        *head = *tail = value;
    } else {
        if (tail != Array + sizeOfArray - 1) {
            ++tail;
            *tail = value;
        } else {
            tail = Array;
            *tail = value;
        }
    }

    ++sizeUsed;
}

template<class T>
T Queue<T>::PopFront() {
    assert(!IsEmpty());

    if (head == Array + sizeOfArray - 1) {
        head = Array;
        --sizeUsed;
        return *(Array + sizeOfArray - 1);
    }

    ++head;
    --sizeUsed;
    return *(head - 1);
}

int main() {
    Queue<int> queue;
    int n = 0;
    std::cin >> n;
    bool result = true;
    for (int i = 0; i < n; ++i) {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        switch (command) {
            case 2:
                if (!queue.IsEmpty()) {
                    result = result && queue.PopFront() == value;
                } else {
                    result = result && value == -1;
                }
                break;
            case 3:
                queue.PushBack(value);
                break;
            default:
                assert(false);
        }
    }
    std::cout << (result ? "YES" : "NO");
    return 0;
}
