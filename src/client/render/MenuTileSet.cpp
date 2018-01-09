#include "MenuTileSet.h"

namespace render {
    
    MenuTileSet::MenuTileSet() {
        tile.setX(0);
        tile.setY(0);
        tile.setWidth(1188);
        tile.setHeight(576);
    }

    int MenuTileSet::getCellHeight() const {
        return 1188;
    }
    
    int MenuTileSet::getCellWidth() const {
        return 576;
    }
    
    const std::string MenuTileSet::getImageFile() const {
        return "res/menu.png";
    }
    
    const Tile& MenuTileSet::getTile() const {
        return tile;
    }        
    
}
