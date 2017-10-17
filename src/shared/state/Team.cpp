#include "Team.h"

namespace state {

    Team::Team(int id) {
        this->id = id;
    }

    int Team::getGold() const {
        return gold;
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

    int Team::getId() const {
        return id;
    }
        
    Team* Team::clone() const {
        return new Team(*this);
    }


}