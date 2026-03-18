#ifndef WORKSHOP_HPP
#define WORKSHOP_HPP

#include <string>
#include <vector>
#include "Battery.hpp"

// Предварительное объявление класса Clock
class Clock;

class Workshop {
private:
    std::string address;
    std::vector<Clock> clocks;   // здесь требуется полное определение Clock,
                                 // поэтому мы включим Clock.h в Workshop.cpp

public:
    Workshop();
    Workshop(const std::string& addr);
    Workshop(const Workshop& other);
    ~Workshop();

    std::string getAddress() const;
    const std::vector<Clock>& getClocks() const;

    void setAddress(const std::string& addr);
    void addClock(const Clock& clock);
    void replaceBattery(int index, const Battery& newBattery);
    void displayInfo() const;
};

#endif