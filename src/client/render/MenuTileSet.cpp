#include "MenuTileSet.h"

namespace render {
    
    MenuTileSet::MenuTileSet() {
        tile = Tile(0, 0, 1188, 576);
    }

    int MenuTileSet::getCellHeight() const {
        return tile.getHeight();
    }
    
    int MenuTileSet::getCellWidth() const {
        return tile.getWidth();
    }
    
    const std::string MenuTileSet::getImageFile() const {
        return "res/menu.png";
    }
    
    const Tile& MenuTileSet::getTile() const {
        return tile;
    }
    
}
