#include "state.hpp"
#include "state/State.h"
#include "state/Leader.h"

#include <iostream>

namespace state {
    
    State* state;
    
    bool unitTest_shouldCreatState() {
        state = new State();
        return (state != NULL);
    }

    bool unitTest_shouldAddTeamToBoard() {
        int teamsSize = state->getBoard().getTeams().size();
        
        std::cout << "  Il y a actuellement " << teamsSize << " équipe(s) dans le jeu" << std::endl;
        std::cout << "  Ajout d'une équipe au jeu" << std::endl;
        
        Team* team = new Team(1);
        state->getBoard().addTeam(team);
        
        int teamsResize = state->getBoard().getTeams().size();
        std::cout << "  Il y a maintenant " << teamsResize << " équipe(s) dans le jeu" << std::endl;
        
        return (teamsResize == teamsSize + 1);    
    }

    bool unitTest_shouldAddTerrainToBoard() {
        int terrainSize = state->getBoard().getTerrains().size();
        
        std::cout << "  Il y a actuellement " << terrainSize << " terrain(s) dans le jeu" << std::endl;
        std::cout << "  Ajout d'un terrain de type HOUSE au jeu" << std::endl;
        
        House* house = new House(1, 1, 1);
        state->getBoard().addTerrain(house);
        
        terrainSize = state->getBoard().getTerrains().size();
        std::cout << "  Il y a maintenant " << terrainSize << " terrain(s) dans le jeu" << std::endl;
        
        if(terrainSize != 1) {
            return false;
        }
        
        TerrainTypeId terrainType = state->getBoard().getTerrains()[0]->getTypeId();
        if(terrainType == TerrainTypeId::HOUSE) {
            std::cout << "  Le terrain ajouté est bien de type HOUSE" << std::endl;
        } else {
            return false;
        }
        
        std::cout << "  Ajout d'un terrain de type CASTLE au jeu" << std::endl;
        
        Castle* castle = new Castle(2, 1, 1);
        state->getBoard().addTerrain(castle);
        
        terrainSize = state->getBoard().getTerrains().size();
        std::cout << "  Il y a maintenant " << terrainSize << " terrain(s) dans le jeu" << std::endl;
                
        if(terrainSize != 2) {
            return false;
        }
        
        terrainType = state->getBoard().getTerrains()[1]->getTypeId();
        if(terrainType == TerrainTypeId::CASTLE) {
            std::cout << "  Le terrain ajouté est bien de type CASTLE" << std::endl;
            return true;
        } else {
            return false;
        }
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
        
        if(unitTest_shouldAddTeamToBoard()) {
            std::cout << "Equipe correctement ajoutée au jeu" << std::endl;
        } else {
            std::cout << "ERREUR : Equipe non ajoutée au jeu !" << std::endl;
        }
        
        if(unitTest_shouldAddTerrainToBoard()) {
            std::cout << "Terrains correctement ajouté au jeu" << std::endl;
        } else {
            std::cout << "ERREUR : L'ajout de terrain au jeu à planté !" << std::endl;
        }
        
    }

}