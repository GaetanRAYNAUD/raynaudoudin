#include "HandleWinCommand.h"

namespace engine {
        
    HandleWinCommand::HandleWinCommand() {

    }
    
    void HandleWinCommand::execute(state::State& state) {       
        if (state.getBoard().isLeaderNotAlive(state::TeamId::TEAM_1)) {
            state.setWinner(state::TeamId::TEAM_2);
        } else if (state.getBoard().isLeaderNotAlive(state::TeamId::TEAM_2)) {
            state.setWinner(state::TeamId::TEAM_1);
        } else {
            return;
        }
    }

    CommandTypeId HandleWinCommand::getTypeId() const {
        return CommandTypeId::HANDLE_WIN;
    }

}
