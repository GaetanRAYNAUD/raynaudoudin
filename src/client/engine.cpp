#include "engine.hpp"

using namespace state;
using namespace render;

namespace engine {
    
    void engineTest() {
        Engine* engine = new Engine();
        Command* command;
        Scene* scene;
        
        int windowWidth = 1152;
        int windowHeight = 576;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        window.setFramerateLimit(30);
        
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
        
        command = new SpawnCommand(engine->getState().getBoard().findUnit(0)->getPositionX(), 
                engine->getState().getBoard().findUnit(0)->getPositionY(), UnitTypeId::SWORDMAN);
        std::cout << "Ajout d'une commande de recrutement d'une unité à partir du château en (3,1)" << std::endl;
        engine->addCommand(1, command);
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
        
        if (engine->getState().getBoard().getUnits().size() == 3) {
            std::cout << "Unité correctement ajoutée au jeu" << std::endl;
        } else {
            std::cout << "L'unité n'a pas pu être ajoutée au jeu" << std::endl;
        }
        
        std::cout << "***************************************************" << std::endl;
        
        command = new MoveCommand(1, 8, 4);
        std::cout << "Ajout d'une commande de déplacement de l'unité 1 en (8,4)" << std::endl;
        engine->addCommand(2, command);
        
        command = new MoveCommand(2, 8, 3);
        std::cout << "Ajout d'une commande de déplacement de l'unité 2 en (8,3)" << std::endl;
        engine->addCommand(3, command);
        
        std::cout << "Éxécution de la liste des commandes" << std::endl;
        engine->update();
                
        if(engine->getState().getBoard().isUnitOnPosition(8, 4)) {
            if(engine->getState().getBoard().findUnitOnPosition(8, 4)->getId() == 1) {
                std::cout << "L'unité 1 est bien en (8,4)" << std::endl;            
            } else {
                std::cout << "ERREUR : L'unité 1 n'est pas en (8,4)" << std::endl;    
            }
        } else {
            std::cout << "ERREUR : Il n'y a pas d'unité en (8,4)" << std::endl;              
        }
        
        if(engine->getState().getBoard().isUnitOnPosition(8, 3)) {
            if(engine->getState().getBoard().findUnitOnPosition(8, 3)->getId() == 2) {
                std::cout << "L'unité 2 est bien en (8,3)" << std::endl;            
            } else {
                std::cout << "ERREUR : L'unité 2 n'est pas en (8,3)" << std::endl;    
            }
        } else {
            std::cout << "ERREUR : Il n'y a pas d'unité en (8,3)" << std::endl;              
        }
        
        std::cout << "***************************************************" << std::endl;
        
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
  
        scene = new Scene(engine->getState());
                
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            scene->draw(window);
            window.display();
        }
    }
}
