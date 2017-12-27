#include "AttackCommand.h"
#include "AttackAction.h"
#include "json/json.h"

namespace engine {

    AttackCommand::AttackCommand(int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId): 
        idUnitAttacker(idUnitAttacker), idUnitDefender(idUnitDefender), weaponTypeId(weaponTypeId) {
        
    }
    
    void AttackCommand::execute(state::State& state, std::stack<std::shared_ptr<Action>>& actions) {
        if(state.getBoard().findUnit(idUnitAttacker)->getTeam() == state.getCurrentTeam()) {
            if (state.getBoard().isUnitAround(idUnitAttacker, idUnitDefender) && state.getBoard().findUnit(idUnitAttacker)->getSpeed() > 0) {            
                std::shared_ptr<Action> action(new AttackAction(idUnitAttacker, idUnitDefender, weaponTypeId));
                actions.push(action);
                action->apply(state);
            }
        }
    }

    CommandTypeId AttackCommand::getTypeId() const {
        return CommandTypeId::ATTACK;
    }

    int AttackCommand::getIdUnitAttacker() const {
        return idUnitAttacker;
    }

    int AttackCommand::getIdUnitDefender() const {
        return idUnitDefender;
    }

    state::WeaponTypeId AttackCommand::getWeaponTypeId() const {
        return weaponTypeId;
    }

    Command* AttackCommand::clone() const {
        return new AttackCommand(*this);
    }

    void AttackCommand::serialize(Json::Value& out) const {
        Json::Value jsonCommand;
        jsonCommand["Type"] = "AttackCommand";
        jsonCommand["idAttacker"] = idUnitAttacker;
        jsonCommand["idDefender"] = idUnitDefender;
        jsonCommand["weaponTypeId"] = weaponTypeId;
        
        out["Commands"].append(jsonCommand);
    }

    AttackCommand* AttackCommand::deserialize(const Json::Value& in) {
        int idUnitAttacker;
        int idUnitDefender;
        state::WeaponTypeId weaponTypeId;
        
        idUnitAttacker = in["idAttacker"].asInt();
        idUnitDefender = in["idDefender"].asInt();
        weaponTypeId = (state::WeaponTypeId)in["weaponTypeId"].asInt();
        
        return new AttackCommand(idUnitAttacker, idUnitDefender, weaponTypeId);
    }

}
