//
// Created by eddie on 10/29/20.
//

#include "../include/Timer.h"
//#include <avr/io.h>
//#include <avr/interrupt.h>

using namespace std;
namespace qde {
    Timer::Timer(unsigned int frequency) {
        // Find the smallest dividend scaler that gives us a valid compare_match (<256)
        for( scaler s : scalers ) {
            unsigned long compare_match_candidate = (16000000 / (s.dividend * frequency)) - 1;
            if( compare_match_candidate < 256 ){
                prescaler = s;
                compare_match = compare_match_candidate;
                break;
            }
        }
    }

    scaler Timer::getPrescaler() {
        return prescaler;
    }

    unsigned int Timer::getCompareMatch() {
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
//        TCCR2A = (1 << WGM21);

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


//        TCCR2B = (1 << CS21);

        // Enable Compare-match register A interrupt for timer2
//        TIMSK2 = (1 << OCIE2A);

        // This value determines the interrupt interval
//        OCR2A = compare_match;
    }

    void Timer::attach(void (*interruptFunction)(void)) {
        // TODO Implement attach
    }

    void Timer::detach() {
        //TODO Implement detach
    }
}
using namespace qde;
