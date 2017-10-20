#include <iostream>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include "state.hpp"
#include "render.hpp"

using namespace std;
using namespace state;

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
            sf::RenderWindow window(sf::VideoMode(1152, 576), "BfW");

            // on définit le niveau à l'aide de numéro de tuiles
            const int level[] =
            {
                0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0, 0, 0, 0,
                0, 0, 5, 6, 7, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 1, 1, 1, 3, 1, 1, 1,
                0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1,
                0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 0, 1, 0, 0, 0, 0, 0, 2, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 0, 1, 0, 0, 0, 0, 0, 6, 0, 0, 0,
                0, 1, 0, 3, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 0, 0, 5, 4, 7, 0, 0,
                0, 0, 0, 0, 0, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
            };
            
            /*0 = herbe, 1 = foret, 2 = eau, 3 = maison, 4 = chateau, 5 = mur droite, 6 = mur bas, 7 = mur gauche*/

            // on crée la tilemap avec le niveau précédemment défini
            render map;
            if (!map.load("res/terrains/terrain.png", sf::Vector2u(72, 72), level, 22, 8))
                return -1;

            // on fait tourner la boucle principale
            while (window.isOpen())
            {
                // on gère les évènements
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if(event.type == sf::Event::Closed)
                        window.close();
                }

                // on dessine le niveau
                window.clear();
                window.draw(map);
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
