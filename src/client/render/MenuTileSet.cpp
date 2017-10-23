#include "MenuTileSet.h"

namespace render {
    
    MenuTileSet::MenuTileSet() {
        
    }

    int MenuTileSet::getCellHeight() const {
        return menus.at(MenuType::MENU_LEFT).getHeight(); // A refaire 
    }
    
    int MenuTileSet::getCellWidth() const {
        return menus.at(MenuType::MENU_LEFT).getWidth(); // A refaire    
    }
    
    const std::string MenuTileSet::getImageFile() const {
        return "res/menus/menu.png";
    }
    
    const Tile& MenuTileSet::getTile(std::string menu) const {
        return menus.at(MenuType::MENU_LEFT);
    }


}
