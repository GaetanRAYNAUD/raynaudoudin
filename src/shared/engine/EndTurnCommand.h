// Generated by dia2code
#ifndef ENGINE__ENDTURNCOMMAND__H
#define ENGINE__ENDTURNCOMMAND__H


namespace state {
  class State;
};
namespace engine {
  class Command;
}

#include "CommandTypeId.h"
#include "Command.h"

namespace engine {

  /// class EndTurnCommand - 
  class EndTurnCommand : public engine::Command {
    // Operations
  public:
    EndTurnCommand ();
    CommandTypeId getTypeId () const;
    void execute (state::State& state);
    // Setters and Getters
  };

};

#endif