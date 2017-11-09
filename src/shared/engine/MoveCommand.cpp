#include "MoveCommand.h"

namespace engine {

    MoveCommand::MoveCommand(state::State& state, int idUnit, int x, int y) {

    }


    void MoveCommand::execute(state::State& state) {

    }

    CommandTypeId MoveCommand::getTypeId() const {
        return CommandTypeId::MOVE;
    }

}
