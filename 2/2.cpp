/*
 * Задача 2.3
 * Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 * Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
 * Требования: Время работы поиска для каждого элемента B[i]: O(log(k)).
 * Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска
 * размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
 */

// time complexity o()
// space complexity o()

int binary_search(const int *arr, const int &comp_element, const int &input_left, const int &input_right) {
    int left = input_left;
    int right = input_right;
    int mid = (left + right) / 2;
    while (left < right) {
        mid = (left + right) / 2;
        if (arr[mid] < comp_element)
            left = mid + 1;
        else
            right = mid;
    }
    return (left == input_right || arr[left] != comp_element) ? -1 : left;
}

int my_search(const int *arr_n, const int &n, const int *arr_m, const int &m, int *arr_res) {
    int pivot = 1;
    int res_amt = 0;
    //arr_res = new int[m];
    for (int i = 0; i < m; ++i) {
        while (pivot < n) {
            if (arr_m[i] >= arr_n[pivot >> 1] && arr_m[i] <= arr_n[pivot]) {
                if ((binary_search(arr_n, arr_m[i], (pivot >> 1), pivot + 1)) != -1) {
                    arr_res[res_amt] = arr_m[i];
                    ++res_amt;
                }
                //pivot = pivot << 1;
                break;
            }
            pivot = pivot << 1;
        }
    }
    return res_amt;
}

#include <iostream>
#include <cassert>

int main() {
    short n = 0;
    short m = 0;
    std::cin >> n >> m; // n - size of arr_n; m - size of arr_m
    assert(n > m && m > 0);
    int *arr_n = new int[n];
    int *arr_m = new int[m];
    for (int i = 0; i < n; ++i)
        std::cin >> arr_n[i];
    for (int i = 0; i < m; ++i)
        std::cin >> arr_m[i];
    //std::cout << "input success\n";

    int *arr_res = new int[m]; // fix!
    int res_amt = my_search(arr_n, n, arr_m, m, arr_res);
    if (res_amt > 0)
        for (int i = 0; i < res_amt; ++i) {
            std::cout << arr_res[i] << " ";
        }
    else
        std::cout << "not found\n";

    //std::cout << "\nfinish\n";

    delete[](arr_res);
    delete[](arr_n);
    delete[](arr_m);
    return 0;
}
