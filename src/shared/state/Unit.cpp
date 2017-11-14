#include "Unit.h"

namespace state {
    
    Unit::Unit() {

    }

    Unit::Unit(const Unit& unit) {
        id = unit.id;
        life = unit.life;
        speed = unit.speed;
        positionX = unit.positionX;
        positionY = unit.positionY;
        team = unit.team;
        typeId = unit.typeId;    
        race = unit.race;
        
        for(auto& w : unit.weapons) {
            weapons.insert(std::make_pair(w.first, std::unique_ptr<Weapon>(w.second->clone())));
        }
    }
    
    Unit& Unit::operator=(const Unit& unit) {
        weapons.clear();
        
        id = unit.id;
        life = unit.life;
        speed = unit.speed;
        positionX = unit.positionX;
        positionY = unit.positionY;
        team = unit.team;
        typeId = unit.typeId;
        race = unit.race;
        
        for(auto& w : unit.weapons) {
            weapons.insert(std::make_pair(w.first, std::unique_ptr<Weapon>(w.second->clone())));
        }
        
        return *this;
    }

    int Unit::getId() const {
        return id;
    }

    int Unit::getLife() const {
        return life;
    }

    int Unit::getPositionX() const {
        return positionX;
    }

    int Unit::getPositionY() const {
        return positionY;
    }

    int Unit::getSpeed() const {
        return speed;
    }

    const TeamId& Unit::getTeam() const {
        return team;
    }

    const UnitTypeId& Unit::getTypeId() const {
        return typeId;
    }

    const std::map<int, std::unique_ptr<Weapon> >& Unit::getWeapons() const {
        return weapons;
    }
    
    void Unit::takeDamage(int damage) {
        life = life - damage;
    }

    bool Unit::isDead() const {
        if (life <= 0) {
            return true;
        }
        else {
            return false;
        }
    }

    void Unit::setId(int id) {
        this->id = id;
    }

    void Unit::setLife(int life) {
        this->life = life;
    }

    void Unit::setPositionX(int positionX) {
        this->positionX = positionX;
    }

    void Unit::setPositionY(int positionY) {
        this->positionY = positionY;
    }

    void Unit::setSpeed(int speed) {
        this->speed = speed;
    }

    void Unit::setTeam(TeamId team) {
        this->team = team;
    }

    void Unit::setTypeId(UnitTypeId typeId) {
        this->typeId = typeId;
    }

    void Unit::setWeapons(const std::map<int, std::unique_ptr<Weapon> >& weapons) {
        
    }
    
    const RaceTypeId& Unit::getRace() const {
        return race;
    }

    void Unit::setRace(RaceTypeId race) {
        this->race = race;
    }

    Unit::~Unit() {
        weapons.clear();
    }
    
}