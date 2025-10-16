#include <iostream>
using namespace std;

int main() {
	setlocale (LC_ALL, "RU");
	int N;
	cout << "Введите кол-во чисел в последовательности: ";
	cin >> N;

	if (N <= 0) {
		cout << "Ошибка";
		return 0;
	}

	int first;
	cout << "Введите первое число псоледовательности: ";
	cin >> first;

	int ost;
	int sum = 0;
	int minV = 0;
	int minI = 0;
	bool found = false;

	for (int i = 2; i <= N; i++) {
		cout << "Введите число " << i << " :";
		cin >> ost;

		if (ost <= first)
			continue;

		if (!found) {
			minV = ost;
			minI = i;
			found = true;
		}

		sum += ost;

		if (ost < minV) {
			minV = ost;
			minI = i;
		}
	}

	if (!found)
		cout << "Нет чисел больше первого в последовательности" << endl;
	else {
		cout << "Сумма чисел последовательности, больше первого: " << sum << endl;
		cout << "Наименьшее из них: " << minV << endl;
		cout << "Его номер в пследовательности: " << minI << endl;
	}
	
// ПУНТК 2

	int X;
	cout << "Введите целое |X| < 1000: ";
	do {
		cin >> X;
		if (X <= -1000 || X >= 1000)
			cout << "Ошибка";

	} while (X <= -1000 || X >= 1000);

	if (X < 0) X = -X;

	int maxD = 9;
	int minD = 0;

	while (X > 0) {
		int d = X % 10;
		if (d < maxD) minD = d;
		if (d > minD) maxD = d;
		X /= 10;
	}

	cout << "Сумма наименьшей и наибольшей цифры равна: " << minD + maxD << endl;
	return 0;
}