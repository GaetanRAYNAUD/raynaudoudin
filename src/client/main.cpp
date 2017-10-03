#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.hpp"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{
    if( argc > 1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour le monde!" << endl;
            
        } else if (string(argv[1]) == "state"){
            cout << "Lancement des tests d'état" << endl;
            unitTest();
            
        } else {
            cout << "Commande inconnue" << endl;
            cout << "Liste des commandes : " << endl;
            cout << "hello : Affiche un message de bienvenue" << endl; 
        }
    }
    return 0;
}
