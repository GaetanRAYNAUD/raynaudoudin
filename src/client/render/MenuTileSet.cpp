#include "MenuTileSet.h"

namespace render {

    int MenuTileSet::getCellHeight() const {

    }
    int MenuTileSet::getCellWidth() const {

    }
    const std::string MenuTileSet::getImageFile() const {
        return "res/menus/menu.png";
    }
    
    const Tile& MenuTileSet::getTile(char menu) const {
        return this->menu[0];
    }


}
