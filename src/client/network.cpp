#include "network.hpp"

#include "server.h"

using namespace std;

namespace server {
    void network_Test(int port, std::string name) {
        
        if(fork()) {
            cout << "Test père" << endl;
        } else {
            //char* const args[] = { "-X", "PUT", "--data", "'{\"name\":\"Gaetan\"}'", "http://localhost:8080/player" };
            cout << "Ajout du joueur : " << name << ", au serveur port : " << port << endl;
            execv("/bin/ls", 0);
            cout << "Passé" << endl;
            //curl -X PUT --data '{"name":"Mathis"}' http://localhost:8080/player
        }
    }
}
