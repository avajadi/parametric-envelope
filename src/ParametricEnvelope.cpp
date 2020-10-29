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
    parameters.state = state_enum::idle;
    parameters.previousState = state_enum::idle;
    parameters.value = 0.0;
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
    if( LEVEL_MAX < level ) {
        parameters.level = LEVEL_MAX;
    } else {
        parameters.level = level;
    }
}

parameter_struct ParametricEnvelope::getParameters() {
    return parameters;
}

double ParametricEnvelope::step() {
    //TODO Implement value update
    return parameters.value;
}

void ParametricEnvelope::onGateOn() {
    parameters.previousState = parameters.state;
    parameters.state = state_enum::attack;
}

void ParametricEnvelope::onGateOff() {
    parameters.previousState=parameters.state;
    parameters.state = state_enum::release;
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