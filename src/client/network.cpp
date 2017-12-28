#include <SFML/Network/Http.hpp>

#include "network.hpp"

using namespace std;

namespace network {
    
    void network_Test(int port, std::string name) {
        sf::Http connection("http://localhost", port);
        sf::Http::Request* request = new sf::Http::Request;
        sf::Http::Response response;
        Json::Value jsonResponse;
        Json::Reader jsonReader;
        int idPlayer;
        std::string requestParameters = "{\"name\":\"" + name  + "\"}";
        
        request->setUri("/game");
        request->setMethod(sf::Http::Request::Get);
        
        response = connection.sendRequest(*request);

        if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
            delete request;
            return;
            
        } else if(response.getStatus() == sf::Http::Response::NotFound) {
            std::cout << "Erreur la partie demandée n'existe pas !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            delete request;
            return;
        }
        
        if (!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        if(jsonResponse.isMember("Game Status")) {
            if(jsonResponse["Game Status"].asString() != "CREATING") {
                std::cout << "La partie n'est plus en phase de création !" << std::endl;
                std::cout << "Statut actuel de la partie : " << jsonResponse["Game Status"].asString() << std::endl;

                delete request;
                return;
            }
        } else {
            std::cout << "Erreur dans les données envoyées par le serveur !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            delete request;
            return;
        }
        
        std::cout << "Partie en cours de création, tentative d'ajout du joueur." << std::endl;
        
        delete request;
        request = new sf::Http::Request;
        
        request->setUri("/player");
        request->setMethod(sf::Http::Request::Post);
        request->setBody(requestParameters);
        
        response = connection.sendRequest(*request);

        if(response.getStatus() == sf::Http::Response::ServiceNotAvailable) {
            std::cout << "Partie pleine !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;

            delete request;
            return;

        } else if(response.getStatus() == sf::Http::Response::BadRequest) {
            std::cout << "Requete invalide !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;

            delete request;
            return;

        } else if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
            delete request;
            return;
            
        } else if(response.getStatus() == sf::Http::Response::Created || response.getStatus() == sf::Http::Response::NoContent) {
            std::cout << "Joueur " + name + " correctement ajouté à la partie !" << std::endl;
        }            


        if (!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        if(jsonResponse.isMember("id")) {
            idPlayer = jsonResponse["id"].asInt();
            
        } else {
            std::cout << "Erreur dans les données envoyées par le serveur !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            delete request;
            return;
        }
        
        delete request;
        request = new sf::Http::Request;
        
        request->setUri("/player/-1");
        request->setMethod(sf::Http::Request::Get);
        
        response = connection.sendRequest(*request);

        if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
            delete request;
            return;
        }

        if (!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        if(jsonResponse.isMember("Players")) {
            std::cout << "***************************************************" << std::endl;
            std::cout << "Liste des joueurs présents dans la partie : " << std::endl;
            
            for(unsigned int i = 0; i < jsonResponse["Players"].size(); i++) {
                std::cout << jsonResponse["Players"][i]["name"].asString() << std::endl;
            }
            
        } else {
            std::cout << "Erreur dans les données envoyées par le serveur !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            delete request;
            return;
        }
        
        std::cout << "***************************************************" << std::endl;
        std::cout << "Appuyez sur <entrée> pour quitter la partie." << std::endl;
        (void)getc(stdin);
        
        std::cout << "***************************************************" << std::endl;
        std::cout << "Tentative de quitter la partie." << std::endl;
        
        delete request;
        request = new sf::Http::Request;
        
        request->setUri("/player/" + std::to_string(idPlayer));
        request->setMethod(sf::Http::Request::Delete);
        
        response = connection.sendRequest(*request);
        
        if(response.getStatus() == sf::Http::Response::NotFound) {
            std::cout << "Erreur le joueur à retirer n'est pas présent dans la partie !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            delete request;
            return;
            
        } else if(response.getStatus() == sf::Http::Response::InternalServerError) {
            std::cout << "Le servveur a rencontré une erreur !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
                
            delete request;
            return;

        } else if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
            delete request;
            return;
            
        } else if(response.getStatus() == sf::Http::Response::NoContent) {
            std::cout << "Joueur correctement retiré de la partie !" << std::endl;
        }
        
        delete request;
        request = new sf::Http::Request;
        
        request->setUri("/player/-1");
        request->setMethod(sf::Http::Request::Get);
        
        response = connection.sendRequest(*request);

        if(response.getStatus() == sf::Http::Response::ConnectionFailed) {
            std::cout << "Connection au serveur impossible, vérifiez qu'il est bien en fonctionnement !" << std::endl;
            std::cout << "Arrêt de la connection !" << std::endl;
            
            delete request;
            return;
        }

        if (!(jsonReader.parse(response.getBody(), jsonResponse, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        std::cout << "***************************************************" << std::endl;
        std::cout << "Liste des joueurs présents dans la partie : " << std::endl;

        for(unsigned int i = 0; i < jsonResponse["Players"].size(); i++) {
            std::cout << jsonResponse["Players"][i]["name"].asString() << std::endl;
        }

        std::cout << "***************************************************" << std::endl;          
        std::cout << "Arrêt de la connection !" << std::endl;

        delete request;
    }
}
