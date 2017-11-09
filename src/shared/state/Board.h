// Generated by dia2code
#ifndef STATE__BOARD__H
#define STATE__BOARD__H

#include <map>
#include <memory>
#include <vector>
#include <string>

namespace state {
  class Board;
  class Unit;
  class Team;
  class Terrain;
  class Observable;
}

#include "UnitTypeId.h"
#include "RaceTypeId.h"
#include "Observable.h"
#include "Unit.h"
#include "Team.h"
#include "Terrain.h"

namespace state {

  /// class Board - 
  class Board : public state::Observable {
    // Associations
    // Attributes
  private:
    /// 	
    int width;
    int height;
    std::map<int, std::unique_ptr<Team>> teams;
    std::map<int, std::unique_ptr<Terrain>> terrains;
    std::map<int, std::unique_ptr<Unit>> units;
    // Operations
  public:
    Board (int width = 10, int height = 10);
    Board (const Board& other);
    Board& operator= (const Board& other);
    ~Board ();
    void addUnit (Unit* unit);
    void addUnit (UnitTypeId unit, RaceTypeId race);
    /// 	
    /// @param team		(???) 
    void addTeam (Team* team);
    /// 		
    /// @param terrain		(???) 
    void addTerrain (Terrain* terrain);
    void deleteUnit (int id);
    bool isUnitAround (int idAttacker, int idDefender);
    Unit* findUnit (int id) const;
    Team* findTeam (int id) const;
    /// 		
    /// @param id		(???) 
    Terrain* findTerrain (int id) const;
    std::vector<int> findUnitAround (int id);
    Unit* findUnitOnPosition (int positionX, int positionY) const;
    Terrain* findTerrainOnPosition (int positionX, int positionY) const;
    int getHeight () const;
    int getWidth () const;
    const std::map<int, std::unique_ptr<Team> >& getTeams () const;
    const std::map<int, std::unique_ptr<Terrain> >& getTerrains () const;
    const std::map<int, std::unique_ptr<Unit> >& getUnits () const;
    void loadTerrainsFromFile (std::string path);
    // Setters and Getters
  };

};

#endif
