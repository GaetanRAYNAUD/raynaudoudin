#include "Swordman.h"
#include "Sword.h"

namespace state {

    Swordman::Swordman(int team, int positionX, int positionY) {
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        
        id = 0;
        life = 60;
        typeId = UnitTypeId::SWORDMAN;
        
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(20))));
    }
}