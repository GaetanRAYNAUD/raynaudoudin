#include "Bowman.h"
#include "Bow.h"
#include "Sword.h"

namespace state {

    Bowman::Bowman(int team, int positionX, int positionY) {
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        
        id = 0;
        life = 40;
        typeId = UnitTypeId::BOWMAN;
        
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(5))));
        weapons.insert(std::make_pair(WeaponTypeId::BOW, std::unique_ptr<Bow>(new Bow(10))));
    } 
}