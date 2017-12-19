#include "Game.h"

namespace server {
        
    Game::Game() {

    }

    Player& Game::getPlayer(int id) {
        return players.at(id);
    }
}

