#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

// Функции для работы с массивом
void printArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i];
        if (i != arr.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}

void addToBeginning(std::vector<int>& arr, int value) {
    arr.insert(arr.begin(), value);
}

void addToEnd(std::vector<int>& arr, int value) {
    arr.push_back(value);
}

void clearArray(std::vector<int>& arr) {
    arr.clear();
}

void searchElement(const std::vector<int>& arr, int value) {
    std::vector<size_t> indices;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == value) {
            indices.push_back(i);
        }
    }

    if (indices.empty()) {
        std::cout << "[]" << std::endl;
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i < indices.size(); ++i) {
            std::cout << indices[i];
            if (i != indices.size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "]" << std::endl;
    }
}

// Вариант 7: Перезаписать массив в обратном порядке, пропустив все числа кратные 7, кроме 777.
void variantTask(std::vector<int>& arr) {
    std::cout << "Массив до выполнения задания: ";
    printArray(arr);

    std::vector<int> result;
    bool hasSpecialNumbers = false;

    // Собираем элементы в обратном порядке, пропуская кратные 7, кроме 777
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        if (*it == 777 || (*it % 7 != 0 && *it != 0)) {
            result.push_back(*it);
            hasSpecialNumbers = true;
        }
    }

    // Если таких чисел нет - добавляем три нуля
    if (!hasSpecialNumbers) {
        result.push_back(0);
        result.push_back(0);
        result.push_back(0);
    }

    arr = result;

    std::cout << "Массив после выполнения задания: ";
    printArray(arr);
}

int main() {
    setlocale(LC_ALL, "RU");
    std::vector<int> arr;
    int choice;
    bool running = true;

    do {
        std::cout << "\n=== МЕНЮ ===" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "1. Просмотр массива" << std::endl;
        std::cout << "2. Добавить элемент в начало" << std::endl;
        std::cout << "3. Добавить элемент в конец" << std::endl;
        std::cout << "4. Очистка всего массива" << std::endl;
        std::cout << "5. Поиск элемента в массиве" << std::endl;
        std::cout << "6. Задание варианта (Вариант 7)" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 0:
            running = false;
            std::cout << "Выход из программы." << std::endl;
            break;

        case 1:
            printArray(arr);
            break;

        case 2: {
            int value;
            std::cout << "Введите значение для добавления в начало: ";
            std::cin >> value;
            addToBeginning(arr, value);
            std::cout << "Элемент добавлен. Текущий массив: ";
            printArray(arr);
            break;
        }

        case 3: {
            int value;
            std::cout << "Введите значение для добавления в конец: ";
            std::cin >> value;
            addToEnd(arr, value);
            std::cout << "Элемент добавлен. Текущий массив: ";
            printArray(arr);
            break;
        }

        case 4:
            clearArray(arr);
            std::cout << "Массив очищен." << std::endl;
            break;

        case 5: {
            int value;
            std::cout << "Введите значение для поиска: ";
            std::cin >> value;
            searchElement(arr, value);
            break;
        }

        case 6:
            variantTask(arr);
            break;

        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }

        // Очистка буфера ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (running);

    return 0;
}