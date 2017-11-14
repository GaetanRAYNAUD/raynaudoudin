#include "MoveCommand.h"

namespace engine {

    MoveCommand::MoveCommand(int idUnit, state::Direction direction) : idUnit(idUnit), direction(direction) {
        
    }

    void MoveCommand::execute(state::State& state) {
        if(state.getBoard().findUnit(idUnit)->getTeam() == state.getCurrentTeam()) {
            state.getBoard().moveUnit(idUnit, direction);
        }
    }

    CommandTypeId MoveCommand::getTypeId() const {
        return CommandTypeId::MOVE;
    }

}
