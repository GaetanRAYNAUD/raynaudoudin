#include "UnitTileSet.h"

namespace render {
    
    UnitTileSet::UnitTileSet() {
        human.push_back(Tile(0, 0, 71, 71));
        /*A finir*/
    }

    int UnitTileSet::getCellHeight() const {
        return human[0].getHeight();
    }

    int UnitTileSet::getCellWidth() const {
        return human[0].getWidth();
    }

    const std::string UnitTileSet::getImageFile() const {
        return "res/units/unit.png";
    }

    const Tile& UnitTileSet::getTile(const state::Unit& unit) const {
        if (unit.getTeam() == 0) {
            return human[0];
        }   
        else {
            return orc[0];
        }
    }

}
