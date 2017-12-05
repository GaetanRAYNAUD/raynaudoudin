#include "DeepAI.h"

namespace ai {

    DeepAI::DeepAI(int randomSeed): randgen(randomSeed) {
        
    }

    int DeepAI::alphabeta(engine::Engine& engine, state::Direction& direction, int depth) {
//        std::vector<engine::Command*> commands = listCommands(engine.getState());
//        std::uniform_int_distribution<int> uniform(0, commands.size() - 1);
//        int rand = uniform(randgen);
//        int val;
//        
//        while (!commands.empty()) {
//            engine.addCommand(1, commands.at(rand));
//            engine.update();
//            if (commands.at(rand)->getTypeId() == engine::CommandTypeId::END_TURN) {
//                break;
//            }
//            commands = listCommands(engine.getState());
//            std::uniform_int_distribution<int> uniform(0, commands.size() - 1);
//            rand = uniform(randgen);
//        }
//        
//        if (engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
//            return getHeuristic(engine.getState());
//        }
//        
//        
//        
//        val = std::numeric_limits<int>::min();
        

        //for (unsigned int i = 0; i < )
    
        return -1;
    }
    
    int DeepAI::getHeuristic(const state::State& state) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = state.getBoard().getUnits();
        int heuristic = 0;
        
        switch (state.getCurrentTeam()) {
            case state::TeamId::TEAM_1:
                for (auto& u : units) {
                    switch (u.second->getTeam()) {
                        case state::TeamId::TEAM_1:
                            heuristic = heuristic + u.second->getLife();
                            break;
                        case state::TeamId::TEAM_2:
                            heuristic = heuristic - u.second->getLife();
                            break;
                        default:
                            break;                            
                    }
                }
                break;
            case state::TeamId::TEAM_2:
                for (auto& u : units) {
                    switch (u.second->getTeam()) {
                        case state::TeamId::TEAM_1:
                            heuristic = heuristic - u.second->getLife();
                            break;
                        case state::TeamId::TEAM_2:
                            heuristic = heuristic + u.second->getLife();
                            break;
                        default:
                            break;                            
                    }
                }
                break;
            default:
                break;
        }
        
        return heuristic;
    }

    void DeepAI::run(engine::Engine& engine) {

    }

}

