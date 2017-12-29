#include <iostream>
#include <fstream>
#include <sstream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.hpp"
#include "render.hpp"
#include "engine.hpp"
#include "random_ai.hpp"
#include "heuristic_ai.hpp"
#include "rollback.hpp"
#include "deep_ai.hpp"
#include "thread.hpp"
#include "play.hpp"
#include "network.hpp"

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace random_ai;
using namespace heuristic_ai;
using namespace rollback;
using namespace deep_ai;
using namespace thread;
using namespace play;
using namespace network;

void listCommands() {
    cout << "Commande inconnue" << endl;
    cout << "Liste des commandes : " << endl;
    cout << "hello : Affiche un message de bienvenue" << endl;
    cout << "state : Effectue une série de tests pour vérifier le fonctionnement d'un état" << endl;
    cout << "render : Lance le rendu d'un état" << endl;
    cout << "engine : Lance le moteur du jeu" << endl;
    cout << "random_ai : Lance l'ia aléatoire du jeu" << endl;
    cout << "heuristique_ai : Lancement de l'ia heuristique" << endl;
    cout << "rollback : Lance le test de rollback" << endl;
    cout << "deep_ai : Lancement de l'ia deep" << endl;
    cout << "thread : Lancement le jeu avec des threads" << endl;
    cout << "play : Restitue les actions de l'IA" << endl;
    cout << "network [port] [nom] : Lancement de la connection à une partie en réseau" << endl;    
}

int main(int argc, char* argv[]) {
    
    if(argc == 1) {
        listCommands();
        
    } else if(argc > 1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour le monde!" << endl;
            
        } else if (string(argv[1]) == "state"){
            cout << "Lancement des tests d'état" << endl;
            unitTest();
            
        } else if (string(argv[1]) == "render"){
            cout << "Lancement du rendu d'un état" << endl;
            renderTest();
            
        } else if (string(argv[1]) == "engine"){
            cout << "Lancement du moteur du jeu" << endl;
            engineTest();
            
        } else if (string(argv[1]) == "random_ai"){
            cout << "Lancement de l'ia aléatoire" << endl;
            random_aiTest();
            
        } else if (string(argv[1]) == "heuristic_ai"){
            cout << "Lancement de l'ia heuristique" << endl;
            cout << "Appuyez sur ESPACE pour accélérer le jeu" << endl;
            cout << "Appuyez sur P pour mettre le jeu en pause" << endl;
            cout << "Appuyez sur A pour retirer les cartes de distances" << endl;
            cout << "Appuyez sur Z pour afficher la carte de distance des unités humaines" << endl;
            cout << "Appuyez sur E pour afficher la carte de distance des unités orcs" << endl;
            cout << "Appuyez sur R pour afficher la carte de distance des maisons humaines" << endl;
            cout << "Appuyez sur T pour afficher la carte de distance des maisons orcs" << endl;
            cout << "Appuyez sur Y pour afficher la carte de distance des châteaux" << endl;
            heuristic_aiTest();
            
        } else if (string(argv[1]) == "rollback"){
            cout << "Lancement du test de rollback" << endl;
            cout << "Appuyez sur ESPACE pour accélérer le jeu" << endl;
            cout << "Appuyez sur P pour mettre le jeu en pause" << endl;
            rollback_Test();
            
        } else if (string(argv[1]) == "deep_ai"){
            cout << "Lancement de l'ia deep" << endl;
            cout << "Appuyez sur P pour mettre le jeu en pause" << endl;
            deep_aiTest();
            
        } else if (string(argv[1]) == "thread"){
            cout << "Lancement du jeu avec des threads" << endl;
            cout << "Appuyez sur ESPACE pour accélérer le jeu" << endl;
            cout << "Appuyez sur P pour mettre le jeu en pause" << endl;
            thread_aiTest();

        } else if (string(argv[1]) == "play"){
            cout << "Restitutions des actions de l'IA" << endl;
            play_Test();
        
        } else if (string(argv[1]) == "network"){
            int port;
            string name;
            
            cout << "Lancement de la connection à une partie en réseau" << endl;
            
            if(argv[2] == nullptr) {
                cout << "Veuillez indiquer le port du serveur" << endl;
                
                return 1;
            } else {
                port = atoi(argv[2]);
            }
            
            if(argv[3] == nullptr) {
                cout << "Veuillez indiquer le nom de votre joueur" << endl;
                
                return 1;
            } else {
                name = string(argv[3]);
            }
            
            network_Test2(port, name);
            
        } else {
            listCommands();
        }
    }
    return 0;
}
