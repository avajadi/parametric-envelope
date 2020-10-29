//
// Created by eddie on 10/29/20.
//

#include "../include/Timer.h"
#include <iostream>

using namespace std;
namespace qde {
    Timer::Timer(uint16_t frequency, scaler prescaler) {
        // Minimum frequency is 61Hz wit ha 1024 prescaler
        this->prescaler = prescaler;
        compare_match = (16000000 / (prescaler * frequency)) - 1;//FIXME Range check
        if( ((16000000 / (prescaler * frequency)) - 1) > 255 ) {
            cerr << "compare_match overflow";
        }
    }

    scaler Timer::getPrescaler() {
        return prescaler;
    }

    int8_t Timer::getCompareMatch() {
        return compare_match;
    }
}
using namespace qde;

int main() {
    Timer t(2000);
    cout << "Timer with frequency 2000 has prescaler " << t.getPrescaler() << " and compare_match value "
         << (int)t.getCompareMatch() << endl << endl;
    Timer t2(10000, scale_256);
    cout << "Timer with frequency 10000 and prescaler " << t2.getPrescaler() << " get a compare value " << (int)t2.getCompareMatch() << endl;
}