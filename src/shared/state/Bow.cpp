#include "Bow.h"

namespace state {
    
    Bow::Bow(int damage) {
        this->damage = damage;
    }

    Bow::~Bow() {

    }
    
    const bool Bow::isCloseCombat() {
        return false;
    }
}