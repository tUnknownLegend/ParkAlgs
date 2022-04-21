// time complexity o(n), but only when calling renew(), otherwise o(1)
// space complexity o(n)

#include <cassert>
#include <iostream>
#include <cmath>

template<class T>
class CompareMore {
public:
    bool operator()(const T &l, const T &r) { return l > r; }
};

template<class T, class Compare = CompareMore<T> >
int getMediana(T *arr, const int left, const int right, Compare cmp = CompareMore<T>()) {
    int mid = (right - left + 1) / 2;

    if ((cmp(arr[mid], arr[left]) && !cmp(arr[mid], arr[right])) ||
        (!cmp(arr[mid], arr[left]) && cmp(arr[mid], arr[right])))
        return mid;

    if ((cmp(arr[left], arr[mid]) && !cmp(arr[left], arr[right])) ||
        (!cmp(arr[left], arr[mid]) && cmp(arr[left], arr[right])))
        return left;

    return right;
}

template<class T, class Compare = CompareMore<T> >
int partition(T *arr, const int left, const int right, Compare cmp = CompareMore<T>()) {
    if (right - left <= 0) {
        return left;
    }

    int pivot = getMediana<T>(arr, left, right);
    std::swap(arr[pivot], arr[right]);
    int i = left;
    int j = left;

    for (; j < right - 1; ++j) {
        if (!cmp(arr[j], arr[right])) {
            std::swap(arr[j], arr[i]);
            ++i;
        }
    }

    std::swap(arr[i], arr[right]);
    return i;
}

template<class T, class Compare = CompareMore<T> >
T &findKStat(T *arr, const int n, const T k, Compare cmp = CompareMore<T>()) {
    int left = 0;
    int right = n - 1;
    int pivot = partition<T>(&arr[0], left, right);
    while (pivot != k) {
        if (k > pivot)
            left = pivot + 1;
        else
            right = pivot;

        pivot = partition<T>(&arr[0], left, right);
    }

    return arr[k];
}

int percentile(const double p, const int size) {
    return (int) round((double) p / 100 * (double) size);
}

int main() {

    int inputArrSize = 0;
    std::cin >> inputArrSize;
    assert(inputArrSize > 0);
    int *inputArr = new int[inputArrSize];
    for (int i = 0; i < inputArrSize; ++i)
        std::cin >> inputArr[i];

    std::cout << findKStat<int>(&inputArr[0], inputArrSize, percentile(10, inputArrSize)) << std::endl;
    std::cout << findKStat<int>(&inputArr[0], inputArrSize, percentile(50, inputArrSize)) << std::endl;
    std::cout << findKStat<int>(&inputArr[0], inputArrSize, percentile(90, inputArrSize)) << std::endl;

    return 0;
}

