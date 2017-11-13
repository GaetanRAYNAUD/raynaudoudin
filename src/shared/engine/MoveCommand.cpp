#include "MoveCommand.h"

namespace engine {

    MoveCommand::MoveCommand(int idUnit, state::Direction direction) : idUnit(idUnit), direction(direction) {
        
    }

    void MoveCommand::execute(state::State& state) {
        state.getBoard().findUnit(idUnit)->Move(direction);
    }

    CommandTypeId MoveCommand::getTypeId() const {
        return CommandTypeId::MOVE;
    }

}
