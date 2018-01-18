#include "StateLayer.h"
#include "StateTileSet.h"
#include "state/House.h"

#include <vector>

namespace render {

    StateLayer::StateLayer(const state::State& state): state(state){
        tileset = std::make_shared<StateTileSet>();
        shiftHeight = 0;
        shiftWidth = 0;
    }

    void StateLayer::initSurface() {
        Tile tileMenuTop, tileMenuLeft, tileGold, tileHouse, tileTeam;
        std::vector<Tile> tilesFlagHouse;
        state::House* tmpHouse;
        int posX, posY;
        int nbQuads = 5;
        
        surface->loadTexture(tileset->getImageFile());
        surface->initQuads(nbQuads);
        
        tileMenuTop = tileset->getTile(MenuTypeId::MENU_TOP);
        
        surface->setSpriteTexture(0, tileMenuTop);
        surface->setSpriteLocation(0, 0 + shiftWidth, 0 + shiftHeight, 1920, tileMenuTop.getHeight());
        
        tileMenuLeft = tileset->getTile(MenuTypeId::MENU_LEFT);
        
        surface->setSpriteTexture(1, tileMenuLeft);
        surface->setSpriteLocation(1, 0 + shiftWidth, tileMenuTop.getHeight() + shiftHeight, 72 / 4, 1920);
        
        tileGold = tileset->getTile(MenuTypeId::MENU_GOLD);
        
        surface->setSpriteTexture(2, tileGold);
        surface->setSpriteLocation(2, 18 + shiftWidth, 12+ shiftHeight, 16, 16);
        
        tileHouse = tileset->getTile(MenuTypeId::MENU_HOUSE);
        
        surface->setSpriteTexture(3, tileHouse);
        surface->setSpriteLocation(3, 100 + shiftWidth, 12+ shiftHeight, 16, 16);
        
        if(state.getCurrentTeam() == state::TeamId::TEAM_1) {
            tileTeam = tileset->getTile(MenuTypeId::MENU_TEAM_1);
        } else {
            tileTeam = tileset->getTile(MenuTypeId::MENU_TEAM_2);
        }
        
        surface->setSpriteTexture(4, tileTeam);
        surface->setSpriteLocation(4, 182 + shiftWidth, 12+ shiftHeight, 16, 16);
        
        for(auto& t : state.getBoard().getTerrains()) {
            if(t.second.get()->getTypeId() == state::TerrainTypeId::HOUSE) {
                tmpHouse = (state::House*)t.second.get();
                
                if(tmpHouse->getTeamId() == state::TeamId::INVALID_TEAM) {
                    continue;
                } else {
                    nbQuads = nbQuads + 1;
                    surface->initQuads(nbQuads);                    
                    
                    if(tmpHouse->getTeamId() == state::TeamId::TEAM_1) {
                        tilesFlagHouse.push_back(tileset->getTile(MenuTypeId::MENU_TEAM_1));

                    } else if(tmpHouse->getTeamId() == state::TeamId::TEAM_2) {
                        tilesFlagHouse.push_back(tileset->getTile(MenuTypeId::MENU_TEAM_2));

                    }

                    posX = tmpHouse->getPositionX() * 72 - tmpHouse->getPositionX() * 72 / 4;
                    if (tmpHouse->getPositionX() % 2) {
                        posY = tmpHouse->getPositionY() / 2 * 72;
                    } else {
                        posY = tmpHouse->getPositionY() / 2 * 72 + 72 / 2;
                    }

                    surface->setSpriteTexture(nbQuads - 1, tilesFlagHouse.back());
                    surface->setSpriteLocation(nbQuads - 1, posX  + shiftWidth + 50, posY + shiftHeight + 10, 16, 16);
                }
            }
        }       

        surface->addText(35 + shiftWidth, 10 + shiftHeight, std::to_string(state.getBoard().findTeam(state.getCurrentTeam())->getGold()), sf::Color::White);
        
        surface->addText(118 + shiftWidth, 11 + shiftHeight, std::to_string(state.getBoard().findTeam(state.getCurrentTeam())->getNbHouses()), sf::Color::White);
    }
}
