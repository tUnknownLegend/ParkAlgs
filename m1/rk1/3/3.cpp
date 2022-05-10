#include <iostream>
#include<cassert>

void InsertionSort(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        int tmp = a[i];
        int j = i - 1;
        for (; j >= 0 && tmp < a[j]; --j) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

void InsertionSortP(struct Points& points) {
    for (int i = 1; i < points.n; ++i) {
        int tmp = points.x[i];
        int j = i - 1;
        for (; j >= 0 && tmp < a[j]; --j) {
            a[j + 1] = a[j];
        }
        a[j + 1] = tmp;
    }
}

struct Points {
    int n = 0;
    int *x = nullptr;
    int *y = nullptr;
    int *z = nullptr;
};

int main() {
    struct Points points;
    std::cin >> points.n;

    points.x = new int[points.n];
    points.y = new int[points.n];
    points.z = new int[points.n];
    int *pointSrt = new int[3];
    int *tmpPoint = nullptr;
    for (int i = 0; i < points.n; ++i) {
        std::cin >> points.x[i] >> points.y[i] >> points.z[i];
        tmpPoint = pointSrt = points.x + i;
        (++tmpPoint) = points.y + i;
        (++tmpPoint) = points.z + i;
        InsertionSort(pointSrt, 3);
    }
    tmpPoint = nullptr;
    delete[] pointSrt;

    for (int i = 0; i < points.n; ++i) {
        InsertionSortP(points);
    }
    //std::cout << result ;

    delete[] points.x;
    delete[] points.y;
    delete[] points.z;
    return 0;
}
