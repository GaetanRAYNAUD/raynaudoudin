#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.h"

using namespace std;
using namespace state;

int main(int argc,char* argv[]) 
{

    if (string(argv[1]) == "hello") {
        cout << "Bonjour le monde!" << endl;
    } else {
        cout << "Commande inconnue" << endl;
        cout << "Liste des commandes : " << endl;
        cout << "hello : Affiche un message de bienvenue" << endl; 
    }
    
    return 0;
}
