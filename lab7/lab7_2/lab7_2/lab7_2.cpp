#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>

// Глобальная константа для размера массива
const int ARRAY_SIZE = 10;

// Функция для заполнения массива случайными числами
void fillRandomArray(std::array<int, ARRAY_SIZE>& arr) {
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> distrib(-10, 10);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = distrib(gen);
    }
}

// Функция для вывода массива
void printArray(const std::array<int, ARRAY_SIZE>& arr) {
    std::cout << "[";
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        std::cout << arr[i];
        if (i != ARRAY_SIZE - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

// Функция сортировки с передачей по ЗНАЧЕНИЮ (копия массива)
void sortByValue(std::array<int, ARRAY_SIZE> arr, bool ascending = true) {
    if (ascending) {
        std::sort(arr.begin(), arr.end());
    }
    else {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
    }
    std::cout << "Внутри функции sortByValue: ";
    printArray(arr);
    // Массив arr - локальная копия, изменения не коснутся исходного массива
}

// Функция сортировки с передачей по ССЫЛКЕ (работа с исходным массивом)
void sortByReference(std::array<int, ARRAY_SIZE>& arr, bool ascending = true) {
    if (ascending) {
        std::sort(arr.begin(), arr.end());
    }
    else {
        std::sort(arr.begin(), arr.end(), std::greater<int>());
    }
    std::cout << "Внутри функции sortByReference: ";
    printArray(arr);
    // Изменения затрагивают исходный массив
}

// Функция сортировки с передачей по УКАЗАТЕЛЮ (работа с исходным массивом)
void sortByPointer(std::array<int, ARRAY_SIZE>* arr, bool ascending = true) {
    if (ascending) {
        std::sort(arr->begin(), arr->end());
    }
    else {
        std::sort(arr->begin(), arr->end(), std::greater<int>());
    }
    std::cout << "Внутри функции sortByPointer: ";
    printArray(*arr);
    // Изменения затрагивают исходный массив
}

int main() {
    setlocale(LC_ALL, "RU");
    std::array<int, ARRAY_SIZE> arr;

    // Заполняем массив случайными числами
    fillRandomArray(arr);

    std::cout << "Исходный массив: ";
    printArray(arr);

    std::cout << "\n=== ПЕРЕДАЧА МАССИВА ПО ЗНАЧЕНИЮ ===" << std::endl;
    std::cout << "Вызываем sortByValue (по возрастанию):" << std::endl;
    sortByValue(arr, true);
    std::cout << "Исходный массив после sortByValue: ";
    printArray(arr);
    std::cout << "Вывод: Исходный массив НЕ изменился, так как в функцию была передана копия.\n";

    std::cout << "\n=== ПЕРЕДАЧА МАССИВА ПО ССЫЛКЕ ===" << std::endl;
    std::cout << "Вызываем sortByReference (по убыванию):" << std::endl;
    sortByReference(arr, false);
    std::cout << "Исходный массив после sortByReference: ";
    printArray(arr);
    std::cout << "Вывод: Исходный массив изменился, так как функция работала с оригиналом через ссылку.\n";

    // Восстанавливаем исходный порядок
    fillRandomArray(arr);
    std::cout << "\nВосстановленный массив: ";
    printArray(arr);

    std::cout << "\n=== ПЕРЕДАЧА МАССИВА ПО УКАЗАТЕЛЮ ===" << std::endl;
    std::cout << "Вызываем sortByPointer (по возрастанию):" << std::endl;
    sortByPointer(&arr, true);
    std::cout << "Исходный массив после sortByPointer: ";
    printArray(arr);
    std::cout << "Вывод: Исходный массив изменился, так как функция работала с оригиналом через указатель.\n";

    std::cout << "\n=== СРАВНЕНИЕ СПОСОБОВ ПЕРЕДАЧИ ===" << std::endl;
    std::cout << "1. Передача по ЗНАЧЕНИЮ:" << std::endl;
    std::cout << "   - Создается полная копия массива" << std::endl;
    std::cout << "   - Изменения внутри функции не затрагивают оригинал" << std::endl;
    std::cout << "   - Затраты памяти и времени на копирование" << std::endl;

    std::cout << "\n2. Передача по ССЫЛКЕ:" << std::endl;
    std::cout << "   - Работа идет с оригинальным массивом" << std::endl;
    std::cout << "   - Изменения внутри функции сохраняются" << std::endl;
    std::cout << "   - Нет затрат на копирование" << std::endl;
    std::cout << "   - Более безопасно, чем указатели (ссылка не может быть nullptr)" << std::endl;

    std::cout << "\n3. Передача по УКАЗАТЕЛЮ:" << std::endl;
    std::cout << "   - Работа идет с оригинальным массивом" << std::endl;
    std::cout << "   - Изменения внутри функции сохраняются" << std::endl;
    std::cout << "   - Нет затрат на копирование" << std::endl;
    std::cout << "   - Указатель может быть nullptr, нужна проверка" << std::endl;
    std::cout << "   - Позволяет изменять сам указатель (адрес)" << std::endl;

    return 0;
}