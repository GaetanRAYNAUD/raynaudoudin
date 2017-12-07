#include "AI.h"
#include "RandomAI.h"
#include "engine/MoveCommand.h"
#include "engine/AttackCommand.h"
#include "engine/SpawnCommand.h"
#include "engine/EndTurnCommand.h"


#include <iostream>
namespace ai {

    void AI::listCommandsMovement(const state::State& state, int idUnit, std::vector<engine::Command*>& commands) {
        state::Unit* unit = state.getBoard().findUnit(idUnit);
        std::vector<state::Direction> directions;
        
        commands.clear();
        
        if(unit->getTeam() == state.getCurrentTeam()) {
            directions = state.getBoard().directionAvailable(unit->getId());

            for(state::Direction d : directions) {
                commands.push_back(new engine::MoveCommand(unit->getId(), d));
            }
        }
    }
    
    void AI::listCommandsSpawn(const state::State& state, int idUnit, std::vector<engine::Command*>& commands) {
        state::Unit* unit = state.getBoard().findUnit(idUnit);
        
        commands.clear();
    
        if(unit->getTeam() == state.getCurrentTeam() && unit->getTypeId() == state::UnitTypeId::LEADER) {
            if(state.getBoard().findTeam(unit->getTeam())->verifyGold(state::UnitTypeId::SWORDMAN) && state.getBoard().findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                commands.push_back(new engine::SpawnCommand(unit->getPositionX(), unit->getPositionY(), state::UnitTypeId::SWORDMAN));
            }

            if(state.getBoard().findTeam(unit->getTeam())->verifyGold(state::UnitTypeId::BOWMAN) && state.getBoard().findTerrainOnPosition(unit->getPositionX(), unit->getPositionY())->getTypeId() == state::TerrainTypeId::CASTLE) {
                commands.push_back(new engine::SpawnCommand(unit->getPositionX(), unit->getPositionY(), state::UnitTypeId::BOWMAN));
            }
        }
    }
    
    void AI::listCommandsAttack(const state::State& state, int idUnit, std::vector<engine::Command*>& commands) {
        state::Unit* unit = state.getBoard().findUnit(idUnit);
        std::vector<int> unitsAround;
        
        commands.clear();
        
        unitsAround = state.getBoard().findIdUnitAround(unit->getId());

        for(auto& uAround : unitsAround) {
            if(state.getBoard().findUnit(uAround)->getTeam() != unit->getTeam()) {
                for(auto& w : unit->getWeapons()) {
                    commands.push_back(new engine::AttackCommand(unit->getId(), uAround, w.second.get()->getTypeId()));
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
                
                unitsAround = state.getBoard().findIdUnitAround(u.second->getId());
                
                for(auto& uAround : unitsAround) {
                    if(state.getBoard().findUnit(uAround)->getTeam() != u.second->getTeam()) {
                        for(auto& w : u.second->getWeapons()) {
                            commands.push_back(new engine::AttackCommand(u.second->getId(), uAround, w.second.get()->getTypeId()));
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
