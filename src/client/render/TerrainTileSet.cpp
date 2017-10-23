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
            case TerrainTypeId::GRASS :  //Grass
                return this->terrains.at(TerrainTypeId::GRASS);
            case TerrainTypeId::FOREST :  //Forest
                break;
            case TerrainTypeId::WATER :  //Water
                break;
            case TerrainTypeId::HOUSE :  //House
                break;
            case TerrainTypeId::CASTLE :  //Castle
                break;
            case TerrainTypeId::WALL_LEFT :  //Wall left
                break;
            case TerrainTypeId::WALL_TOP :  //Wall top
                break;
            case TerrainTypeId::WALL_RIGHT :  //Wall right
                break;
            default :
                return this->terrains.at(TerrainTypeId::GRASS);
        }
        
        return this->terrains.at(TerrainTypeId::GRASS);
    }

}
