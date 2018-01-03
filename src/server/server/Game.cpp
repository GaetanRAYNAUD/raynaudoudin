#include "Game.h"
#include "engine/LoadCommand.h"
#include "engine/HandleWinCommand.h"

#include <unistd.h>
#include <iostream>

namespace server {

    Game::Game() {
        engineThread.reset(new std::thread(&Game::run, this));
        idseq = 0;        
    }

    Game::~Game() {
        engineThread->~thread();
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

        if(players.size() == 0) {
            player->teamId = state::TeamId::TEAM_1;
            
        } else if(players.size() == 1) {
            player->teamId = state::TeamId::TEAM_2;
            
        } else {
            player->teamId = state::TeamId::INVALIDTEAM;
        }
        
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

    engine::Engine& Game::getEngine() {
        return engine;
    }

    const std::map<int, std::unique_ptr<Player> >& Game::getPlayers() const {
        return players;
    }

    void Game::run() {        
        while(engine.getState().getEpoch() == 0) {
            if(players.size() == maxPlayer) {
                engine.addCommand(1, new engine::LoadCommand("res/map.txt"));
                engine.update();
                
            } else {
                usleep(300000);
            }
        }

        while(engine.getState().getWinner() == state::TeamId::INVALIDTEAM) {
            if(players.size() < maxPlayer) {
                return;
            }
            
            if(engine.getCurrentCommands().size() > 0) {
                engine.addCommand(engine.getCurrentCommands().size(), new engine::HandleWinCommand());
                engine.update();
            }
            
            usleep(30000);
        }
        
        std::cout << "Partie terminée !" << std::endl;
    }    
}

