#include "clock2.h"
#include <algorithm>
#include <random>
#include <ctime>

Clock::Clock() {
    day = 1; month = 1; year = 2024;
    hours = 0; minutes = 0;
    dayOfWeek = "Пн";
    tasks = new std::vector<std::string>();
    tasks->push_back("default");
    std::cout << "Часы созданы по умолчанию" << std::endl;
}

Clock::Clock(int d, int m, int y, int h, int min, std::string dw, std::vector<std::string>* t) {
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
    std::cout << "Создан новый экземпляр часов" << std::endl;
}

Clock::Clock(const Clock& other) {
    day = other.day;
    month = other.month;
    year = other.year;
    hours = other.hours;
    minutes = other.minutes;
    dayOfWeek = other.dayOfWeek;
    tasks = new std::vector<std::string>(*other.tasks);
    std::cout << "Копия часов создана" << std::endl;
}

Clock::~Clock() {
    if (tasks != nullptr) {
        tasks->clear();
        delete tasks;
        tasks = nullptr;
        std::cout << "Динамическое поле tasks очищено" << std::endl;
    }
    std::cout << "Работа деструктора: объект часов удален" << std::endl;
}

Clock& Clock::operator=(const Clock& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hours = other.hours;
        minutes = other.minutes;
        dayOfWeek = other.dayOfWeek;
        
        if (tasks != nullptr) {
            tasks->clear();
            delete tasks;
        }
        
        tasks = new std::vector<std::string>(*other.tasks);
    }
    std::cout << "Оператор присваивания выполнен" << std::endl;
    return *this;
}

Clock Clock::operator+(const Clock& other) const {
    Clock result;
    if (year > other.year || 
        (year == other.year && month > other.month) ||
        (year == other.year && month == other.month && day > other.day)) {
        result = *this;
    } else {
        result = other;
    }
    
    for (int i = 0; i < 7; i++) {
        result.addOneDay();
    }
    result.hours = (result.hours + 1) % 24;
    
    std::vector<std::string> uniqueTasks = getUniqueTasks(*this->tasks, *other.tasks);
    result.setTasks(&uniqueTasks);
    
    return result;
}

Clock Clock::operator/(const Clock& other) const {
    Clock result;
    if (year < other.year || 
        (year == other.year && month < other.month) ||
        (year == other.year && month == other.month && day < other.day)) {
        result = *this;
    } else {
        result = other;
    }
    
    for (int i = 0; i < 3; i++) {
        result.addOneDay();
    }
    
    std::vector<std::string> randomTasks = getRandomTasks(*this->tasks, *other.tasks);
    result.setTasks(&randomTasks);
    
    return result;
}

int Clock::getDay() const { return day; }
int Clock::getMonth() const { return month; }
int Clock::getYear() const { return year; }
int Clock::getHours() const { return hours; }
int Clock::getMinutes() const { return minutes; }
std::string Clock::getDayOfWeek() const { return dayOfWeek; }
std::vector<std::string>* Clock::getTasks() const { return tasks; }

void Clock::setYear(int y) { year = (y >= 0) ? y : 2024; }
void Clock::setMonth(int m) { if (m >= 1 && m <= 12) month = m; else month = 1; }
void Clock::setDay(int d) { 
    int maxDays = getMaxDays(month);
    if (d >= 1 && d <= maxDays) day = d; else day = 1;
}
void Clock::setHours(int h) { if (h >= 0 && h < 24) hours = h; else hours = 0; }
void Clock::setMinutes(int m) { if (m >= 0 && m < 60) minutes = m; else minutes = 0; }

void Clock::setDayOfWeek(std::string dw) {
    if (dw == "Пн" || dw == "Вт" || dw == "Ср" || dw == "Чт" || dw == "Пт" || dw == "Сб" || dw == "Вс") {
        dayOfWeek = dw;
    } else {
        dayOfWeek = "Пн"; 
    }
}

void Clock::setTasks(std::vector<std::string>* t) {
    if (tasks != nullptr) {
        tasks->clear();
        delete tasks;
    }
    tasks = new std::vector<std::string>(*t);
}

int Clock::getMaxDays(int m) const {
    if (m == 2) return 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

void Clock::displayInfo() const {
    std::cout << "--- Данные часов ---" << std::endl;
    printf("Дата: %02d.%02d.%04d\n", day, month, year);
    printf("Время: %02d:%02d\n", hours, minutes);
    std::cout << "День недели: " << dayOfWeek << std::endl;
    std::cout << "Дела: ";
    if (tasks && !tasks->empty()) {
        for (size_t i = 0; i < tasks->size(); i++) {
            std::cout << (*tasks)[i];
            if (i < tasks->size() - 1) std::cout << ", ";
        }
    } else {
        std::cout << "нет";
    }
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;
}

void Clock::addMinutes(int x) {
    if (x < 0) return;
    minutes += x;
    while (minutes >= 60) {
        minutes -= 60;
        hours++;
        if (hours >= 24) {
            hours = 0;
            addOneDay();
        }
    }
}

void Clock::addOneDay() {
    day++;
    if (day > getMaxDays(month)) {
        day = 1;
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

void Clock::addWeek() {
    for (int i = 0; i < 7; i++) {
        addOneDay();
    }
}

void Clock::addThreeDays() {
    for (int i = 0; i < 3; i++) {
        addOneDay();
    }
}

std::vector<std::string> Clock::getUniqueTasks(const std::vector<std::string>& t1, 
                                               const std::vector<std::string>& t2) const {
    std::vector<std::string> result = t1;
    for (const auto& task : t2) {
        if (std::find(result.begin(), result.end(), task) == result.end()) {
            result.push_back(task);
        }
    }
    return result;
}

std::vector<std::string> Clock::getRandomTasks(const std::vector<std::string>& t1, 
                                               const std::vector<std::string>& t2) const {
    std::vector<std::string> combined;
    std::vector<std::string> result;
    
    combined = getUniqueTasks(t1, t2);
    
    if (combined.empty()) return result;
    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int count = std::rand() % combined.size() + 1;
    
    std::shuffle(combined.begin(), combined.end());
    
    for (int i = 0; i < count; i++) {
        result.push_back(combined[i]);
    }
    
    return result;
}