#include "bfw.hpp"

using namespace state;
using namespace render;
using namespace engine;

namespace bfw {
    
    void run() {
        int windowWidth = 1188;
        int windowHeight = 576;
        int mapWidth = 22;
        int mapHeight = 8;
        Engine engine(mapWidth, mapHeight);  
        Scene scene(engine.getState());
        sf::Vector2i startMousePos, endMousePos;
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "BfW");
        sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
        
        window.setFramerateLimit(60);
        window.setView(view);
        
        scene.setMenu(true);
        
        std::vector<std::unique_ptr<sf::VertexArray>> triangles;

        std::unique_ptr<sf::VertexArray> triangle(new sf::VertexArray(sf::TrianglesStrip, 0));
        
        triangle->append(sf::Vertex(sf::Vector2f(0, 36 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(18, 0 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(18, 36 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(54, 0 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(54, 36 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(72, 36 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(54, 72 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(18, 36 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(18, 72 + 36), sf::Color::Red));
        triangle->append(sf::Vertex(sf::Vector2f(0, 36 + 36), sf::Color::Red));
        
        triangles.push_back(std::move(triangle));
        
        std::unique_ptr<sf::VertexArray> triangle2(new sf::VertexArray(sf::TrianglesStrip, 0));
        
        triangle2->append(sf::Vertex(sf::Vector2f(0 + 72 + 36, 36 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 0 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 36 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(54 + 72 + 36, 0 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(54 + 72 + 36, 36 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(72 + 72 + 36, 36 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(54 + 72 + 36, 72 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 36 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 72 + 36)));
        triangle2->append(sf::Vertex(sf::Vector2f(0 + 72 + 36, 36 + 36)));  
        
        triangles.push_back(std::move(triangle2));
        
        while (window.isOpen()) {
            sf::Event event;
            
            while (window.pollEvent(event)) {
                if(event.type == sf::Event::Closed) {
                    window.close();
                    
                } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    endMousePos = sf::Mouse::getPosition(window);
                    
                } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    startMousePos = sf::Mouse::getPosition(window);
                    
                    if(!scene.getMenu() && startMousePos.x > 18 && startMousePos.y > 36) {
                        Terrain* ter = scene.getTerrainFromPositionOnWindow(startMousePos.x, startMousePos.y);
                        std::cout << ter->getPositionX() << "," << ter->getPositionY() << std::endl;
                    }
                }
            }
            
            if(scene.getMenu()) {              
                if(startMousePos.x >= 550 && startMousePos.x <= 630 && startMousePos.y >= 360 && startMousePos.y <= 400) {
                    scene.setMenu(false);
                    
                    engine.addCommand(0, new LoadCommand("res/map.txt"));
                    engine.update();
                }
            }
            
            scene.stateChanged();
            
            scene.getDebugLayer().printPosMap();        
            
            scene.draw(window);
            for(auto& t : triangles) {
                window.draw(*(t.get()));     
            }
            window.display();
        }
    }
    
}
