#include "Engine.h"

namespace engine {

    Engine::Engine() {
        currentState = state::State();
    }

    void Engine::addCommand(int priority, Command* cmd) {
        currentCommands.insert(std::make_pair(priority, std::unique_ptr<Command>(cmd)));
    }

    void Engine::addPassiveCommands() {

    }

    const state::State& Engine::getState() const {

    }

    void Engine::update() {

    }

    Engine::~Engine() {

    }

}
