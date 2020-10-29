//
// Created by eddie on 10/29/20.
//

#ifndef PARAMETRIC_ENVELOPE_TIMER_H
#define PARAMETRIC_ENVELOPE_TIMER_H

#include <cstdint>

namespace QDE {
    class Timer {
        // compare match register = [ 16,000,000Hz/ (prescaler * desired interrupt frequency) ] - 1
    private:
        uint16_t prescaler;
        int8_t compare_match;
    public:
        static const uint16_t PRESCALE_1 = 1;
        static const uint16_t PRESCALE_8 = 8;
        static const uint16_t PRESCALE_64 = 64;
        static const uint16_t PRESCALE_256 = 256;
        static const uint16_t PRESCALE_1024 = 1024;

        Timer(uint16_t frequency, uint16_t prescaler = PRESCALE_1024);

        void start();

        void stop();

        uint16_t getPrescaler();

        int8_t getCompareMatch();
    };
}

#endif //PARAMETRIC_ENVELOPE_TIMER_H
