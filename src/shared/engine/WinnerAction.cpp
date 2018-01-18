#include "WinnerAction.h"
#include "state/State.h"

namespace engine {

    WinnerAction::WinnerAction(state::TeamId teamId) : teamId(teamId) {
        
    }

    void WinnerAction::apply(state::State& state) {     
        state.addEpoch();
        state.setWinner(teamId);       
    }

    void WinnerAction::undo(state::State& state) {
        state.removeEpoch();        
        state.setWinner(state::TeamId::INVALID_TEAM);
    }

}
