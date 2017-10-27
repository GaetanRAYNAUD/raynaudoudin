#include "TileSet.h"

namespace render {

    const Tile& TileSet::getTile(MenuTypeId menu) const {
        return *new Tile();
    }

    const Tile& TileSet::getTile(const state::Terrain& terrain) const {
        return *new Tile();
    }

    const Tile& TileSet::getTile(const state::Unit& unit) const {
        return *new Tile();        
    }
    
    TileSet::~TileSet() {

    }
    
}