#include "Unit.h"

namespace state {

    Unit::Unit() {

    }

    Unit::Unit(const Unit& unit) {

    }
    
    Unit& Unit::operator=(const Unit& unit) {

    }

    int Unit::getId() const {

    }

    int Unit::getLife() const {

    }

    int Unit::getPositionX() const {

    }

    int Unit::getPositionY() const {

    }

    int Unit::getPrice(UnitTypeId typeId) {

    }

    int Unit::getSpeed() const {

    }

    int Unit::getTeam() const {

    }

    UnitTypeId Unit::getTypeId() const {

    }

    const std::map<int, std::unique_ptr<Weapon> >& Unit::getWeapons() const {

    }

    bool Unit::isDead() const {

    }

    void Unit::setId(int id) {

    }

    void Unit::setLife(int life) {

    }

    void Unit::setPositionX(int positionX) {

    }

    void Unit::setPositionY(int positionY) {

    }

    void Unit::setSpeed(int speed) {

    }

    void Unit::setTeam(int team) {

    }

    void Unit::setTypeId(UnitTypeId typeId) {

    }

    void Unit::setWeapons(const std::map<int, std::unique_ptr<Weapon> >& weapons) {

    }

    Unit::~Unit() {

    }
    
}