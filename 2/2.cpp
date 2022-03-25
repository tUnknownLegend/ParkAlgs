/*
 * Задача 2.3
 * Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
 * A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение.
 * Требования: Время работы: O(m * log k),
 * где k - позиция элемента B[m-1] в массиве A.
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
 * Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k
 * помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
 */

// time complexity o(m * log k)
// space complexity o(2 * m + n)

#include <iostream>
#include <cassert>

int binary_search(const int *arr, const int &comp_element, const int &input_left, const int &input_right);

int my_search(const int *arr_n, const int &n, const int *arr_m, const int &m, int *arr_res);

int main() {
    short n = 0;
    short m = 0;
    std::cin >> n >> m; // n - size of arr_n; m - size of arr_m
    assert(n > m && m >= 0 && n <= 10000);
    int *arr_n = new int[n];
    int *arr_m = new int[m];
    for (int i = 0; i < n; ++i)
        std::cin >> arr_n[i];
    for (int i = 0; i < m; ++i)
        std::cin >> arr_m[i];

    int *arr_res = new int[m];  // output array
    int res_amt = my_search(arr_n, n, arr_m, m, arr_res);  //  amount of resulting elements
    if (res_amt > 0)
        for (int i = 0; i < res_amt; ++i) {
            std::cout << arr_res[i] << " ";
        }
   // else
   //     std::cout << "not found\n";

    delete[](arr_res);
    delete[](arr_n);
    delete[](arr_m);
    return 0;
}

int binary_search(const int *arr, const int &comp_element, const int &input_left, const int &input_right) {
    int left = input_left;
    int right = input_right; // element in input_right excluded from search
    int mid = -1;
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
    int index = 0;

    //  finding first element from arr_m, which is greater than arr_n[0]
    if (std::min(arr_m[index], arr_n[0]) != arr_n[0]) {
        ++index;
        for (; index <= m && std::max(arr_m[index], arr_n[0]) != arr_m[index]; ++index) {}
    }

    // iterate through arr_m to find elements in range from arr_n[pivot >> 1] to arr_n[pivot]
    for (; index < m; ++index) {
        while (pivot < n) {
            if (arr_m[index] >= arr_n[pivot >> 1] && arr_m[index] <= arr_n[pivot]) {
                // if elements found adding to resulting array and breaking while loop
                if ((binary_search(arr_n, arr_m[index], (pivot >> 1), pivot + 1)) != -1) {
                    arr_res[res_amt] = arr_m[index];
                    ++res_amt;
                }
                break;
            }
            pivot = pivot << 1; // pivot *= 2 each step if not found
        }
        //  checking right limit value separately
        if (pivot >= n && arr_m[index] >= arr_n[pivot >> 1] && arr_m[index] <= arr_n[n - 1]) {
            if ((binary_search(arr_n, arr_m[index], (pivot >> 1), n)) != -1) {
                arr_res[res_amt] = arr_m[index];
                ++res_amt;
            }
        }
    }
    return res_amt;
}
