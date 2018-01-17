#include "TerrainLayer.h"
#include "TerrainTileSet.h"

#include <limits>
#include <complex>

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
        double minDist = std::numeric_limits<double>::max();
        int nbTile = -1;
        
        for(unsigned int i = 0; i < vertex.getVertexCount() - 3; i = i + 4) {
            sf::Vector2f center((vertex[i].position.x + vertex[i + 2].position.x) / 2, (vertex[i].position.y + vertex[i + 2].position.y) / 2);
            double disti = std::sqrt(std::pow(x - center.x, 2) + std::pow(y - center.y, 2));
            
            if(disti < minDist) {
                minDist = disti;
                nbTile = i / 4;
            }
        }
        
        if(nbTile != -1) {
            return board.getTerrains().at(nbTile)->clone();
        }
        
        return nullptr;
    }
    

}

