#include "TerrainLayer.h"
#include "TerrainTileSet.h"
#include <iostream>

namespace render {

    TerrainLayer::TerrainLayer(const state::Board& board) : board(board) {
         std::dynamic_pointer_cast<TerrainTileSet> (tileset);
         
    }

    void TerrainLayer::initSurface() {
        surface->loadTexture(tileset->getImageFile());
        
        int numberOfTerrain = board.getTerrains().size();
        surface->initQuads(numberOfTerrain);
        
        int posX, posY;
        for(int i = 0; i < numberOfTerrain; i++) {
            Tile tileTerrain = tileset->getTile(*board.getTerrains().at(i));
            surface->setSpriteTexture(i, tileTerrain);
            
            posX = board.getTerrains().at(i).get()->getPositionX() * tileTerrain.getWidth() - board.getTerrains().at(i).get()->getPositionX() * tileTerrain.getWidth() / 4;
            if (board.getTerrains().at(i).get()->getPositionX() % 2) {
                posY = board.getTerrains().at(i).get()->getPositionY() * tileTerrain.getHeight();      
            } else {
                posY = board.getTerrains().at(i).get()->getPositionY() * tileTerrain.getHeight() + tileTerrain.getHeight() / 2;
            }
            
            surface->setSpriteLocation(i, posX, posY, tileTerrain.getWidth(), tileTerrain.getHeight());
        }
    }

}

