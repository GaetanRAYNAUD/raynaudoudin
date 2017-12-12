#include "thread.hpp"
#include "engine/Engine.h"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;
using namespace client;

namespace thread {
    
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    bool loopThread = true;
    
    void thread_ai(Engine* engine) {
        HeuristicAI* ai = new HeuristicAI();
        
        do {
            std::unique_lock<std::mutex> lck(mtx);
            while (!ready) cv.wait(lck);
            ai->run(*engine);
            ready = false;
        } while (loopThread);
        
        delete ai;
    }
    
    void thread_aiTest() {
        bool pause = 0;
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        int timePause = 500;
        Engine* engine = new Engine(mapWidth, mapHeight);  
        Scene* scene = new Scene(engine->getState());
        std::random_device rand;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::Clock clock;
        sf::Time time;
        
        window.setFramerateLimit(30);
            
        engine->addCommand(1, new LoadCommand("res/map.txt"));
        engine->update();

        std::thread threadAI = std::thread(thread_ai, engine);
        while (window.isOpen()) {
            sf::Event event;
            
            if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > timePause && !pause) {
                cv.notify_one();
                ready = true;
  
                time = clock.getElapsedTime();
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
            
            mtx.lock();
            delete scene;
            scene = new Scene(engine->getState());
            
            if(engine->getState().getWinner() != TeamId::INVALIDTEAM) {
                pause = true;
                std::string s = std::to_string(engine->getState().getWinner());
                std::string winnerMessage = "L equipe " + s + " a gagne !";
                scene->getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
            }
            mtx.unlock();
            
            scene->draw(window);
            window.display();
        }
        
        cv.notify_one();
        ready = true;
        loopThread = false;
        threadAI.join();
        
        delete scene;
        delete engine; 
    }
}