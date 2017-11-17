#include "HandleWinCommand.h"

#include <iostream> //A supprimer à terme

namespace engine {
        
    HandleWinCommand::HandleWinCommand() {

    }
    
    void HandleWinCommand::execute(state::State& state) {
        state::TeamId teamIdWin = state::TeamId::INVALIDTEAM;
        
        if (state.getBoard().isLeaderNotAlive(state::TeamId::TEAM_1)) {
            teamIdWin = state::TeamId::TEAM_2;
        } else if (state.getBoard().isLeaderNotAlive(state::TeamId::TEAM_2)) {
            teamIdWin = state::TeamId::TEAM_1;
        } else {
            return;
        }
        
        std::cout << "L'équipe " << teamIdWin << " a gagnée la partie !" <<std::endl;
        
        //Afficher teamIdwin l'équipe gagnante sur le jeu
    }

    CommandTypeId HandleWinCommand::getTypeId() const {
        return CommandTypeId::HANDLE_WIN;
    }

}
