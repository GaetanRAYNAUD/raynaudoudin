#include "heuristic_ai.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace heuristic_ai {
    
    void heuristic_aiTest() {
        int windowWidth = 1260;
        int windowHeight = 648;
        int mapWidth = 44;
        int mapHeight = 16;
        int shiftWidth = 0;
        int shiftHeight = 0;
        Engine* engine = new Engine(mapWidth, mapHeight);  
        Scene* scene;
        Command* command;
        std::random_device rand;
        HeuristicAI* ai = new HeuristicAI(rand());
        sf::Vector2i startMousePos, endMousePos;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
        sf::Time timeSleep = sf::milliseconds(500);
        
        window.setFramerateLimit(30);
        window.setView(view);
            
        command = new LoadCommand("res/mapBig.txt");
        engine->addCommand(1, command);
        engine->update();

        scene = new Scene(engine->getState());
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    delete scene;
                    scene = new Scene(engine->getState());
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
            
            ai->run(*engine);
            
            delete scene;
            scene = new Scene(engine->getState());
            scene->draw(window);
            window.display();
            
            sf::sleep(timeSleep);
        }
        
        delete scene;
        delete engine;
        delete ai;
    }
}