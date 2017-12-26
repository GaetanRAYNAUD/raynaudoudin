#include "Game.h"

namespace server {

    Game::Game() {
        idseq = 0;
    }

    const Player* Game::getPlayer(int id) const {
        auto ite = players.find(id);
        
        if (ite == players.cend()) {
            return nullptr;
        }
        
        return ite->second.get();
    }

    int Game::addPlayer(std::unique_ptr<Player> player) {
        int id = idseq++;
        players.insert(std::make_pair(id, std::move(player)));
        
        return id;
    }

    void Game::setPlayer(int id, std::unique_ptr<Player> player) {
        players[id] = std::move(player);
        
        if (id > idseq) {
            idseq = id;
        }
    }
    
    void Game::removePlayer(int id) {
        auto ite = players.find(id);
        
        if (ite == players.end()) {
            return;
        }
        
        players.erase(ite);
    }

    void Game::run() {

    }

    const engine::Engine& Game::getEngine() const {
        return engine;
    }

    const std::map<int, std::unique_ptr<Player> >& Game::getPlayers() const {
        return players;
    }

}

