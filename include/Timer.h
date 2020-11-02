//
// Created by eddie on 10/29/20.
//

#ifndef PARAMETRIC_ENVELOPE_TIMER_H
#define PARAMETRIC_ENVELOPE_TIMER_H

namespace qde {
    struct scaler {
        unsigned int dividend;
        unsigned int cs20: 1;
        unsigned int cs21: 1;
        unsigned int cs22: 1;
    };
    const scaler
    scalers[] = {
            {
                    .dividend = 1,
                    .cs20 = 1,
                    .cs21 = 0,
                    .cs22 = 0
            },
            {
                    .dividend = 8,
                    .cs20 = 0,
                    .cs21 = 1,
                    .cs22 = 0
            },
            {
                    .dividend=32,
                    .cs20=1,
                    .cs21=1,
                    .cs22=0
            },
            {
                    .dividend=64,
                    .cs20 = 0,
                    .cs21=0,
                    .cs22=1
            },
            {
                    .dividend=128,
                    .cs20=1,
                    .cs21=0,
                    .cs22=1
            },
            {
                    .dividend= 256,
                    .cs20=0,
                    .cs21=1,
                    .cs22=1
            },
            {
                    .dividend=1024,
                    .cs20=1,
                    .cs21=1,
                    .cs22=1
            }
    };

    class Timer {
    private:
        scaler prescaler;
        unsigned int compare_match;
    public:
        Timer(unsigned int frequency);

        void start();

        void stop();

        scaler getPrescaler();

        unsigned int getCompareMatch();

        void attach(void (*interruptFunction)(void));

        void detach();
    };
}

#endif //PARAMETRIC_ENVELOPE_TIMER_H
