#include "CommandService.h"
#include "ServiceException.h"
#include "engine/HandleWinCommand.h"
#include "engine/MoveCommand.h"
#include "engine/AttackCommand.h"
#include "engine/SpawnCommand.h"
#include "engine/LoadCommand.h"
#include "engine/EndTurnCommand.h"

#include <iostream>

namespace server {

    CommandService::CommandService(engine::Engine& engine) : AbstractService("/command"), engine(engine) {

    }

    HttpStatus CommandService::get(Json::Value& out, int id) const {
        if(id <= engine.getState().getEpoch()) {
            Json::Value commandHistory = engine.getCommandHistory();

            if(!commandHistory.empty()) {
                for(auto& jsonCommands : commandHistory["Commands"]) {
                    if(jsonCommands["epoch"].isInt() && jsonCommands["epoch"].asInt() == id) {
                        out["Commands"].append(jsonCommands);
                    }
                }
            }
            
            return HttpStatus::OK;
            
        } else {
            throw ServiceException(HttpStatus::NOT_FOUND, "Not found");
                
            return HttpStatus::NOT_FOUND;            
        }
    }

    HttpStatus CommandService::post(Json::Value& out, const Json::Value& in) {     
        if(!in.empty()) {                       
            engine.addCommands(in);
        }

        out["epoch"] = engine.getState().getEpoch();
        
        return HttpStatus::CREATED;
    }

}

