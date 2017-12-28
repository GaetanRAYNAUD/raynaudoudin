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
        Json::Value jsonCommands;
        
        
        
        if(getServerCommands(jsonCommands, engine.getState().getTurn())) {
            engine.addCommands(jsonCommands);
            engine.update();
            engine.addCommand(1, new engine::HandleWinCommand());
            engine.update();
        }
        
        if(engine.getState().getCurrentTeam() == player) {
            putServerCommand(player_ai->run(engine, player));
        }
    }

}