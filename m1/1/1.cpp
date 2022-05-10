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

unsigned int GetReveresed(const unsigned int &value, const short &reveresInd);

int main() {
    unsigned int inputVal = 0;
    int reveresInd = 0;
    std::cin >> inputVal >> reveresInd;
    assert(0 <= reveresInd && reveresInd < sizeof(int) * 8);
    inputVal = GetReveresed(inputVal, (short) reveresInd);
    std::cout << inputVal;

    return 0;
}

unsigned int GetReveresed(const unsigned int &value, const short &reveresInd) {
    return (value ^ (1 << reveresInd));
}
