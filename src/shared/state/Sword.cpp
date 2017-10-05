#include "Sword.h"

namespace state {

    Sword::Sword(int damage) {
        this->damage = damage;
    }

    Sword::~Sword() {
        
    }
    
    const bool Sword::isCloseCombat() {
        return true;
    }
}