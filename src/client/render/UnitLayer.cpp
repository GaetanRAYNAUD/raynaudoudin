#include "UnitLayer.h"
#include "UnitTileSet.h"

namespace render {

    UnitLayer::UnitLayer(const state::Board& board) : board(board){
        std::dynamic_pointer_cast<UnitTileSet> (tileset);
    }

    void UnitLayer::initSurface() {
        int numberOfUnit = board.getUnits().size();
        surface->initQuads(numberOfUnit);

        surface->loadTexture(tileset->getImageFile());
        
        int posX, posY;
        for(int i = 0; i < numberOfUnit; i++) {
            Tile tileUnit = tileset->getTile(*board.getUnits().at(i));
            surface->setSpriteTexture(i, tileUnit);
            
            posX = board.getUnits().at(i).get()->getPositionX() * tileUnit.getWidth() - board.getUnits().at(i).get()->getPositionX() * tileUnit.getWidth() / 4;
            if (board.getUnits().at(i).get()->getPositionX() % 2) {
                posY = board.getUnits().at(i).get()->getPositionY() * tileUnit.getHeight();      
            } else {
                posY = board.getUnits().at(i).get()->getPositionY() * tileUnit.getHeight() + tileUnit.getHeight() / 2;
            }
            
            surface->setSpriteLocation(i, posX, posY, tileUnit.getWidth(), tileUnit.getHeight());
        }
    }

}