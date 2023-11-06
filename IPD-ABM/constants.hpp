//
//  constants.hpp
//  IPD-ABM
//
//  Created by Aldric Labarthe on 20/10/2023.
//

#ifndef constants_hpp
#define constants_hpp

#include <iostream>
#include <array>
#include <cmath>
#include <cassert>
#include <utility>
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

#define PAIRS_POP_SIZE 100
#define AGENTS_POP_SIZE PAIRS_POP_SIZE * 2
#define ROUNDS 10
#define GEN_ROUDS 200
#define AGENT_MEMORY_DURATION 3
#define COOPERATE true

#define REWARD_ALLCOOP REWARD_BETRAYER + REWARD_BETRAYED + 1
#define REWARD_BETRAYER 1
#define REWARD_BETRAYED -0.5
#define REWARD_NOCOOP 0


#define NN_INPUT_LEN AGENT_MEMORY_DURATION*2 /*+4*/

#define AKML_NEURAL_LAYER_NB 3
#define AKML_NN_STRUCTURE { NN_INPUT_LEN, NN_INPUT_LEN*2, 1 }

// AKML.hpp contains all the basic utilities needed to build a NeuralNetwork
#include "AKML/AKML.hpp"
#include "AKML/GeneticAlgorithm.cpp"
#include "AKML/AgentBasedUtilities/BaseAgent.hpp"
#include "AKML/AgentBasedUtilities/CSV_Saver.hpp"

#endif /* constants_hpp */
