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
#include "state.h"
#include "render.h"

using namespace std;
using namespace state;
using namespace render;

int main(int argc,char* argv[]) 
{
    if( argc > 1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour le monde!" << endl;
            
        } else if (string(argv[1]) == "state"){
            cout << "Lancement des tests d'état" << endl;
            state::unitTest();
            
        } else if (string(argv[1]) == "render"){
            cout << "Lancement du rendu d'un état" << endl;
            
            int windowWidth = 1152;
            int windowHeight = 576;
            sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
            
            Board board(22, 8);
            board.loadTerrainsFromFile("res/map.txt");

            TerrainLayer* terLayer = new TerrainLayer(board);
            terLayer->initSurface();

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if(event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                window.draw(*(terLayer->getSurface()));
                window.display();
            }
            
        }else {
            cout << "Commande inconnue" << endl;
            cout << "Liste des commandes : " << endl;
            cout << "hello : Affiche un message de bienvenue" << endl;
            cout << "state : Effectue une série de tests pour vérifier le fonctionnement d'un état" << endl;
            cout << "render : Lance le rendu d'un état" << endl;
        }
    }
    return 0;
}
