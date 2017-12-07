#include "EndTurnAction.h"
#include "state/State.h"

namespace engine {

    EndTurnAction::EndTurnAction() {

    }

    void EndTurnAction::apply(state::State& state) {
        for(auto& u : state.getBoard().getUnits()) {
            speeds.insert(std::make_pair(u.second->getId(), u.second->getSpeed()));
        }
        
        gold = state.getBoard().findTeam(state.getCurrentTeam())->getGold();
        state.endTurn();
    }

    void EndTurnAction::undo(state::State& state) {
        for(auto& s : speeds) {
            state.getBoard().findUnit(s.first)->setSpeed(s.second);
        }
        state.setTurn(state.getTurn() - 1);
        state.getBoard().findTeam(state.getCurrentTeam())->setGold(gold);                
    }

}

