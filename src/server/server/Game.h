// Generated by dia2code
#ifndef SERVER__GAME__H
#define SERVER__GAME__H

#include <map>
#include <memory>

namespace server {
  class Player;
  class PlayerService;
}

#include "Player.h"
#include "PlayerService.h"

namespace server {

  /// class Game - 
  class Game {
    // Associations
    // Attributes
  public:
    const unsigned int maxPlayer     = 2;
  protected:
    std::map<int, std::unique_ptr<server::Player>> players;
    int idseq;
    // Operations
  public:
    Game ();
    const Player* getPlayer (int id) const;
    int addPlayer (std::unique_ptr<server::Player> player);
    void setPlayer (int id, std::unique_ptr<server::Player> player);
    void removePlayer (int id);
    // Setters and Getters
    const std::map<int, std::unique_ptr<server::Player>>& getPlayers() const;
    void setPlayers(const std::map<int, std::unique_ptr<server::Player>>& players);
    int getIdseq() const;
    void setIdseq(int idseq);
  };

};

#endif
