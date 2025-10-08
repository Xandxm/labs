#include <iostream>
#include <cmath>
using namespace std;


int main() {
	setlocale(LC_ALL, "RU");

        int x; // используем int — целое число
        cout << "Введите целое число (не 0): ";
        cin >> x;

        if (x == 0) {
            cout << "Ошибка: число не должно быть равно 0." << endl;
            return 0;
        }
       
        cout << "Тип данных: int\n" << "Размер: " << sizeof(int) * 8 << " бит" << endl;

        // Минимальное и максимальное значение int
        int min = -pow(2, sizeof(int) * 8 - 1);
        int max = pow(2, sizeof(int) * 8 - 1) - 1;
        cout << "Минимальное значение: " << min << endl;
        cout << "Максимальное значение: " << max << endl;

        // Вычисления
        double inverse = 1.0 / x;
        int square = x * x;
        int power5 = pow(x, 5);

        cout << "1 / X = " << inverse << endl;
        cout << "X^2 = " << square << endl;
        cout << "X^5 = " << power5 << endl;

        return 0;
}