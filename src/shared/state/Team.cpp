#include "Team.h"

namespace state {

    Team::Team() {
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
   
    bool Team::verifyGold(int unitPrice) const{
        if(gold > unitPrice) {
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