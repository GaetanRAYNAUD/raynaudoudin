#include "Engine.h"
#include "json/json.h"
#include "engine/HandleWinCommand.h"
#include "engine/MoveCommand.h"
#include "engine/AttackCommand.h"
#include "engine/SpawnCommand.h"
#include "engine/LoadCommand.h"
#include "engine/EndTurnCommand.h"

#include <iostream>
namespace engine {

    Engine::Engine() : state(22, 8) {

    }

    Engine::Engine(int width, int height) : state(width, height) {
        
    }

    void Engine::addCommand(int priority, Command* cmd) {
        currentCommands.insert(std::make_pair(priority, std::unique_ptr<Command>(cmd)));
    }

    void Engine::addCommands(const Json::Value& in) {
        Json::Value jsonCommands;
        
        if(in.empty()) {
            return;
        }
        
        if(in.isMember("Commands")) {
            for(unsigned int i = 0; i < in["Commands"].size(); i++) {
                jsonCommands = in["Commands"][i];

                if(!in.empty() && jsonCommands.isMember("Type") && jsonCommands.isMember("priority")) {
                    if(jsonCommands["Type"] == "HandleWinCommand") {
                        addCommand(jsonCommands["priority"].asInt(), engine::HandleWinCommand::deserialize(jsonCommands));
                    } else if(jsonCommands["Type"] == "EndTurnCommand") {
                        addCommand(jsonCommands["priority"].asInt(), engine::EndTurnCommand::deserialize(jsonCommands));
                    } else if(jsonCommands["Type"] == "MoveCommand") {
                        addCommand(jsonCommands["priority"].asInt(), engine::MoveCommand::deserialize(jsonCommands));
                    } else if(jsonCommands["Type"] == "AttackCommand") {
                        addCommand(jsonCommands["priority"].asInt(), engine::AttackCommand::deserialize(jsonCommands));
                    } else if(jsonCommands["Type"] == "SpawnCommand") {
                        addCommand(jsonCommands["priority"].asInt(), engine::SpawnCommand::deserialize(jsonCommands));
                    } else if(jsonCommands["Type"] == "LoadCommand") {
                        addCommand(jsonCommands["priority"].asInt(), engine::LoadCommand::deserialize(jsonCommands));
                    }
                }
            }
        }
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
            c.second->serialize(commandHistory);
            
            commandHistory["Commands"][commandHistory["Commands"].size() - 1]["priority"] = c.first;
            commandHistory["Commands"][commandHistory["Commands"].size() - 1]["epoch"] = state.getEpoch();
            
            state.addEpoch();
        }
        
        currentCommands.clear();
        
        return actions;
    }

    void Engine::undo(std::stack<std::shared_ptr<Action>>& actions) {
        while(!actions.empty()) {
            actions.top()->undo(state);
            actions.pop();
        }
    }

    const Json::Value& Engine::getCommandHistory() const {
        return commandHistory;
    }

    Engine::~Engine() {

    }

}
