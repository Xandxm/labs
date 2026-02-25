#include <iostream>
#include "Clock.h"

int main() {
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

    return 0;
}