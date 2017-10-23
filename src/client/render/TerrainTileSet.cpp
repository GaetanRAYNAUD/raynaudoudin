#include "TerrainTileSet.h"

namespace render {

    TerrainTileSet::TerrainTileSet() {
        terrains.insert(std::make_pair(TerrainType::GRASS, Tile(0, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::FOREST, Tile(72, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::WATER, Tile(144, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::HOUSE, Tile(216, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::CASTLE, Tile(288, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::WALL_LEFT, Tile(360, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::WALL_TOP, Tile(432, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainType::WALL_RIGHT, Tile(504, 0, 72, 72)));
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
