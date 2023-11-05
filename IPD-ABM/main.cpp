//
//  main.cpp
//  IPD-ABM
//
//  Created by Aldric Labarthe on 20/10/2023.
//

//                                                                 AA     LL
//                 pzr--}fC/][dn1wYnfJ                            AAAA    LL
//              c{?_x[v){Ur}][ft(vX(|wzrmOcQ                     AA |AA   LL
//            #][_j(L}u-[[{x[{)q|)fztfXxUQuJkUm                 AAAAAAA   LL
//        .])-1-U)t}-v})}}]L/(}hZjjmtXdYCZuCkJCnLC|Xx          |AA   AAA  LLLLLLLL
//      I{(}11_-+/-q{p}f[1Oj{){QnfL|J00kC*#aqh0zQnjvwz/fCj^
//    "tf1f(fxtujXzt(jcf{{vX/t|bOxJ8hmJ0zwLwJCqzCxYLrYXXYcxx?
//   >()vxcJpUaXMUfdtcuj{]XrtrkkQC0#WhwkhokwCCzChbdcQB@BuO|vxn[
//  "f(|xcOhW&OB@B*BMvJ//(cCzXmqzhB%Mo*qrbUZLbma0&paB@B&X*Zw)xruLx/"
//  rv/    a%Mw88(  ./jujn0nvu   mh%%B%B%ad*Qk0Y0#B@@@@@@*puQqdt/ntCujx/)
// .xu  O  oh88c  .`.1ptL|OXY   @@@@c   #mJhd_        BBqhoLYkd#ju/j|rtnfnrjxjx~'
// `YuO  doBa`    nOCOXmQhmw    @@@B"    #ozbJk,         {?{jb*QbO#W*8*#mha0LxfIl`
//  cCZwdk&,      jzzQcak*u.    %%%%B    WoddJmO_            ddddbM*p/U0dbM*p/Ueudk
//   hMW          J[fY:          wBB8    M*p/U0{                 wLwJCqzCxYwLwJCqzfdfd
//                !qv              !qv   `}czjf:                    wLwJCqzCxYwLwJCddddfd

#include "constants.hpp"
#include "Agent.hpp"

struct versus {
    Agent* first_player;
    Agent* second_player;
    float score, score_p1, score_p2;
    versus () : score(0) {
        first_player = nullptr;
        second_player = nullptr;
    }
    ~versus () {
        if (first_player == nullptr)
            delete first_player;
        if (second_player == nullptr)
            delete second_player;
    }
};

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    
    akml::BaseGeneticAlgorithm<AKML_NEURAL_LAYER_NB, NN_INPUT_LEN, 1, AGENTS_POP_SIZE> ga;
    ga.setNewGenerationRates(0, 0.9);
    
    std::array<Agent*, AGENTS_POP_SIZE> agents;
    std::array<versus, PAIRS_POP_SIZE> pairs;
    
    // Initialization
    for (unsigned short int i(0); i < AGENTS_POP_SIZE; i++){
        agents[i] = nullptr;
    }
    for (unsigned short int i(0); i < AGENTS_POP_SIZE; i++){
        agents[i] = new Agent(i, ga.getNetworksPopulation()[i]);
    }
    
    int pairs_i (0);
    for (unsigned short int i(0); i < AGENTS_POP_SIZE; i++){
            if (i%2!=0){
                pairs[pairs_i].first_player = agents[i];
                pairs_i++;
            }else {
                pairs[pairs_i].second_player = agents[i];
            }
    }
    
    
    std::size_t generationsCounter(0);
    // Rounds
    for (unsigned short int genround(1); genround <= GEN_ROUDS; genround++){
        for (unsigned short int round(1); round <= ROUNDS; round++){
            for (unsigned short int i(0); i < PAIRS_POP_SIZE; i++){
                bool p1 = pairs[i].first_player->makedecision();
                bool p2 = pairs[i].second_player->makedecision();
                pairs[i].first_player->createMemory(p2, p1);
                pairs[i].second_player->createMemory(p1, p2);
                if (p1 == true){
                    if (p2 == true){
                        pairs[i].first_player->payoff = REWARD_ALLCOOP;
                        pairs[i].second_player->payoff = REWARD_ALLCOOP;
                    }else {
                        pairs[i].first_player->payoff = REWARD_BETRAYED;
                        pairs[i].second_player->payoff = REWARD_BETRAYER;
                    }
                }else {
                    if (p2 == true){
                        pairs[i].first_player->payoff = REWARD_BETRAYER;
                        pairs[i].second_player->payoff = REWARD_BETRAYED;
                    }else {
                        pairs[i].first_player->payoff = REWARD_NOCOOP;
                        pairs[i].second_player->payoff = REWARD_NOCOOP;
                    }
                }
                pairs[i].score = pairs[i].score + pairs[i].first_player->payoff + pairs[i].second_player->payoff;
                pairs[i].score_p1 = pairs[i].score_p1 + pairs[i].first_player->payoff;
                pairs[i].score_p2 = pairs[i].score_p2 + pairs[i].second_player->payoff;
                
                //std::cout << "Players " << pairs[i].first_player->id << " - " << pairs[i].second_player->id << " have chosen " <<  p1 << " - " << p2 << "\n";
                if (generationsCounter == 0)
                    std::cout << "Players " << pairs[i].first_player->id << " - " << pairs[i].second_player->id << " have chosen " <<  p1 << " - " << p2 << " - Score " << pairs[i].score << " - Score P1 " << pairs[i].score_p1 << " - Score P2 " << pairs[i].score_p2 << "\n";
            }
        }
        
        //std::sort(pairs.begin(), pairs.end(), [](versus a, versus b){ return a.score < b.score; });
        
        
        std::array<std::pair<float, akml::NeuralNetwork<>*>, AGENTS_POP_SIZE> MSE_net;
        pairs_i = 0;
        for (unsigned short int i(0); i < AGENTS_POP_SIZE; i++){
            if (i%2!=0){
                MSE_net[i] = std::pair<float, akml::NeuralNetwork<>*>((float)pairs[pairs_i].score_p1, pairs[pairs_i].first_player->getNNAccess());
                pairs[pairs_i].score = 0; pairs[pairs_i].score_p1 = 0; pairs[pairs_i].score_p2 = 0;
                pairs_i++;
            }else {
                MSE_net[i] = std::pair<float, akml::NeuralNetwork<>*>((float)pairs[pairs_i].score_p2, pairs[pairs_i].second_player->getNNAccess());
            }
        }
        std::sort(MSE_net.begin(), MSE_net.end());
        
        generationsCounter++;
        ga.generateNewGeneration(MSE_net, generationsCounter);
        
        std::array<akml::NeuralNetwork<>*, AGENTS_POP_SIZE> networksPopulation = ga.getNetworksPopulation();
        
        std::random_device rd; std::mt19937 g(rd());
        std::shuffle(std::begin(networksPopulation), std::end(networksPopulation), g);
        
        for (std::size_t agent_id(0); agent_id < AGENTS_POP_SIZE; agent_id++){
            agents[agent_id]->editNNPointer(networksPopulation[agent_id]);
        }
        
        /*for (unsigned short int i(0); i < PAIRS_POP_SIZE; i++){
            std::cout << "Players " << pairs[i].first_player->id << " - " << pairs[i].second_player->id << " Score " <<  pairs[i].score << "\n";
        }*/
        
    }
    
    for (unsigned short int round(1); round <= ROUNDS; round++){
        unsigned short int i = PAIRS_POP_SIZE-1;
        bool p1 = pairs[i].first_player->makedecision();
        bool p2 = pairs[i].second_player->makedecision();
        pairs[i].first_player->createMemory(p2, p1);
        pairs[i].second_player->createMemory(p1, p2);
        if (p1 == true){
            if (p2 == true){
                pairs[i].first_player->payoff = REWARD_ALLCOOP;
                pairs[i].second_player->payoff = REWARD_ALLCOOP;
            }else {
                pairs[i].first_player->payoff = REWARD_BETRAYED;
                pairs[i].second_player->payoff = REWARD_BETRAYER;
            }
        }else {
            if (p2 == true){
                pairs[i].first_player->payoff = REWARD_BETRAYER;
                pairs[i].second_player->payoff = REWARD_BETRAYED;
            }else {
                pairs[i].first_player->payoff = REWARD_NOCOOP;
                pairs[i].second_player->payoff = REWARD_NOCOOP;
            }
        }
        pairs[i].score = pairs[i].score + pairs[i].first_player->payoff + pairs[i].second_player->payoff;
        std::cout << "Players " << pairs[i].first_player->id << " - " << pairs[i].second_player->id << " have chosen " <<  p1 << " - " << p2 << "\n";
    }
    
    //pairs[PAIRS_POP_SIZE-1].first_player->getNNAccess()->saveNetwork("cout");
    
    for (unsigned short int i(0); i < AGENTS_POP_SIZE; i++){
        if (agents[i] != nullptr)
            delete agents[i];
    }
    
    
    
    return 0;
}
