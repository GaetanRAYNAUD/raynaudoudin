#include "HandleAttackCommand.h"

namespace engine {

    std::vector<int> HandleAttackCommand::listUnitCanBeAttacked(state::State& state, int idUnit) {

    }

    void HandleAttackCommand::attackUnit(state::State& state, int idUnitAttacker, int idUnitDefender) {
        /*Vérifier qu'il reste des mouvements à l'attaquant, que les unités sont */
    }

    void HandleAttackCommand::execute(state::State& state) {

    }

    CommandTypeId HandleAttackCommand::getTypeId() const {

    }

    void HandleAttackCommand::killUnit(state::State& state, int idUnit) {

    }

}
