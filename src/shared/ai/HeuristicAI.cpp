#include "HeuristicAI.h"
#include "state/House.h"
#include "Point.h"
#include "state/Unit.h"
#include "engine/AttackCommand.h"
#include "engine/MoveCommand.h"
#include "engine/EndTurnCommand.h"
#include "engine/HandleWinCommand.h"

namespace ai {
    
    HeuristicAI::HeuristicAI(int randomSeed): randgen(randomSeed) {

    }

    const PathMap& HeuristicAI::getHouseTeam1PathMap() const {
        return houseTeam1PathMap;
    }

    const PathMap& HeuristicAI::getHouseTeam2PathMap() const {
        return houseTeam2PathMap;
    }

    const PathMap& HeuristicAI::getUnitTeam1PathMap() const {
        return unitTeam1PathMap;
    }

    const PathMap& HeuristicAI::getUnitTeam2PathMap() const {
        return unitTeam2PathMap;
    }

    void HeuristicAI::initPathMaps(const state::Board& board) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = board.getUnits();
        const std::map<int, std::unique_ptr<state::Terrain> >& terrains = board.getTerrains();

        unitTeam1PathMap.init(board);
        unitTeam2PathMap.init(board);
        houseTeam1PathMap.init(board);
        houseTeam2PathMap.init(board);
        
        for (auto& u : units) {
            if (u.second->getTeam() == state::TeamId::TEAM_1) {
                unitTeam1PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY(), 0));
            } else if (u.second->getTeam() == state::TeamId::TEAM_2) {
                unitTeam2PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY(), 0));
            }
        }
        
        for (auto& t : terrains) {
            if (t.second->getTypeId() == state::TerrainTypeId::HOUSE) {
                switch (((state::House*)t.second.get())->getTeamId()) {
                    case state::TeamId::TEAM_1:
                        houseTeam1PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                        break;
                    
                    case state::TeamId::TEAM_2:
                        houseTeam2PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                        break;
                        
                    case state::TeamId::INVALIDTEAM:
                        houseTeam1PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                        houseTeam2PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                }
            }
        }
        
        unitTeam1PathMap.update(board);
        unitTeam2PathMap.update(board);
        houseTeam1PathMap.update(board);
        houseTeam2PathMap.update(board);
    }
    
    void HeuristicAI::run(engine::Engine& engine) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = engine.getState().getBoard().getUnits();
        std::vector<engine::Command*> commands;
        unsigned int it;

        initPathMaps(engine.getState().getBoard());
        commands = listCommands(engine.getState());
        
        switch (engine.getState().getCurrentTeam()) {
            case state::TeamId::TEAM_1:
                for (auto& u : units) {
                            if (u.second->getTeam() == state::TeamId::TEAM_1) {
                                Point point = unitTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                                if (point.getWeight() == 0) {
                                    for (it = 0; it < commands.size(); it++) {
                                        if (commands.at(it)->getTypeId() == engine::CommandTypeId::ATTACK) {
                                            if (((engine::AttackCommand*)commands.at(it))->getIdUnitAttacker() == u.second->getId()) {
                                                engine.addCommand(1, commands.at(it));
                                                engine.update();
                                                break;
                                            }
                                        }
                                    }
                                } else if (point.getWeight() > 0) {
                                    bool commandMovement = false;
                                    for (it = 0; it < commands.size(); it++) {
                                        if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                            if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId()) {
                                                commandMovement = true;                                    
                                                break;
                                            }
                                        }
                                    }

                                    while (commandMovement) {
                                        engine.addCommand(1, commands.at(it));
                                        engine.update();
                                        initPathMaps(engine.getState().getBoard());
                                        commands = listCommands(engine.getState());
                                        commandMovement = false;

                                        for (it = 0; it < commands.size(); it++) {
                                            if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                                if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId()) {
                                                    commandMovement = true;                                    
                                                    break;
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }                
                break;
                
            case state::TeamId::TEAM_2:
                for (auto& u : units) {
                            if (u.second->getTeam() == state::TeamId::TEAM_2) {
                                Point point = unitTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                                if (point.getWeight() == 0) {
                                    for (it = 0; it < commands.size(); it++) {
                                        if (commands.at(it)->getTypeId() == engine::CommandTypeId::ATTACK) {
                                            if (((engine::AttackCommand*)commands.at(it))->getIdUnitAttacker() == u.second->getId()) {
                                                engine.addCommand(1, commands.at(it));
                                                engine.update();
                                                break;
                                            }
                                        }
                                    }
                                } else if (point.getWeight() > 0) {
                                    bool commandMovement = false;
                                    for (it = 0; it < commands.size(); it++) {
                                        if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                            if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId() 
                                                    && ((engine::MoveCommand*)commands.at(it))->getDirection() == point.) {
                                                commandMovement = true;                                    
                                                break;
                                            }
                                        }
                                    }

                                    while (commandMovement) {
                                        engine.addCommand(1, commands.at(it));
                                        engine.update();
                                        initPathMaps(engine.getState().getBoard());
                                        commands = listCommands(engine.getState());
                                        commandMovement = false;

                                        for (it = 0; it < commands.size(); it++) {
                                            if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                                if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId()) {
                                                    commandMovement = true;                                    
                                                    break;
                                                }
                                            }
                                        }

                                    }
                                }
                            }
                        }                
                break;
            
            case state::TeamId::INVALIDTEAM:
                break;
        }
        
            
        engine.addCommand(1, new engine::EndTurnCommand());        
        engine.addCommand(2, new engine::HandleWinCommand());
        engine.update();
        
        commands.clear();      
    }

}
