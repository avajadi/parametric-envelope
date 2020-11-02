#include "../../include/ParametricEnvelope.h"
#include <iostream>

using namespace std;

int main() {
    unsigned int stepFrequency = 1000;
    ParametricEnvelope p(10.0,stepFrequency);
    p.setAttackSlope(-2.0);
    p.setDecaySlope(-2.0);
    p.setReleaseSlope(-2.0);
    cout << "## Step\tValue\tState\tGate\n";
    int sustainTimeSteps = 3 * stepFrequency;
    unsigned int step = 0;
    int gate = 0;
    for(;step<500;step++){
        cout << step << "\t" << 0.0 << "\t" << 0 << "\t" << gate << endl;
    }
    p.onGateOn();
    gate = 8;
    while( true ){
        double value = p.step();
        state_enum state = p.getState();
        cout << step++ << "\t" << value << "\t" << state << "\t" << gate << endl;
        sustainTimeSteps--;
        if(sustainTimeSteps==0){
            p.onGateOff();
            gate = 0;
        }
        if(state == state_enum::idle) {
            return 0;
        }
    }
}