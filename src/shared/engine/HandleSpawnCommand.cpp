#include "HandleSpawnCommand.h"

namespace engine {

    void HandleSpawnCommand::spawnUnit(state::State& state, state::UnitTypeId unitTypeId) {

    }

    void HandleSpawnCommand::execute(state::State& state) {

    }

    CommandTypeId HandleSpawnCommand::getTypeId() const {
        return CommandTypeId::HANDLE_SPAWN;
    }

}
