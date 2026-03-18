#include "Workshop.hpp"
#include "Clock.h"
#include <iostream>

// ---------- Battery ----------
Battery::Battery() : currentCharge(100), maxCharge(100) {}

Battery::Battery(int current, int max)
    : currentCharge(current), maxCharge(max) {
    if (currentCharge > maxCharge) currentCharge = maxCharge;
    if (currentCharge < 0) currentCharge = 0;
}

Battery::Battery(const Battery& other)
    : currentCharge(other.currentCharge), maxCharge(other.maxCharge) {
}

// ---------- Workshop ----------
Workshop::Workshop() : address("Unknown") {}

Workshop::Workshop(const std::string& addr) : address(addr) {}

Workshop::Workshop(const Workshop& other)
    : address(other.address), clocks(other.clocks) {
}

Workshop::~Workshop() {
    std::cout << "Workshop destroyed" << std::endl;
}

std::string Workshop::getAddress() const { return address; }

const std::vector<Clock>& Workshop::getClocks() const { return clocks; }

void Workshop::setAddress(const std::string& addr) { address = addr; }

void Workshop::addClock(const Clock& clock) {
    clocks.push_back(clock);
}

void Workshop::replaceBattery(int index, const Battery& newBattery) {
    if (index >= 0 && index < static_cast<int>(clocks.size())) {
        clocks[index].setBattery(newBattery);
        std::cout << "Battery replaced for clock at index " << index << std::endl;
    }
    else {
        std::cout << "Invalid clock index!" << std::endl;
    }
}

void Workshop::displayInfo() const {
    std::cout << "=== Workshop Info ===" << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "Clocks in work: " << clocks.size() << std::endl;
    for (size_t i = 0; i < clocks.size(); ++i) {
        std::cout << "Clock #" << i << ":" << std::endl;
        clocks[i].displayInfo();
    }
    std::cout << "=====================" << std::endl;
}