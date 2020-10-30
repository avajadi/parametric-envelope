//
// Created by eddie on 2020-10-29.
//
#include "../include/ParametricEnvelope.h"
#include <iostream>
#include <string>

ParametricEnvelope::ParametricEnvelope() {
    reset();
}

void ParametricEnvelope::reset() {
    currentState = idle;
    previousState = idle;
    currentValue = 0.0;
    currentStep = 0;
}

void ParametricEnvelope::setAttackTime(uint16_t time) {
    parameters.attackTime = time;
}

void ParametricEnvelope::setAttackSlope(int8_t slope) {
    parameters.attackSlope = slope;
}

void ParametricEnvelope::setDecayTime(uint16_t time) {
    parameters.decayTime = time;
}

void ParametricEnvelope::setDecaySlope(int8_t slope) {
    parameters.decaySlope = slope;
}

void ParametricEnvelope::setReleaseTime(uint16_t time) {
    parameters.releaseTime = time;
}

void ParametricEnvelope::setReleaseSlope(int8_t slope) {
    parameters.releaseSlope = slope;
}

void ParametricEnvelope::setSustainLevel(double level) {
    if (LEVEL_MAX < level) {
        parameters.sustainLevel = LEVEL_MAX;
    } else {
        parameters.sustainLevel = level;
    }
}

parameter_struct ParametricEnvelope::getParameters() {
    return parameters;
}

//
// step is called periodically to update the inner state and the currentValue of this envelope. It returns the current value
double ParametricEnvelope::step() {
    //TODO Implement value update
    switch (currentState) {
        case idle:
            break;
        case attack:
            if (previousState == idle) {
                currentStep = 0;
                previousState = attack;
            }
            currentValue = calculateAttackValue(currentStep, parameters.attackTime, parameters.attackSlope)
            if (currentValue >= LEVEL_MAX) {
                gotoState(decay);
            } else {
                currentStep++;
            }
            break;
        case decay:
            if (previousState == decay) {
                currentStep = 0;
                previousState = decay;
            }
            currentValue = calculateDecayValue(currentStep, parameters.decayTime, parameters.decaySlope,
                                               parameters.sustainLevel);
            if (currentValue <= parameters.sustainLevel) {
                gotoState(sustain);
            } else {
                currentStep++;
            }
            break;
        case sustain:
            if (previousState != sustain) {
                previousState = sustain;
            }
            break;
        case release:
            if (previousState != release) {
                currentStep = 0;
                previousState = release;
            }
            currentValue = calculateReleaseValue(currentStep, parameters.releaseTime, parameters.releaseSlope,
                                                 parameters.sustainLevel);
            if (currentValue <= 0.0) {
                currentValue = 0.0;
                gotoState(idle);
            } else {
                currentStep++;
            }
    }
    return currentValue;
}

void ParametricEnvelope::onGateOn() {
    gotoState(attack);
}

void ParametricEnvelope::onGateOff() {
    gotoState(release);
}

void ParametricEnvelope::gotoState(state_enum newState) {
    parameters.previousState = parameters.state;
    parameters.state = newState;
}

double ParametricEnvelope::calculateAttackValue(uint16_t currentStep, double time, double slope) {
    return LEVEL_MAX * (currentStep / time) ^ (2 ^ -slope);
}

double ParametricEnvelope::calculateDecayValue(uint16_t currentStep, double time, double slope, double targetLevel) {
    return LEVEL_MAX * (currentStep / time) ^ (2 ^ -slope) * (parameters.sustainLevel/LEVEL_MAX - 1) + 1
}

double ParametricEnvelope::calculateReleaseValue(uint16_t currentStep, double time, double slope, double originLevel) {

}

using namespace std;

int main() {
    ParametricEnvelope p;
    p.setSustainLevel(4.6);
    cout << "Sustain level " << p.getParameters().level << endl;
    cout << "State " << p.getParameters().state << endl;
    p.onGateOn();
    cout << "State with gate on " << p.getParameters().state << endl;
    p.onGateOff();
    cout << "State with gate off " << p.getParameters().state << endl;

}