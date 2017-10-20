#include "TerrainTileSet.h"

namespace render {

    int TerrainTileSet::getCellHeight() const {
    }

    int TerrainTileSet::getCellWidth() const {
    }

    const std::string TerrainTileSet::getImageFile() const {
        return "res/terrains/terrain.png";
    }
    
    const Tile& TerrainTileSet::getTile(const state::Terrain& terrain) const {
        return this->terrain[0];
    }


}
