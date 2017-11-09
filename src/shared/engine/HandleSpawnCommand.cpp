#include "HandleSpawnCommand.h"

namespace engine {

    void HandleSpawnCommand::spawnUnit(state::State& state, int x, int y, state::UnitTypeId unitTypeId) {
        if (state.getBoard().findTerrainOnPosition(x, y)->getTypeId() == state::TerrainTypeId::CASTLE && state.getBoard().findUnitOnPosition(x, y)->getTypeId() == state::UnitTypeId::LEADER) {
            
        }
    }

    void HandleSpawnCommand::execute(state::State& state) {

    }

    CommandTypeId HandleSpawnCommand::getTypeId() const {
        return CommandTypeId::HANDLE_SPAWN;
    }

}
