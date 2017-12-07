#include "MoveCommand.h"
#include "MoveAction.h"

namespace engine {

    MoveCommand::MoveCommand(int idUnit, state::Direction direction) : idUnit(idUnit), direction(direction) {
        
    }

    void MoveCommand::execute(state::State& state, std::stack<std::shared_ptr<Action>>& actions) {
        if(state.getBoard().findUnit(idUnit)->getTeam() == state.getCurrentTeam()) {
            if(state.getBoard().findTerrainOnPosition(state.getBoard().findUnit(idUnit)->getPositionX(), state.getBoard().findUnit(idUnit)->getPositionY(), direction) != nullptr) {
                std::shared_ptr<Action> action(new MoveAction(idUnit, direction, state.getBoard().findUnit(idUnit)->getSpeed()));
                actions.push(action);
                action->apply(state);                
            }
        }
    }

    CommandTypeId MoveCommand::getTypeId() const {
        return CommandTypeId::MOVE;
    }

    state::Direction MoveCommand::getDirection() const {
        return direction;
    }

    int MoveCommand::getIdUnit() const {
        return idUnit;
    }

}
