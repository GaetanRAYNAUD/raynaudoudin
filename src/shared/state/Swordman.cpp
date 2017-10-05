#include "Swordman.h"
#include "Sword.h"

namespace state {

    Swordman::Swordman(int id, int team, int positionX, int positionY) {
        this->id = id;
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        
        life = 60;
        typeId = UnitTypeId::SWORDMAN;
        
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(WeaponTypeId::SWORD, 20))));
    }

    Unit* Swordman::clone() const {
        return new Swordman(*this);
    }

}