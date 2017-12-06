#include "DeepAI.h"
#include "engine/EndTurnCommand.h"

#include <iostream>

namespace ai {

    DeepAI::DeepAI(int randomSeed): randgen(randomSeed) {
        
    }
    
    int DeepAI::minimax_rec_min(engine::Engine& engine, int depth) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands = listCommands(engine.getState());
//        std::uniform_int_distribution<int> uniform(0, commands.size() - 1);
//        int rand = uniform(randgen);
        int min = std::numeric_limits<int>::max();
        int heuristicChild;
        int commandCount = 0;
        int leavesCount;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return getHeuristic(engine.getState());
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            while (!commands.empty()) {
                engine.addCommand(1, commands.at(0));
                actions.push(engine.update());
                commandCount++;

                commands = listCommands(engine.getState());
//                std::uniform_int_distribution<int> uniform(0, commands.size() - 1);
//                rand = uniform(randgen);
            }

            heuristicChild = minimax_rec_max(engine, depth);
            
            if (heuristicChild > min) {
                min = heuristicChild;
            }
                    
            while (commandCount > 0) {
                engine.undo(actions.top());
                actions.pop();
                commandCount--;
            }
        }
        
        return min;
    }
    
    int DeepAI::minimax_rec_max(engine::Engine& engine, int depth) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands = listCommands(engine.getState());
//        std::uniform_int_distribution<int> uniform(0, commands.size() - 1);
//        int rand = uniform(randgen);
        int max = std::numeric_limits<int>::min();
        int heuristicChild;
        int commandCount = 0;
        int leavesCount;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return getHeuristic(engine.getState());
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            while (!commands.empty()) {
                engine.addCommand(1, commands.at(0));
                actions.push(engine.update());
                commandCount++;

                commands = listCommands(engine.getState());
//                std::uniform_int_distribution<int> uniform(0, commands.size() - 1);
//                rand = uniform(randgen);
            }

            heuristicChild = minimax_rec_min(engine, depth);
            
            if (heuristicChild > max) {
                max = heuristicChild;
            }
                    
            while (commandCount > 0) {
                engine.undo(actions.top());
                actions.pop();
                commandCount--;
            }
        }
        
        return max;
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
        minimax_rec_max(engine, 0);
        engine.addCommand(1, new engine::EndTurnCommand()); 
        engine.update();
        std::cout << "turn" << std::endl;
    }

    
}

