#include "MenuTileSet.h"

namespace render {
    
    MenuTileSet::MenuTileSet() {
        menus.insert(std::make_pair(MenuTypeId::MENU_TOP, Tile(0, 0, 833, 36)));
        menus.insert(std::make_pair(MenuTypeId::MENU_LEFT, Tile(0, 37, 58, 736)));
    }

    int MenuTileSet::getCellHeight() const {
        return menus.at(MenuTypeId::MENU_TOP).getHeight(); // A refaire 
    }
    
    int MenuTileSet::getCellWidth() const {
        return menus.at(MenuTypeId::MENU_TOP).getWidth(); // A refaire    
    }
    
    const std::string MenuTileSet::getImageFile() const {
        return "res/menus/menu.png";
    }
    
    const Tile& MenuTileSet::getTile(MenuTypeId menu) const {
        switch (menu) {
            case MenuTypeId::MENU_TOP:
                return menus.at(MenuTypeId::MENU_TOP);
            case MenuTypeId::MENU_LEFT:
                return menus.at(MenuTypeId::MENU_LEFT);
            default:
                return menus.at(MenuTypeId::MENU_TOP);
        }
    }

}
