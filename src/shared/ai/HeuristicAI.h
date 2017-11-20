// Generated by dia2code
#ifndef AI__HEURISTICAI__H
#define AI__HEURISTICAI__H

#include <random>

namespace ai {
  class PathMap;
};
namespace engine {
  class Engine;
};
namespace ai {
  class AI;
}

#include "PathMap.h"
#include "AI.h"

namespace ai {

  /// class HeuristicAI - 
  class HeuristicAI : public ai::AI {
    // Associations
    // Attributes
  private:
    std::mt19937 randgen;
    PathMap Team1_PathMap;
    PathMap Team2_PathMap;
    // Operations
  public:
    HeuristicAI (int randomSeed);
    const PathMap& getTeam1_PathMap () const;
    const PathMap& getTeam2_PathMap () const;
    void run (engine::Engine& engine);
    // Setters and Getters
  };

};

#endif
