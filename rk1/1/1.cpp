#include <iostream>
#include<cassert>

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
    return left;
}

int main() {
    int n;
    std::cin >> n;

    int *array = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> array[i];

    int k;
    std::cin >> k;

    int result = -2;
    result = binary_search(array, k, 0, n);

    std::cout << result ;

    delete[] array;
    return 0;
}
