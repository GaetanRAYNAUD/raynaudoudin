#include "EndTurnCommand.h"

namespace engine {

    EndTurnCommand::EndTurnCommand() {

    }

    void EndTurnCommand::execute(state::State& state) {
        state.endTurn();
    }

    CommandTypeId EndTurnCommand::getTypeId() const {
        return CommandTypeId::END_TURN;
    }

}

