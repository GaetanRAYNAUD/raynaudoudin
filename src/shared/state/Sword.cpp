#include "Sword.h"

namespace state {

    Sword::Sword(int id, int damage) {
        this->id = id;
        this->damage = damage;
        
        typeId = WeaponTypeId::SWORD;
    }

    Sword::~Sword() {
        
    }
    
    const bool Sword::isCloseCombat() {
        return true;
    }
      
    Weapon* Sword::clone() const {
        return new Sword(*this);
    }

}