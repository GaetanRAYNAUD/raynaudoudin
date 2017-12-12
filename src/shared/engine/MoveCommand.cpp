#include "MoveCommand.h"
#include "MoveAction.h"
#include "../../../extern/jsoncpp-1.8.0/json/json.h"

#include <iostream>
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

    Command* MoveCommand::clone() const {
        return new MoveCommand(*this);
    }

    void MoveCommand::serialize(Json::Value& out) const {
        Json::Value jsonCommand;
        jsonCommand["Type"] = "MoveCommand";
        jsonCommand["idUnit"] = idUnit;
        
        switch (direction) {
            case state::Direction::TOP:
                jsonCommand["Direction"] = "TOP";
                break;
            case state::Direction::TOP_RIGHT:
                jsonCommand["Direction"] = "TOP_RIGHT";
                break;
            case state::Direction::BOT_RIGHT:
                jsonCommand["Direction"] = "BOT_RIGHT";
                break;
            case state::Direction::BOT:
                jsonCommand["Direction"] = "BOT";
                break;
            case state::Direction::BOT_LEFT:
                jsonCommand["Direction"] = "BOT_LEFT";
                break;
            case state::Direction::TOP_LEFT:
                jsonCommand["Direction"] = "TOP_LEFT";
                break;
        }
        
        out["Commands"].append(jsonCommand);
    }

    MoveCommand* MoveCommand::deserialize(const Json::Value& in) {
        int idUnit;
        state::Direction direction;
        
        idUnit = in["idUnit"].asInt();
        
        if(in["Direction"].asString() == "TOP") {
            direction = state::Direction::TOP;
        } else if(in["Direction"].asString() == "TOP_RIGHT") {
            direction = state::Direction::TOP_RIGHT;
        } else if(in["Direction"].asString() == "BOT_RIGHT") {
            direction = state::Direction::BOT_RIGHT;
        } else if(in["Direction"].asString() == "BOT") {
            direction = state::Direction::BOT;
        } else if(in["Direction"].asString() == "BOT_LEFT") {
            direction = state::Direction::BOT_LEFT;
        } else if(in["Direction"].asString() == "TOP_LEFT") {
            direction = state::Direction::TOP_LEFT;
        } else {
            direction = state::Direction::BOT;
        }

        return new MoveCommand(idUnit, direction);
    }

}
