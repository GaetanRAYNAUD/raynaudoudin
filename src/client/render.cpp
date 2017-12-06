#include "render.hpp"

using namespace state;

namespace render {
    
    void renderTest() {
        int windowWidth = 1260;
        int windowHeight = 648;
        int mapWidth = 44;
        int mapHeight = 16;
        int shiftWidth = 0;
        int shiftHeight = 0;
        sf::Vector2i startMousePos, endMousePos;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
        window.setFramerateLimit(30);
        window.setView(view);
            
        State* state = new State(mapWidth, mapHeight);
        state->getBoard().loadTerrainsFromFile("res/mapBig.txt");
        
        Scene* scene = new Scene(*state);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    delete scene;
                    scene = new Scene(*state);
                    endMousePos = sf::Mouse::getPosition();
                    shiftWidth = startMousePos.x - endMousePos.x;
                    shiftHeight = startMousePos.y - endMousePos.y;
                    view.move(shiftWidth, shiftHeight);
                    if (view.getCenter().x < windowWidth / 2) {
                        view.setCenter(windowWidth / 2, view.getCenter().y);
                    
                    } else if (view.getCenter().x > mapWidth * 72 * 3 / 4 - windowWidth / 2) {
                        view.setCenter(mapWidth * 72 * 3 / 4 - windowWidth / 2, view.getCenter().y);
                    }
                    
                    if (view.getCenter().y < windowHeight / 2) {
                        view.setCenter(view.getCenter().x, windowHeight / 2);
                        
                    } else if (view.getCenter().y > mapHeight * 72 - windowHeight / 2) {
                        view.setCenter(view.getCenter().x, mapHeight * 72 - windowHeight / 2);
                    }
                    
                    scene->setShiftWidth(view.getCenter().x - windowWidth / 2);
                    scene->setShiftHeight(view.getCenter().y - windowHeight / 2);
                    window.setView(view);
                    
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    startMousePos = sf::Mouse::getPosition();
                }
            }
            scene->draw(window);
            window.display();
        }
        
    delete scene;
    delete state;
    }
}
