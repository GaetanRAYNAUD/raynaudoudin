#include "DebugLayer.h"

namespace render {

    DebugLayer::DebugLayer(const state::State& state) : state(state) {
        
    }
    
    void DebugLayer::initSurface() {

    }

    void DebugLayer::printPathMap(const std::vector<int>& weights) {
        int posX, posY;
        
        for(int i = 0;i < (int)weights.size();i++) {
            posX = (i % state.getBoard().getWidth()) * 72 - (i % state.getBoard().getWidth()) * 72 / 4;
            if ((i % state.getBoard().getWidth()) % 2) {
                posY = i / state.getBoard().getWidth() * 72;
            } else {
                posY = i / state.getBoard().getWidth() * 72 + 72 / 2;
            }
            surface->addText(posX + 32, posY + 32, std::to_string(weights.at(i)), sf::Color::White);
        }
    }


}

