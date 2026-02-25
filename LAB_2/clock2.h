#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <string>
#include <vector>

class Clock {
private:
    int day;
    int month;
    int year;
    std::vector<std::string>* tasks;

protected:
    int hours;
    int minutes;

public:
    std::string dayOfWeek;

    Clock();
    Clock(int d, int m, int y, int h, int min, std::string dw, std::vector<std::string>* t);
    Clock(const Clock& other);
    ~Clock();
    Clock& operator=(const Clock& other);
    Clock operator+(const Clock& other) const;
    Clock operator/(const Clock& other) const;
    
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getHours() const;
    int getMinutes() const;
    std::string getDayOfWeek() const;
    std::vector<std::string>* getTasks() const;
    
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    void setHours(int h);
    void setMinutes(int m);
    void setDayOfWeek(std::string dw);
    void setTasks(std::vector<std::string>* t);
    
    int getMaxDays(int m) const;
    void displayInfo() const;
    void addMinutes(int x);
    void addOneDay();
    void addWeek();
    void addThreeDays();
    std::vector<std::string> getUniqueTasks(const std::vector<std::string>& t1, 
                                            const std::vector<std::string>& t2) const;
    std::vector<std::string> getRandomTasks(const std::vector<std::string>& t1, 
                                            const std::vector<std::string>& t2) const;
};

#endif