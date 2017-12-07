#include "Leader.h"
#include "Sword.h"
#include "Bow.h"

namespace state {

    Leader::Leader(TeamId team, int positionX, int positionY, RaceTypeId race) {
        this->id = id;
        this->team = team;
        this->positionX = positionX;
        this->positionY = positionY;
        this->race = race;
        
        life = 100;
        typeId = UnitTypeId::LEADER;
        
        weapons.insert(std::make_pair(WeaponTypeId::SWORD, std::unique_ptr<Sword>(new Sword(WeaponTypeId::SWORD, 20))));
        weapons.insert(std::make_pair(WeaponTypeId::BOW, std::unique_ptr<Bow>(new Bow(WeaponTypeId::BOW, 10))));
    }    

    Unit* Leader::clone() const {
        return new Leader(*this);
    }
    
    bool Leader::equals(const Unit& other) const {
        Leader& otherCompare = (Leader&)other;
        
        
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