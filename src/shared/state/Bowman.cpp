#include "Bowman.h"
#include "Bow.h"
#include "Sword.h"

namespace state {

    Bowman::Bowman(TeamId team, int positionX, int positionY, RaceTypeId race) {
        this->id = id;
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        this->race = race;
        
        life = 40;
        typeId = UnitTypeId::BOWMAN;

        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(WeaponTypeId::SWORD, 5))));
        weapons.insert(std::make_pair(WeaponTypeId::BOW, std::unique_ptr<Bow>(new Bow(WeaponTypeId::BOW, 15))));
    }
    
    Unit* Bowman::clone() const {
         return new Bowman(*this);
    }
    
    bool Bowman::equals(const Unit& other) const {
        Bowman& otherCompare = (Bowman&)other;
        
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
        
        if(weapons.at(WeaponTypeId::BOW)->equals(*otherCompare.weapons.at(WeaponTypeId::BOW)->clone()) == false) {         
            return false;
        }        
        
        return true;
    }      
}