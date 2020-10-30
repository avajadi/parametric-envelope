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
        uint16_t attackTime;
        double attackSlope;
        uint16_t decayTime;
        double decaySlope;
        double sustainLevel;
        uint16_t releaseTime;
        double releaseSlope;
};


class ParametricEnvelope {
private:
    double currentValue;
    uint16_t currentStep;
    state_enum currentState;
    state_enum previousState;

    const double LEVEL_MAX = 10.0;
    parameter_struct parameters;
    void gotoState(state_enum newState);
    double calculateAttackValue(uint16_t currentStep,double time, double slope);
    double calculateDecayValue(uint16_t currentStep,double time, double slope, double targetLevel);
    double calculateReleaseValue(uint16_t currentStep,double time, double slope, double originLevel);

public:
    ParametricEnvelope();

    //
    // Setters for all envelope parameters, with reasonable defaults
    //
    void setAttackTime(uint16_t time=10);

    void setAttackSlope(int8_t slope=1);

    void setDecayTime(uint16_t time=10);

    void setDecaySlope(int8_t slope=1);

    void setSustainLevel(double level=5.0);

    void setReleaseTime(uint16_t time=10);

    void setReleaseSlope(int8_t slope=1);

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
