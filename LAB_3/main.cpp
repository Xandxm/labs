#include <iostream>
#include "Clock.h"
#include "Workshop.hpp"

// Функция вывода оценки лабораторной работы
void printEvaluation() {
    std::cout << "\n=== Evaluation of Lab Work ===" << std::endl;
    std::cout << "Interest: 8/10" << std::endl;
    std::cout << "Completeness: 9/10" << std::endl;
    std::cout << "Difficulty: 7/10" << std::endl;
    std::cout << "==============================\n" << std::endl;
}

int main() {
    // --- Исходная демонстрация из предыдущей лабораторной ---
    std::vector<std::string> tasks1;
    tasks1.push_back("a");
    tasks1.push_back("b");
    tasks1.push_back("v");

    std::vector<std::string> tasks2;
    tasks2.push_back("b");
    tasks2.push_back("p");
    tasks2.push_back("r");

    Clock c1(27, 12, 2005, 12, 0, "Tue", &tasks1);
    Clock c2(5, 6, 2003, 10, 0, "Thu", &tasks2);

    std::cout << "\n=== Clock 1 ===" << std::endl;
    c1.displayInfo();

    std::cout << "\n=== Clock 2 ===" << std::endl;
    c2.displayInfo();

    std::cout << "\n=== Test operator + ===" << std::endl;
    Clock c3 = c1 + c2;
    c3.displayInfo();

    std::cout << "\n=== Test operator / ===" << std::endl;
    Clock c4 = c1 / c2;
    c4.displayInfo();

    std::cout << "\n=== Test copy ===" << std::endl;
    Clock c5 = c3;
    c5.displayInfo();

    std::cout << "\n=== Test assignment ===" << std::endl;
    Clock c6;
    c6 = c4;
    c6.displayInfo();

    // --- Новая демонстрация работы библиотеки (Мастерская и Батарейка) ---
    std::cout << "\n=== Demonstration of Workshop and Battery ===" << std::endl;

    // Создаём мастерскую
    Workshop ws("123 Main Street");
    ws.addClock(c1);
    ws.addClock(c2);
    ws.displayInfo();

    // Создаём часы с низким зарядом
    std::vector<std::string> tasks3;
    tasks3.push_back("x");
    Clock cLow(1, 1, 2024, 0, 0, "Mon", &tasks3);
    Battery lowBatt(5, 10);
    cLow.setBattery(lowBatt);
    ws.addClock(cLow);                     // добавляем в мастерскую
    ws.displayInfo();

    // Заменяем батарейку у третьих часов в мастерской (индекс 2)
    Battery newBatt(100, 100);
    ws.replaceBattery(2, newBatt);
    ws.displayInfo();

    // Проверяем расход заряда на отдельном экземпляре (не из мастерской)
    std::cout << "\nTesting battery drain on a separate clock (initial charge 5/10):" << std::endl;
    Clock testClock = cLow;   // копия с зарядом 5
    for (int i = 0; i < 10; ++i) {
        std::cout << "Attempt " << i + 1 << ": ";
        if (!testClock.addOneDay()) {
            std::cout << "Cannot add day – battery dead." << std::endl;
            break;
        }
        testClock.displayInfo();
        std::cout << "Battery: " << testClock.getBattery().currentCharge
            << "/" << testClock.getBattery().maxCharge << std::endl;
    }

    // Вывод личной оценки
    printEvaluation();

    return 0;
}