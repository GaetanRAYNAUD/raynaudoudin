#include "Engine.h"

#include <iostream>
namespace engine {

    Engine::Engine(int width, int height) : state(width, height) {
        
    }

    void Engine::addCommand(int priority, Command* cmd) {
        currentCommands.insert(std::make_pair(priority, std::unique_ptr<Command>(cmd)));
    }

    const state::State& Engine::getState() const {
        return state;
    }

    std::stack<std::shared_ptr<Action>> Engine::update() {
        std::stack<std::shared_ptr<Action>> actions;
        
        for(auto& c : currentCommands) {
            c.second.get()->execute(state, actions);
        }
        
        currentCommands.clear();
        
        return actions;
    }

    void Engine::undo(std::stack<std::shared_ptr<Action>>& actions) {
        unsigned int size = actions.size();
        for(unsigned int i = 0; i < size; i++) {
            actions.top()->undo(state);
            actions.pop();
        }
    }
    

    Engine::~Engine() {

    }

}
