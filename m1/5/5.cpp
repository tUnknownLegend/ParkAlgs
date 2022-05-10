/*
 * Требование для всех вариантов Задачи 5
 * Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Общее время работы алгоритма O(n log n).
 * 5_1. Реклама.
 * В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
 * Каждому покупателю необходимо показать минимум 2 рекламы.
 * Рекламу можно транслировать только в целочисленные моменты времени.
 * Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
 * В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
 * Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
 * Требуется определить минимальное число показов рекламы.
 */

//  time complexity O(n log n)
//  space complexity O(n)

#include <iostream>
#include <cassert>
#include <cstring>

#ifndef REQ_AMT_OF_ADS
#define REQ_AMT_OF_ADS 2
#endif

template<class T>
class CompareLess {
public:
    bool operator()(const T &l, const T &r) { return l < r; }
};

template<class T, class Compare = CompareLess<T> >
void Merge(T *arr, T *tempArr, const int arrSize, const int mid, Compare cmp = CompareLess<T>()) {
    int tempArrCounter = 0;
    int i = 0;
    int j = mid;//arrSize / 2;
    int halfArrSize = j;
    for (; i < halfArrSize && j < arrSize;) {
        if (cmp(arr[i], arr[j])) {
            *(tempArr + tempArrCounter) = *(arr + i);
            ++i;
        } else {
            *(tempArr + tempArrCounter) = *(arr + j);
            ++j;
        }
        ++tempArrCounter;
    }

    for (; i < halfArrSize;) {
        *(tempArr + tempArrCounter) = *(arr + i);
        ++i;
        ++tempArrCounter;
    }

    for (; j < arrSize;) {
        *(tempArr + tempArrCounter) = *(arr + j);
        ++j;
        ++tempArrCounter;
    }
}

template<class T>
void cpy(T *arr, T *tempArr, const int arrSize) {
    if (std::is_trivially_copyable<T>::value) {
        memcpy(arr, tempArr, arrSize * sizeof(T));
    } else //  if not trivially copyable
        for (int i = 0; i < arrSize; ++i)
            arr[i] = tempArr[i];
}

template<class T, class Compare = CompareLess<T> >
void MergeSort(T *arr, int arrSize, Compare cmp = CompareLess<T>()) {
    if (arrSize <= 1) {
        return;
    }
    T *tempArr = new T[arrSize];
    bool odd = false;
    if (arrSize % 2 == 1) {
        --arrSize;
        odd = true;
    }
    int tempArrSize = 0;
    for (int j = 2; j <= arrSize; j *= 2) {
        for (int i = 0; i <= arrSize - j; i += j) {
            Merge(&arr[i], &tempArr[i], j, j / 2, cmp);
        }

        cpy(arr, tempArr, arrSize);

        if (arrSize % j > tempArrSize) {
            Merge(&arr[arrSize - arrSize % j], &tempArr[arrSize - arrSize % j], arrSize % j, tempArrSize, cmp);
            cpy(&arr[arrSize - arrSize % j], &tempArr[arrSize - arrSize % j], arrSize % j);
        }

        tempArrSize = j;
    }

    if (odd) {
        ++arrSize;
        for (int j = arrSize - 1; j > 0 && cmp(arr[j], arr[j - 1]); --j) // arrSize % tempArrSize + 1
            std::swap(arr[j], arr[j - 1]);
    }
    if (arrSize % tempArrSize != 0) {
        Merge(&arr[0], &tempArr[0], arrSize, (arrSize - arrSize % tempArrSize), cmp);
        cpy(arr, tempArr, arrSize);
    }
    delete[] tempArr;
}

struct Buyer {
    bool operator()(const Buyer &l, const Buyer &r) { return l.out < r.out; }

    int in = -1;
    int out = -2;
    short amtOfAds = 0;
};

int main() {
    int amtOfClients = 0;
    std::cin >> amtOfClients;
    assert(amtOfClients > 0);

    Buyer *clients = new Buyer[amtOfClients];

    for (int i = 0; i < amtOfClients; ++i) {
        std::cin >> clients[i].in >> clients[i].out;
        //std::cin >> clients[i].out;
    }

    MergeSort(&clients[0], amtOfClients, Buyer());

    //std::cout << clients[0].in << " " << clients[0].out << "\n";
    assert(clients[1].out >= clients[0].out);
    for (int i = 1; i < amtOfClients; ++i) {
        //std::cout << clients[i].in << " " << clients[i].out << "\n";
        assert(clients[i].out >= clients[i - 1].out);
    }

    int amtOfAds = 0;
    int amtOfClientsSawAds = 0;
    int ind = 0;
    while (amtOfClientsSawAds != amtOfClients) {
        if (clients[ind].amtOfAds >= 2) {
            ++ind;
            continue;
        }
        for (int i = ind + 1; i < amtOfClients; ++i) {
            for (int j = 0; j < REQ_AMT_OF_ADS - clients[ind].amtOfAds; ++j) {
                if (clients[i].in <= clients[ind].out - j) { // clients[ind].out - j <= clients[i].out &&
                    ++clients[i].amtOfAds;
                }
            }
        }
        assert(ind <= amtOfClients);
        assert(amtOfClientsSawAds <= amtOfClients * REQ_AMT_OF_ADS);
        assert(amtOfClientsSawAds < amtOfClients);
        if (clients[ind].amtOfAds < 2) {
            amtOfAds += REQ_AMT_OF_ADS - clients[ind].amtOfAds;
            ++amtOfClientsSawAds;
        }
        ++ind;
        for (int i = ind; i < amtOfClients; ++i)
            if (clients[i].amtOfAds >= REQ_AMT_OF_ADS && clients[i].amtOfAds < 4) {
                ++amtOfClientsSawAds;
                clients[i].amtOfAds = 4;
            } else {
                ind = i;
                break;
            }

        for (int i = ind + 1; i < amtOfClients; ++i)
            if (clients[i].amtOfAds >= REQ_AMT_OF_ADS && clients[i].amtOfAds < 4) {
                ++amtOfClientsSawAds;
                clients[i].amtOfAds = 4;
            }
    }

    std::cout << amtOfAds;

    delete[] clients;

    return 0;
}