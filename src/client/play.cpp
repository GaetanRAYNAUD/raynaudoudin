#include "play.hpp"
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
        int commandIterator = 0;
        Engine engine(mapWidth, mapHeight);  
        Scene* scene = new Scene(engine.getState());
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::Clock clock;
        sf::Time time;
        Json::Value jsonCommands;
        Json::Reader jsonReader;        
        std::ifstream fileJson("replay.txt", std::ifstream::binary);

        if (!(jsonReader.parse(fileJson, jsonCommands, false))) {
            std::cout  << jsonReader.getFormattedErrorMessages() << std::endl;
        }
        
        fileJson.close();
        
        window.setFramerateLimit(30);

        while (window.isOpen()) {
            sf::Event event;
            
            if(clock.getElapsedTime().asMilliseconds() - time.asMilliseconds() > timePause && !pause) {
                time = clock.getElapsedTime();

                if(!jsonCommands.empty() && (unsigned int)commandIterator < jsonCommands["Commands"].size()) {
                    readCommandJson(jsonCommands["Commands"][commandIterator], engine);
                    commandIterator++;
                    engine.update();
                }
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
            
            delete scene;
            scene = new Scene(engine.getState());   
            
            if(engine.getState().getWinner() != TeamId::INVALIDTEAM) {
                pause = true;
                std::string s = std::to_string(engine.getState().getWinner());
                std::string winnerMessage = "L equipe " + s + " a gagne !";
                scene->getDebugLayer().getSurface()->addText(windowWidth/2 - 50, windowHeight / 2 - 5, winnerMessage, sf::Color::Red);
            }         
            
            scene->draw(window);
            window.display();
        }
        
        delete scene;
    }
    
    void readCommandJson(Json::Value& jsonValue, engine::Engine& engine) {
        if(jsonValue.empty()) {
            std::cout << "Json vide !" << std::endl;
        } else {            
            if(jsonValue["Type"].asString() == "HandleWinCommand") {
                engine.addCommand(1, engine::HandleWinCommand::deserialize(jsonValue));
            } else if(jsonValue["Type"].asString() == "EndTurnCommand") {
                engine.addCommand(1, engine::EndTurnCommand::deserialize(jsonValue));
            } else if(jsonValue["Type"].asString() == "MoveCommand") {
                engine.addCommand(1, engine::MoveCommand::deserialize(jsonValue));
            } else if(jsonValue["Type"].asString() == "AttackCommand") {
                engine.addCommand(1, engine::AttackCommand::deserialize(jsonValue));
            } else if(jsonValue["Type"].asString() == "SpawnCommand") {
                //engine.addCommand(1, engine::SpawnCommand::deserialize(jsonValue));
            } else if(jsonValue["Type"].asString() == "LoadCommand") {
                engine.addCommand(1, engine::LoadCommand::deserialize(jsonValue));
            }
        }
    }
}