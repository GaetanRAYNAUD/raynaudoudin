#include "AttackCommand.h"

namespace engine {

    AttackCommand::AttackCommand(int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId): 
        idUnitAttacker(idUnitAttacker), idUnitDefender(idUnitDefender), weaponTypeId(weaponTypeId) {
        
    }

    void AttackCommand::attackUnit(state::State& state, int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId) {
        if(state.getBoard().findUnit(idUnitAttacker)->getTeam() == state.getCurrentTeam()) {
            if (state.getBoard().isUnitAround(idUnitAttacker, idUnitDefender) && state.getBoard().findUnit(idUnitAttacker)->getSpeed() > 0) {            
                state.getBoard().findUnit(idUnitDefender)->takeDamage(state.getBoard().findUnit(idUnitAttacker)->getWeapons().at(weaponTypeId)->getDamage());
                state.getBoard().findUnit(idUnitAttacker)->setSpeed(0);

                if (state.getBoard().findUnit(idUnitDefender)->isDead()) {
                    killUnit(state, idUnitDefender);
                }
            }
        }
    }

    void AttackCommand::killUnit(state::State& state, int idUnit) {
        state.getBoard().deleteUnit(idUnit);          
    }
    
    void AttackCommand::execute(state::State& state) {
        attackUnit(state, idUnitAttacker, idUnitDefender, weaponTypeId);
    }

    CommandTypeId AttackCommand::getTypeId() const {
        return CommandTypeId::ATTACK;
    }

}
