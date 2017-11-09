#include "SpawnCommand.h"

namespace engine {

    void SpawnCommand::spawnUnit(state::State& state, int x, int y, state::UnitTypeId unitTypeId) {
        if (state.getBoard().findTerrainOnPosition(x, y)->getTypeId() == state::TerrainTypeId::CASTLE && 
                state.getBoard().findUnitOnPosition(x, y)->getTypeId() == state::UnitTypeId::LEADER) {
            if (state.getBoard().isUnitOnPosition(x - 1, y - 1)) {
                state.getBoard().addUnit(unitTypeId, state.getBoard().findTeam(state.getTurn()%2)->getRace(), x - 1, y - 1);
            } else if (state.getBoard().isUnitOnPosition(x, y - 1)) {
                state.getBoard().addUnit(unitTypeId, state.getBoard().findTeam(state.getTurn()%2)->getRace(), x, y - 1);
            } else if (state.getBoard().isUnitOnPosition(x + 1, y - 1)) {
                state.getBoard().addUnit(unitTypeId, state.getBoard().findTeam(state.getTurn()%2)->getRace(), x + 1, y - 1);
            }
        }
    }

    void SpawnCommand::execute(state::State& state) {

    }

    CommandTypeId SpawnCommand::getTypeId() const {
        return CommandTypeId::SPAWN;
    }

}
