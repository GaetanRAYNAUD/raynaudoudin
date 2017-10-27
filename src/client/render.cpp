#include "render.hpp"

using namespace state;

namespace render {
    
    void renderTest() {
        int windowWidth = 1152;
            int windowHeight = 576;
            sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
            
            State* state = new State();
            state->getBoard().loadTerrainsFromFile("res/map.txt");
            
            Unit* unit = new Leader(0, 1, 3, 2, RaceTypeId::HUMAN);
            state->getBoard().addUnit(unit);
        
            unit = new Leader(1, 2, 18, 6, RaceTypeId::ORC);
            state->getBoard().addUnit(unit);
            

            TerrainLayer* terrainLayer = new TerrainLayer(state->getBoard());
            terrainLayer->initSurface();
            
            UnitLayer* unitLayer = new UnitLayer(state->getBoard());
            unitLayer->initSurface();
            
            StateLayer* stateLayer = new StateLayer(*state);
            stateLayer->initSurface();

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if(event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                window.draw(*(terrainLayer->getSurface()));
                window.draw(*(unitLayer->getSurface()));
                window.draw(*(stateLayer->getSurface()));
                window.display();
            }
    }
}
