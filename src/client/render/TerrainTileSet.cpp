#include "TerrainTileSet.h"

namespace render {

    TerrainTileSet::TerrainTileSet() {
        
    }

    int TerrainTileSet::getCellHeight() const {
        return terrain[0].getHeight();
    }

    int TerrainTileSet::getCellWidth() const {
        return terrain[0].getWidth();
    }

    const std::string TerrainTileSet::getImageFile() const {
        return "res/terrains/terrain.png";
    }
    
    const Tile& TerrainTileSet::getTile(const state::Terrain& terrain) const {
        return this->terrain[0];
    }


}
