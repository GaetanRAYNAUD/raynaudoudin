#include "Bow.h"

namespace state {
    
    Bow::Bow(int id, int damage) {
        this->id = id;
        this->damage = damage;
    }

    Bow::~Bow() {

    }
    
    const bool Bow::isCloseCombat() {
        return false;
    }
    
    Weapon* Bow::clone() const {
        return new Bow(*this);
    }

    
}