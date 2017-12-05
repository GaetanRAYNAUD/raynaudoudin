#include "SpawnAction.h"
#include "state/State.h"

namespace engine {

    SpawnAction::SpawnAction(int x, int y, state::UnitTypeId unitTypeId, state::TeamId teamId) : x(x), y(y), unitTypeId(unitTypeId), teamId(teamId) {

    }

    void SpawnAction::apply(state::State& state) {
        state.getBoard().createNewUnit(unitTypeId, teamId, x, y);
        spawnUnitId = state.getBoard().findUnitOnPosition(x, y)->getId();
        state.getBoard().findTeam(state.getBoard().findUnitOnPosition(x, y)->getTeam())->withdrawGold(unitTypeId);        
    }

    void SpawnAction::undo(state::State& state) {
        state.getBoard().deleteUnit(spawnUnitId);
        //Penser à remettre gold
    }    
}

