#include "AI.h"
#include "RandomAI.h"
#include "engine/MoveCommand.h"
#include "engine/AttackCommand.h"

namespace ai {

    std::vector<engine::Command*> AI::listCommands(const state::State& state) {
        std::vector<engine::Command*> commands;
        std::vector<state::Direction> directions;
        std::vector<int> unitsAround;
        
        for(auto& u : state.getBoard().getUnits()) {
            if(u.second.get()->getTeam() == state.getCurrentTeam()) {
                directions = state.getBoard().directionAvailable(u.second.get()->getId());
                
                for(state::Direction d : directions) {
                    commands.push_back(new engine::MoveCommand(u.second.get()->getId(), d));
                }
                
                unitsAround = state.getBoard().findIdUnitAround(u.second.get()->getId());
                
                for(int& uAround : unitsAround) {
                    if(state.getBoard().findUnit(uAround)->getTeam() != u.second.get()->getTeam()) {
                        commands.push_back(new engine::AttackCommand(u.second.get()->getId(), uAround, u.second.get()->getWeapons().find(rand() % 2)->second->getTypeId()));
                    }
                }
            }
        }
        
        return commands;
    }

}
