#include "TerrainTileSet.h"

using namespace state;

namespace render {

    TerrainTileSet::TerrainTileSet() {
        terrains.insert(std::make_pair(TerrainTypeId::GRASS, Tile(0, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::FOREST, Tile(72, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::WATER, Tile(144, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::HOUSE, Tile(216, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::CASTLE, Tile(288, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::WALL_LEFT, Tile(360, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::WALL_TOP, Tile(432, 0, 72, 72)));
        terrains.insert(std::make_pair(TerrainTypeId::WALL_RIGHT, Tile(504, 0, 72, 72)));
    }

    int TerrainTileSet::getCellHeight() const {
        return terrains.at(TerrainTypeId::GRASS).getHeight();
    }

    int TerrainTileSet::getCellWidth() const {
        return terrains.at(TerrainTypeId::GRASS).getWidth();
    }

    const std::string TerrainTileSet::getImageFile() const {
        return "res/terrains/terrain.png";
    }

    const Tile& TerrainTileSet::getTile(const state::Terrain& terrain) const {
        switch (terrain.getTypeId()) {
            case TerrainTypeId::GRASS:
                return terrains.at(TerrainTypeId::GRASS);
            case TerrainTypeId::FOREST:
                return terrains.at(TerrainTypeId::FOREST);
            case TerrainTypeId::WATER:
                return terrains.at(TerrainTypeId::WATER);
            case TerrainTypeId::HOUSE:
                return terrains.at(TerrainTypeId::HOUSE);
            case TerrainTypeId::CASTLE:
                return terrains.at(TerrainTypeId::CASTLE);
            case TerrainTypeId::WALL_LEFT:
                return terrains.at(TerrainTypeId::WALL_LEFT);
            case TerrainTypeId::WALL_TOP:
                return terrains.at(TerrainTypeId::WALL_TOP);
            case TerrainTypeId::WALL_RIGHT:
                return terrains.at(TerrainTypeId::WALL_RIGHT);
            default :
                return terrains.at(TerrainTypeId::GRASS);
        }
    }

}
