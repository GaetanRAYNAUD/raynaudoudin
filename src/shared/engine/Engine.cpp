#include "Engine.h"
#include "../../../extern/jsoncpp-1.8.0/json/json.h"

namespace engine {

    Engine::Engine() : state(22, 8) {

    }

    Engine::Engine(int width, int height) : state(width, height) {
        
    }

    void Engine::addCommand(int priority, Command* cmd) {
        currentCommands.insert(std::make_pair(priority, std::unique_ptr<Command>(cmd)));
    }

    const state::State& Engine::getState() const {
        return state;
    }
    
    state::State& Engine::getState() {
        return state;
    }    

    const std::map<int, std::unique_ptr<Command> >& Engine::getCurrentCommands() const {
        return currentCommands;
    }

    std::stack<std::shared_ptr<Action>> Engine::update() {
        std::stack<std::shared_ptr<Action>> actions;
        
        for(auto& c : currentCommands) {
            c.second.get()->execute(state, actions);
        }
        
        currentCommands.clear();
        
        return actions;
    }
    
    void Engine::update(Json::Value& jsonValue) {
        std::stack<std::shared_ptr<Action>> actions;
        
        for(auto& c : currentCommands) {
            c.second.get()->execute(state, actions);
            c.second->serialize(jsonValue);
        }
        
        currentCommands.clear();
        while(!actions.empty()) {
            actions.pop();
        }
    }

    void Engine::undo(std::stack<std::shared_ptr<Action>>& actions) {
        while(!actions.empty()) {
            actions.top()->undo(state);
            actions.pop();
        }
    }
    

    Engine::~Engine() {

    }

}
