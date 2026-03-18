#include "Battery.hpp"

Battery::Battery() : currentCharge(100), maxCharge(100) {}

Battery::Battery(int current, int max)
    : currentCharge(current), maxCharge(max) {
    if (currentCharge > maxCharge) currentCharge = maxCharge;
    if (currentCharge < 0) currentCharge = 0;
}

Battery::Battery(const Battery& other)
    : currentCharge(other.currentCharge), maxCharge(other.maxCharge) {
}