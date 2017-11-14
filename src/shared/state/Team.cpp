#include "Team.h"

namespace state {

    Team::Team(TeamId id, RaceTypeId race): id(id), race(race) {
        gold = 50;
        nbHouses = 0;
    }

    int Team::getGold() const {
        return gold;
    }

    const TeamId& Team::getId() const {
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
        gold = gold + nbHouses * 2 + 5;
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

    void Team::setId(TeamId id) {
        this->id = id;
    }


}