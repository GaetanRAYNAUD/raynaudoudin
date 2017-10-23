#include "UnitTileSet.h"

namespace render {
    
    UnitTileSet::UnitTileSet() {
        humans.insert(std::make_pair(UnitType::HUMANLEADER, Tile(0, 0, 72, 72)));
        humans.insert(std::make_pair(UnitType::HUMANSWORDMAN, Tile(0, 360, 72, 72)));
        humans.insert(std::make_pair(UnitType::HUMANBOWMAN, Tile(0, 648, 72, 72)));
        orcs.insert(std::make_pair(UnitType::ORCLEADER, Tile(0, 1008, 72, 72)));
        orcs.insert(std::make_pair(UnitType::ORCSWORDMAN, Tile(0, 1368, 72, 72)));
        orcs.insert(std::make_pair(UnitType::ORCBOWMAN, Tile(0, 1656, 72, 72)));
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
