#include "UnitLayer.h"
#include "UnitTileSet.h"

namespace render {

    UnitLayer::UnitLayer(const state::Board& board) : board(board) {
        tileset = std::make_shared<UnitTileSet>();
    }

    void UnitLayer::initSurface() {
        int posX, posY, i = 0;
               
        surface->loadTexture(tileset->getImageFile());
                
        int numberOfUnit = board.getUnits().size();
        surface->initQuads(numberOfUnit);
        
        for(auto& u : board.getUnits()) {
            Tile tileUnit = tileset->getTile(*(u.second.get()));
            surface->setSpriteTexture(i, tileUnit);
            
            posX = u.second.get()->getPositionX() * tileUnit.getWidth() - u.second.get()->getPositionX() * tileUnit.getWidth() / 4;
            if (u.second.get()->getPositionX() % 2) {
                posY = u.second.get()->getPositionY() / 2 * tileUnit.getHeight();      
            } else {
                posY = u.second.get()->getPositionY() / 2 * tileUnit.getHeight() + tileUnit.getHeight() / 2;
            }
            
            surface->setSpriteLocation(i, posX, posY, tileUnit.getWidth(), tileUnit.getHeight());
            
            if(u.second->getTeam() == state::TeamId::TEAM_1) {
                surface->addText(posX + tileUnit.getWidth() / 3, posY + tileUnit.getHeight() - 20, std::to_string(u.second.get()->getLife()), sf::Color::Red);
            } else if(u.second->getTeam() == state::TeamId::TEAM_2) {
                surface->addText(posX + tileUnit.getWidth() / 3, posY + tileUnit.getHeight() - 20, std::to_string(u.second.get()->getLife()), sf::Color::Green);
            }
            i++;
        }
        
    }

    void UnitLayer::stateChanged(const state::Event& event) {

    }

    void UnitLayer::updateUnit(int i, int j) {

    }


}