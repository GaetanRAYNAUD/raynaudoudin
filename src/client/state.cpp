#include <iostream>

#include "state.hpp"

namespace state {
    
    State* state;
    
    bool unitTest_shouldCreatState() {
        state = new State();
        return (state != NULL);
    }

    bool unitTest_shouldAddTeamToBoard() {
        Team* team = new Team();
        return (team != NULL);    
    }

    bool unitTest_shouldAddTerrainToBoard() {
        return false;    
    }

    bool unitTest_shouldAddUnitToBoard() {
        return false;    
    }

    bool unitTest_shouldAddWeaponToUnit() {
        return false;    
    }

    void unitTest() {    
        std::cout << "Création du état" << std::endl;

        if(unitTest_shouldCreatState()) {
            std::cout << "Etat créé" << std::endl;
        } else {
            std::cout << "ERREUR : Etat non créé !" << std::endl;
        }
        
        std::cout << "Ajout d'une équipe au jeu" << std::endl;
        
        if(unitTest_shouldAddTeamToBoard()) {
            std::cout << "Equipe ajoutée au jeu" << std::endl;
        } else {
            std::cout << "ERREUR : Equipe non ajoutée au jeu !" << std::endl;
        }
        
    }

}