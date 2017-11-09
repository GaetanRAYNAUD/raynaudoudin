#include "AttackCommand.h"

namespace engine {

    void AttackCommand::attackUnit(state::State& state, int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId) {
        if (state.getBoard().isUnitAround(idUnitAttacker, idUnitDefender)) {
            state.getBoard().findUnit(idUnitDefender)->takeDamage(state.getBoard().findUnit(idUnitAttacker)->getWeapons().at(weaponTypeId)->getDamage());
            if (state.getBoard().findUnit(idUnitDefender)->isDead()) {
                killUnit(state, idUnitDefender);
            }
        }
    }

    void AttackCommand::killUnit(state::State& state, int idUnit) {
        state.getBoard().deleteUnit(idUnit);          
    }
    
    void AttackCommand::execute(state::State& state) {
        
    }

    CommandTypeId AttackCommand::getTypeId() const {
        return CommandTypeId::ATTACK;
    }

}
