#include "HeuristicAI.h"
#include "state/House.h"

namespace ai {
    
    HeuristicAI::HeuristicAI(int randomSeed): randgen(randomSeed) {

    }

    const PathMap& HeuristicAI::getHouseTeam1PathMap() const {
        return houseTeam1PathMap;
    }

    const PathMap& HeuristicAI::getHouseTeam2PathMap() const {
        return houseTeam2PathMap;
    }

    const PathMap& HeuristicAI::getUnitTeam1PathMap() const {
        return unitTeam1PathMap;
    }

    const PathMap& HeuristicAI::getUnitTeam2PathMap() const {
        return unitTeam2PathMap;
    }
    
    void HeuristicAI::run(engine::Engine& engine) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = engine.getState().getBoard().getUnits();
        const std::map<int, std::unique_ptr<state::Terrain> >& terrains = engine.getState().getBoard().getTerrains();

        unitTeam1PathMap.init(engine.getState().getBoard());
        unitTeam2PathMap.init(engine.getState().getBoard());
        houseTeam1PathMap.init(engine.getState().getBoard());
        houseTeam2PathMap.init(engine.getState().getBoard());
        
        for (auto& u : units) {
            if (u.second->getTeam() == state::TeamId::TEAM_1) {
                unitTeam1PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY(), 0));
            } else if (u.second->getTeam() == state::TeamId::TEAM_2) {
                unitTeam2PathMap.addWell(Point(u.second->getPositionX(), u.second->getPositionY(), 0));
            }
        }
        
        for (auto& t : terrains) {
            if (t.second->getTypeId() == state::TerrainTypeId::HOUSE) {
                switch (((state::House*)t.second.get())->getTeamId()) {
                    case state::TeamId::TEAM_1:
                        houseTeam1PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                        break;
                    
                    case state::TeamId::TEAM_2:
                        houseTeam2PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                        break;
                        
                    case state::TeamId::INVALIDTEAM:
                        houseTeam1PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                        houseTeam2PathMap.addWell(Point(t.second->getPositionX(), t.second->getPositionY(), 0));
                }
            }
        }        
    }
   
}
