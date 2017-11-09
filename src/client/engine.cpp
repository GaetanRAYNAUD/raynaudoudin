#include <climits>

#include "engine.hpp"

using namespace state;
using namespace render;

namespace engine {
    
    void engineTest() {
        State* state = new State();
        state->getBoard().loadTerrainsFromFile("res/map.txt");
        
        state->getBoard().getUnits().at(0).get()->Move(8,4);
        std::cout << "Déplacement de l'unité 0 de (3,2) à (8,4)" << std::endl;
        
        if(state->getBoard().findUnitOnPosition(8, 4)->getId() == 0) {
            std::cout << "L'unité 0 est bien en (8,4)" << std::endl;            
        } else {
            std::cout << "ERREUR : L'unité 0 n'est pas en (8,4)" << std::endl;              
        }
    }
}


