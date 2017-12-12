#include "EndTurnCommand.h"
#include "EndTurnAction.h"
#include "../../../extern/jsoncpp-1.8.0/json/json.h"

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

    Command* EndTurnCommand::clone() const {
        return new EndTurnCommand(*this);
    }

    void EndTurnCommand::serialize(Json::Value& out) const {
        Json::Value jsonCommand;
        jsonCommand["Type"] = "EndTurnCommand";
        
        out["Commands"].append(jsonCommand);
    }
    
    EndTurnCommand* EndTurnCommand::deserialize(const Json::Value& in) {
        return new EndTurnCommand();
    }

}

