//
//  Agent.hpp
//  IPD-ABM
//
//  Created by Aldric Labarthe on 20/10/2023.
//

#ifndef Agent_hpp
#define Agent_hpp

#include "constants.hpp"


class Agent : public akml::BaseAgent{
protected:
    std::array <short int, AGENT_MEMORY_DURATION> memory;
    std::array <short int, AGENT_MEMORY_DURATION> self_memory;
    
    
public:
    const unsigned int id;
    float payoff;

    Agent(const unsigned int id, akml::NeuralNetwork<>* NN) : BaseAgent(id, NN), id(id) {
        payoff = 0;
        memory = self_memory = {0, 0, 0};
    };
    
    bool makedecision();
    void createMemory(bool& adv_moove, bool& self_moove);
    

};
#endif /* Agent_hpp */
