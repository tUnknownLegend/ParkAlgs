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

int BinarySearch(const int *arr, const int &compElement, const int &inputLeft, const int &inputRight);

int MySearch(const int *arrN, const int &n, const int *arrM, const int &m, int *arrRes);

int main() {
    short n = 0;
    short m = 0;
    std::cin >> n >> m; // n - size of arrN; m - size of arrM
    assert(n > m && m >= 0 && n <= 10000);
    int *arrN = new int[n];
    int *arrM = new int[m];
    for (int i = 0; i < n; ++i)
        std::cin >> arrN[i];
    for (int i = 0; i < m; ++i)
        std::cin >> arrM[i];

    int *arrRes = new int[m];  // output array
    int resAmt = MySearch(arrN, n, arrM, m, arrRes);  //  amount of resulting elements
    if (resAmt > 0)
        for (int i = 0; i < resAmt; ++i) {
            std::cout << arrRes[i] << " ";
        }
   // else
   //     std::cout << "not found\n";

    delete[](arrRes);
    delete[](arrN);
    delete[](arrM);
    return 0;
}

int BinarySearch(const int *arr, const int &compElement, const int &inputLeft, const int &inputRight) {
    int left = inputLeft;
    int right = inputRight; // element in inputRight excluded from search
    int mid = -1;
    while (left < right) {
        mid = (left + right) / 2;
        if (arr[mid] < compElement)
            left = mid + 1;
        else
            right = mid;
    }
    return (left == inputRight || arr[left] != compElement) ? -1 : left;
}

int MySearch(const int *arrN, const int &n, const int *arrM, const int &m, int *arrRes) {
    int pivot = 1;
    int resAmt = 0;
    int index = 0;

    //  finding first element from arrM, which is greater than arrN[0]
    if (std::min(arrM[index], arrN[0]) != arrN[0]) {
        ++index;
        for (; index <= m && std::max(arrM[index], arrN[0]) != arrM[index]; ++index) {}
    }

    // iterate through arrM to find elements in range from arrN[pivot >> 1] to arrN[pivot]
    for (; index < m; ++index) {
        while (pivot < n) {
            if (arrM[index] >= arrN[pivot >> 1] && arrM[index] <= arrN[pivot]) {
                // if elements found adding to resulting array and breaking while loop
                if ((BinarySearch(arrN, arrM[index], (pivot >> 1), pivot + 1)) != -1) {
                    arrRes[resAmt] = arrM[index];
                    ++resAmt;
                }
                break;
            }
            pivot = pivot << 1; // pivot *= 2 each step if not found
        }
        //  checking right limit value separately
        if (pivot >= n && arrM[index] >= arrN[pivot >> 1] && arrM[index] <= arrN[n - 1]) {
            if ((BinarySearch(arrN, arrM[index], (pivot >> 1), n)) != -1) {
                arrRes[resAmt] = arrM[index];
                ++resAmt;
            }
        }
    }
    return resAmt;
}
