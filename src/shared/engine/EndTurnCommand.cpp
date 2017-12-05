#include "EndTurnCommand.h"
#include "EndTurnAction.h"

namespace engine {

    EndTurnCommand::EndTurnCommand() {

    }

    void EndTurnCommand::execute(state::State& state, std::stack<std::shared_ptr<Action>>& actions) {
        std::shared_ptr<Action> action(new EndTurnAction());        
        actions.push(action);
        action->apply(state);
    }

    CommandTypeId EndTurnCommand::getTypeId() const {
        return CommandTypeId::END_TURN;
    }

}

