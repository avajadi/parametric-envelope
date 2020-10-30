//
// Created by eddie on 2020-10-29.
//
#include "../include/ParametricEnvelope.h"
#include <iostream>
#include <string>
#include <cmath>

ParametricEnvelope::ParametricEnvelope(double maxLevel, double stepFrequency) {
    this->maxLevel = maxLevel;
    this->stepFrequency = stepFrequency;
    reset();
}

void ParametricEnvelope::reset() {
    currentState = idle;
    previousState = idle;
    currentValue = 0.0;
    currentStep = 0;
}

void ParametricEnvelope::setAttackTime(double time) {
    parameters.attackTime = time;
}

void ParametricEnvelope::setAttackSlope(double slope) {
    parameters.attackSlope = slope;
}

void ParametricEnvelope::setDecayTime(double time) {
    parameters.decayTime = time;
}

void ParametricEnvelope::setDecaySlope(double slope) {
    parameters.decaySlope = slope;
}

void ParametricEnvelope::setReleaseTime(double time) {
    parameters.releaseTime = time;
}

void ParametricEnvelope::setReleaseSlope(double slope) {
    parameters.releaseSlope = slope;
}

void ParametricEnvelope::setSustainLevel(double level) {
    if (level>maxLevel) {
        parameters.sustainLevel = 1.0;
    } else {
        parameters.sustainLevel = level/maxLevel;
    }
}

parameter_struct ParametricEnvelope::getParameters() {
    return parameters;
}

state_enum ParametricEnvelope::getState() {
    return currentState;
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
            currentValue = calculateAttackValue(currentStep, parameters.attackTime, parameters.attackSlope);
            if (currentValue >= 1.0) {
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
            if (currentValue < 0.0) {
                currentValue = 0.0;
                gotoState(idle);
            } else {
                currentStep++;
            }
    }
    return currentValue * maxLevel;
}

void ParametricEnvelope::onGateOn() {
    gotoState(attack);
}

void ParametricEnvelope::onGateOff() {
    gotoState(release);
}

void ParametricEnvelope::gotoState(state_enum newState) {
    previousState = currentState;
    currentState = newState;
}

double ParametricEnvelope::calculateAttackValue(uint16_t currentStep, double time, double slope) {
    double currentTime = currentStep / stepFrequency;
    return std::pow(currentTime / time, std::pow(2.0, -slope));
}

double ParametricEnvelope::calculateDecayValue(uint16_t currentStep, double time, double slope, double targetLevel) {
    double currentTime = currentStep / stepFrequency;
    return std::pow(currentTime / time, std::pow(2.0, -slope)) * (targetLevel - 1) + 1;
}

double ParametricEnvelope::calculateReleaseValue(uint16_t currentStep, double time, double slope, double originLevel) {
    double currentTime = currentStep / stepFrequency;
    return originLevel - ( originLevel * currentTime );//FIXME Implement proper algorithm for release value
}

using namespace std;

int main() {
    ParametricEnvelope p(10.0,50.0);
    p.setAttackSlope(0.0);
    p.setDecaySlope(1.0);
    cout << "Value\tState\n";
    p.onGateOn();
    int sustainTimeSteps = 100;
    while( true ){
        double value = p.step();
        state_enum state = p.getState();
        cout <<  value << "\t" << state << endl;
        if(state == state_enum::sustain) {
            sustainTimeSteps--;
            if(sustainTimeSteps==0){
                p.onGateOff();
            }
        }
        if(state == state_enum::idle) {
            return 0;
        }
    }
}