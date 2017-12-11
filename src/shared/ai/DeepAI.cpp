#include "DeepAI.h"
#include "engine/EndTurnCommand.h"

#include<iostream>

namespace ai {

    DeepAI::DeepAI(int randomSeed): randgen(randomSeed) {

    }
    
    void DeepAI::run(engine::Engine& engine) {
        std::vector<engine::Command*> bestCommands;
        
        minimax_max_init(engine, 0, bestCommands);
        
        for(int i = 0; (unsigned int)i < bestCommands.size(); i++) {
            engine.addCommand(i, bestCommands.at(i));
        }
        engine.update();
        
        engine.addCommand(0, new engine::EndTurnCommand()); 
        engine.update();
    }
    
    int DeepAI::minimax_rec_min(engine::Engine& engine, int depth) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands;
        int min = std::numeric_limits<int>::max();
        int heuristicChild;
        int leavesCount;
        int rand;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return getHeuristic(engine.getState());
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {            
            listCommands(engine.getState(), commands);
            while (!commands.empty()) {
                rand = uniform(0, commands.size() - 1);
                engine.addCommand(0, commands.at(rand));
                actions.push(engine.update());
                listCommands(engine.getState(), commands);
            }
            engine.addCommand(0, new engine::EndTurnCommand());
            actions.push(engine.update());          

            heuristicChild = minimax_rec_max(engine, depth);
            
            if (heuristicChild < min) {
                min = heuristicChild;
            }
                    
            while (!actions.empty()) {
                engine.undo(actions.top());
                actions.pop();
            }
        }
        
        commands.clear();
        
        return min;
    }
    
    int DeepAI::minimax_rec_max(engine::Engine& engine, int depth) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands;
        int max = std::numeric_limits<int>::min();
        int heuristicChild;
        int leavesCount;
        int rand;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return getHeuristic(engine.getState());
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            listCommands(engine.getState(), commands);
            while (!commands.empty()) {
                rand = uniform(0, commands.size() - 1);
                engine.addCommand(0, commands.at(rand));
                actions.push(engine.update());
                listCommands(engine.getState(), commands);
            }
            engine.addCommand(0, new engine::EndTurnCommand());
            actions.push(engine.update());

            heuristicChild = minimax_rec_min(engine, depth);
            
            if (heuristicChild > max) {
                max = heuristicChild;
            }
                    
            while (!actions.empty()) {
                engine.undo(actions.top());
                actions.pop();
            }
        }
        
        commands.clear();
        
        return max;
    }
      
    void DeepAI::minimax_max_init(engine::Engine& engine, int depth, std::vector<engine::Command*>& bestCommand) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands;
        std::vector<engine::Command*> currentCommands;
        int max = std::numeric_limits<int>::min();
        int heuristicChild;
        int leavesCount;
        int rand;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return;
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            listCommands(engine.getState(), commands);
            while (!commands.empty()) {
                rand = uniform(0, commands.size() - 1);
                engine.addCommand(0, commands.at(rand));
                for(auto& c : engine.getCurrentCommands()) {
                    currentCommands.push_back(c.second->clone());
                }
                actions.push(engine.update());
                listCommands(engine.getState(), commands);
            }
            
            engine.addCommand(0, new engine::EndTurnCommand());
            actions.push(engine.update());

            heuristicChild = minimax_rec_min(engine, depth);
            
            if (heuristicChild > max) {
                max = heuristicChild;

                bestCommand.clear();
                bestCommand = currentCommands;  
                currentCommands.clear();
            }
                    
            while (!actions.empty()) {
                engine.undo(actions.top());
                actions.pop();
            }
        }
        
        commands.clear();
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
    
    int DeepAI::uniform(int min, int max) {
        std::uniform_int_distribution<int> uniform(min, (max >= min)?max:min);
        
        return uniform(randgen);
    }

}

