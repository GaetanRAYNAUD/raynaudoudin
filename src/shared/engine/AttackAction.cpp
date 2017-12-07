#include "AttackAction.h"
#include "state/State.h"

namespace engine {

    AttackAction::AttackAction(int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId) : idUnitAttacker(idUnitAttacker), idUnitDefender(idUnitDefender), weaponTypeId(weaponTypeId) {

    }

    void AttackAction::apply(state::State& state) {
        speedAttacker = state.getBoard().findUnit(idUnitAttacker)->getSpeed();
        unitAttacked.reset(state.getBoard().findUnit(idUnitDefender)->clone());
        state.getBoard().findUnit(idUnitDefender)->takeDamage(state.getBoard().findUnit(idUnitAttacker)->getWeapons().at(weaponTypeId)->getDamage());
        state.getBoard().findUnit(idUnitAttacker)->setSpeed(0);

        if (state.getBoard().findUnit(idUnitDefender)->isDead()) {
            state.getBoard().deleteUnit(idUnitDefender);
        }        
    }

    void AttackAction::undo(state::State& state) {
        state.getBoard().findUnit(idUnitAttacker)->setSpeed(speedAttacker);
        state.getBoard().addUnit(std::move(unitAttacked), unitAttacked->getId());
    }

}
