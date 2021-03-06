// Generated by dia2code
#ifndef ENGINE__ATTACKACTION__H
#define ENGINE__ATTACKACTION__H

#include <memory>

namespace state {
  class Unit;
  class State;
};
namespace engine {
  class Action;
}

#include "state/WeaponTypeId.h"
#include "state/Unit.h"
#include "Action.h"

namespace engine {

  /// class AttackAction - 
  class AttackAction : public engine::Action {
    // Attributes
  protected:
    int idUnitAttacker;
    int idUnitDefender;
    int speedAttacker;
    state::WeaponTypeId weaponTypeId;
    std::unique_ptr<state::Unit> unitAttacked;
    // Operations
  public:
    AttackAction (int idUnitAttacker, int idUnitDefender, state::WeaponTypeId weaponTypeId);
    void apply (state::State& state);
    void undo (state::State& state);
    // Setters and Getters
    int getIdUnitAttacker() const;
    void setIdUnitAttacker(int idUnitAttacker);
    int getIdUnitDefender() const;
    void setIdUnitDefender(int idUnitDefender);
    int getSpeedAttacker() const;
    void setSpeedAttacker(int speedAttacker);
    state::WeaponTypeId getWeaponTypeId() const;
    void setWeaponTypeId(state::WeaponTypeId weaponTypeId);
    const std::unique_ptr<state::Unit>& getUnitAttacked() const;
    void setUnitAttacked(const std::unique_ptr<state::Unit>& unitAttacked);
  };

};

#endif
