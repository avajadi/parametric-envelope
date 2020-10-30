//
// Created by eddie on 10/29/20.
//

#include "../include/Timer.h"
#include <iostream>
#include <avr/io.h>
#include <avr/interrupt.h>

using namespace std;
namespace qde {
    Timer::Timer(uint16_t frequency, scaler prescaler) {
        // Minimum frequency is 61Hz with a 1024 prescaler
        this->prescaler = prescaler;
        compare_match = (16000000 / (prescaler * frequency)) - 1;//FIXME Range check
        if (((16000000 / (prescaler * frequency)) - 1) > 255) {
            cerr << "compare_match overflow"; // FIXME A REAL range check, with errors.
        }
    }

    scaler Timer::getPrescaler() {
        return prescaler;
    }

    int8_t Timer::getCompareMatch() {
        return compare_match;
    }

    void Timer::start() {
        // If you change the prescale value, it affects CS22, CS21, and CS20
        // For a given prescale value, the eight-bit number that you
        // load into OCR2A determines the frequency according to the
        // following formulas:

        // Set Timer 2 CTC mode and prescale by 8
        //
        // WGM22:0 = 010: CTC Mode
        // WGM2 bits 1 and 0 are in TCCR2A,
        // WGM2 bit 2 is in TCCR2B
        //
        TCCR2A = (1 << WGM21);

        // Set Timer 2  No prescaling
        //
        // CS22:0 = 010: prescale = 8
        // CS2 bits 2:0 are all in TCCR2B
        // prescaler table
        // CS22     CS21    CS20
        //    0        0       0    Clock stopped
        //    0        0       1    No scaling, factor 1
        //    0        1       0    Factor 8
        //    0        1       1    Factor 32
        //    1        0       0    Factor 64
        //    1        0       1    Factor 128
        //    1        1       0    Factor 256
        //    1        1       1    Factor 1024

        TCCR2B = (1 << CS21);

        // Enable Compare-match register A interrupt for timer2
        TIMSK2 = (1 << OCIE2A);

        // This value determines the interrupt interval
        OCR2A = compare_match;
    }

    void Timer::attach(void (*interruptFunction)(void)) {
        // TODO Implement attach
    }
}
using namespace qde;

int main() {
    Timer t(2000);
    cout << "Timer with frequency 2000 has prescaler " << t.getPrescaler() << " and compare_match value "
         << (int) t.getCompareMatch() << endl << endl;
    Timer t2(10000, scale_256);
    cout << "Timer with frequency 10000 and prescaler " << t2.getPrescaler() << " get a compare value "
         << (int) t2.getCompareMatch() << endl;
}