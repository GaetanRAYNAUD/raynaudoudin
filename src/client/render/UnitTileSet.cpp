#include "UnitTileSet.h"

using namespace state;

namespace render {
    
    UnitTileSet::UnitTileSet() {
        humans.insert(std::make_pair(UnitTypeId::LEADER, Tile(0, 0, 72, 72)));
        humans.insert(std::make_pair(UnitTypeId::SWORDMAN, Tile(0, 360, 72, 72)));
        humans.insert(std::make_pair(UnitTypeId::BOWMAN, Tile(0, 648, 72, 72)));
        orcs.insert(std::make_pair(UnitTypeId::LEADER, Tile(0, 1008, 72, 72)));
        orcs.insert(std::make_pair(UnitTypeId::SWORDMAN, Tile(0, 1368, 72, 72)));
        orcs.insert(std::make_pair(UnitTypeId::BOWMAN, Tile(0, 1656, 72, 72)));
    }

    int UnitTileSet::getCellHeight() const {
        return humans.at(UnitTypeId::LEADER).getHeight();
    }

    int UnitTileSet::getCellWidth() const {
        return humans.at(UnitTypeId::LEADER).getWidth();
    }

    const std::string UnitTileSet::getImageFile() const {
        return "res/units/unit.png";
    }
    
    const Tile& UnitTileSet::getTile(const state::Unit& unit) const {
        switch (unit.getRace()) {
            case RaceTypeId::HUMAN :
                switch (unit.getTypeId()) {
                    case UnitTypeId::LEADER :
                        return humans.at(UnitTypeId::LEADER);
                    case UnitTypeId::SWORDMAN :
                        return humans.at(UnitTypeId::SWORDMAN);
                    case UnitTypeId::BOWMAN :
                        return humans.at(UnitTypeId::BOWMAN);
                    default :
                        return humans.at(UnitTypeId::SWORDMAN);
                }              
            case RaceTypeId::ORC :
                switch (unit.getTypeId()) {
                    case UnitTypeId::LEADER :
                        return orcs.at(UnitTypeId::LEADER);
                    case UnitTypeId::SWORDMAN :
                        return orcs.at(UnitTypeId::SWORDMAN);
                    case UnitTypeId::BOWMAN :
                        return orcs.at(UnitTypeId::BOWMAN);
                    default :
                        return orcs.at(UnitTypeId::SWORDMAN);
                }               
            default :
                return humans.at(UnitTypeId::SWORDMAN);
        }

    }

}
