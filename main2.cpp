#include <iostream>
#include <locale>
#include "clock2.h"

int main() {
    setlocale(LC_ALL, "RU");
    
    std::vector<std::string> tasks1;
    tasks1.push_back("a");
    tasks1.push_back("b");
    tasks1.push_back("v");
    
    std::vector<std::string> tasks2;
    tasks2.push_back("b");
    tasks2.push_back("p");
    tasks2.push_back("r");
    
    Clock c1(27, 12, 2005, 12, 0, "Вт", &tasks1);
    Clock c2(5, 6, 2003, 10, 0, "Чт", &tasks2);
    
    std::cout << "\n=== Часы 1 ===" << std::endl;
    c1.displayInfo();
    
    std::cout << "\n=== Часы 2 ===" << std::endl;
    c2.displayInfo();
    
    std::cout << "\n=== Тест оператора + ===" << std::endl;
    Clock c3 = c1 + c2;
    c3.displayInfo();
    
    std::cout << "\n=== Тест оператора / ===" << std::endl;
    Clock c4 = c1 / c2;
    c4.displayInfo();
    
    std::cout << "\n=== Тест копирования ===" << std::endl;
    Clock c5 = c3;
    c5.displayInfo();
    
    std::cout << "\n=== Тест присваивания ===" << std::endl;
    Clock c6;
    c6 = c4;
    c6.displayInfo();
    
    return 0;
}