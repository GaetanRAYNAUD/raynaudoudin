#include "render.hpp"

using namespace state;

namespace render {
    
    void renderTest() {
        int windowWidth = 1188;
        int windowHeight = 576;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        window.setFramerateLimit(30);
            
        State* state = new State(22, 8);
        state->getBoard().loadTerrainsFromFile("res/map.txt");
        
        Scene* scene = new Scene(*state);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                } else if(event.type == sf::Event::MouseButtonReleased) {
                    
                } else if(event.type == sf::Event::MouseButtonPressed) {
                    
                }
            }
            
            scene->draw(window);
            window.display();
        }
    }
}
