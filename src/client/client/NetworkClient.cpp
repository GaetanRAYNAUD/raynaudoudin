#include "NetworkClient.h"
#include "ai/HeuristicAI.h"
#include "engine/HandleWinCommand.h"

#include <SFML/Network/Http.hpp>
#include <iostream>

namespace client {

    NetworkClient::NetworkClient(const std::string& url, int port, state::TeamId player) : url(url), port(port), player(player) {
        player_ai = std::unique_ptr<ai::HeuristicAI>(new ai::HeuristicAI());
    }

    std::string NetworkClient::getGameStatus() {
        sf::Http connection(url, port);
        sf::Http::Request request;
        sf::Http::Response response;
        Json::Value jsonResponse;
        Json::Reader jsonReader;
        
        request.setUri("/game");
        request.setMethod(sf::Http::Request::Get);
        
        response = connection.sendRequest(request);
        
        if(response.getStatus() != sf::Http::Response::Ok) {
            return "";
        }
        
        if(!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        if(jsonResponse.isMember("Game Status")) {
            return jsonResponse["Game Status"].asString();
        } else {
            return "";
        }
    }

    bool NetworkClient::getServerCommands(Json::Value& out, int turn) {
        sf::Http connection(url, port);
        sf::Http::Request request;
        sf::Http::Response response;
        Json::Value jsonResponse;
        Json::Reader jsonReader;
        
        request.setUri("/command" + std::to_string(turn));
        request.setMethod(sf::Http::Request::Get);
        
        response = connection.sendRequest(request);
        
        if(response.getStatus() == sf::Http::Response::NotFound) {
            return false;
            
        } else {
            if(!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
                std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
            }
            
            out.append(jsonResponse);
            
            return true;
        }
    }

    void NetworkClient::putServerCommand(engine::Command* command) {
        sf::Http connection(url, port);
        sf::Http::Request request;
        Json::Value jsonCommand;
        
        command->serialize(jsonCommand);
        
        request.setUri("/command");
        request.setMethod(sf::Http::Request::Post);
        request.setBody(jsonCommand.asString());
        
        connection.sendRequest(request);
    }

    void NetworkClient::run() {
        bool pause = 0;
        int windowWidth = 1188;
        int windowHeight = 576;
        int timePause = 100;        
        Json::Value jsonCommands;
        render::Scene scene(engine.getState());
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        
        window.setFramerateLimit(60);

        while (window.isOpen()) {
            sf::Event event;
            
            if(getGameStatus() != "RUNNING") {
                std::cout << "La partie est terminée !" << std::endl;
                std::cout << "Arrêt du client : " << player << "!" << std::endl;                
                return;
            }
            
            if(!pause) {

                while (window.pollEvent(event)) {
                    if(event.type == sf::Event::Closed) {
                        window.close(); 
                    } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                        pause = !pause;
                    } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                        if(timePause == 100) {
                            timePause = 10;
                        } else {
                            timePause = 100;
                        }
                    }

                }

                if(getServerCommands(jsonCommands, engine.getState().getTurn())) {
                    engine.addCommands(jsonCommands);
                    engine.update();

                    scene.stateChanged();                
                }

                if(engine.getState().getCurrentTeam() == player) {
                    putServerCommand(player_ai->run(engine, player));
                }
                
                if(engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
                    pause = true;
                    std::string s = std::to_string(engine.getState().getWinner());
                    std::string winnerMessage = "L equipe " + s + " a gagne !";
                    scene.getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
                }


                scene.draw(window);
                window.display();
            }
        }        
    }

}