#include "DeepAI.h"
#include "engine/EndTurnCommand.h"

#include <iostream>

namespace ai {

    DeepAI::DeepAI(int randomSeed): randgen(randomSeed) {

    }
    
    int DeepAI::minimax_rec_min(engine::Engine& engine, int depth) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands;
        int min = std::numeric_limits<int>::max();
        int heuristicChild;
        int leavesCount;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return getHeuristic(engine.getState());
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            listCommands(engine.getState(), commands);
            std::uniform_int_distribution<int> uniform(0, (commands.size() == 0)?commands.size():commands.size() - 1);
            int rand = uniform(randgen);
            
            while (!commands.empty()) {
                engine.addCommand(0, commands.at(rand));
                actions.push(engine.update());
                
                listCommands(engine.getState(), commands);
                std::uniform_int_distribution<int> uniform(0, (commands.size() == 0)?commands.size():commands.size() - 1);
                rand = uniform(randgen);
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
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return getHeuristic(engine.getState());
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            listCommands(engine.getState(), commands);
            std::uniform_int_distribution<int> uniform(0, (commands.size() == 0)?commands.size():commands.size() - 1);
            int rand = uniform(randgen);
            
            while (!commands.empty()) {
                engine.addCommand(0, commands.at(rand));
                actions.push(engine.update());
                
                listCommands(engine.getState(), commands);
                std::uniform_int_distribution<int> uniform(0, (commands.size() == 0)?commands.size():commands.size() - 1);
                rand = uniform(randgen);
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
      
    void DeepAI::minimax_max_init(engine::Engine& engine, int depth, std::stack<std::stack<std::shared_ptr<engine::Action> > > bestActions) {
        std::stack<std::stack<std::shared_ptr<engine::Action>>> actions;
        std::vector<engine::Command*> commands;
        int max = std::numeric_limits<int>::min();
        int heuristicChild;
        int leavesCount;
        
        if (depth == maxDepth || engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
            return;
        }
        depth++;
        
        for (leavesCount = 0; leavesCount < maxLeaves; leavesCount++) {
            listCommands(engine.getState(), commands);
            std::uniform_int_distribution<int> uniform(0, (commands.size() == 0)?commands.size():commands.size() - 1);
            int rand = uniform(randgen);
            
            while (!commands.empty()) {
                engine.addCommand(0, commands.at(rand));
                actions.push(engine.update());
                
                listCommands(engine.getState(), commands);
                std::uniform_int_distribution<int> uniform(0, (commands.size() == 0)?commands.size():commands.size() - 1);
                rand = uniform(randgen);
            }
            engine.addCommand(0, new engine::EndTurnCommand());
            actions.push(engine.update());

            heuristicChild = minimax_rec_min(engine, depth);
            
            if (heuristicChild > max) {
                max = heuristicChild;
                
                while (!bestActions.empty()) {
                    actions.pop();
                }                
                while (!actions.empty()) {
                    bestActions.push(actions.top());
                    engine.undo(actions.top());
                    actions.pop();
                } 
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

    void DeepAI::run(engine::Engine& engine) {
        minimax_rec_max(engine, 0);
        engine.addCommand(0, new engine::EndTurnCommand()); 
        engine.update();
        std::cout << "turn" << std::endl;
    }
    
}

