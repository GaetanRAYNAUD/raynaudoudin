// Generated by dia2code
#ifndef AI__AI__H
#define AI__AI__H

#include <vector>

namespace engine {
  class Engine;
};
namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "engine/Engine.h"
#include "engine/Command.h"
#include "state/State.h"

namespace ai {

  /// class AI - 
  class AI {
    // Operations
  public:
    virtual ~AI ();
    virtual void run (engine::Engine& engine) = 0;
  protected:
    std::vector<engine::Command*> listCommands (const state::State& state);
    std::vector<engine::Command*> listCommandsMovement (const state::State& state, int idUnit);
    std::vector<engine::Command*> listCommandsSpawn (const state::State& state, int idUnit);
    std::vector<engine::Command*> listCommandsAttack (const state::State& state, int idUnit);
    // Setters and Getters
  };

};

#endif
