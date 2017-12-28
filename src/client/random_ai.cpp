#include "random_ai.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace random_ai {
    
    void random_aiTest() {
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        Engine* engine = new Engine(mapWidth, mapHeight);
        std::random_device rand;
        RandomAI* ai = new RandomAI(rand());
        Scene* scene;
        Command* command;
        sf::Time timeSleep = sf::milliseconds(500);
        
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        window.setFramerateLimit(30);
                
        command = new LoadCommand("res/map.txt");
        engine->addCommand(1, command);
        engine->update();
      
        test_spawnUnit(engine);
        test_moveUnit1(engine);
        test_moveUnit2(engine);
        test_moveUnit3(engine);
        
        scene = new Scene(engine->getState());
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {            
                if (event.type == sf::Event::Closed) {
                    window.close();
                } 
            }
            
            ai->run(*engine, state::TeamId::INVALIDTEAM);
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
