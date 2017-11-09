#include "MoveCommand.h"

namespace engine {

    MoveCommand::MoveCommand(int idUnit, int x, int y) : idUnit(idUnit), x(x), y(y) {
        
    }


    void MoveCommand::execute(state::State& state) {
        state.getBoard().findUnit(idUnit)->Move(x, y);
    }

    CommandTypeId MoveCommand::getTypeId() const {
        return CommandTypeId::MOVE;
    }

}
