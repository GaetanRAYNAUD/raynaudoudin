#include "rollback.hpp"

using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

namespace rollback {
    
    void rollback_Test() {
        bool pause = 0;
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        int timePause = 1000;
        int epock = 0;
        int statesGood = 0;
        std::stack<std::stack<std::shared_ptr<Action>>> actions;
        std::stack<State*> states;
        Engine* engine = new Engine(mapWidth, mapHeight);
        Scene* scene;
        Command* command;
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
                time = clock.getElapsedTime();
                if(engine->getState().getWinner() != TeamId::INVALIDTEAM) {
                    pause = true;
                }

                switch (epock) {           
                    case 0:
                        command = new SpawnCommand(engine->getState().getBoard().findUnit(0)->getPositionX(), engine->getState().getBoard().findUnit(0)->getPositionY(), UnitTypeId::SWORDMAN);
                        engine->addCommand(1, command);
                        
                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;
                        
                    case 1:
                        command = new MoveCommand(2, state::Direction::BOT);
                        engine->addCommand(1, command);

                        command = new MoveCommand(2, state::Direction::BOT);
                        engine->addCommand(2, command);

                        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
                        engine->addCommand(3, command);

                        command = new MoveCommand(2, state::Direction::TOP_RIGHT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
                        engine->addCommand(5, command);

                        command = new EndTurnCommand();
                        engine->addCommand(6, command);

                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;
                        
                    case 2:
                        command = new SpawnCommand(engine->getState().getBoard().findUnit(1)->getPositionX(), engine->getState().getBoard().findUnit(1)->getPositionY(), UnitTypeId::SWORDMAN);
                        engine->addCommand(1, command);
                        
                        command = new SpawnCommand(engine->getState().getBoard().findUnit(1)->getPositionX(), engine->getState().getBoard().findUnit(1)->getPositionY(), UnitTypeId::SWORDMAN);
                        engine->addCommand(2, command);

                        command = new SpawnCommand(engine->getState().getBoard().findUnit(1)->getPositionX(), engine->getState().getBoard().findUnit(1)->getPositionY(), UnitTypeId::SWORDMAN);
                        engine->addCommand(3, command);
                                               
                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;
                        
                    case 3:
                        command = new MoveCommand(1, state::Direction::BOT_LEFT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(1, state::Direction::TOP_LEFT);
                        engine->addCommand(2, command);

                        command = new MoveCommand(1, state::Direction::TOP_LEFT);
                        engine->addCommand(3, command);
                        
                        command = new MoveCommand(1, state::Direction::TOP_LEFT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(1, state::Direction::TOP);
                        engine->addCommand(5, command);

                        states.push(engine->getState().clone());
                        actions.push(engine->update());
        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;
                        
                    case 4:
                        command = new MoveCommand(3, state::Direction::TOP_LEFT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(3, state::Direction::TOP_LEFT);
                        engine->addCommand(2, command);

                        command = new MoveCommand(3, state::Direction::BOT_LEFT);
                        engine->addCommand(3, command);
                        
                        command = new MoveCommand(3, state::Direction::TOP_LEFT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(3, state::Direction::TOP_LEFT);
                        engine->addCommand(5, command);

                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                    case 5:
                        command = new MoveCommand(4, state::Direction::TOP_LEFT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(4, state::Direction::TOP_LEFT);
                        engine->addCommand(2, command);

                        command = new MoveCommand(4, state::Direction::TOP_LEFT);
                        engine->addCommand(3, command);
                        
                        command = new MoveCommand(4, state::Direction::TOP_LEFT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(4, state::Direction::TOP_LEFT);
                        engine->addCommand(5, command);

                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                    case 6:
                        
                        command = new MoveCommand(5, state::Direction::TOP_LEFT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(5, state::Direction::TOP_LEFT);
                        engine->addCommand(2, command);

                        command = new MoveCommand(5, state::Direction::TOP_LEFT);
                        engine->addCommand(3, command);
                        
                        command = new MoveCommand(5, state::Direction::TOP_LEFT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(5, state::Direction::TOP_LEFT);
                        engine->addCommand(5, command);
                        
                        command = new EndTurnCommand();
                        engine->addCommand(6, command);

                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                    case 7:
                        command = new SpawnCommand(engine->getState().getBoard().findUnit(0)->getPositionX(), engine->getState().getBoard().findUnit(0)->getPositionY(), UnitTypeId::BOWMAN);
                        engine->addCommand(1, command);

                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                    case 8:
                        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
                        engine->addCommand(2, command);
                        
                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                    case 9:
                        command = new MoveCommand(0, state::Direction::BOT_RIGHT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(0, state::Direction::BOT_RIGHT);
                        engine->addCommand(2, command);
                        
                        command = new MoveCommand(0, state::Direction::BOT_RIGHT);
                        engine->addCommand(3, command);
                        
                        command = new MoveCommand(0, state::Direction::BOT_RIGHT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(0, state::Direction::BOT_RIGHT);
                        engine->addCommand(5, command);
                        
                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;
                        
                    case 10:
                        command = new MoveCommand(6, state::Direction::BOT_RIGHT);
                        engine->addCommand(1, command);
                        
                        command = new MoveCommand(6, state::Direction::BOT_RIGHT);
                        engine->addCommand(2, command);
                        
                        command = new MoveCommand(6, state::Direction::BOT_RIGHT);
                        engine->addCommand(3, command);
                        
                        command = new MoveCommand(6, state::Direction::BOT_RIGHT);
                        engine->addCommand(4, command);

                        command = new MoveCommand(6, state::Direction::BOT_RIGHT);
                        engine->addCommand(5, command);
                        
                        command = new EndTurnCommand();
                        engine->addCommand(6, command);
                        
                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                        case 11:                     
                        
                        states.push(engine->getState().clone());
                        actions.push(engine->update());
                        
                        delete scene;
                        scene = new Scene(engine->getState());
                        epock = epock + 1;
                        break;

                        
                    default:
                        if(actions.size() > 0) {
                            engine->undo(actions.top());
                            actions.pop();
                            
                            if(states.top()->equals(engine->getState()) == false) {
                                std::cout << "Etat " << states.size() << " mal restitué !" << std::endl;
                            } else {
                                statesGood = statesGood + 1;
                            }
                            
                            states.pop();
                        } else {
                            if(statesGood == epock) {
                                std::cout << "Rollback correctement effectué !" << std::endl;
                            } else {
                                std::cout << "Il y a " << epock - statesGood << " mal restitués !" << std::endl;
                            }
                            
                            window.close();
                            
                        }
                        break;
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
                    if(timePause == 1000) {
                        timePause = 10;
                    } else {
                        timePause = 1000;
                    }
                }
                
            }
            
            delete scene;
            scene = new Scene(engine->getState());
            scene->draw(window);
            window.display();
        }
        
        delete scene;
        delete engine;
    }
}

