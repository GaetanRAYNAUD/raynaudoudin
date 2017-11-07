#include "HandleAttackCommand.h"


namespace engine {

    void HandleAttackCommand::attackUnit(state::State& state, int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId) {
        if (state.getBoard().isUnitAround(idUnitAttacker, idUnitDefender)) {
            state.getBoard().findUnit(idUnitDefender)->takeDamage(state.getBoard().findUnit(idUnitAttacker)->getWeapons().at(weaponTypeId)->getDamage());
            if (state.getBoard().findUnit(idUnitDefender)->isDead()) {
                killUnit(state, idUnitDefender);
            }
        }
    }

    void HandleAttackCommand::execute(state::State& state) {

    }

    CommandTypeId HandleAttackCommand::getTypeId() const {

    }

    void HandleAttackCommand::killUnit(state::State& state, int idUnit) {

    }

}
