#include "deep_ai.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace deep_ai {
    
    void deep_aiTest() {
        bool pause = false;
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        Engine engine(mapWidth, mapHeight);
        Scene scene(engine.getState());
        std::random_device rand;
        DeepAI ai(rand());
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        
        window.setFramerateLimit(60);
            
        engine.addCommand(0, new engine::LoadCommand("res/map.txt"));
        engine.update();
        
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close(); 
                } else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                    pause = !pause;
                }
            }
            
            if(!pause) {
                ai.run(engine, engine.getState().getCurrentTeam());
                
                engine.addCommand(engine.getCurrentCommands().size(), new HandleWinCommand());
                engine.update();
            }
            
            if(engine.getState().getWinner() != TeamId::INVALIDTEAM) {
                pause = true;
                scene.getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, "L equipe " + std::to_string(engine.getState().getWinner()) + " a gagne !", sf::Color::Red, 25);
            }
            
            scene.stateChanged();            
            scene.draw(window);
            window.display();
        }
    }
}