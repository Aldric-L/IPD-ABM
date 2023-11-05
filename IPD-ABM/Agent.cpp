//
//  Agent.cpp
//  IPD-ABM
//
//  Created by Aldric Labarthe on 20/10/2023.
//

#include "Agent.hpp"

void Agent::editNNPointer(akml::NeuralNetwork<>* NN) {
    brainNN = new akml::NeuralNetwork<>* (NN);
}

akml::NeuralNetwork<>* Agent::getNNAccess() { return *brainNN; }

bool Agent::makedecision() {
    akml::Matrix<float, NN_INPUT_LEN, 1> input;
    for (int i(0); i < AGENT_MEMORY_DURATION; i++){
        input(i,1) = (float)memory[i];
    }
    for (int i(0); i < AGENT_MEMORY_DURATION; i++){
        input(AGENT_MEMORY_DURATION-1+i,1) = (float)self_memory[i];
    }
    akml::Matrix <float, 1, 1> localoutput = *((*brainNN)->template process<NN_INPUT_LEN, 1>(input));
    return (localoutput.read(1,1) >= 0.5);
}


void Agent::createMemory(bool& adv_moove, bool& self_moove) {
    for (int i(0); i < AGENT_MEMORY_DURATION-1; i++){
        memory[i] = memory[i+1];
        self_memory[i] = self_memory[i+1];
    }
    if (adv_moove)
        memory[AGENT_MEMORY_DURATION-1] = 1;
    else
        memory[AGENT_MEMORY_DURATION-1] = -1;
    
    if (self_moove)
        self_memory[AGENT_MEMORY_DURATION-1] = 1;
    else
        self_memory[AGENT_MEMORY_DURATION-1] = -1;
}
