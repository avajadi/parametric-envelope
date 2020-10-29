//
// Created by eddie on 2020-10-29.
//

#ifndef PARAMETRIC_ENVELOPE_PARAMETRICENVELOPE_H
#define PARAMETRIC_ENVELOPE_PARAMETRICENVELOPE_H

#include <cstdint>
enum state_enum {
    idle,attack,decay,sustain,release
};

struct parameter_struct {
        double value;
        state_enum state;
        uint8_t previousState;
        uint16_t attackTime;
        int8_t attackSlope;
        uint16_t decayTime;
        int8_t decaySlope;
        double level;
        uint16_t releaseTime;
        int8_t releaseSlope;
};


class ParametricEnvelope {
private:
/*    const uint8_t STATE_IDLE = 0;
    const uint8_t STATE_ATTACK = 1;
    const uint8_t STATE_DECAY = 2;
    const uint8_t STATE_SUSTAIN = 3;
    const uint8_t STATE_RELEASE = 4;
*/
    const uint8_t LEVEL_MAX = 10.0;
    parameter_struct parameters;

public:
    ParametricEnvelope();

    //
    // Setters for all envelope parameters
    //
    void setAttackTime(uint16_t time);

    void setAttackSlope(int8_t slope);

    void setDecayTime(uint16_t time);

    void setDecaySlope(int8_t slope);

    void setSustainLevel(double level);

    void setReleaseTime(uint16_t time);

    void setReleaseSlope(int8_t slope);

    //
    // Even handlers for gate transitions
    // onGateOn will transition the envelop into STATE_ATTACK
    //
    void onGateOn();

    //
    // onGateOff will transition the envelope into STATE_RELEASE
    //
    void onGateOff();

    //
    // step is called at regular intervals to get the current signal value
    //
    double step();

    //
    // Reset the envelope
    //
    void reset();

    //
    // Return current parameters
    parameter_struct getParameters();
};


#endif //PARAMETRIC_ENVELOPE_PARAMETRICENVELOPE_H
