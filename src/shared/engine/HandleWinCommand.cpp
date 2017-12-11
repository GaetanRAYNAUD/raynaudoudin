#include "HandleWinCommand.h"
#include "WinnerAction.h"
#include "../../../extern/jsoncpp-1.8.0/json/json.h"


namespace engine {
        
    HandleWinCommand::HandleWinCommand() {

    }
    
    void HandleWinCommand::execute(state::State& state, std::stack<std::shared_ptr<Action>>& actions) {       
        if (state.getBoard().isLeaderNotAlive(state::TeamId::TEAM_1)) {
            std::shared_ptr<Action> action(new WinnerAction(state::TeamId::TEAM_2));
            actions.push(action);
            action->apply(state);
        } else if (state.getBoard().isLeaderNotAlive(state::TeamId::TEAM_2)) {
            std::shared_ptr<Action> action(new WinnerAction(state::TeamId::TEAM_1));
            actions.push(action);
            action->apply(state);
        } else {
            return;
        }
    }

    CommandTypeId HandleWinCommand::getTypeId() const {
        return CommandTypeId::HANDLE_WIN;
    }

    Command* HandleWinCommand::clone() const {
        return new HandleWinCommand(*this);
    }

    void HandleWinCommand::serialize(Json::Value& out) const {
        Json::Value jsonCommand;
        jsonCommand["Type"] = "HandleWinCommand";
        
        out["Commands"].append(jsonCommand);
    }

    HandleWinCommand* HandleWinCommand::deserialize(const Json::Value& in) {
        
        return new HandleWinCommand();
    }

}
