#include "Client.h"
#include "render/Scene.h"
#include "engine/LoadCommand.h"
#include "engine/EndTurnCommand.h"
#include "ai/RandomAI.h"
#include "engine/SpawnCommand.h"
#include "engine/AttackCommand.h"
#include "engine/MoveCommand.h"
#include "engine/HandleWinCommand.h"

#include <iostream>
namespace client {

    Client::Client(engine::Engine& engine, state::TeamId teamId) : engine(engine), scene(engine.getState()), window(sf::VideoMode(windowWidth, windowHeight), "BfW"), teamId(teamId) {
        window.setFramerateLimit(60);
        
        scene.setMenu(true);        
    }

    engine::Command* Client::generateCommand() {
        engine::Command* commandToReturn = nullptr;
        state::Unit* controlledUnit = engine.getState().getBoard().findUnitOnPosition(startingTerrain->getPositionX(), startingTerrain->getPositionY());
        state::Unit* targetUnit = engine.getState().getBoard().findUnitOnPosition(targetTerrain->getPositionX(), targetTerrain->getPositionY());
        ai::RandomAI* aiToGetAvailableCommands = new ai::RandomAI(0);
        std::vector<engine::Command*> commandsAttack;
        std::vector<engine::Command*> commandsMovement;
        std::vector<engine::Command*> commandsSpawn;

        aiToGetAvailableCommands->listCommandsAttack(engine.getState(), commandsAttack);
        aiToGetAvailableCommands->listCommandsMovement(engine.getState(), commandsMovement);
        aiToGetAvailableCommands->listCommandsSpawn(engine.getState(), commandsSpawn);
        
        if(!commandsSpawn.empty()) {
            if(targetTerrain->getTypeId() == state::TerrainTypeId::WALL_LEFT 
                    || targetTerrain->getTypeId() == state::TerrainTypeId::WALL_RIGHT 
                    || targetTerrain->getTypeId() == state::TerrainTypeId::WALL_TOP) {
                
                for(auto& c : commandsSpawn) {
                    if(((engine::SpawnCommand*)c)->getX() == startingTerrain->getPositionX() 
                            && ((engine::SpawnCommand*)c)->getY() == startingTerrain->getPositionY() 
                            && ((engine::SpawnCommand*)c)->getUnitTypeId() == unitSpawnTypeId) {
                        
                        commandToReturn = c->clone();
                        unitSpawnTypeId = state::UnitTypeId::INVALID_UNIT;
                        break;
                    }
                }
                
            }
        }
        
        if(!commandsAttack.empty() && commandToReturn == nullptr) {
            if(targetUnit != nullptr && targetUnit->getTeam() != teamId) {
                for(auto& c : commandsAttack) {
                    if(((engine::AttackCommand*)c)->getIdUnitAttacker() == controlledUnit->getId() 
                            && ((engine::AttackCommand*)c)->getIdUnitDefender() == targetUnit->getId()) {
                        
                        commandToReturn = c->clone();
                        break;
                    }
                }
            }
        }
        
        if(!commandsMovement.empty() && commandToReturn == nullptr) {
            for(auto& c : commandsMovement) {
                if(((engine::MoveCommand*)c)->getIdUnit() == controlledUnit->getId() 
                        && ((engine::MoveCommand*)c)->getDirection() == engine.getState().getBoard().getDirectionFromTerrains(startingTerrain, targetTerrain)) {
                    
                    commandToReturn = c->clone();
                    break;
                }
            }
        }
        
        for(auto& c : commandsAttack) {
            delete  c;
        }
        
        for(auto& c : commandsMovement) {
            delete  c;
        }
        
        for(auto& c : commandsSpawn) {
            delete  c;
        }
        
        delete aiToGetAvailableCommands;
        
        if(commandToReturn == nullptr) {
            commandToReturn = new engine::HandleWinCommand();
        }
        
        return commandToReturn;
    }

    void Client::displayBoard() {
        if(startMousePos.x > 18 && startMousePos.y > 36 && engine.getState().getCurrentTeam() == teamId) {
            state::Terrain* terrainClickedOn = scene.getTerrainFromPositionOnWindow(startMousePos.x, startMousePos.y);

            if(startingTerrain == nullptr) {
                if(engine.getState().getBoard().findUnitOnPosition(terrainClickedOn->getPositionX(), terrainClickedOn->getPositionY()) != nullptr 
                        && engine.getState().getBoard().findUnitOnPosition(terrainClickedOn->getPositionX(), terrainClickedOn->getPositionY())->getTeam() == teamId) {                            

                    startingTerrain = terrainClickedOn;

                }

            } else if (startingTerrain->getId() == terrainClickedOn->getId()) {
                startingTerrain = nullptr;
                targetTerrain = nullptr;

            } else if (targetTerrain == nullptr) {
                targetTerrain = terrainClickedOn;

            } else if(targetTerrain->getId() == terrainClickedOn->getId()) {
                targetTerrain = nullptr;
            }
        }

        if (targetTerrain != nullptr && unitSpawnTypeId == state::UnitTypeId::INVALID_UNIT) {
            if((targetTerrain->getTypeId() == state::TerrainTypeId::WALL_LEFT 
                    || targetTerrain->getTypeId() == state::TerrainTypeId::WALL_RIGHT 
                    || targetTerrain->getTypeId() == state::TerrainTypeId::WALL_TOP) 
                    && engine.getState().getBoard().findUnitOnPosition(startingTerrain->getPositionX(), startingTerrain->getPositionY())->getTypeId() == state::UnitTypeId::LEADER) {

                mode = 2;
                return;
            }
        }   
        
        if(startMousePos.x > windowWidth - 110 && startMousePos.y < 36 && engine.getState().getCurrentTeam() == teamId) {
            engine.addCommand(1, new engine::EndTurnCommand());
        }
            
        if(engine.getState().getCurrentTeam() == teamId) {                        
            if(startingTerrain != nullptr && targetTerrain != nullptr) {

                engine.addCommand(engine.getCurrentCommands().size(), generateCommand());

                startingTerrain = nullptr;
                targetTerrain = nullptr;
            }
        }
    }

    void Client::displayMenu() {
        if(startMousePos.x >= 550 && startMousePos.x <= 630 && startMousePos.y >= 360 && startMousePos.y <= 400) {
            scene.setMenu(false);
            mode = 1;

            engine.addCommand(0, new engine::LoadCommand("res/map.txt"));
            engine.update();
        }
    }

    void Client::displaySpawn() {
        int posXSwordman, posYSwordman, posXBowman, posYBowman;
        
        posXSwordman = targetTerrain->getPositionX() * 72 - targetTerrain->getPositionX() * 72 / 4;
        posYSwordman = targetTerrain->getPositionY() * 36 + 10;
        
        posXBowman = posXSwordman;
        posYBowman = posYSwordman + 20;
        
        scene.getDebugLayer().getSurface()->addText(posXSwordman, posYSwordman, "Swordman", sf::Color::White, 13);        
        scene.getDebugLayer().getSurface()->addText(posXBowman, posYBowman, "Bowman", sf::Color::White, 13);
        
        if(startMousePos.x > posXSwordman && startMousePos.x < posXSwordman + 72 
                && startMousePos.y > posYSwordman && startMousePos.y < posYSwordman + 13) {
            
            unitSpawnTypeId = state::UnitTypeId::SWORDMAN;
            mode = 1;
        }
        
        if(startMousePos.x > posXBowman && startMousePos.x < posXBowman + 72 
                && startMousePos.y > posYBowman && startMousePos.y < posYBowman + 13) {
            
            unitSpawnTypeId = state::UnitTypeId::BOWMAN;
            mode = 1;
        }
        
    }

    void Client::run() {
        while (window.isOpen()) {
            sf::Event event;
            
            startMousePos.x = -1;
            startMousePos.y = -1;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    startMousePos = sf::Mouse::getPosition(window);
                }
            }
            
            switch (mode) {
                case 0: 
                    displayMenu();
                    break;
                    
                case 1:
                    displayBoard();
                    break;
                
                case 2:
                    displaySpawn();
                    break;
            }

            if(engine.getState().getWinner() != state::TeamId::INVALID_TEAM) {                
                if(engine.getState().getWinner() == teamId) {
                    scene.getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, "Victoire !", sf::Color::Green, 50);
                } else {
                    scene.getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, "Defaite !", sf::Color::Red, 50);
                }
            }
            
            scene.getDebugLayer().getSurface()->addText(windowWidth - 110, 5, "Fin du tour", sf::Color::White, 18);
            scene.stateChanged();
            scene.draw(window);
            
            window.display();
        }
        
        if(engine.getState().getWinner() == state::TeamId::INVALID_TEAM) {
            if(teamId == state::TeamId::TEAM_1) {
                engine.getState().setWinner(state::TeamId::TEAM_2);
            } else {
                engine.getState().setWinner(state::TeamId::TEAM_1);
            }               
        }
    }

}