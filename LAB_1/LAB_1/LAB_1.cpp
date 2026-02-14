#include <iostream>
#include <string>
#include <vector>

class Watch {
private:
    int day;
    int month;
    int year;

protected:
    int hours;
    int minutes;

public:
    std::string dayOfWeek;

    Watch() {
        day = 1; month = 1; year = 2024;
        hours = 0; minutes = 0;
        dayOfWeek = "Пн";
        std::cout << "Часы созданы по умолчанию" << std::endl;
    }

    Watch(int d, int m, int y, int h, int min, std::string dw) {
        setYear(y);
        setMonth(m);
        setDay(d);
        setHours(h);
        setMinutes(min);
        setDayOfWeek(dw);
        std::cout << "Создан новый экземпляр часов" << std::endl;
    }

    Watch(const Watch& other) {
        day = other.day;
        month = other.month;
        year = other.year;
        hours = other.hours;
        minutes = other.minutes;
        dayOfWeek = other.dayOfWeek;
        std::cout << "Копия часов создана" << std::endl;
    }

    ~Watch() {
        std::cout << "Работа деструктора: объект часов удален" << std::endl;
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    std::string getDayOfWeek() const { return dayOfWeek; }

    void setYear(int y) { year = (y >= 0) ? y : 2024; }

    void setMonth(int m) {
        if (m >= 1 && m <= 12) month = m;
        else month = 1;
    }

    void setDay(int d) {
        int maxDays = getMaxDays(month);
        if (d >= 1 && d <= maxDays) day = d;
        else day = 1;
    }

    void setHours(int h) {
        if (h >= 0 && h < 24) hours = h;
        else hours = 0;
    }

    void setMinutes(int m) {
        if (m >= 0 && m < 60) minutes = m;
        else minutes = 0;
    }

    void setDayOfWeek(std::string dw) {
        if (dw == "Пн" || dw == "Вт" || dw == "Ср" || dw == "Чт" || dw == "Пт" || dw == "Сб" || dw == "Вс") {
            dayOfWeek = dw;
        }
        else {
            dayOfWeek = "Пн"; 
        }
    }

    int getMaxDays(int m) const {
        if (m == 2) return 28;
        if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
        return 31;
    }

    void displayInfo() const {
        std::cout << "--- Данные часов ---" << std::endl;
        printf("Дата: %02d.%02d.%04d\n", day, month, year);
        printf("Время: %02d:%02d\n", hours, minutes);
        std::cout << "День недели: " << dayOfWeek << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    void addMinutes(int x) {
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

private:
    void addOneDay() {
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
};

int main() {
    setlocale(LC_ALL, "RU");

    Watch w1;
    w1.displayInfo();

    Watch w2(28, 2, 2023, 23, 50, "Вт");
    w2.displayInfo();

        std::cout << "\nДобавляем 20 минут к 28 февраля..." << std::endl;
    w2.addMinutes(20);
    w2.displayInfo();

    w2.setDayOfWeek("Ср");
    std::cout << "После смены дня недели: " << w2.getDayOfWeek() << std::endl;

    Watch w3 = w2;
    w3.displayInfo();

    return 0;
}