#include "heuristic_ai.hpp"

using namespace state;
using namespace render;
using namespace engine;

namespace play {
    
    void play_Test() {
        bool pause = 0;
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        int timePause = 1000;
        Engine engine(mapWidth, mapHeight);  
        Scene* scene = new Scene(engine.getState());
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::Clock clock;
        sf::Time time;
        
        window.setFramerateLimit(30);

        while (window.isOpen()) {
            sf::Event event;
            
            if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > timePause && !pause) {
                time = clock.getElapsedTime();
                
            }
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close(); 
                } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    pause = !pause;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                    if(timePause == 1000) {
                        timePause = 10;
                    } else {
                        timePause = 1000;
                    }
                }
                
            }
            
            if(engine.getState().getWinner() != TeamId::INVALIDTEAM) {
                pause = true;
                std::string s = std::to_string(engine.getState().getWinner());
                std::string winnerMessage = "L equipe " + s + " a gagne !";
                scene->getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
            }
            
            delete scene;
            scene = new Scene(engine.getState());            
            
            scene->draw(window);
            window.display();
        }
        
        delete scene;
    }
}