#include "Client.h"
#include "render/Scene.h"
#include "engine/LoadCommand.h"
#include "engine/EndTurnCommand.h"

namespace client {

    Client::Client(engine::Engine& engine, state::TeamId teamId) : teamId(teamId), engine(engine) {
        
    }

    engine::Command* Client::generateCommand() {
        return nullptr;
    }

    void Client::run() {
        int windowWidth = 1188;
        int windowHeight = 576;  
        render::Scene scene(engine.getState());
        sf::Vector2i startMousePos, endMousePos;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
        state::Terrain* terrainClickedOn = nullptr;
        
        window.setFramerateLimit(60);
        window.setView(view);
        
        scene.setMenu(true);
        
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    endMousePos = sf::Mouse::getPosition(window);
                    
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    startMousePos = sf::Mouse::getPosition(window);
                    
                    if(!scene.getMenu() && startMousePos.x > 18 && startMousePos.y > 36 && engine.getState().getCurrentTeam() == teamId) {
                        terrainClickedOn = scene.getTerrainFromPositionOnWindow(startMousePos.x, startMousePos.y);
                    }
                    
                    if(!scene.getMenu() && startMousePos.x > windowWidth - 80 && startMousePos.y < 36 && engine.getState().getCurrentTeam() == teamId) {
                        engine.addCommand(1, new engine::EndTurnCommand());
                    }
                }
            }
            
            if(scene.getMenu()) {              
                if(startMousePos.x >= 550 && startMousePos.x <= 630 && startMousePos.y >= 360 && startMousePos.y <= 400) {
                    scene.setMenu(false);
                    
                    engine.addCommand(0, new engine::LoadCommand("res/map.txt"));
                    engine.update();
                }
            } else {
                
            }
            
            scene.stateChanged();

            if(engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
                std::string s = std::to_string(engine.getState().getWinner());
                std::string winnerMessage = "L equipe " + s + " a gagne !";
                scene.getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
            }
            
            scene.getDebugLayer().getSurface()->addText(windowWidth - 80, 5, "End turn", sf::Color::White, 18);
            
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
        
        delete terrainClickedOn;
    }

}