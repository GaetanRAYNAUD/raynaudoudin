#include "DeepAI.h"

namespace ai {

    DeepAI::DeepAI(const state::State& state) {
        
    }

    int DeepAI::alphabeta(engine::Engine& engine, state::Direction& direction, int depth) {
//        int val;
//        
//        if (depth % 2 == 0) { /*Noeud min*/
//            val = std::numeric_limits<int>::max();
//            
//            for (tous les fils de engine)
//        } else {
//            
//        }
        return -1;
    }
    
    int DeepAI::getHeuristic(const state::State& state) {
        const std::map<int, std::unique_ptr<state::Unit> >& units = state.getBoard().getUnits();
        int heuristic = 0;
        
        for (auto& u : units) {
            heuristic = heuristic + u.second->getLife();
        }
        
        return heuristic;
    }

    void DeepAI::run(engine::Engine& engine) {

    }

}

