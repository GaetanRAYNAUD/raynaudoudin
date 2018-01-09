#include "StateTileSet.h"

namespace render {
    
    StateTileSet::StateTileSet() {
        menus.insert(std::make_pair(MenuTypeId::MENU_TOP, Tile(0, 0, 833, 36)));
        menus.insert(std::make_pair(MenuTypeId::MENU_LEFT, Tile(0, 37, 58, 736)));
        menus.insert(std::make_pair(MenuTypeId::MENU_GOLD, Tile(59, 37, 16, 16)));
        menus.insert(std::make_pair(MenuTypeId::MENU_HOUSE, Tile(59, 52, 16, 16)));
        menus.insert(std::make_pair(MenuTypeId::MENU_TEAM_1, Tile(59, 68, 27, 18)));
        menus.insert(std::make_pair(MenuTypeId::MENU_TEAM_2, Tile(61, 87, 21, 16)));
    }

    int StateTileSet::getCellHeight() const {
        return menus.at(MenuTypeId::MENU_TOP).getHeight();// A refaire 
    }
    
    int StateTileSet::getCellWidth() const {
        return menus.at(MenuTypeId::MENU_TOP).getWidth();// A refaire    
    }
    
    const std::string StateTileSet::getImageFile() const {
        return "res/menus/menu.png";
    }
    
    const Tile& StateTileSet::getTile(MenuTypeId menu) const {
        return menus.at(menu);
    }

}
