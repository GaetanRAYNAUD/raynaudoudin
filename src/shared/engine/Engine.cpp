#include "Engine.h"

namespace engine {

    Engine::Engine(int width, int height) : currentState(width, height) {
        
    }

    void Engine::addCommand(int priority, Command* cmd) {
        currentCommands.insert(std::make_pair(priority, std::unique_ptr<Command>(cmd)));
    }

    const state::State& Engine::getState() const {
        return currentState;
    }

    void Engine::update() {
        for(auto& c : currentCommands) {
            c.second.get()->execute(currentState);
        }
        
        currentCommands.clear();
    }

    Engine::~Engine() {

    }

}
