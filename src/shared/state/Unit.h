// Generated by dia2code
#ifndef STATE__UNIT__H
#define STATE__UNIT__H

#include <map>
#include <memory>

namespace state {
  class Unit;
  class Weapon;
}

#include "UnitTypeId.h"
#include "RaceTypeId.h"
#include "Weapon.h"

namespace state {

  /// class Unit - 
  class Unit {
    // Associations
    // Attributes
  protected:
    int id     = 0;
    int life     = 50;
    int speed     = 5;
    int positionX;
    int positionY;
    int team;
    std::map<int, std::unique_ptr<Weapon>> weapons;
    UnitTypeId typeId     = UnitTypeId::INVALIDUNIT;
    RaceTypeId race     = RaceTypeId::HUMAN;
    // Operations
  public:
    Unit ();
    Unit (const Unit& other);
    Unit& operator= (const Unit& other);
    virtual ~Unit ();
    void takeDamage (int damage);
    bool isDead () const;
    int getPositionX () const;
    int getPositionY () const;
    int getLife () const;
    int getSpeed () const;
    const UnitTypeId& getTypeId () const;
    int getId () const;
    int getTeam () const;
    const RaceTypeId& getRace () const;
    void setSpeed (int speed);
    virtual Unit* clone () const = 0;
    // Setters and Getters
    void setId(int id);
    void setLife(int life);
    void setPositionX(int positionX);
    void setPositionY(int positionY);
    void setTeam(int team);
    const std::map<int, std::unique_ptr<Weapon>>& getWeapons() const;
    void setWeapons(const std::map<int, std::unique_ptr<Weapon>>& weapons);
    void setTypeId(UnitTypeId typeId);
    void setRace(RaceTypeId race);
  };

};

#endif
