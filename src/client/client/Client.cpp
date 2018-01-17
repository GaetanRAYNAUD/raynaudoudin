#include "Client.h"
#include "render/Scene.h"
#include "engine/LoadCommand.h"
#include "engine/EndTurnCommand.h"
#include "ai/RandomAI.h"
#include "engine/SpawnCommand.h"
#include "engine/AttackCommand.h"
#include "engine/MoveCommand.h"
#include "engine/HandleWinCommand.h"

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
                    if(((engine::SpawnCommand*)c)->getX() == startingTerrain->getPositionX() && ((engine::SpawnCommand*)c)->getY() == startingTerrain->getPositionY()) {
                        commandToReturn = c->clone();
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

            engine.addCommand(0, new engine::LoadCommand("res/map.txt"));

        }
    }


    void Client::run() {
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    startMousePos = sf::Mouse::getPosition(window);
                    
                    if(!scene.getMenu() && startMousePos.x > 18 && startMousePos.y > 36 && engine.getState().getCurrentTeam() == teamId) {
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
                    
                    if(!scene.getMenu() && startMousePos.x > windowWidth - 110 && startMousePos.y < 36 && engine.getState().getCurrentTeam() == teamId) {
                        engine.addCommand(1, new engine::EndTurnCommand());
                    }
                }
            }
            
            if(scene.getMenu()) {            
                if(startMousePos.x >= 550 && startMousePos.x <= 630 && startMousePos.y >= 360 && startMousePos.y <= 400) {
                    scene.setMenu(false);
                    
                    engine.addCommand(0, new engine::LoadCommand("res/map.txt"));
                    
                }
                
            } else {
                if(engine.getState().getCurrentTeam() == teamId) {                        
                    if(startingTerrain != nullptr && targetTerrain != nullptr) {
                        
                        engine.addCommand(engine.getCurrentCommands().size(), generateCommand());

                        startingTerrain = nullptr;
                        targetTerrain = nullptr;
                    }
                }
            }

            if(engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {                
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
        
        if(engine.getState().getWinner() == state::TeamId::INVALIDTEAM) {
            if(teamId == state::TeamId::TEAM_1) {
                engine.getState().setWinner(state::TeamId::TEAM_2);
            } else {
                engine.getState().setWinner(state::TeamId::TEAM_1);
            }               
        }
    }

}