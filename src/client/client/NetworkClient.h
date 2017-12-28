// Generated by dia2code
#ifndef CLIENT__NETWORKCLIENT__H
#define CLIENT__NETWORKCLIENT__H

#include <string>
#include <memory>
#include <json/json.h>

namespace engine {
  class Engine;
};
namespace ai {
  class AI;
}

#include "state/TeamId.h"
#include "engine/Engine.h"
#include "ai/AI.h"

namespace client {

  /// class NetworkClient - 
  class NetworkClient {
    // Associations
    // Attributes
  private:
    std::string url;
    int port;
    state::TeamId player;
    engine::Engine engine;
    std::unique_ptr<ai::AI> player_ai;
    // Operations
  public:
    NetworkClient (const std::string& url, int port, state::TeamId player);
    std::string getGameStatus ();
    bool getServerCommands (Json::Value& out, int turn);
    void putServerCommand (engine::Command* command);
    void run ();
    // Setters and Getters
  };

};

#endif
