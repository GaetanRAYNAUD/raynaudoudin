#include "DeepAI.h"
#include "engine/EndTurnCommand.h"
#include "state/House.h"

namespace ai {

    DeepAI::DeepAI(int randomSeed): randgen(randomSeed) {
        maxLeaves = 5;
        maxDepth = 4;
    }
    
    engine::Command* DeepAI::run(engine::Engine& engine, state::TeamId player) {
        if(engine.getState().getCurrentTeam() != player || player == state::TeamId::INVALIDTEAM) {
            return nullptr;
        }
        
        std::vector<engine::Command*> bestCommands;
        
        this->player = player;

        minimax_max_init(engine, 0, bestCommands);
        
        for(unsigned int i = 0; i < bestCommands.size(); i++) {
            engine.addCommand(i, bestCommands.at(i));
        }
        
        return nullptr;
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
        
        for (leavesCount = 0; leavesCount < maxLeaves * 2; leavesCount++) {
            listCommands(engine.getState(), commands);            
            rand = uniform(0, commands.size() - 1);
            engine.addCommand(0, commands.at(rand));
            engine.addCommand(1, new engine::EndTurnCommand());
            currentCommands.push_back(commands.at(rand)->clone());
            currentCommands.push_back(new engine::EndTurnCommand());
            actions.push(engine.update());

            heuristicChild = minimax_rec_min(engine, depth);
            
            if (heuristicChild > max) {
                max = heuristicChild;

                bestCommand.clear();
                bestCommand = currentCommands;
            }
                    
            while (!actions.empty()) {
                engine.undo(actions.top());
                actions.pop();
            }
            
            currentCommands.clear();
        }
        
        commands.clear();
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
            rand = uniform(0, commands.size() - 1);
            engine.addCommand(0, commands.at(rand));
            engine.addCommand(1, new engine::EndTurnCommand());
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
            rand = uniform(0, commands.size() - 1);
            engine.addCommand(0, commands.at(rand));
            engine.addCommand(1, new engine::EndTurnCommand());
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

    int DeepAI::getHeuristic(const state::State& state) {
        int heuristic = 0;
        
        initPathMaps(state.getBoard());
        switch (player) {
            case state::TeamId::TEAM_1:
                for (auto& u : state.getBoard().getUnits()) {
                    switch (u.second->getTeam()) {
                        case state::TeamId::TEAM_1:
                            heuristic = heuristic + u.second->getLife();
                            heuristic = heuristic - team2PathMap.getPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight();
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
                for (auto& u : state.getBoard().getUnits()) {
                    switch (u.second->getTeam()) {
                        case state::TeamId::TEAM_1:
                            heuristic = heuristic - u.second->getLife();
                            break;
                        case state::TeamId::TEAM_2:
                            heuristic = heuristic + u.second->getLife();
                            heuristic = heuristic - team1PathMap.getPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight();
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
    
    void DeepAI::initPathMaps(const state::Board& board) {
        team1PathMap.init(board);
        team2PathMap.init(board);
        
        for (auto& u : board.getUnits()) {
            if (u.second->getTeam() == state::TeamId::TEAM_1) {
                team1PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY()));
            } else if (u.second->getTeam() == state::TeamId::TEAM_2) {
                team2PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY()));
            }
        }
        
        team1PathMap.update(board);
        team2PathMap.update(board);
    }
    
    int DeepAI::uniform(int min, int max) {
        std::uniform_int_distribution<int> uniform(min, (max >= min)?max:min);
        
        return uniform(randgen);
    }

}

