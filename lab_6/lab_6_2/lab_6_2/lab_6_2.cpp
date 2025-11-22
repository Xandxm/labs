#include <iostream>

int main() {
    setlocale(LC_ALL, "RU");
    int a, b;

    std::cout << "Введите значение a: ";
    std::cin >> a;
    std::cout << "Введите значение b: ";
    std::cin >> b;

    int* ptr_a = &a;
    int* ptr_b = &b;

    *ptr_a *= 2;
    std::cout << "Значение A, увеличенное через указатель в 2 раза: " << a << std::endl;

    int temp = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = temp;

    std::cout << "После операций: a = " << a << std::endl
        << "b = " << b << std::endl;

    return 0;
}