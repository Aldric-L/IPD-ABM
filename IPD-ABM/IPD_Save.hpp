//
//  IPD_Save.hpp
//  IPD-ABM
//
//  Created by Aldric Labarthe on 05/11/2023.
//

#ifndef IPD_Save_hpp
#define IPD_Save_hpp

#include <stdio.h>
#include <iostream>
#include <string>


#include "constants.hpp"

class IPD_Save : public akml::Save {
    unsigned long int cooperator_mooves, agents;
    unsigned short int bestscore, fullcoop_agents, fulldefector_agents;
    float pair_score_mean;
    
public:
    inline IPD_Save (unsigned long int cooperator_mooves, unsigned long int agents, unsigned short int bestscore, unsigned short int fullcoop_agents, unsigned short int fulldefector_agents, float pair_score_mean) : cooperator_mooves(cooperator_mooves), agents(agents), bestscore(bestscore), fullcoop_agents(fullcoop_agents), fulldefector_agents(fulldefector_agents), pair_score_mean(pair_score_mean) {};
    
    inline std::string printAsCSV() {
        std::string rtrn ("");
        rtrn += std::to_string(cooperator_mooves) + ", ";
        rtrn += std::to_string(agents) + ", ";
        rtrn += std::to_string(bestscore) + ", ";
        rtrn += std::to_string(fullcoop_agents) + ", ";
        rtrn += std::to_string(fulldefector_agents) + ", ";
        rtrn += std::to_string(pair_score_mean);
        return rtrn;
    };
    
    
    inline static std::string printTitleAsCSV() {
        std::string rtrn ("");
        rtrn += "cooperator_mooves, agents, bestscore, fullcoop_agents, fulldefector_agents, pair_score_mean";
        return rtrn;
    }
};

#endif /* IPD_Save_hpp */
