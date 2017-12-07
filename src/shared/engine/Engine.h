// Generated by dia2code
#ifndef ENGINE__ENGINE__H
#define ENGINE__ENGINE__H

#include <map>
#include <memory>
#include <stack>

namespace state {
  class State;
};
namespace engine {
  class Command;
  class Action;
}

#include "state/State.h"
#include "Action.h"
#include "Command.h"

namespace engine {

  /// class Engine - 
  class Engine {
    // Associations
    // Attributes
  protected:
    state::State state;
    std::map<int, std::unique_ptr<Command>> currentCommands;
    // Operations
  public:
    Engine (int width, int height);
    virtual ~Engine ();
    void addCommand (int priority, Command* cmd);
    std::stack<std::shared_ptr<Action>> update ();
    void undo (std::stack<std::shared_ptr<Action>>& actions);
    state::State& getState ();
    const state::State& getState () const;
    // Setters and Getters
    void setState(const state::State& state);
    const std::map<int, std::unique_ptr<Command>>& getCurrentCommands() const;
    void setCurrentCommands(const std::map<int, std::unique_ptr<Command>>& currentCommands);
  };

};

#endif
