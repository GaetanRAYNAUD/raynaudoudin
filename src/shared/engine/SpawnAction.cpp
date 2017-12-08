#include "SpawnAction.h"
#include "state/State.h"

namespace engine {

    SpawnAction::SpawnAction(int x, int y, state::UnitTypeId unitTypeId, state::TeamId teamId) : x(x), y(y), unitTypeId(unitTypeId), teamId(teamId) {

    }

    void SpawnAction::apply(state::State& state) {        
        state.addEpoch();
        teamGold = state.getBoard().findTeam(teamId)->getGold();
        state.getBoard().createNewUnit(unitTypeId, teamId, x, y);
        spawnUnitId = state.getBoard().findUnitOnPosition(x, y)->getId();
        state.getBoard().findTeam(teamId)->withdrawGold(unitTypeId);        
    }

    void SpawnAction::undo(state::State& state) {
        state.removeEpoch();        
        state.getBoard().deleteUnit(spawnUnitId);
        state.getBoard().findTeam(teamId)->setGold(teamGold);
    }    
}

