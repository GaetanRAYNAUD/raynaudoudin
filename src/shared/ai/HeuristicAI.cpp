#include "HeuristicAI.h"
#include "state/House.h"
#include "Point.h"
#include "state/Unit.h"
#include "state/UnitTypeId.h"
#include "engine/AttackCommand.h"
#include "engine/MoveCommand.h"
#include "engine/EndTurnCommand.h"
#include "engine/HandleWinCommand.h"
#include "engine/SpawnCommand.h"

#include <iostream>
using namespace std;

namespace ai {
    
    HeuristicAI::HeuristicAI() {

    }

    void HeuristicAI::initPathMaps(const state::Board& board) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = board.getUnits();
        const std::map<int, std::unique_ptr<state::Terrain> >& terrains = board.getTerrains();

        unitTeam1PathMap.init(board);
        unitTeam2PathMap.init(board);
        houseTeam1PathMap.init(board);
        houseTeam2PathMap.init(board);
        castlePathMap.init(board);
        
        for (auto& u : units) {
            if (u.second->getTeam() == state::TeamId::TEAM_1) {
                unitTeam1PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY()));
                unitTeam2PathMap.addWall(Point(u.second->getPositionX(), u.second->getPositionY()));
            } else if (u.second->getTeam() == state::TeamId::TEAM_2) {
                unitTeam2PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY()));
                unitTeam1PathMap.addWall(Point(u.second->getPositionX(), u.second->getPositionY()));
            }
            houseTeam1PathMap.addWall(Point(u.second->getPositionX(), u.second->getPositionY()));
            houseTeam2PathMap.addWall(Point(u.second->getPositionX(), u.second->getPositionY()));
            castlePathMap.addWall(Point(u.second->getPositionX(), u.second->getPositionY()));
        }
        
        for (auto& t : terrains) {
            if (t.second->getTypeId() == state::TerrainTypeId::HOUSE) {
                switch (((state::House*)t.second.get())->getTeamId()) {
                    case state::TeamId::TEAM_1:
                        houseTeam1PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY()));
                        break;
                    
                    case state::TeamId::TEAM_2:
                        houseTeam2PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY()));
                        break;
                        
                    case state::TeamId::INVALIDTEAM:
                        houseTeam1PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY()));
                        houseTeam2PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY()));
                }
            } else if(t.second->getTypeId() == state::TerrainTypeId::CASTLE) {
                castlePathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY()));
            }
        }
        
        unitTeam1PathMap.update(board);
        unitTeam2PathMap.update(board);
        houseTeam1PathMap.update(board);
        houseTeam2PathMap.update(board);
        castlePathMap.update(board);
    }
    
    void HeuristicAI::run(engine::Engine& engine) {
        std::vector<engine::Command*> commandsAttack;
        std::vector<engine::Command*> commandsMovement;
        std::vector<engine::Command*> commandsSpawn;

        initPathMaps(engine.getState().getBoard());
        listCommandsAttack(engine.getState(), commandsAttack);
        listCommandsMovement(engine.getState(), commandsMovement);
        listCommandsSpawn(engine.getState(), commandsSpawn);
        
        switch (engine.getState().getCurrentTeam()) {
            case state::TeamId::TEAM_1:
                if (commandsSpawn.size() != 0) {
                    engine.addCommand(1, commandsSpawn.front());
                    break;
                }
                if (commandsAttack.size() != 0) {
                    engine.addCommand(1, commandsAttack.front());
                    break;
                }
                if (commandsMovement.size() != 0) {
                    state::Unit* unit = engine.getState().getBoard().findUnit(((engine::MoveCommand*)commandsMovement.front())->getIdUnit());
                    Point pointUnit(unit->getPositionX(), unit->getPositionY());
                    Point bestPoint = unitTeam2PathMap.getBestPoint(unit->getPositionX(), unit->getPositionY());
                    unsigned int it;
                    
                    for (it = 0; it < commandsMovement.size(); it++) {
                        if (unit->getId() == ((engine::MoveCommand*)commandsMovement.at(it))->getIdUnit() && 
                                ((engine::MoveCommand*)commandsMovement.at(it))->getDirection() == bestPoint.transformToDirection(pointUnit)) {
                            engine.addCommand(1, commandsMovement.at(it));
                            break;
                        }
                    }
                    if (it == commandsMovement.size()) {
                        engine.getState().getBoard().findUnit(unit->getId())->setSpeed(0);
                    }
                    break;
                }

                engine.addCommand(1, new engine::EndTurnCommand());
                break;
                
            case state::TeamId::TEAM_2:
                if (commandsSpawn.size() != 0) {
                    engine.addCommand(1, commandsSpawn.front());
                    break;
                }
                if (commandsAttack.size() != 0) {
                    engine.addCommand(1, commandsAttack.front());
                    break;
                }
                if (commandsMovement.size() != 0) {
                    state::Unit* unit = engine.getState().getBoard().findUnit(((engine::MoveCommand*)commandsMovement.front())->getIdUnit());
                    Point pointUnit(unit->getPositionX(), unit->getPositionY());
                    Point bestPoint = unitTeam1PathMap.getBestPoint(unit->getPositionX(), unit->getPositionY());
                    unsigned int it;
                    
                    for (it = 0; it < commandsMovement.size(); it++) {
                        if (unit->getId() == ((engine::MoveCommand*)commandsMovement.at(it))->getIdUnit() && 
                                ((engine::MoveCommand*)commandsMovement.at(it))->getDirection() == bestPoint.transformToDirection(pointUnit)) {
                            engine.addCommand(1, commandsMovement.at(it));
                            break;
                        }
                    }
                    if (it == commandsMovement.size()) {
                        engine.getState().getBoard().findUnit(unit->getId())->setSpeed(0);
                    }
                    break;
                }

                engine.addCommand(1, new engine::EndTurnCommand());
                break;
            
            case state::TeamId::INVALIDTEAM:
                break;
        }
        
        commandsAttack.clear();
        commandsMovement.clear();
        commandsSpawn.clear();
    }

    void HeuristicAI::run(engine::Engine& engine, Json::Value& jsonValue) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = engine.getState().getBoard().getUnits();
        std::vector<engine::Command*> commands;
        Point point(0, 0);
        unsigned int it;

        initPathMaps(engine.getState().getBoard());
        listCommands(engine.getState(), commands);
        
        switch (engine.getState().getCurrentTeam()) {
            case state::TeamId::TEAM_1:
                for (auto& u : units) {
                    if (u.second->getTeam() == state::TeamId::TEAM_1) {
                        if(u.second->getTypeId() == state::UnitTypeId::LEADER) {
                            bool commandSpawn = false;
                            for (it = 0; it < commands.size(); it++) {
                                if (commands.at(it)->getTypeId() == engine::CommandTypeId::SPAWN) {
                                    if (((engine::SpawnCommand*)commands.at(it))->getX() == u.second->getPositionX() && ((engine::SpawnCommand*)commands.at(it))->getY() == u.second->getPositionY()) {
                                        commandSpawn = true;
                                        break;
                                    }
                                }
                            }
                            
                            while (commandSpawn) {
                                engine.addCommand(1, commands.at(it));
                                engine.update(jsonValue);
                                
                                commandSpawn = false;
                                listCommands(engine.getState(), commands);
                                for (it = 0; it < commands.size(); it++) {
                                    if (commands.at(it)->getTypeId() == engine::CommandTypeId::SPAWN) {
                                        if (((engine::SpawnCommand*)commands.at(it))->getX() == u.second->getPositionX() && ((engine::SpawnCommand*)commands.at(it))->getY() == u.second->getPositionY()) {
                                            commandSpawn = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            
                            commands.clear();
                        }

                        listCommands(engine.getState(), commands);
                        if(unitTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight() < houseTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight()) {
                            point = unitTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                        } else {
                            point = houseTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                        }

                        if (unitTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight() == 0) {
                            for (it = 0; it < commands.size(); it++) {
                                if (commands.at(it)->getTypeId() == engine::CommandTypeId::ATTACK) {
                                    if (((engine::AttackCommand*)commands.at(it))->getIdUnitAttacker() == u.second->getId()) {
                                        engine.addCommand(1, commands.at(it));
                                        engine.update(jsonValue);
                                        break;
                                    }
                                }
                            }

                            commands.clear();
                        } else {
                            bool commandMovement = false;
                            for (it = 0; it < commands.size(); it++) {
                                if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                    if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId() 
                                            && ((engine::MoveCommand*)commands.at(it))->getDirection() == 
                                            point.transformToDirection(Point(u.second->getPositionX(), u.second->getPositionY()))) {
                                        commandMovement = true;                                    
                                        break;
                                    }
                                }
                            }

                            while (commandMovement) {
                                engine.addCommand(1, commands.at(it));
                                engine.update(jsonValue);
                                initPathMaps(engine.getState().getBoard());
                                listCommands(engine.getState(), commands);
                                if(unitTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight() < houseTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight()) {
                                    point = unitTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                                } else {
                                    point = houseTeam2PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                                }
                                commandMovement = false;

                                for (it = 0; it < commands.size(); it++) {
                                    if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                        if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId() 
                                                && ((engine::MoveCommand*)commands.at(it))->getDirection() == 
                                                point.transformToDirection(Point(u.second->getPositionX(), u.second->getPositionY()))) {
                                            commandMovement = true;                                    
                                            break;
                                        }
                                    }
                                }
                            }
                            commands.clear();
                        }
                    }
                }               
                break;
                
            case state::TeamId::TEAM_2:
                for (auto& u : units) {
                    if (u.second->getTeam() == state::TeamId::TEAM_2) {
                        if(u.second->getTypeId() == state::UnitTypeId::LEADER) {
                            bool commandSpawn = false;
                            for (it = 0; it < commands.size(); it++) {
                                if (commands.at(it)->getTypeId() == engine::CommandTypeId::SPAWN) {
                                    if (((engine::SpawnCommand*)commands.at(it))->getX() == u.second->getPositionX() && ((engine::SpawnCommand*)commands.at(it))->getY() == u.second->getPositionY()) {
                                        commandSpawn = true;
                                        break;
                                    }
                                }
                            }
                            
                            while (commandSpawn) {
                                engine.addCommand(1, commands.at(it));
                                engine.update(jsonValue);
                                
                                commandSpawn = false;
                                listCommands(engine.getState(), commands);
                                for (it = 0; it < commands.size(); it++) {
                                    if (commands.at(it)->getTypeId() == engine::CommandTypeId::SPAWN) {
                                        if (((engine::SpawnCommand*)commands.at(it))->getX() == u.second->getPositionX() && ((engine::SpawnCommand*)commands.at(it))->getY() == u.second->getPositionY()) {
                                            commandSpawn = true;
                                            break;
                                        }
                                    }
                                }
                            }
                            
                            commands.clear();
                        }
                        
                        listCommands(engine.getState(), commands);
                        if(unitTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight() < houseTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight()) {
                            point = unitTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                        } else {
                            point = houseTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                        }
                        
                        if (unitTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight() == 0) {
                            for (it = 0; it < commands.size(); it++) {
                                if (commands.at(it)->getTypeId() == engine::CommandTypeId::ATTACK) {
                                    if (((engine::AttackCommand*)commands.at(it))->getIdUnitAttacker() == u.second->getId()) {
                                        engine.addCommand(1, commands.at(it));
                                        engine.update(jsonValue);
                                        break;
                                    }
                                }
                            }
                        } else if (point.getWeight() > 0) {
                            bool commandMovement = false;
                            for (it = 0; it < commands.size(); it++) {
                                if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                    if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId() 
                                            && ((engine::MoveCommand*)commands.at(it))->getDirection() == 
                                            point.transformToDirection(Point(u.second->getPositionX(), u.second->getPositionY()))) {
                                        commandMovement = true;                                    
                                        break;
                                    }
                                }
                            }

                            while (commandMovement) {
                                engine.addCommand(1, commands.at(it));
                                engine.update(jsonValue);
                                initPathMaps(engine.getState().getBoard());
                                listCommands(engine.getState(), commands);
                                if(unitTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight() < houseTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY()).getWeight()) {
                                    point = unitTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                                } else {
                                    point = houseTeam1PathMap.getBestPoint(u.second->getPositionX(), u.second->getPositionY());
                                }
                                commandMovement = false;

                                for (it = 0; it < commands.size(); it++) {
                                    if (commands.at(it)->getTypeId() == engine::CommandTypeId::MOVE) {
                                        if (((engine::MoveCommand*)commands.at(it))->getIdUnit() == u.second->getId() 
                                                && ((engine::MoveCommand*)commands.at(it))->getDirection() == 
                                                point.transformToDirection(Point(u.second->getPositionX(), u.second->getPositionY()))) {
                                            commandMovement = true;                                    
                                            break;
                                        }
                                    }
                                }
                            }
                            
                            commands.clear();                            
                        }
                    }
                }
                break;
            
            case state::TeamId::INVALIDTEAM:
                break;
        }
        
            
        engine.addCommand(1, new engine::EndTurnCommand());        
        engine.addCommand(2, new engine::HandleWinCommand());
        engine.update(jsonValue);
        
        commands.clear(); 
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

    const PathMap& HeuristicAI::getCastlePathMap() const {
        return castlePathMap;
    }
    
}
