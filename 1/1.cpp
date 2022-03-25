/*
 * Задача 1.4
 * Инвертируйте значение бита в числе N по его номеру K.
 * Формат входных данных. Число N, номер бита K.
 * Формат выходных данных. Число с инвертированным битом в десятичном виде.
 */

// time complexity o(1)
// space complexity o(1)

#include <iostream>
#include <cassert>

unsigned int get_reveresed(const unsigned int &value, const short &reveres_ind);

int main() {
    unsigned int input_val = 0;
    int reveres_ind = 0;
    std::cin >> input_val >> reveres_ind;
    assert(0 <= reveres_ind && reveres_ind < sizeof(int) * 8);
    input_val = get_reveresed(input_val, (short) reveres_ind);
    std::cout << input_val;

    return 0;
}

unsigned int get_reveresed(const unsigned int &value, const short &reveres_ind) {
    return (value ^ (1 << reveres_ind));
}
