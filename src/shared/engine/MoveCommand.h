// Generated by dia2code
#ifndef ENGINE__MOVECOMMAND__H
#define ENGINE__MOVECOMMAND__H


namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "CommandTypeId.h"
#include "Command.h"

namespace engine {

  /// class MoveCommand - 
  class MoveCommand : public engine::Command {
    // Operations
  public:
    MoveCommand (state::State& state, int idUnit, int x, int y);
    CommandTypeId getTypeId () const;
    void execute (state::State& state);
    // Setters and Getters
  };

};

#endif
