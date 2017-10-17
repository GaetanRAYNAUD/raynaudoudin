#include "Weapon.h"

namespace state {

    Weapon::Weapon() {
        
    }
    
    Weapon::~Weapon() {

    }

    const int& Weapon::getDamage() const {
        return damage;
    }

    const int& Weapon::getId() const {
        return id;
    }

    const WeaponTypeId& Weapon::getTypeId() const {
        return typeId;
    }

    void Weapon::setDamage(int damage) {
        this->damage = damage;
    }

    void Weapon::setId(int id) {
        this->id = id;
    }

    void Weapon::setTypeId(WeaponTypeId typeId) {
        this->typeId = typeId;
    }

    const bool Weapon::isCloseCombat() {
        return false;
    }

}