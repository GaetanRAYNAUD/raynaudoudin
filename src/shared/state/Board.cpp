#include <fstream>

#include "Board.h"

namespace state {
    
    Board::Board(int width, int height) {
        this->width = width;
        this->height = height;
    }
        
    Board::Board(const Board& other) {
        height = other.height;
        width = other.width;
        
        for(auto& t : other.teams) {
            teams.insert(std::make_pair(t.first, std::unique_ptr<Team>(t.second->clone())));
        }
        
        for(auto& t : other.terrains) {
            terrains.insert(std::make_pair(t.first, std::unique_ptr<Terrain>(t.second->clone())));
        }
        
        for(auto& u : other.units) {
            units.insert(std::make_pair(u.first, std::unique_ptr<Unit>(u.second->clone())));
        }
    }
            
    Board& Board::operator=(const Board& other) {
        teams.clear();
        terrains.clear();
        units.clear();
        
        height = other.height;
        width = other.width;
        
        for(auto& t : other.teams) {
            teams.insert(std::make_pair(t.first, std::unique_ptr<Team>(t.second->clone())));
        }
        
        for(auto& t : other.terrains) {
            terrains.insert(std::make_pair(t.first, std::unique_ptr<Terrain>(t.second->clone())));
        }
        
        for(auto& u : other.units) {
            units.insert(std::make_pair(u.first, std::unique_ptr<Unit>(u.second->clone())));
        }
        
        return *this;
    }

    void Board::addTeam(Team* team) {
        teams.insert(std::make_pair(team->getId(), std::unique_ptr<Team>(team)));
    }

    void Board::addTerrain(Terrain* terrain) {
        terrains.insert(std::make_pair(terrain->getId(), std::unique_ptr<Terrain>(terrain)));
    }

    void Board::addUnit(Unit* unit) {
        units.insert(std::make_pair(unit->getId(), std::unique_ptr<Unit> (unit)));
    }

    Team* Board::findTeam(int id) const {
        return teams.find(id)->second.get();
    }

    Terrain* Board::findTerrain(int id) const {
        return terrains.find(id)->second.get();
    }

    Terrain* Board::findTerrainOnPosition(int positionX, int positionY) const {
        for (auto& it : terrains) {
            if (it.second->getPositionX() == positionX) {
                if (it.second->getPositionY() == positionY) {
                    return it.second.get();
                }
            }
        }
        
        return NULL;
    }

    Unit* Board::findUnit(int id) const {
        return units.find(id)->second.get();
    }

    std::vector<Unit*> Board::findUnitAround(int positionX, int positionY) {
        return {};
    }

    Unit* Board::findUnitOnPosition(int positionX, int positionY) const {
        for (auto& it : units) {
            if (it.second->getPositionX() == positionX) {
                if (it.second->getPositionY() == positionY) {
                    return it.second.get();
                }
            }
        }
        
        return NULL;
    }

    int Board::getHeight() const {
        return height;
    }

    int Board::getWidth() const {
        return width;
    }

    const std::map<int, std::unique_ptr<Team> >& Board::getTeams() const {      
        return teams;
    }

    const std::map<int, std::unique_ptr<Terrain> >& Board::getTerrains() const {
        return terrains;
    }

    const std::map<int, std::unique_ptr<Unit> >& Board::getUnits() const {
        return units;
    }

    Board::~Board() {
        teams.clear();
        terrains.clear();
        units.clear();
    }

    void Board::loadTerrainsFromFile(std::string path) const {
        std::vector<int> terrainsTmp;
        std::ifstream file;
        file.open(path, std::ios::in);    
        std::string line;
            
        while(!file.eof()){
            std::getline(file, line);
                
            for(auto l : line) {
                terrainsTmp.push_back(l - '0');
            }
        }
        
        file.close();
        
        for(auto t : terrainsTmp) {
        }
    }


}