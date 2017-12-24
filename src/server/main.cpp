#include <iostream>

#include "record.hpp"
#include "listen.hpp"

using namespace std;
using namespace record;
using namespace listenn;

void listCommands() {
    cout << "Commande inconnue" << endl;
    cout << "Liste des commandes : " << endl;
    cout << "record : Enregistre les commandes de l'IA" << endl;
    cout << "listen : Lance le serveur pour faire une partie en réseau" << endl;
}

int main(int argc, char* argv[]) {
    
    if(argc == 1) {
        listCommands();
        
    } else if(argc > 1) {
        if (string(argv[1]) == "hello") {
            cout << "Bonjour le monde!" << endl;
        } else if (string(argv[1]) == "record"){
            cout << "Enregistrement des actions de l'IA" << endl;
            record_test();
        } else if (string(argv[1]) == "listen"){
            cout << "Lancement des tests de l'API" << endl;
            listen_Test();
        } else {
            listCommands();
        }
    }
    return 0;
}



