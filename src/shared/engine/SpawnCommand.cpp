#include "SpawnCommand.h"

namespace engine {

    SpawnCommand::SpawnCommand(int x, int y, state::UnitTypeId unitTypeId): x(x), y(y), unitTypeId(unitTypeId) {

    }
   
    void SpawnCommand::spawnUnit(state::State& state, int x, int y, state::UnitTypeId unitTypeId) {
        if (state.getBoard().findTerrainOnPosition(x, y)->getTypeId() == state::TerrainTypeId::CASTLE && 
                state.getBoard().findUnitOnPosition(x, y)->getTypeId() == state::UnitTypeId::LEADER) {
            if (!state.getBoard().isUnitOnPosition(x - 1, y - 1)) {
                state.getBoard().addUnit(unitTypeId, state.getBoard().findUnitOnPosition(x, y)->getRace(), x - 1, y - 1);
            } else if (!state.getBoard().isUnitOnPosition(x, y - 1)) {
                state.getBoard().addUnit(unitTypeId, state.getBoard().findUnitOnPosition(x, y)->getRace(), x, y - 1);
            } else if (!state.getBoard().isUnitOnPosition(x + 1, y - 1)) {
                state.getBoard().addUnit(unitTypeId, state.getBoard().findUnitOnPosition(x, y)->getRace(), x + 1, y - 1);
            }
        }
    }

    void SpawnCommand::execute(state::State& state) {
        spawnUnit(state, x, y, unitTypeId);
    }

    CommandTypeId SpawnCommand::getTypeId() const {
        return CommandTypeId::SPAWN;
    }

}
