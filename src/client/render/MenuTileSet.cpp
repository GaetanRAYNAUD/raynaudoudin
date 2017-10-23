#include "MenuTileSet.h"

namespace render {
    
    MenuTileSet::MenuTileSet() {
        menus.insert(std::make_pair(MenuType::MENU_TOP, Tile(0, 0, 833, 36)));
        menus.insert(std::make_pair(MenuType::MENU_LEFT, Tile(0, 37, 58, 736)));
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
