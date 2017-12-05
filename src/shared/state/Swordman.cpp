#include "Swordman.h"
#include "Sword.h"

namespace state {

    Swordman::Swordman(TeamId team, int positionX, int positionY, RaceTypeId race) {
        this->id = id;
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        this->race = race;
        
        life = 60;
        typeId = UnitTypeId::SWORDMAN;
        
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(WeaponTypeId::SWORD, 20))));
    }

    Unit* Swordman::clone() const {
        return new Swordman(*this);
    }
    
    bool Swordman::equals(const Unit& other) const {
        Swordman& otherCompare = (Swordman&)other;
        
        if(typeId != otherCompare.typeId) {
            return false;
        }
        
        if(team != otherCompare.team) {
            return false;
        }
        
        if(race != otherCompare.race) {
            return false;
        }
        
        if(life != otherCompare.life) {
            return false;
        }
        
        if(positionX != otherCompare.positionX) {
            return false;
        }
        
        if(positionY != otherCompare.positionY) {
            return false;
        }
        
        if(speed != otherCompare.speed) {
            return false;
        }
        
        if(weapons.size() != otherCompare.weapons.size()) {
            return false;
        }
        
        if(weapons.at(WeaponTypeId::SWORD)->equals(*otherCompare.weapons.at(WeaponTypeId::SWORD)->clone()) == false) {           
            return false;
        }
        
        return true;
    }      

}