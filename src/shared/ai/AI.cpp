#include "AI.h"
#include "RandomAI.h"
#include "engine/MoveCommand.h"
#include "engine/AttackCommand.h"
#include "engine/SpawnCommand.h"
#include "engine/EndTurnCommand.h"

namespace ai {

    std::vector<engine::Command*> AI::listCommandsMovement(const state::State& state) {
        std::vector<engine::Command*> commands;
        std::vector<state::Direction> directions;
        
        for(auto& u : state.getBoard().getUnits()) {
            if(u.second.get()->getTeam() == state.getCurrentTeam()) {
                directions = state.getBoard().directionAvailable(u.second.get()->getId());
                
                for(state::Direction d : directions) {
                    commands.push_back(new engine::MoveCommand(u.second.get()->getId(), d));
                }
            }
        }
        
        return commands;
    }
    
    std::vector<engine::Command*> AI::listCommandsSpawn(const state::State& state) {
        std::vector<engine::Command*> commands;
    
        for(auto& u : state.getBoard().getUnits()) {
            if(u.second.get()->getTeam() == state.getCurrentTeam() && u.second.get()->getTypeId() == state::UnitTypeId::LEADER) {
                if(state.getBoard().findTeam(u.second.get()->getTeam())->verifyGold(state::UnitTypeId::SWORDMAN) && state.getBoard().findTerrainOnPosition(u.second.get()->getPositionX(), u.second.get()->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                    commands.push_back(new engine::SpawnCommand(u.second.get()->getPositionX(), u.second.get()->getPositionY(), state::UnitTypeId::SWORDMAN));
                }

                if(state.getBoard().findTeam(u.second.get()->getTeam())->verifyGold(state::UnitTypeId::BOWMAN) && state.getBoard().findTerrainOnPosition(u.second.get()->getPositionX(), u.second.get()->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                    commands.push_back(new engine::SpawnCommand(u.second.get()->getPositionX(), u.second.get()->getPositionY(), state::UnitTypeId::BOWMAN));
                }

                break;
            }
        }
        
        return commands;
    }
    
    std::vector<engine::Command*> AI::listCommandsAttack(const state::State& state) {
        std::vector<engine::Command*> commands;
        std::vector<int> unitsAround;
        
        for(auto& u : state.getBoard().getUnits()) {
            unitsAround = state.getBoard().findIdUnitAround(u.second.get()->getId());

            for(auto& uAround : unitsAround) {
                if(state.getBoard().findUnit(uAround)->getTeam() != u.second.get()->getTeam()) {
                    for(auto& w : u.second.get()->getWeapons()) {
                        commands.push_back(new engine::AttackCommand(u.second.get()->getId(), uAround, w.second.get()->getTypeId()));
                    }
                }
            }
        }
        
        return commands;
    }

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
                
                for(auto& uAround : unitsAround) {
                    if(state.getBoard().findUnit(uAround)->getTeam() != u.second.get()->getTeam()) {
                        for(auto& w : u.second.get()->getWeapons()) {
                            commands.push_back(new engine::AttackCommand(u.second.get()->getId(), uAround, w.second.get()->getTypeId()));
                        }
                    }
                }
                
                if(u.second.get()->getTypeId() == state::UnitTypeId::LEADER) {
                    if(state.getBoard().findTeam(u.second.get()->getTeam())->verifyGold(state::UnitTypeId::SWORDMAN) && state.getBoard().findTerrainOnPosition(u.second.get()->getPositionX(), u.second.get()->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                        commands.push_back(new engine::SpawnCommand(u.second.get()->getPositionX(), u.second.get()->getPositionY(), state::UnitTypeId::SWORDMAN));
                    }
                    
                    if(state.getBoard().findTeam(u.second.get()->getTeam())->verifyGold(state::UnitTypeId::BOWMAN) && state.getBoard().findTerrainOnPosition(u.second.get()->getPositionX(), u.second.get()->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                        commands.push_back(new engine::SpawnCommand(u.second.get()->getPositionX(), u.second.get()->getPositionY(), state::UnitTypeId::BOWMAN));
                    }
                }
            }
        }
        
        return commands;
    }
    
    AI::~AI() {

    }

}
