#include "PlayerService.h"
#include "Player.h"
#include "Game.h"
#include "ServiceException.h"

namespace server {
    
    PlayerService::PlayerService(Game& game) : AbstractService("/player"), game(game) {

    }

    HttpStatus PlayerService::get(Json::Value& out, int id) const {
        if(id >= 0) {  
            const Player* player = game.getPlayer(id);
            
            if(player != nullptr) {
                out["name"] = player->name;

                return HttpStatus::OK;

            } else {
                throw ServiceException(HttpStatus::NOT_FOUND, "Not found");
                
                return HttpStatus::NOT_FOUND;
            }
        } else {
            Json::Value jsonPlayer;
            
            for(auto& p : game.getPlayers()) {
                jsonPlayer["name"] = p.second->name;
                
                out["Players"].append(jsonPlayer);
            }
            
            return HttpStatus::OK;
        }
    }

    HttpStatus PlayerService::post(Json::Value& out, const Json::Value& in) {
        int id;
        std::string name;
        
        if(game.maxPlayer > game.getPlayers().size()) {
            if(in.size() == 1) {
                if(in.isMember("name")) {
                    if(in["name"].isString()) {
                        name = in["name"].asString();
                    } else {
                        throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");

                        return HttpStatus::BAD_REQUEST;
                    }

                    id = game.addPlayer(std::move(std::unique_ptr<Player>(new Player(name, false))));

                    out["id"] = id;
                    
                    if(game.getPlayer(id)->teamId == state::TeamId::TEAM_1) {
                        out["teamId"] = "TEAM_1";
                        
                    } else if(game.getPlayer(id)->teamId == state::TeamId::TEAM_2) {
                        out["teamId"] = "TEAM_2";
                        
                    } else {
                        out["teamId"] = "INVALID_TEAM";
                    }

                    return HttpStatus::CREATED;
                } else {
                    throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");

                    return HttpStatus::BAD_REQUEST;
                }
            } else {
                throw ServiceException(HttpStatus::BAD_REQUEST,"Bad request");

                return HttpStatus::BAD_REQUEST;                
            }
            
        } else {
            throw ServiceException(HttpStatus::OUT_OF_RESSOURCES, "Out of ressources");
            
            return HttpStatus::OUT_OF_RESSOURCES;
        }
    }

    HttpStatus PlayerService::put(const Json::Value& in, int id) {
        const Player* player = game.getPlayer(id);

        if(player != nullptr) {
            std::string name;

            if(in.size() == 1) {
                if(in.isMember("name")) {
                    if(in["name"].isString()) {
                        name = in["name"].asString();
                    } else {
                        throw ServiceException(HttpStatus::BAD_REQUEST, "Bad request");

                        return HttpStatus::BAD_REQUEST;
                    }
                } else {
                    name = player->name;
                }

                game.setPlayer(id, std::move(std::unique_ptr<Player>(new Player(name, player->free))));

                return HttpStatus::NO_CONTENT;

            } else {
                throw ServiceException(HttpStatus::BAD_REQUEST, "Bad request");

                return HttpStatus::BAD_REQUEST;                    

            }
        } else {
            throw ServiceException(HttpStatus::NOT_FOUND, "Not found");
            
            return HttpStatus::NOT_FOUND;
        }        
    }

    HttpStatus PlayerService::remove(int id) {
        if(game.getPlayer(id) == nullptr) {
            throw ServiceException(HttpStatus::NOT_FOUND, "Not found");
            
            return HttpStatus::NOT_FOUND;
        } else {
            game.removePlayer(id);

            if(game.getPlayer(id) == nullptr) {
                return HttpStatus::NO_CONTENT;
            } else {
                throw ServiceException(HttpStatus::SERVER_ERROR, "Server error");

                return HttpStatus::SERVER_ERROR;
            }
        }
    }
}