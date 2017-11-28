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
        
        unitTeam1PathMap.update(board);
        unitTeam2PathMap.update(board);
        houseTeam1PathMap.update(board);
        houseTeam2PathMap.update(board);
    }
    
    void HeuristicAI::run(engine::Engine& engine) {
//        const std::map<int, std::unique_ptr<state::Unit> >& units = engine.getState().getBoard().getUnits();
//        std::vector<engine::Command*> commands;
//
//        initPathMaps(engine.getState().getBoard());
//        commands = listCommands(engine.getState());
//        
//        switch (engine.getState().getCurrentTeam()) {
//            case state::TeamId::TEAM_1:
//                break;
//            case state::TeamId::TEAM_2:
//                break;
//        }
//        for (auto& u : units) {
//            if (u.second->getTeam() == state::TeamId::TEAM_1) {
//                unitTeam2PathMap.getWeight(Point(u.second->getPositionX() - 1, u.second->getPositionY()))
//
//                engine.addCommand(1, commands.at(rand));
//                engine.update();
//            }
//        }
//            
//        engine.addCommand(1, new engine::EndTurnCommand());        
//        engine.addCommand(2, new engine::HandleWinCommand());
//        engine.update();
//        
//        commands.clear();      
    }

}
