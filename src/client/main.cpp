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

using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace random_ai;

int main(int argc,char* argv[]) 
{
    if( argc > 1) {
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
            
        } else {
            cout << "Commande inconnue" << endl;
            cout << "Liste des commandes : " << endl;
            cout << "hello : Affiche un message de bienvenue" << endl;
            cout << "state : Effectue une série de tests pour vérifier le fonctionnement d'un état" << endl;
            cout << "render : Lance le rendu d'un état" << endl;
            cout << "engine : Lance le moteur du jeu" << endl;
            cout << "random_ai : Lance l'ia aléatoire du jeu" << endl;
            cout << "heuristique_ai : Lancement de l'ia heuristique" << endl;
        }
    }
    return 0;
}
