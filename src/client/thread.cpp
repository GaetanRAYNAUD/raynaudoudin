#include "thread.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;
using namespace client;

namespace thread {
    
    void thread_aiTest() {
        bool pause = 0;
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        int timePause = 500;
        Engine* engine = new Engine(mapWidth, mapHeight);  
        Scene* scene;
        std::random_device rand;
        Client* client = new Client();
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::Clock clock;
        sf::Time time;
        
        window.setFramerateLimit(30);
            
        engine->addCommand(1, new LoadCommand("res/map.txt"));
        engine->update();

        scene = new Scene(engine->getState());
        while (window.isOpen()) {
            sf::Event event;
            
            if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > timePause && !pause) {
                client->run();
  
                time = clock.getElapsedTime();
                if(engine->getState().getWinner() != TeamId::INVALIDTEAM) {
                    pause = true;
                }
            }
            
            if(engine->getState().getWinner() != TeamId::INVALIDTEAM) {
                pause = true;
                std::string s = std::to_string(engine->getState().getWinner());
                std::string winnerMessage = "L equipe " + s + " a gagne !";
                scene->getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
            }
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close(); 
                } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    pause = !pause;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                    if(timePause == 500) {
                        timePause = 10;
                    } else {
                        timePause = 500;
                    }
                }
            }
            
            delete scene;
            scene = new Scene(engine->getState());
            
            scene->draw(window);
            window.display();
        }
        
        delete scene;
        delete client;
        delete engine; 
    }
}