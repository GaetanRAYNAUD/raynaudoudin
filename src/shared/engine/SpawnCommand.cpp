#include "SpawnCommand.h"

namespace engine {

    SpawnCommand::SpawnCommand(int x, int y, state::UnitTypeId unitTypeId): x(x), y(y), unitTypeId(unitTypeId) {

    }
   
    void SpawnCommand::spawnUnit(state::State& state, int x, int y, state::UnitTypeId unitTypeId) {
        if(state.getBoard().findUnitOnPosition(x, y)->getTeam() == state.getCurrentTeam()) {
            if(state.getBoard().findTeam(state.getBoard().findUnitOnPosition(x, y)->getTeam())->verifyGold(unitTypeId) && unitTypeId != state::UnitTypeId::LEADER) {
                if (state.getBoard().findTerrainOnPosition(x, y)->getTypeId() == state::TerrainTypeId::CASTLE &&
                        state.getBoard().findUnitOnPosition(x, y)->getTypeId() == state::UnitTypeId::LEADER) {
                    if (!state.getBoard().isUnitOnPosition(x - 1, y - 1)) {
                        state.getBoard().createNewUnit(unitTypeId, state.getBoard().findUnitOnPosition(x, y)->getTeam(), x - 1, y - 1);
                        state.getBoard().findTeam(state.getBoard().findUnitOnPosition(x, y)->getTeam())->withdrawGold(unitTypeId);
                        
                    } else if (!state.getBoard().isUnitOnPosition(x, y - 2)) {
                        state.getBoard().createNewUnit(unitTypeId, state.getBoard().findUnitOnPosition(x, y)->getTeam(), x, y - 2);
                        state.getBoard().findTeam(state.getBoard().findUnitOnPosition(x, y)->getTeam())->withdrawGold(unitTypeId);
                        
                    } else if (!state.getBoard().isUnitOnPosition(x + 1, y - 1)) {
                        state.getBoard().createNewUnit(unitTypeId, state.getBoard().findUnitOnPosition(x, y)->getTeam(), x + 1, y - 1);
                        state.getBoard().findTeam(state.getBoard().findUnitOnPosition(x, y)->getTeam())->withdrawGold(unitTypeId);
                    }
                }
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
