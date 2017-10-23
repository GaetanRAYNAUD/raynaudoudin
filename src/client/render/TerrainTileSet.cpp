#include "TerrainTileSet.h"

namespace render {

    TerrainTileSet::TerrainTileSet() {
        
    }

    int TerrainTileSet::getCellHeight() const {
        return terrains.at(TerrainType::GRASS).getHeight();
    }

    int TerrainTileSet::getCellWidth() const {
        return terrains.at(TerrainType::GRASS).getWidth();
    }

    const std::string TerrainTileSet::getImageFile() const {
        return "res/terrains/terrain.png";
    }

    const Tile& TerrainTileSet::getTile(const state::Terrain& terrain) const {
        return this->terrains.at(TerrainType::GRASS);
    }

}
