#include "render.hpp"

using namespace state;

namespace render {
    
    void renderTest() {
        int windowWidth = 1152;
        int windowHeight = 576;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        window.setFramerateLimit(30);
            
        State* state = new State();
        state->getBoard().loadTerrainsFromFile("res/map.txt");
            
        Unit* unit = new Leader(0, 1, 3, 2, RaceTypeId::HUMAN);
        state->getBoard().addUnit(unit);
        
        unit = new Leader(1, 2, 18, 6, RaceTypeId::ORC);
        state->getBoard().addUnit(unit);
        
        Scene* scene = new Scene(*state);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    window.close();
            }
            
            //scene->stateChanged(event);
            scene->draw(window);
            window.display();
        }
    }
}
