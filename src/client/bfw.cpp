#include "bfw.hpp"

using namespace state;
using namespace ai;
using namespace engine;
using namespace client;

namespace bfw {
    
    void run() {
        int mapWidth = 22;
        int mapHeight = 8;
        TeamId playerTeamId = TeamId::TEAM_1;
        TeamId aiTeamId = TeamId::TEAM_2;
        Engine engine(mapWidth, mapHeight);  
        HeuristicAI ai = HeuristicAI();
        Client client(engine, playerTeamId);
        
        client.run();
        
        while(engine.getState().getWinner() == TeamId::INVALIDTEAM) {
            if(engine.getState().getCurrentTeam() == aiTeamId) {
                engine.addCommand(1, ai.run(engine, aiTeamId));
                engine.update();
                engine.addCommand(1, new HandleWinCommand());
                engine.update();
            }
            
            usleep(15000);
        }
        
//        std::vector<std::unique_ptr<sf::VertexArray>> triangles;
//
//        std::unique_ptr<sf::VertexArray> triangle(new sf::VertexArray(sf::TrianglesStrip, 0));
//        
//        triangle->append(sf::Vertex(sf::Vector2f(0, 36 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(18, 0 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(18, 36 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(54, 0 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(54, 36 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(72, 36 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(54, 72 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(18, 36 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(18, 72 + 36), sf::Color::Red));
//        triangle->append(sf::Vertex(sf::Vector2f(0, 36 + 36), sf::Color::Red));
//        
//        triangles.push_back(std::move(triangle));
//        
//        std::unique_ptr<sf::VertexArray> triangle2(new sf::VertexArray(sf::TrianglesStrip, 0));
//        
//        triangle2->append(sf::Vertex(sf::Vector2f(0 + 72 + 36, 36 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 0 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 36 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(54 + 72 + 36, 0 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(54 + 72 + 36, 36 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(72 + 72 + 36, 36 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(54 + 72 + 36, 72 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 36 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(18 + 72 + 36, 72 + 36)));
//        triangle2->append(sf::Vertex(sf::Vector2f(0 + 72 + 36, 36 + 36)));  
//        
//        triangles.push_back(std::move(triangle2));
    }
    
}
