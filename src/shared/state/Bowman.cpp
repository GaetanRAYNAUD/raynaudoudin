#include "Bowman.h"
#include "Bow.h"

namespace state {

    Bowman::Bowman(int team, int positionX, int positionY) {
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        
        id = 0;
        life = 40;
        typeId = UnitTypeId::BOWMAN;
        
        weapons.insert(std::make_pair(0, std::unique_ptr<Bow>(new Bow(10))));

    }

    Unit* Bowman::clone() const {

    }
    
}