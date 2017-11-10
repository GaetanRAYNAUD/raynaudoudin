#include "Team.h"

namespace state {

    Team::Team() {
        gold = 50;
    }

    int Team::getGold() const {
        return gold;
    }

    int Team::getId() const {
        return id;
    }

    const RaceTypeId& Team::getRace() const {
        return race;
    }
   
    bool Team::verifyGold(UnitTypeId unitTypeId) const{
        int price;
        
        switch (unitTypeId) {
            case UnitTypeId::BOWMAN:
                price = 10;
                break;
            case UnitTypeId::SWORDMAN:
                price = 15;
                break;
            case UnitTypeId::LEADER:
                price = -1;
                break;
            default:
                price = -2;
        }
        
        if(gold >= price) {
            return true;
        } else {
            return false;
        }
    }

    void Team::generateGold() {
        gold += nbHouses * 2;
    }

    void Team::addHouse() {
        nbHouses++;
    }

    void Team::removeHouse() {
        nbHouses--;
    }
        
    Team* Team::clone() const {
        return new Team(*this);
    }

    void Team::setId(int id) {
        this->id = id;
    }


}