#include "NetworkClient.h"
#include "ai/HeuristicAI.h"
#include "engine/HandleWinCommand.h"

#include <SFML/Network/Http.hpp>
#include <iostream>
#include <unistd.h>

namespace client {

    NetworkClient::NetworkClient(const std::string& url, int port, std::string player) : url(url), port(port), player(player) {
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
            return "SERVERNOTFOUND";
        }
        
        if(!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        if(jsonResponse.isMember("Game Status")) {
            return jsonResponse["Game Status"].asString();
            
        } else {
            return "BADREQUEST";
        }
    }

    bool NetworkClient::getServerCommands(Json::Value& out, int epoch) {
        sf::Http connection(url, port);
        sf::Http::Request request;
        sf::Http::Response response;
        Json::Value jsonResponse;
        Json::Reader jsonReader;
        
        request.setUri("/command/" + std::to_string(epoch));
        request.setMethod(sf::Http::Request::Get);
        
        response = connection.sendRequest(request);
        
        if(response.getStatus() == sf::Http::Response::NotFound) {
            return false;
            
        } else {
            if(!(jsonReader.parse(response.getBody(), out, false))) {
                std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
            }
            
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
        int windowWidth = 1188;
        int windowHeight = 576;
        int idPlayer;
        std::string gameStatus;
        render::Scene scene(engine.getState());
        sf::Clock clock;
        sf::Time time = clock.getElapsedTime();
        sf::Http connection(url, port);
        sf::Http::Request request;
        sf::Http::Response response;
        Json::Reader jsonReader;
        Json::Value jsonCommands;
        Json::Value jsonResponse;        

        gameStatus = getGameStatus();
        
        if(gameStatus == "RUNNING") {
            std::cout << "La partie n'est plus en phase de création !" << std::endl;
            std::cout << "Réessayez plus tard !" << std::endl;
            std::cout << "Arrêt du client !" << std::endl;
            return;
        }    
        
        std::string requestParameters = "{\"name\":\"" + player  + "\"}";
        
        request.setUri("/player");
        request.setMethod(sf::Http::Request::Post);
        request.setBody(requestParameters);
        
        response = connection.sendRequest(request);

        if(response.getStatus() == sf::Http::Response::ServiceNotAvailable) {
            std::cout << "Partie pleine !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;

            return;

        } else if(response.getStatus() == sf::Http::Response::BadRequest) {
            std::cout << "Requete invalide !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;

            return;

        } else if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
            return;
            
        } else if(response.getStatus() == sf::Http::Response::Created || response.getStatus() == sf::Http::Response::NoContent) {
            std::cout << "Joueur " + player + " correctement ajouté à la partie !" << std::endl;
        }            


        if (!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        if(jsonResponse.isMember("id") && jsonResponse.isMember("teamId")) {
            idPlayer = jsonResponse["id"].asInt();
            
            if(jsonResponse["teamId"].asString() == "TEAM_1") {
                teamId = state::TeamId::TEAM_1;
            } else {
                teamId = state::TeamId::TEAM_2;
            }
            
        } else {
            std::cout << "Erreur dans les données envoyées par le serveur !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            return;
        }
        
        std::cout << "En attente des autre joeurs." << std::endl;
        
        while(gameStatus != "RUNNING" && time.asMilliseconds() < 60000) {
            sleep(1);
            gameStatus = getGameStatus();
            time = clock.getElapsedTime();
        }
        
        if(gameStatus == "SERVERNOTFOUND") {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt du client !" << std::endl;
            return;
            
        } else if(time.asMilliseconds() >= 60000) {
            std::cout << "1 minute sans que la partie démarre !" << std::endl;
            std::cout << "Réessayez plus tard !" << std::endl;
            std::cout << "Arrêt du client !" << std::endl;
            return;            
        }    
        
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        window.setFramerateLimit(60);
        
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            
            if(getGameStatus() != "RUNNING") {
                std::cout << "La partie est terminée !" << std::endl;
                std::cout << "Arrêt du client : " << player << "!" << std::endl;
                return;
                
            } else if(getGameStatus() == "SERVERNOTFOUND") {
                std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
                std::cout << "Arrêt de la connection !" << std::endl;
                return;
            }

            std::cout << "Check ok" << std::endl;
            
            if(getServerCommands(jsonCommands, engine.getState().getEpoch())) {
                engine.addCommands(jsonCommands);
                std::cout << "Epoch : " << engine.getState().getEpoch() << std::endl;
                std::cout << jsonCommands << std::endl;
                std::cout << "Command size : " << engine.getCurrentCommands().size() << std::endl;
                engine.update();
                
                scene.stateChanged();
            }

            std::cout << "Commands ok" << std::endl;

            std::cout << engine.getCommandHistory().size() << std::endl;
            
            if(engine.getState().getCurrentTeam() == teamId) {
                putServerCommand(player_ai->run(engine, teamId));
            }

            std::cout << "AI ok" << std::endl;
            
            if(engine.getState().getWinner() != state::TeamId::INVALIDTEAM) {
                std::string s = std::to_string(engine.getState().getWinner());
                std::string winnerMessage = "L equipe " + s + " a gagne !";
                scene.getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
            }


            scene.draw(window);
            window.display();
        }
        
        request.setUri("/player/" + std::to_string(idPlayer));
        request.setMethod(sf::Http::Request::Delete);
        
        response = connection.sendRequest(request);
        
        if(response.getStatus() == sf::Http::Response::NotFound) {
            std::cout << "Erreur le joueur à retirer n'est pas présent dans la partie !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
        } else if(response.getStatus() == sf::Http::Response::InternalServerError) {
            std::cout << "Le servveur a rencontré une erreur !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;

        } else if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
        } else if(response.getStatus() == sf::Http::Response::NoContent) {
            std::cout << "Partie quittée avec succès !" << std::endl;
            std::cout << "A bientôt" << std::endl;
        }        
    }
}