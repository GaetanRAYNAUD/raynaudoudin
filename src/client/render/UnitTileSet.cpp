#include "UnitTileSet.h"

namespace render {

    int UnitTileSet::getCellHeight() const {
    }

    int UnitTileSet::getCellWidth() const {
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
