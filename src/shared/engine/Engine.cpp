#include "Engine.h"

namespace engine {

    Engine::Engine(int width, int height) : state(width, height) {
        
    }

    void Engine::addCommand(int priority, Command* cmd) {
        currentCommands.insert(std::make_pair(priority, std::unique_ptr<Command>(cmd)));
    }

    const state::State& Engine::getState() const {
        return state;
    }

    void Engine::update() {
        for(auto& c : currentCommands) {
            c.second.get()->execute(state);
        }
        
        currentCommands.clear();
    }

    Engine::~Engine() {

    }

}
