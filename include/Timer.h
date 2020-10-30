//
// Created by eddie on 10/29/20.
//

#ifndef PARAMETRIC_ENVELOPE_TIMER_H
#define PARAMETRIC_ENVELOPE_TIMER_H

#include <cstdint>

namespace qde {
    enum scaler {
        scale_1 = 1,
        scale_8 = 8,
        scale_64 = 64,
        scale_256 = 256,
        scale_1024 = 1024
    };
    class Timer {
    private:
        scaler prescaler;
        int8_t compare_match;
    public:
        Timer(uint16_t frequency, scaler prescaler = scaler::scale_1024);

        void start();

        void stop();

        scaler getPrescaler();

        int8_t getCompareMatch();

        void attach(void (*interruptFunction)(void));
    };
}

#endif //PARAMETRIC_ENVELOPE_TIMER_H
