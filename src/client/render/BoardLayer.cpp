#include "BoardLayer.h"

namespace render {

    BoardLayer::BoardLayer(const state::Board& board): board(board){
    }

    void BoardLayer::initSurface() {
        Surface* surfaceTerrain = new Surface();
        
        int numberOfTerrain = board.getTerrains().size();
        surfaceTerrain->initQuads(numberOfTerrain);
        
        int posX, posY;
        for(int i = 0; i < numberOfTerrain; i++) {
            Tile tileTerrain = tileset->getTile(*board.getTerrains().at(i));
            surfaceTerrain->setSpriteTexture(i, tileTerrain);
            
            posX = board.getTerrains().at(i).get()->getPositionX() * tileTerrain.getWidth() - board.getTerrains().at(i).get()->getPositionX() * tileTerrain.getWidth() / 4;
            if (board.getTerrains().at(i).get()->getPositionX() % 2) {
                posY = board.getTerrains().at(i).get()->getPositionY() * tileTerrain.getHeight();      
            } else {
                posY = board.getTerrains().at(i).get()->getPositionY() * tileTerrain.getHeight() + tileTerrain.getHeight() / 2;
            }
            
            surfaceTerrain->setSpriteLocation(i, posX, posY);
        }
    }

}
