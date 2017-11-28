#include "heuristic_ai.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace heuristic_ai {
    
    void heuristic_aiTest() {
        bool pause = 0;
        int displayMap = 0;
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        Engine* engine = new Engine(mapWidth, mapHeight);  
        Scene* scene;
        Command* command;
        std::random_device rand;
        HeuristicAI* ai = new HeuristicAI(rand());
        RandomAI* airand = new RandomAI(rand());
        sf::Vector2i startMousePos, endMousePos;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
        sf::Clock clock;
        sf::Time time;
        
        window.setFramerateLimit(30);
        window.setView(view);
            
        command = new LoadCommand("res/map.txt");
        engine->addCommand(1, command);
        engine->update();

        scene = new Scene(engine->getState());
        while (window.isOpen()) {
            sf::Event event;
            
            if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > 300 && !pause) {            
                airand->run(*engine);
                ai->initPathMaps(engine->getState().getBoard());
                time = clock.getElapsedTime();
            }
            
            delete scene;
            scene = new Scene(engine->getState());
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close(); 
                } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                    pause = !pause;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A) {
                    displayMap = 0;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Z) {
                    displayMap = 1;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::E) {
                    displayMap = 2;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
                    displayMap = 3;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::T) {
                    displayMap = 4;
                }
                
            }

            switch(displayMap) {
                case 1:
                    scene->getDebugLayer().printPathMap(ai->getUnitTeam1PathMap().getWeights());
                    break;
                case 2:
                    scene->getDebugLayer().printPathMap(ai->getUnitTeam2PathMap().getWeights());
                    break;
                case 3:
                    scene->getDebugLayer().printPathMap(ai->getHouseTeam1PathMap().getWeights());
                    break;
                case 4:
                    scene->getDebugLayer().printPathMap(ai->getHouseTeam2PathMap().getWeights());
                    break;
                default:
                    break;
            }
            scene->draw(window);
            window.display();
        }
        
        delete scene;
        delete engine;
        delete ai;
    }
}