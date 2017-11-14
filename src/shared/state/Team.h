// Generated by dia2code
#ifndef STATE__TEAM__H
#define STATE__TEAM__H


namespace state {
  class Team;
}

#include "TeamId.h"
#include "RaceTypeId.h"
#include "UnitTypeId.h"

namespace state {

  /// class Team - 
  class Team {
    // Attributes
  private:
    TeamId id;
    int gold;
    int nbHouses;
    RaceTypeId race;
    // Operations
  public:
    Team (TeamId teamId, RaceTypeId race);
    const TeamId& getId () const;
    int getGold () const;
    const RaceTypeId& getRace () const;
    void setId (TeamId id);
    bool verifyGold (UnitTypeId unitTypeId) const;
    void generateGold ();
    void addHouse ();
    void removeHouse ();
    Team* clone () const;
    // Setters and Getters
  };

};

#endif
