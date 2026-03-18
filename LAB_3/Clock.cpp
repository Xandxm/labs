#include "Clock.h"
#include <algorithm>
#include <random>
#include <chrono>

// … остальные методы без изменений, кроме перечисленных ниже …

// Конструктор по умолчанию (инициализация battery добавлена неявно, но можно явно)
Clock::Clock()
    : day(1), month(1), year(2024), hours(0), minutes(0), dayOfWeek("Mon"),
    tasks(new std::vector<std::string>()), battery() {
    tasks->push_back("default");
    std::cout << "Clock created by default" << std::endl;
}

// Конструктор с параметрами
Clock::Clock(int d, int m, int y, int h, int min, std::string dw, std::vector<std::string>* t)
    : battery() {
    setYear(y);
    setMonth(m);
    setDay(d);
    setHours(h);
    setMinutes(min);
    setDayOfWeek(dw);
    tasks = new std::vector<std::string>();
    if (t != nullptr) {
        *tasks = *t;
    }
    std::cout << "New Clock instance created" << std::endl;
}

// Конструктор копирования (копируем battery)
Clock::Clock(const Clock& other)
    : day(other.day), month(other.month), year(other.year),
    hours(other.hours), minutes(other.minutes), dayOfWeek(other.dayOfWeek),
    tasks(new std::vector<std::string>(*other.tasks)), battery(other.battery) {
    std::cout << "Clock copy created" << std::endl;
}

// Оператор присваивания (копируем battery)
Clock& Clock::operator=(const Clock& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hours = other.hours;
        minutes = other.minutes;
        dayOfWeek = other.dayOfWeek;
        battery = other.battery;

        if (tasks != nullptr) {
            tasks->clear();
            delete tasks;
        }
        tasks = new std::vector<std::string>(*other.tasks);
    }
    std::cout << "Assignment operator executed" << std::endl;
    return *this;
}

// Геттер и сеттер для батарейки
Battery Clock::getBattery() const {
    return battery;
}

void Clock::setBattery(const Battery& b) {
    battery = b;
}

// Добавление одного дня с учётом заряда
bool Clock::addOneDay() {
    if (battery.currentCharge <= 0) {
        std::cout << "Battery dead! Cannot add day." << std::endl;
        return false;
    }
    battery.currentCharge--;
    day++;
    if (day > getMaxDays(month)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    return true;
}

// Добавление минут с учётом заряда
void Clock::addMinutes(int x) {
    if (x < 0) return;
    if (battery.currentCharge <= 0) {
        std::cout << "Battery dead! Cannot add minutes." << std::endl;
        return;
    }
    minutes += x;
    while (minutes >= 60) {
        minutes -= 60;
        hours++;
        if (hours >= 24) {
            hours = 0;
            if (!addOneDay()) {   // если заряд кончился, останавливаемся
                break;
            }
        }
    }
}

// Добавление недели
void Clock::addWeek() {
    for (int i = 0; i < 7; i++) {
        if (!addOneDay()) break;
    }
}

// Добавление трёх дней
void Clock::addThreeDays() {
    for (int i = 0; i < 3; i++) {
        if (!addOneDay()) break;
    }
}

// … остальные методы (displayInfo, getMaxDays, getUniqueTasks, getRandomTasks, operator+, operator/)
// остаются без изменений (как в исходном файле)