#include "AI.h"
#include "RandomAI.h"
#include "engine/MoveCommand.h"
#include "engine/AttackCommand.h"
#include "engine/SpawnCommand.h"
#include "engine/EndTurnCommand.h"

namespace ai {

    void AI::listCommandsMovement(const state::State& state, std::vector<engine::Command*>& commands) {
        const std::map<int, std::unique_ptr<state::Unit>>& units = state.getBoard().getUnits();
        std::vector<state::Direction> directions;
        
        commands.clear();
        
        for (auto& u : units) {
            if(u.second->getTeam() == state.getCurrentTeam()) {
                directions = state.getBoard().directionAvailable(u.second->getId());

                for(state::Direction d : directions) {
                    commands.push_back(new engine::MoveCommand(u.second->getId(), d));
                }
            }
        }
    }
    
    void AI::listCommandsSpawn(const state::State& state, std::vector<engine::Command*>& commands) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = state.getBoard().getUnits();
        
        commands.clear();
    
        for (auto& u : units) {
            if(u.second->getTeam() == state.getCurrentTeam()) {
                if(u.second->getTypeId() == state::UnitTypeId::LEADER) {
                    if(state.getBoard().findTeam(u.second->getTeam())->verifyGold(state::UnitTypeId::SWORDMAN) && 
                            state.getBoard().findTerrainOnPosition(u.second->getPositionX(), u.second->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                        commands.push_back(new engine::SpawnCommand(u.second->getPositionX(), u.second->getPositionY(), state::UnitTypeId::SWORDMAN));
                    }

                    if(state.getBoard().findTeam(u.second->getTeam())->verifyGold(state::UnitTypeId::BOWMAN) && 
                            state.getBoard().findTerrainOnPosition(u.second->getPositionX(), u.second->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                        commands.push_back(new engine::SpawnCommand(u.second->getPositionX(), u.second->getPositionY(), state::UnitTypeId::BOWMAN));
                    }

                    break;
                }
            }
        }
    }
    
    void AI::listCommandsAttack(const state::State& state, std::vector<engine::Command*>& commands) {
       const std::map<int, std::unique_ptr<state::Unit> >& units = state.getBoard().getUnits();
        std::vector<int> unitsAround;
        
        commands.clear();
        
        for (auto& u : units) {
            if(u.second->getTeam() == state.getCurrentTeam()) {
                if(u.second->getSpeed() > 0) {
                    unitsAround = state.getBoard().findIdUnitsAround(u.second->getId());

                    for(auto& uAround : unitsAround) {
                        if(units.at(uAround)->getTeam() != u.second->getTeam()) {
                            for(auto& w : u.second->getWeapons()) {
                                commands.push_back(new engine::AttackCommand(u.second->getId(), uAround, w.second.get()->getTypeId()));
                            }
                        }
                    }
                }
            }
        }
    }

    void AI::listCommands(const state::State& state, std::vector<engine::Command*>& commands) {
        std::vector<state::Direction> directions;
        std::vector<int> unitsAround;
        
        commands.clear();
                
        for(auto& u : state.getBoard().getUnits()) {
            if(u.second->getTeam() == state.getCurrentTeam()) {
                directions = state.getBoard().directionAvailable(u.second->getId());
                
                for(state::Direction d : directions) {
                    commands.push_back(new engine::MoveCommand(u.second->getId(), d));
                }
                
                if(u.second->getSpeed() > 0) {
                    unitsAround = state.getBoard().findIdUnitsAround(u.second->getId());

                    for(auto& uAround : unitsAround) {
                        if(state.getBoard().findUnit(uAround)->getTeam() != u.second->getTeam()) {
                            for(auto& w : u.second->getWeapons()) {
                                commands.push_back(new engine::AttackCommand(u.second->getId(), uAround, w.second.get()->getTypeId()));
                            }
                        }
                    }
                }
                
                if(u.second->getTypeId() == state::UnitTypeId::LEADER) {
                    if(state.getBoard().findTeam(u.second->getTeam())->verifyGold(state::UnitTypeId::SWORDMAN) && state.getBoard().findTerrainOnPosition(u.second->getPositionX(), u.second->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                        commands.push_back(new engine::SpawnCommand(u.second->getPositionX(), u.second->getPositionY(), state::UnitTypeId::SWORDMAN));
                    }
                    
                    if(state.getBoard().findTeam(u.second->getTeam())->verifyGold(state::UnitTypeId::BOWMAN) && state.getBoard().findTerrainOnPosition(u.second->getPositionX(), u.second->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                        commands.push_back(new engine::SpawnCommand(u.second->getPositionX(), u.second->getPositionY(), state::UnitTypeId::BOWMAN));
                    }
                }
            }
        }
    }    
    
    AI::~AI() {

    }

}
