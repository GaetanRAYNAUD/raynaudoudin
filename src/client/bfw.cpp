#include "bfw.hpp"

using namespace render;
using namespace engine;

namespace bfw {
    
    void run() {
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        Engine engine(mapWidth, mapHeight);  
        Scene scene(engine.getState());
        sf::Vector2i startMousePos, endMousePos;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
        
        window.setFramerateLimit(60);
        window.setView(view);
        
        scene.setMenu(true);
        
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    endMousePos = sf::Mouse::getPosition();
                    
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    startMousePos = sf::Mouse::getPosition(window);
                }
            }
            
            if(scene.getMenu()) {              
                if(startMousePos.x >= 550 && startMousePos.x <= 630 && startMousePos.y >= 360 && startMousePos.y <= 400) {
                    scene.setMenu(false);
                    
                    engine.addCommand(0, new LoadCommand("res/map.txt"));
                    engine.update();
                }
                
            }
            
            scene.stateChanged();
            
            scene.getDebugLayer().printPosMap();        
            
            scene.draw(window);
            window.display();
        }
    }
    
}
