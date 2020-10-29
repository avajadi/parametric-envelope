//
// Created by eddie on 10/29/20.
//

#include "../include/Timer.h"
#include <iostream>

using namespace std;
namespace QDE {
    Timer::Timer(uint16_t frequency, uint16_t prescaler) {
        // Minimum frequency is 61Hz wit ha 1024 prescaler
        this->prescaler = prescaler; //FIXME Make sure this is a valid value
        compare_match = (16000000 / (prescaler * frequency)) - 1;//FIXME Range check
    }

    uint16_t Timer::getPrescaler() {
        return prescaler;
    }

    int8_t Timer::getCompareMatch() {
        return compare_match;
    }
}
using namespace QDE;

int main() {
    Timer t(2000);
    cout << "Timer with frequency 2000 has prescaler " << t.getPrescaler() << " and compare_match value "
         << (int)t.getCompareMatch() << endl << endl;
}