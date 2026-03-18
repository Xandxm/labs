#ifndef BATTERY_HPP
#define BATTERY_HPP

struct Battery {
    int currentCharge;
    int maxCharge;

    Battery();
    Battery(int current, int max);
    Battery(const Battery& other);
};

#endif