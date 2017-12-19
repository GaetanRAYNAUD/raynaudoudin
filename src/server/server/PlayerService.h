// Generated by dia2code
#ifndef SERVER__PLAYERSERVICE__H
#define SERVER__PLAYERSERVICE__H

#include <json/json.h>

namespace server {
  class Game;
  class AbstractService;
}

#include "HttpStatus.h"
#include "AbstractService.h"
#include "Game.h"

namespace server {

  /// class PlayerService - 
  class PlayerService : public server::AbstractService {
    // Associations
    // Attributes
  private:
    Game& game;
    // Operations
  public:
    PlayerService (Game& game);
    HttpStatus get (Json::Value& out, int id) const;
    HttpStatus post (const Json::Value& in, int id);
    HttpStatus put (Json::Value& out, const Json::Value& in);
    HttpStatus remove (int id);
    // Setters and Getters
  };

};

#endif
