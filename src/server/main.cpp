#include <iostream>
#include <fstream>
#include <sstream>

#include "state.hpp"
#include "engine.hpp"
#include "heuristic_ai.hpp"
#include "record.hpp"

using namespace std;
using namespace state;
using namespace engine;
using namespace heuristic_ai;
using namespace record;

int main(int argc, char* argv[]) 
{
    if( argc > 1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour le monde!" << endl;
        } else if (string(argv[1]) == "record"){
            cout << "Enregistrement des actions de l'IA" << endl;
            record_test();
        } else {
            cout << "Commande inconnue" << endl;
            cout << "Liste des commandes : " << endl;
            cout << "record : Enregistre les commandes de l'IA" << endl;
        }
    }
    return 0;
}



