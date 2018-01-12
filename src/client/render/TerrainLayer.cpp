#include "TerrainLayer.h"
#include "TerrainTileSet.h"

#include <iostream>
namespace render {

    TerrainLayer::TerrainLayer(const state::Board& board) : board(board) {
        tileset = std::make_shared<TerrainTileSet>();
    }

    void TerrainLayer::initSurface() {
        int posX, posY, i = 0;
        
        surface->loadTexture(tileset->getImageFile());
        
        int numberOfTerrain = board.getTerrains().size();
        surface->initQuads(numberOfTerrain);
        
        for(auto& t : board.getTerrains()) {
            Tile tileTerrain = tileset->getTile(*(t.second.get()));
            surface->setSpriteTexture(i, tileTerrain);
            
            posX = t.second.get()->getPositionX() * tileTerrain.getHeight() - t.second.get()->getPositionX() * tileTerrain.getWidth() / 4;
            if (t.second.get()->getPositionX() % 2) {
                posY = t.second.get()->getPositionY() / 2 * tileTerrain.getHeight();
            } else {
                posY = t.second.get()->getPositionY() / 2 * tileTerrain.getHeight() + tileTerrain.getHeight() / 2;
            }
            
            surface->setSpriteLocation(i, posX, posY, tileTerrain.getWidth(), tileTerrain.getHeight());
            i++;
        }
    }

    state::Terrain* TerrainLayer::getTerrainFromPositionOnWindow(int x, int y) {
        sf::VertexArray vertex = surface->getQuads();
        
        for(unsigned int i = 0; i < vertex.getVertexCount() - 3; i = i + 4) {
            if(vertex[i].position.x < x && vertex[i].position.y < y && vertex[i + 2].position.x > x && vertex[i + 2].position.y > y) {
                return board.getTerrains().at(i / 4)->clone();
            }
        }
        
        return nullptr;
    }
    

}

