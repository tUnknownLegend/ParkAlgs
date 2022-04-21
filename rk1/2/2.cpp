#include <iostream>
#include<cassert>

int main() {
    int n;
    std::cin >> n;

    int *array = new int[n];
    for (int i = 0; i < n; ++i)
        std::cin >> array[i];


    //std::cout << result ;

    return 0;
}
