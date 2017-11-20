#include "HeuristicAI.h"

namespace ai {
    
    HeuristicAI::HeuristicAI(int randomSeed): randgen(randomSeed) {

    }
    
    const PathMap& HeuristicAI::getTeam1_PathMap() const {
        return Team1_PathMap;
    }
    
    const PathMap& HeuristicAI::getTeam2_PathMap() const {
        return Team2_PathMap;
    }
    
    void HeuristicAI::run(engine::Engine& engine) {

    }
   
}
