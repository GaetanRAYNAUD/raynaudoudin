#include "PlayerService.h"

#include <string>

namespace server {
    PlayerService::PlayerService (Game& game) : AbstractService("/user"), game(game) {

    }

    HttpStatus PlayerService::get (Json::Value& out, int id) const {
        Player player = game.getPlayer(id);

        out["free"] = player.free;
        out["name"] = player.name;

        return HttpStatus::OK;
    }

    HttpStatus PlayerService::post (const Json::Value& in, int id) {
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
        
        return HttpStatus::OK;
    }

    HttpStatus PlayerService::put (Json::Value& out, const Json::Value& in) {            
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

    HttpStatus PlayerService::remove (int id) {
        return HttpStatus::OK;
    }
}