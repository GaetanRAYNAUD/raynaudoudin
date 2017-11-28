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
        int timePause = 500;
        Engine* engine = new Engine(mapWidth, mapHeight);  
        Scene* scene;
        Command* command;
        std::random_device rand;
        HeuristicAI* ai = new HeuristicAI(rand());
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
            
            if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > timePause && !pause) {            
                ai->run(*engine);
                time = clock.getElapsedTime();
                if(engine->getState().getWinner() != TeamId::INVALIDTEAM) {
                    pause = true;
                }
            }
            
            delete scene;
            scene = new Scene(engine->getState());
            
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
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Y) {
                    displayMap = 5;
                } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                    if(timePause == 500) {
                        timePause = 10;
                    } else {
                        timePause = 500;
                    }
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
                case 5:
                    scene->getDebugLayer().printPathMap(ai->getCastlePathMap().getWeights());
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