#include "engine.hpp"

using namespace state;
using namespace render;

namespace engine {
    
    void test_createBoard(Engine* engine) {
        Command* command;
                
        std::cout << "***************************************************" << std::endl;
                
        command = new LoadCommand("res/map.txt");        
        std::cout << "Ajout d'une commande de création du jeu" << std::endl;        
        engine->addCommand(1, command);
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
                
        if(engine->getState().getBoard().getUnits().size() == 2) {
            std::cout << "Jeu créé" << std::endl;
        } else {
            std::cout << "Le jeu n'a pas pu être créé" << std::endl;
        }
        
        std::cout << "***************************************************" << std::endl;
    }
    
    void test_spawnUnit(Engine* engine) {
        Command* command;
        
        command = new SpawnCommand(engine->getState().getBoard().findUnit(0)->getPositionX(), 
                engine->getState().getBoard().findUnit(0)->getPositionY(), UnitTypeId::SWORDMAN);
        std::cout << "Ajout d'une commande de recrutement d'une unité à partir du château en (" << engine->getState().getBoard().findUnit(0)->getPositionX() << "," <<  engine->getState().getBoard().findUnit(0)->getPositionY() << ")" << std::endl;
        engine->addCommand(1, command);
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
        
        if (engine->getState().getBoard().getUnits().size() == 3) {
            std::cout << "Unité correctement ajoutée au jeu" << std::endl;
        } else {
            std::cout << "L'unité n'a pas pu être ajoutée au jeu" << std::endl;
        }
        
        std::cout << "***************************************************" << std::endl;
    }
    
    void test_moveUnit1(Engine* engine) {
        Command* command;
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 2 vers le bas" << std::endl;
        command = new MoveCommand(2, state::Direction::BOT);
        engine->addCommand(1, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 2 vers le bas" << std::endl;
        command = new MoveCommand(2, state::Direction::BOT);
        engine->addCommand(2, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 2 vers le bas-droit" << std::endl;
        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
        engine->addCommand(3, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 2 vers le haut-droit" << std::endl;
        command = new MoveCommand(2, state::Direction::TOP_RIGHT);
        engine->addCommand(4, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 2 vers le bas-droit" << std::endl;
        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
        engine->addCommand(5, command);
        
        std::cout << "Ajout d'une commande de fin de tour" << std::endl;
        command = new EndTurnCommand();
        engine->addCommand(6, command);
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
        
        if(engine->getState().getBoard().isUnitOnPosition(5, 8)) {
            if(engine->getState().getBoard().findUnitOnPosition(5, 8)->getId() == 2) {
                std::cout << "L'unité 2 est bien en (5,8)" << std::endl;            
            } else {
                std::cout << "ERREUR : L'unité 2 n'est pas en (5,8)" << std::endl;    
            }
        } else {
            std::cout << "ERREUR : Il n'y a pas d'unité en (5,8)" << std::endl;              
        }
        
        std::cout << "***************************************************" << std::endl;
    }
    
    
    void test_moveUnit2(Engine* engine) {
        Command* command;
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 1 vers le haut" << std::endl;
        command = new MoveCommand(1, state::Direction::TOP);
        engine->addCommand(1, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 1 vers le haut" << std::endl;
        command = new MoveCommand(1, state::Direction::TOP);
        engine->addCommand(2, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 1 vers le haut-gauche" << std::endl;
        command = new MoveCommand(1, state::Direction::TOP_LEFT);
        engine->addCommand(3, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 1 vers le bas-gauche" << std::endl;
        command = new MoveCommand(1, state::Direction::BOT_LEFT);
        engine->addCommand(4, command);
        
        std::cout << "Ajout d'une commande de déplacement de l'unité 1 vers le bas-gauche" << std::endl;
        command = new MoveCommand(1, state::Direction::BOT_LEFT);
        engine->addCommand(5, command);
        
        std::cout << "Ajout d'une commande de fin de tour" << std::endl;
        command = new EndTurnCommand();
        engine->addCommand(6, command);
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
                
        if(engine->getState().getBoard().isUnitOnPosition(15, 10)) {
            if(engine->getState().getBoard().findUnitOnPosition(15, 10)->getId() == 1) {
                std::cout << "L'unité 1 est bien en (15,10)" << std::endl;            
            } else {
                std::cout << "ERREUR : L'unité 1 n'est pas en (15,10)" << std::endl;    
            }
        } else {
            std::cout << "ERREUR : Il n'y a pas d'unité en (15,10)" << std::endl;              
        }
        
        std::cout << "***************************************************" << std::endl;
    }
    
    void test_moveUnit3(Engine* engine) {
        Command* command;
        
        std::cout << "Déplacement des unités 1 et 2 côte à côte" << std::endl;
        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
        engine->addCommand(1, command);
        
        command = new MoveCommand(2, state::Direction::TOP_RIGHT);
        engine->addCommand(2, command);
        
        command = new EndTurnCommand();
        engine->addCommand(3, command);
        
        command = new MoveCommand(1, state::Direction::BOT_LEFT);
        engine->addCommand(4, command);

        command = new MoveCommand(1, state::Direction::TOP_LEFT);
        engine->addCommand(5, command);
        
        command = new MoveCommand(1, state::Direction::BOT_LEFT);
        engine->addCommand(6, command);

        command = new MoveCommand(1, state::Direction::TOP_LEFT);
        engine->addCommand(7, command);         
        
        command = new EndTurnCommand();
        engine->addCommand(8, command);
        
        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
        engine->addCommand(9, command);

        command = new EndTurnCommand();
        engine->addCommand(10, command);

        command = new MoveCommand(1, state::Direction::TOP_LEFT);
        engine->addCommand(11, command);
        
        command = new EndTurnCommand();
        engine->addCommand(12, command);

        command = new MoveCommand(2, state::Direction::BOT_RIGHT);
        engine->addCommand(13, command);

        command = new EndTurnCommand();
        engine->addCommand(14, command);        
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
                
        if(engine->getState().getBoard().isUnitAround(1, 2)) {
            std::cout << "Les unités 1 et 2 sont bien côte à côte." << std::endl;
        } else {
            std::cout << "ERREUR : Les unités 1 et 2 ne sont pas côte à côte." << std::endl;
        }
        
        std::cout << "***************************************************" << std::endl;
    }
    
    void test_attackUnit(Engine* engine) {
        Command* command;
        
        command = new AttackCommand(1, 2, WeaponTypeId::SWORD);
        std::cout << "Ajout d'une commande d'attaque de la case (8,3) à (8,4)" << std::endl;
        engine->addCommand(4, command);
        
        command = new AttackCommand(1, 2, WeaponTypeId::SWORD);
        std::cout << "Ajout d'une commande d'attaque de la case (8,3) à (8,4)" << std::endl;
        engine->addCommand(5, command);
        
        command = new AttackCommand(1, 2, WeaponTypeId::SWORD);
        std::cout << "Ajout d'une commande d'attaque de la case (8,3) à (8,4)" << std::endl;
        engine->addCommand(6, command);
        
        command = new AttackCommand(1, 2, WeaponTypeId::SWORD);
        std::cout << "Ajout d'une commande d'attaque de la case (8,3) à (8,4)" << std::endl;
        engine->addCommand(7, command);
        
        command = new AttackCommand(1, 2, WeaponTypeId::SWORD);
        std::cout << "Ajout d'une commande d'attaque de la case (8,3) à (8,4)" << std::endl;
        engine->addCommand(8, command);
        
        std::cout << "Éxécution de la  liste des commandes" << std::endl;
        engine->update();
        
        if (engine->getState().getBoard().getUnits().size() == 2) {
            std::cout << "Le personnage est mort après plusieurs attaques" << std::endl;
        } else {
            std::cout << "ERREUR : Le personnage n'est pas mort après plusieurs attaques" << std::endl;
        }
        
        std::cout << "***************************************************" << std::endl;        
    }
    
    void engineTest() {
        Engine* engine = new Engine();
        Scene* scene;
        int caseTest = 0;
        
        int windowWidth = 1152;
        int windowHeight = 576;
        
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        window.setFramerateLimit(30);
        
        test_createBoard(engine);
        scene = new Scene(engine->getState());
                                
        std::cout << "Appuyer sur espace pour lancer les tests" << std::endl;
        std::cout << "***************************************************" << std::endl;
        
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                        switch (caseTest) {           
                            case 0:
                                test_spawnUnit(engine);
                                scene = new Scene(engine->getState());
                                caseTest++; 
                                break;
                            case 1:
                                test_moveUnit1(engine);
                                scene = new Scene(engine->getState());
                                caseTest++; 
                                break;
                            case 2:
                                test_moveUnit2(engine);
                                scene = new Scene(engine->getState());
                                caseTest++; 
                                break;
                            case 3:
                                test_moveUnit3(engine);
                                scene = new Scene(engine->getState());
                                caseTest++; 
                                break;                                
                            case 4:
                                //test_attackUnit(engine);
                                scene = new Scene(engine->getState());
                                caseTest++;
                                break;
                            default:
                                window.close();
                        }
                        
                        std::cout << "Appuyer sur espace pour continuer" << std::endl;
                        std::cout << "***************************************************" << std::endl;                        
                    }
                    
                if (event.type == sf::Event::Closed) {
                    window.close();
                } 
            }

            scene->draw(window);
            window.display();
        }
        
        delete scene;
        delete engine;
    }
}
