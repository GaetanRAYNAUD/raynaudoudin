#include "Team.h"

#include <iostream>
namespace state {

    const std::map<UnitTypeId, int> Team::unitsPrices = {
        { UnitTypeId::BOWMAN, 10 },
        { UnitTypeId::SWORDMAN, 15},
        { UnitTypeId::LEADER, -1},
        { UnitTypeId::INVALIDUNIT, -2}
    };
    
    Team::Team(TeamId id, RaceTypeId race): id(id), race(race) {
        gold = 50;
        nbHouses = 0;
    }

    int Team::getGold() const {
        return gold;
    }

    TeamId Team::getId() const {
        return id;
    }

    RaceTypeId Team::getRace() const {
        return race;
    }
    
    int Team::getNbHouses() const {
        return nbHouses;
    }

    void Team::setGold(int gold) {
        this->gold = gold;
    }

    void Team::setId(TeamId id) {
        this->id = id;
    }
    
   
    bool Team::verifyGold(UnitTypeId unitTypeId) const {
        if(gold >= unitsPrices.at(unitTypeId)) {
            return true;
        } else {
            return false;
        }
    }

    void Team::withdrawGold(UnitTypeId unitTypeId) {
        gold = gold - unitsPrices.at(unitTypeId);
    }


    void Team::generateGold() {
        gold = gold + nbHouses * 5;
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
    
    bool Team::equals(const Team& other) const {
        if(race != other.race) {
            return false;
        }
                
        if(gold != other.gold) {
            std::cout << "gold different" << std::endl;
            return false;
        }
        
        if(nbHouses != other.nbHouses) {
            std::cout << "nbhouse different" << std::endl;            
            return false;
        }
        
        return true;
    }

}