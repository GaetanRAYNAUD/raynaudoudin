#include "GameService.h"

#include <iostream>
namespace server {

    GameService::GameService(Game* game) : AbstractService("/game"), game(game) {

    }

    HttpStatus GameService::get(Json::Value& out, int id) const {
        if(game->getEngine().getState().getEpoch() != 0) {
            out["Game Status"] = "RUNNING";
        } else {
            out["Game Status"] = "CREATING";
        }

        return HttpStatus::OK;
    }
}