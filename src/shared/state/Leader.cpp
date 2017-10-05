#include "Leader.h"
#include "Sword.h"
#include "Bow.h"

namespace state {

    Leader::Leader(int team, int positionX, int positionY) {
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        
        id = 0;
        life = 100;
        typeId = UnitTypeId::LEADER;
        
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(20))));
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(10))));
    }    

    Unit* Leader::clone() const {
        return new Leader(*this);
    }
}