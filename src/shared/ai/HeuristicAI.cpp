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

    void HeuristicAI::initPathMaps(const state::Board& board) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = board.getUnits();
        const std::map<int, std::unique_ptr<state::Terrain> >& terrains = board.getTerrains();

        unitTeam1PathMap.init(board);
        unitTeam2PathMap.init(board);
        houseTeam1PathMap.init(board);
        houseTeam2PathMap.init(board);
        
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
    
    void HeuristicAI::run(engine::Engine& engine) {
//        std::vector<engine::Command*> commands = listCommands(engine.getState());
//
//        initPathMaps(engine.getState().getBoard());
//        
//        if(commands.size() > 0) {
//            std::uniform_int_distribution<int> dis(0, commands.size() - 1);
//            int rand = dis(randgen);
//            engine.addCommand(1, commands.at(rand));
//            engine.update();
//        } else {
//            engine.addCommand(1, new engine::EndTurnCommand());
//            engine.update();
//        }
//        
//        engine.addCommand(2, new engine::HandleWinCommand());
//        engine.update();
//        
//        commands.clear();
//        
    }
   
}
