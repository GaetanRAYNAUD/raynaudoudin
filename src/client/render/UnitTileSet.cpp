#include "UnitTileSet.h"

namespace render {
    
    UnitTileSet::UnitTileSet() {
        /*A finir*/
    }

    int UnitTileSet::getCellHeight() const {
        return humans.at(UnitType::HUMANLEADER).getHeight();
    }

    int UnitTileSet::getCellWidth() const {
        return humans.at(UnitType::HUMANLEADER).getWidth();
    }

    const std::string UnitTileSet::getImageFile() const {
        return "res/units/unit.png";
    }
    
    const Tile& UnitTileSet::getTile(const state::Unit& unit) const {
        return humans.at(UnitType::HUMANLEADER);
    }

}
