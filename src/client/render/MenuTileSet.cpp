#include "MenuTileSet.h"

namespace render {
    
    MenuTileSet::MenuTileSet() {
        
    }

    int MenuTileSet::getCellHeight() const {
        return menu[0].getHeight();
    }
    
    int MenuTileSet::getCellWidth() const {
        return menu[0].getWidth();        
    }
    
    const std::string MenuTileSet::getImageFile() const {
        return "res/menus/menu.png";
    }
    
    const Tile& MenuTileSet::getTile(char menu) const {
        return this->menu[0];
    }


}
