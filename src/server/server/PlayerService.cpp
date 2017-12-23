#include "PlayerService.h"
#include "Player.h"
#include "Game.h"

#include <string>

namespace server {
    
    PlayerService::PlayerService(Game* game) : AbstractService("/player"), game(game) {

    }

    HttpStatus PlayerService::get(Json::Value& out, int id) const {
        if(id >= 0) {  
            const Player* player = game->getPlayer(id);
            
            if(player != nullptr) {
                out["name"] = player->name;

                return HttpStatus::OK;

            } else {
                return HttpStatus::NOT_FOUND;
            }
        } else {
            Json::Value jsonPlayer;
            
            for(auto& p : game->getPlayers()) {
                jsonPlayer["name"] = p.second->name;
                
                out["Players"].append(jsonPlayer);
            }
            
            return HttpStatus::OK;
        }
    }

    HttpStatus PlayerService::post(const Json::Value& in, int id) {
//        const Player* player = game.getPlayer(id);
//        std::string name;
//        bool free;

//        if(player != nullptr) {
//            if(in.isMember("free")) {
//                if(in["free"].isBool()) {
//                    free = in["free"].asInt();
//                } else {
//                    throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");
//
//                    return HttpStatus::BAD_REQUEST;
//                }
//            } else {
//                free = player->free;
//            }
//
//            if(in.isMember("name")) {
//                if(in["name"].isString()) {
//                    name = in["name"].asString();
//                } else {
//                    throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");
//
//                    return HttpStatus::BAD_REQUEST;
//                }
//            } else {
//                name = player->name;
//            }
//
//            return HttpStatus::OK;
//        } else {
//            throw ServiceException(HttpStatus::NOT_FOUND,"Not found");
//
//            return HttpStatus::NOT_FOUND;
//        }
        
        return HttpStatus::NO_CONTENT;
    }

    HttpStatus PlayerService::put(Json::Value& out, const Json::Value& in) {            
//        bool free;
//        int id;
//        std::string name;

//        if(in.isMember("free") && in.isMember("name")) {
//            if(in["free"].isBool()) {
//                free = in["free"].asInt();
//            } else {
//                throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");
//
//                return HttpStatus::BAD_REQUEST;
//            }
//
//            if(in["name"].isString()) {
//                name = in["name"].asString();
//            } else {
//                throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");
//
//                return HttpStatus::BAD_REQUEST;
//            }
//
//            out["id"] = id;
//
//            return HttpStatus::CREATED;
//        } else {
//            throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");
//
//            return HttpStatus::BAD_REQUEST;
//        }
        return HttpStatus::OK;
    }

    HttpStatus PlayerService::remove(int id) {
        return HttpStatus::OK;
    }
}