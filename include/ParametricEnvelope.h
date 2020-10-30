//
// Created by eddie on 2020-10-29.
//

#ifndef PARAMETRIC_ENVELOPE_PARAMETRICENVELOPE_H
#define PARAMETRIC_ENVELOPE_PARAMETRICENVELOPE_H

#include <cstdint>

enum state_enum {
    idle, attack, decay, sustain, release
};

struct parameter_struct {
    double attackTime = 10.0;
    double attackSlope = 0.0;
    double decayTime = 10.0;
    double decaySlope = 0.0;
    double sustainLevel = 0.5;
    double releaseTime = 10.0;
    double releaseSlope = 0.0;
};


class ParametricEnvelope {
private:
    double currentValue;
    uint16_t currentStep;
    state_enum currentState;
    state_enum previousState;

    // Amplitude scale
    double maxLevel;
    // Time scale. Essentially, how often is step() called?
    double stepFrequency;
    parameter_struct parameters;

    void gotoState(state_enum newState);

    double calculateAttackValue(uint16_t currentStep, double time, double slope);

    double calculateDecayValue(uint16_t currentStep, double time, double slope, double targetLevel);

    double calculateReleaseValue(uint16_t currentStep, double time, double slope, double originLevel);

public:
    ParametricEnvelope(double maxLevel = 10.0, double stepFrequency = 10000.0);

    //
    // Setters for all envelope parameters, with reasonable defaults
    //
    void setAttackTime(double time);

    void setAttackSlope(double slope);

    void setDecayTime(double time);

    void setDecaySlope(double slope);

    void setSustainLevel(double level);

    void setReleaseTime(double time);

    void setReleaseSlope(double slope);

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
    // Get the current state.
    //
    state_enum getState();

    //
    // Return current parameters
    parameter_struct getParameters();
};


#endif //PARAMETRIC_ENVELOPE_PARAMETRICENVELOPE_H
